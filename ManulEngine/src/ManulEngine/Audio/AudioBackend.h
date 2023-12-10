#pragma once
#include "ManulEngine/Core/Math/Math.h"
class AudioBackend
{
public:
	virtual ~AudioBackend() {};
	virtual bool Init() { return false; };
	virtual void Shutdown() {};
	virtual void PlayAudioFile(std::string file, Vector3 listenerPos, Vector3 sourcePos) {}; //TODO: Add more args
};