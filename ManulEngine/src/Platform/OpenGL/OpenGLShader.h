#pragma once

class OpenGLShader
{
public:
	int Compile(const char* vertexShaderSource, const char* fragmentShaderSource);

	uint32_t shaderProgram;

	uint32_t vertexShader;
	uint32_t fragmentShader;
private:

};