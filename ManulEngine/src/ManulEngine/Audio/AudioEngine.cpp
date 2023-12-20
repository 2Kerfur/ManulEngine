#include "mapch.h"
#include "AudioEngine.h"
#include "OpenAL/OpenALBackend.h"
#include "FMOD/FMODBackend.h"

bool AudioEngine::Init(AudioBackendAPI api)
{
	switch (api) {
	case AudioBackendAPI::OpenAL:
		//audioBackend = dynamic_cast<AudioBackend*>(new OpenALBackend());
		//if (!audioBackend->Init())
		//{
		//	M_CORE_ERROR("Audio Engine failed to initialize (Backend = OpenAL)");
		//	return false;
		//}
		M_CORE_ERROR("Audio Engine failed to initialize OpenAL not supported");
		return false;
	case AudioBackendAPI::FMOD:
		audioBackend = dynamic_cast<AudioBackend*>(new FMODBackend());
		if (!audioBackend->Init())
		{
			M_CORE_ERROR("Audio Engine failed to initialize (Backend = FMOD)");
			return false;
		}
		return true;
	default:
		M_CORE_ERROR("Audio Engine failed to initialize (Backend not supported)");
	}
	return false;
}

void AudioEngine::PlayAudioFile(std::string file, Vector3 position)
{
	audioBackend->PlayAudioFile(file, listnerPos, position);
}
