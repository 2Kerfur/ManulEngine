
#include "config.h"

#include "bformatdec.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <utility>

#include "almalloc.h"
#include "alnumbers.h"
#include "filters/splitter.h"
#include "front_stablizer.h"
#include "mixer.h"
#include "opthelpers.h"


namespace {

template<typename... Ts>
struct overloaded : Ts... { using Ts::operator()...; };

template<typename... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

} // namespace

BFormatDec::BFormatDec(const size_t inchans, const al::span<const ChannelDec> coeffs,
    const al::span<const ChannelDec> coeffslf, const float xover_f0norm,
    std::unique_ptr<FrontStablizer> stablizer)
    : mStablizer{std::move(stablizer)}
{
    if(coeffslf.empty())
    {
        auto &decoder = mChannelDec.emplace<std::vector<ChannelDecoderSingle>>(inchans);
        for(size_t j{0};j < decoder.size();++j)
        {
            float *outcoeffs{decoder[j].mGains.data()};
            for(const ChannelDec &incoeffs : coeffs)
                *(outcoeffs++) = incoeffs[j];
        }
    }
    else
    {
        auto &decoder = mChannelDec.emplace<std::vector<ChannelDecoderDual>>(inchans);
        decoder[0].mXOver.init(xover_f0norm);
        for(size_t j{1};j < decoder.size();++j)
            decoder[j].mXOver = decoder[0].mXOver;

        for(size_t j{0};j < decoder.size();++j)
        {
            float *outcoeffs{decoder[j].mGains[sHFBand].data()};
            for(const ChannelDec &incoeffs : coeffs)
                *(outcoeffs++) = incoeffs[j];

            outcoeffs = decoder[j].mGains[sLFBand].data();
            for(const ChannelDec &incoeffs : coeffslf)
                *(outcoeffs++) = incoeffs[j];
        }
    }
}


void BFormatDec::process(const al::span<FloatBufferLine> OutBuffer,
    const FloatBufferLine *InSamples, const size_t SamplesToDo)
{
    ASSUME(SamplesToDo > 0);

    auto decode_dualband = [=](std::vector<ChannelDecoderDual> &decoder)
    {
        auto *input = InSamples;
        const al::span<float> hfSamples{mSamples[sHFBand].data(), SamplesToDo};
        const al::span<float> lfSamples{mSamples[sLFBand].data(), SamplesToDo};
        for(auto &chandec : decoder)
        {
            chandec.mXOver.process({input->data(), SamplesToDo}, hfSamples.data(),
                lfSamples.data());
            MixSamples(hfSamples, OutBuffer, chandec.mGains[sHFBand].data(),
                chandec.mGains[sHFBand].data(), 0, 0);
            MixSamples(lfSamples, OutBuffer, chandec.mGains[sLFBand].data(),
                chandec.mGains[sLFBand].data(), 0, 0);
            ++input;
        }
    };
    auto decode_singleband = [=](std::vector<ChannelDecoderSingle> &decoder)
    {
        auto *input = InSamples;
        for(auto &chandec : decoder)
        {
            MixSamples({input->data(), SamplesToDo}, OutBuffer, chandec.mGains.data(),
                chandec.mGains.data(), 0, 0);
            ++input;
        }
    };

    std::visit(overloaded{decode_dualband, decode_singleband}, mChannelDec);
}

void BFormatDec::processStablize(const al::span<FloatBufferLine> OutBuffer,
    const FloatBufferLine *InSamples, const size_t lidx, const size_t ridx, const size_t cidx,
    const size_t SamplesToDo)
{
    ASSUME(SamplesToDo > 0);

    /* Move the existing direct L/R signal out so it doesn't get processed by
     * the stablizer.
     */
    float *RESTRICT mid{al::assume_aligned<16>(mStablizer->MidDirect.data())};
    float *RESTRICT side{al::assume_aligned<16>(mStablizer->Side.data())};
    for(size_t i{0};i < SamplesToDo;++i)
    {
        mid[i] = OutBuffer[lidx][i] + OutBuffer[ridx][i];
        side[i] = OutBuffer[lidx][i] - OutBuffer[ridx][i];
    }
    std::fill_n(OutBuffer[lidx].begin(), SamplesToDo, 0.0f);
    std::fill_n(OutBuffer[ridx].begin(), SamplesToDo, 0.0f);

    /* Decode the B-Format input to OutBuffer. */
    process(OutBuffer, InSamples, SamplesToDo);

    /* Include the decoded side signal with the direct side signal. */
    for(size_t i{0};i < SamplesToDo;++i)
        side[i] += OutBuffer[lidx][i] - OutBuffer[ridx][i];

    /* Get the decoded mid signal and band-split it. */
    std::transform(OutBuffer[lidx].cbegin(), OutBuffer[lidx].cbegin()+SamplesToDo,
        OutBuffer[ridx].cbegin(), mStablizer->Temp.begin(),
        [](const float l, const float r) noexcept { return l + r; });

    mStablizer->MidFilter.process({mStablizer->Temp.data(), SamplesToDo}, mStablizer->MidHF.data(),
        mStablizer->MidLF.data());

    /* Apply an all-pass to all channels to match the band-splitter's phase
     * shift. This is to keep the phase synchronized between the existing
     * signal and the split mid signal.
     */
    const size_t NumChannels{OutBuffer.size()};
    for(size_t i{0u};i < NumChannels;i++)
    {
        /* Skip the left and right channels, which are going to get overwritten,
         * and substitute the direct mid signal and direct+decoded side signal.
         */
        if(i == lidx)
            mStablizer->ChannelFilters[i].processAllPass({mid, SamplesToDo});
        else if(i == ridx)
            mStablizer->ChannelFilters[i].processAllPass({side, SamplesToDo});
        else
            mStablizer->ChannelFilters[i].processAllPass({OutBuffer[i].data(), SamplesToDo});
    }

    /* This pans the separate low- and high-frequency signals between being on
     * the center channel and the left+right channels. The low-frequency signal
     * is panned 1/3rd toward center and the high-frequency signal is panned
     * 1/4th toward center. These values can be tweaked.
     */
    const float cos_lf{std::cos(1.0f/3.0f * (al::numbers::pi_v<float>*0.5f))};
    const float cos_hf{std::cos(1.0f/4.0f * (al::numbers::pi_v<float>*0.5f))};
    const float sin_lf{std::sin(1.0f/3.0f * (al::numbers::pi_v<float>*0.5f))};
    const float sin_hf{std::sin(1.0f/4.0f * (al::numbers::pi_v<float>*0.5f))};
    for(size_t i{0};i < SamplesToDo;i++)
    {
        /* Add the direct mid signal to the processed mid signal so it can be
         * properly combined with the direct+decoded side signal.
         */
        const float m{mStablizer->MidLF[i]*cos_lf + mStablizer->MidHF[i]*cos_hf + mid[i]};
        const float c{mStablizer->MidLF[i]*sin_lf + mStablizer->MidHF[i]*sin_hf};
        const float s{side[i]};

        /* The generated center channel signal adds to the existing signal,
         * while the modified left and right channels replace.
         */
        OutBuffer[lidx][i] = (m + s) * 0.5f;
        OutBuffer[ridx][i] = (m - s) * 0.5f;
        OutBuffer[cidx][i] += c * 0.5f;
    }
}


std::unique_ptr<BFormatDec> BFormatDec::Create(const size_t inchans,
    const al::span<const ChannelDec> coeffs, const al::span<const ChannelDec> coeffslf,
    const float xover_f0norm, std::unique_ptr<FrontStablizer> stablizer)
{
    return std::make_unique<BFormatDec>(inchans, coeffs, coeffslf, xover_f0norm,
        std::move(stablizer));
}
