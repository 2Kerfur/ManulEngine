#pragma once

#include "ManulEngine/Audio/AudioBackend.h"

class OpenALBackend : public AudioBackend
{
public:
	virtual bool Init() override;
	virtual void Shutdown() override;
	virtual void PlayAudioFile(std::string file, Vector3 listenerPos, Vector3 sourcePos) override;
private:
	//bool CheckAlErrors(const std::string& filename, const std::uint_fast32_t line);
};