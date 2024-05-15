#pragma once

#include "FreeImage.h"
class OpenGLScreenShot
{
public:
	bool sceenMade = false;
	void TakeScreenShot(int width, int height);
};