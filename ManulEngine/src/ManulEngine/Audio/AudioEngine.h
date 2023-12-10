#pragma once
#include "ManulEngine/Core/Math/Math.h"
#include "AudioBackend.h"

enum AudioBackendAPI
{
	OpenAL,
	FMOD
};

class AudioEngine {
public:
	bool Init(AudioBackendAPI api);
	void PlayAudioFile(std::string file, Vector3 position);
private:
	Vector3 listnerPos = { 0, 0, 0 };
	AudioBackend *audioBackend;
};


