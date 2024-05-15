#include "glad/glad.h"
#include "OpenGLScreenShot.h"

void OpenGLScreenShot::TakeScreenShot(int width, int height)
{
	if (sceenMade) return;
	sceenMade = true;
	BYTE* pixels = new BYTE[3 * width * height];

	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	// Convert to FreeImage format & save to file
	FIBITMAP* image = FreeImage_ConvertFromRawBits(pixels, width, height, 3 * width, 24, 0x0000FF, 0xFF0000, 0x00FF00, false);
	FreeImage_Save(FIF_BMP, image, "C:/DEV/C++/ManulEngine/out/build/x64-Release/sceenshots/sceenshot.bmp", 0);
	if (!image) M_CORE_ERROR("No image taken");
	else M_CORE_INFO("Sceenshot taken");
	
	// Free resources
	FreeImage_Unload(image);
	delete[] pixels;
}
