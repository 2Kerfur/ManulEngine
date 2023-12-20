#include "mapch.h"
#include "FMODBackend.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
bool FMODBackend::Init()
{
	return true;
}

void FMODBackend::Shutdown()
{
}

void FMODBackend::PlayAudioFile(std::string file, Vector3 listenerPos, Vector3 sourcePos)
{
	M_CORE_INFO("Played sound");
}
