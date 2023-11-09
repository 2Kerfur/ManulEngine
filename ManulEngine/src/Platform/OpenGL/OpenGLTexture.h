#pragma once
#include <string>

class OpenGLTexture
{
public:
	bool Create(std::string path);
	void Bind();

public:
	int32_t width, height, nrChannels;
	unsigned char* imageData;
	uint32_t ID;
private:

};