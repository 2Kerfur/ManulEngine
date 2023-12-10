#include "mapch.h"
#define AL_LIBTYPE_STATIC
#include "AL/al.h"
#include "AL/alc.h"

std::int32_t convert_to_int(char* buffer, std::size_t len)
{
    std::int32_t a = 0;

    if (std::endian::native == std::endian::little)
        std::memcpy(&a, buffer, len);
    else
        for (std::size_t i = 0; i < len; ++i)
            reinterpret_cast<char*>(&a)[3 - i] = buffer[i];
    return a;
}
bool CheckAlErrors(const std::string& filename, const std::uint_fast32_t line, ALCdevice* device)
{
    ALenum error = alGetError();
    if (error != AL_NO_ERROR)
    {
        std::cerr << "***ERROR*** (" << filename << ": " << line << ")\n";
        switch (error)
        {
        case AL_INVALID_NAME:
            M_CORE_ERROR("AL_INVALID_NAME: a bad name (ID) was passed to an OpenAL function");
            break;
        case AL_INVALID_ENUM:
            M_CORE_ERROR("AL_INVALID_ENUM: an invalid enum value was passed to an OpenAL function");
            break;
        case AL_INVALID_VALUE:
            M_CORE_ERROR("AL_INVALID_VALUE: an invalid value was passed to an OpenAL function");
            break;
        case AL_INVALID_OPERATION:
            M_CORE_ERROR("AL_INVALID_OPERATION: the requested operation is not valid");
            break;
        case AL_OUT_OF_MEMORY:
            M_CORE_ERROR("AL_OUT_OF_MEMORY: the requested operation resulted in OpenAL running out of memory");
            break;
        default:
            M_CORE_ERROR("UNKNOWN AL ERROR:" + error);
        }
        return false;
    }
    return true;
}


template<typename alcFunction, typename... Params>
auto alcCallImpl(const char* filename,
    const std::uint_fast32_t line,
    alcFunction function,
    ALCdevice* device,
    Params... params)
    -> typename std::enable_if_t<std::is_same_v<void, decltype(function(params...))>, bool>
{
    function(std::forward<Params>(params)...);
    return CheckAlErrors(filename, line, device);
}

template<typename alcFunction, typename ReturnType, typename... Params>
auto alcCallImpl(const char* filename,
    const std::uint_fast32_t line,
    alcFunction function,
    ReturnType& returnValue,
    ALCdevice* device,
    Params... params)
    -> typename std::enable_if_t<!std::is_same_v<void, decltype(function(params...))>, bool>
{
    returnValue = function(std::forward<Params>(params)...);
    return CheckAlErrors(filename, line, device);
}

#define alCall(function, ...) alCallImpl(__FILE__, __LINE__, function, __VA_ARGS__)
#define alcCall(function, device, ...) alcCallImpl(__FILE__, __LINE__, function, device, __VA_ARGS__)

#include "OpenALBackend.h"
#include <bit>
ALCdevice* openALDevice;
ALCcontext* openALContext;
bool get_available_devices(std::vector<std::string>& devicesVec, ALCdevice* device)
{
    const ALCchar* devices;
    if (!alcCall(alcGetString, devices, device, nullptr, ALC_DEVICE_SPECIFIER))
        return false;

    const char* ptr = devices;

    devicesVec.clear();

    do
    {
        devicesVec.push_back(std::string(ptr));
        ptr += devicesVec.back().size() + 1;
    } while (*(ptr + 1) != '\0');

    return true;
}
bool load_wav_file_header(std::ifstream& file,
    std::uint8_t& channels,
    std::int32_t& sampleRate,
    std::uint8_t& bitsPerSample,
    ALsizei& size)
{
    char buffer[4];
    if (!file.is_open())
        return false;

    // the RIFF
    if (!file.read(buffer, 4))
    {
        std::cerr << "ERROR: could not read RIFF" << std::endl;
        return false;
    }
    if (std::strncmp(buffer, "RIFF", 4) != 0)
    {
        std::cerr << "ERROR: file is not a valid WAVE file (header doesn't begin with RIFF)" << std::endl;
        return false;
    }

    // the size of the file
    if (!file.read(buffer, 4))
    {
        std::cerr << "ERROR: could not read size of file" << std::endl;
        return false;
    }

    // the WAVE
    if (!file.read(buffer, 4))
    {
        std::cerr << "ERROR: could not read WAVE" << std::endl;
        return false;
    }
    if (std::strncmp(buffer, "WAVE", 4) != 0)
    {
        std::cerr << "ERROR: file is not a valid WAVE file (header doesn't contain WAVE)" << std::endl;
        return false;
    }

    // "fmt/0"
    if (!file.read(buffer, 4))
    {
        std::cerr << "ERROR: could not read fmt/0" << std::endl;
        return false;
    }

    // this is always 16, the size of the fmt data chunk
    if (!file.read(buffer, 4))
    {
        std::cerr << "ERROR: could not read the 16" << std::endl;
        return false;
    }

    // PCM should be 1?
    if (!file.read(buffer, 2))
    {
        std::cerr << "ERROR: could not read PCM" << std::endl;
        return false;
    }

    // the number of channels
    if (!file.read(buffer, 2))
    {
        std::cerr << "ERROR: could not read number of channels" << std::endl;
        return false;
    }
    channels = convert_to_int(buffer, 2);

    // sample rate
    if (!file.read(buffer, 4))
    {
        std::cerr << "ERROR: could not read sample rate" << std::endl;
        return false;
    }
    sampleRate = convert_to_int(buffer, 4);

    // (sampleRate * bitsPerSample * channels) / 8
    if (!file.read(buffer, 4))
    {
        std::cerr << "ERROR: could not read (sampleRate * bitsPerSample * channels) / 8" << std::endl;
        return false;
    }

    // ?? dafaq
    if (!file.read(buffer, 2))
    {
        std::cerr << "ERROR: could not read dafaq" << std::endl;
        return false;
    }

    // bitsPerSample
    if (!file.read(buffer, 2))
    {
        std::cerr << "ERROR: could not read bits per sample" << std::endl;
        return false;
    }
    bitsPerSample = convert_to_int(buffer, 2);

    // data chunk header "data"
    if (!file.read(buffer, 4))
    {
        std::cerr << "ERROR: could not read data chunk header" << std::endl;
        return false;
    }
    if (std::strncmp(buffer, "data", 4) != 0)
    {
        std::cerr << "ERROR: file is not a valid WAVE file (doesn't have 'data' tag)" << std::endl;
        return false;
    }

    // size of data
    if (!file.read(buffer, 4))
    {
        std::cerr << "ERROR: could not read data size" << std::endl;
        return false;
    }
    size = convert_to_int(buffer, 4);

    /* cannot be at the end of file */
    if (file.eof())
    {
        std::cerr << "ERROR: reached EOF on the file" << std::endl;
        return false;
    }
    if (file.fail())
    {
        std::cerr << "ERROR: fail state set on the file" << std::endl;
        return false;
    }

    return true;
}

char* load_wav(const std::string& filename,
    std::uint8_t& channels,
    std::int32_t& sampleRate,
    std::uint8_t& bitsPerSample,
    ALsizei& size)
{
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open())
    {
        std::cerr << "ERROR: Could not open \"" << filename << "\"" << std::endl;
        return nullptr;
    }
    if (!load_wav_file_header(in, channels, sampleRate, bitsPerSample, size))
    {
        std::cerr << "ERROR: Could not load wav header of \"" << filename << "\"" << std::endl;
        return nullptr;
    }

    char* data = new char[size];

    in.read(data, size);

    return data;
}
void OpenALBackend::Shutdown()
{
    ALCboolean closed;
    alcCall(alcCloseDevice, closed, openALDevice, openALDevice);    
}
bool OpenALBackend::Init()
{
    std::cout << "starting...\n";
    return true;
}

void OpenALBackend::PlayAudioFile(std::string file, Vector3 listenerPos, Vector3 sourcePos)
{
    M_CORE_INFO("Audio play");

    ALCdevice* openALDevice = alcOpenDevice(nullptr);
    if (!openALDevice)
        M_CORE_ERROR("Failed to open device");

    ALCcontext* openALContext = alcCreateContext(openALDevice, (ALCint*)nullptr);
    ALCboolean contextMadeCurrent = false;
    alcMakeContextCurrent(openALContext);


    std::uint8_t channels;
    std::int32_t sampleRate;
    std::uint8_t bitsPerSample;
    std::vector<char> soundData;
    //ALsizei& size;

    //if (!load_wav("sound.wav",
    //    channels,
    //    sampleRate,
    //    bitsPerSample,
    //    soundData)) {
    //    M_CORE_ERROR("ERROR: Could not load wav");
    //    
    //}

    alGetError(); // clear error code 
    ALuint buffer;
    alGenBuffers(1, &buffer);
    if (alGetError() != AL_NO_ERROR) {
        std::cout << "ERRRR\n";
    }

    ALenum format;
    if (channels == 1 && bitsPerSample == 8)
        format = AL_FORMAT_MONO8;
    else if (channels == 1 && bitsPerSample == 16)
        format = AL_FORMAT_MONO16;
    else if (channels == 2 && bitsPerSample == 8)
        format = AL_FORMAT_STEREO8;
    else if (channels == 2 && bitsPerSample == 16)
        format = AL_FORMAT_STEREO16;
    else {
        std::cerr << "ERROR: unrecognised wave format: " << channels << " channels, " << bitsPerSample << " bps"
            << std::endl;
    }

    alGetError(); // clear error code 
    alBufferData(buffer, format, soundData.data(), soundData.size(), sampleRate);
    //soundData.clear(); // erase the sound in RAM
    if (alGetError() != AL_NO_ERROR) {
        std::cout << "ERRRR\n";
    }

    ALuint source;
    alGenSources(1, &source);
    alSourcef(source, AL_PITCH, 1);
    alSourcef(source, AL_GAIN, 1.0f);
    alSource3f(source, AL_POSITION, 0, 0, 0);
    alSource3f(source, AL_VELOCITY, 0, 0, 0);
    alSourcei(source, AL_LOOPING, AL_FALSE);
    alSourcei(source, AL_BUFFER, buffer);
    ALfloat maxGain = 1.0f;
    alSourcef(source, AL_GAIN, maxGain);
    alSourcePlay(source);

    ALint state = AL_PLAYING;

    while (state == AL_PLAYING && alGetError() == AL_NO_ERROR) {
        alGetSourcei(source, AL_SOURCE_STATE, &state);
    }

    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);

    alcCloseDevice(openALDevice);
}