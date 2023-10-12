#pragma once
#include "OpenGLShader.h"

class OpenGLBox
{
public:
	void Create(Vector3 pos, Vector2 size);
	void Draw();
private:
	OpenGLShader shader;
};

class OpenGLLine
{
public:
	void Create(Vector3 pos, Vector2 size);
	void Draw();
private:
	OpenGLShader shader;	
};