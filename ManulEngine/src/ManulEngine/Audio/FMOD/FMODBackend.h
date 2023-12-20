#include "ManulEngine/Audio/AudioBackend.h"

class FMODBackend : public AudioBackend
{
public:
	virtual bool Init() override;
	virtual void Shutdown() override;
	virtual void PlayAudioFile(std::string file, Vector3 listenerPos, Vector3 sourcePos) override;
private:
};