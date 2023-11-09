#pragma once
#include <cstdint>
class OpenGLShader
{
public:
	int Compile(const char* vertexShaderSource, const char* fragmentShaderSource);
	void Use();

public:
	uint32_t shaderProgram;
	uint32_t vertexShader;
	uint32_t fragmentShader;

private:

};