#include "mapch.h"
#include "AudioEngine.h"
#include "OpenAL/OpenALBackend.h"

bool AudioEngine::Init(AudioBackendAPI api)
{
	switch (api) {
	case AudioBackendAPI::OpenAL:
		audioBackend = dynamic_cast<AudioBackend*>(new OpenALBackend());
		if (!audioBackend->Init())
		{
			M_CORE_ERROR("Audio Engine failed to initialize (Backend = OpenAL)");
			return false;
		}
		return true;
	case AudioBackendAPI::FMOD:
		M_CORE_ERROR("Audio Engine failed to initialize (Backend not supported)");
	default:
		M_CORE_ERROR("Audio Engine failed to initialize (Backend not supported)");
	}
	return false;
}

void AudioEngine::PlayAudioFile(std::string file, Vector3 position)
{
	audioBackend->PlayAudioFile(file, listnerPos, position);
}
