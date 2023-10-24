#pragma once
#include "OpenGLShader.h"
#include "ManulEngine/Core/Math/Math.h"
class OpenGLBox
{
public:
	void Create(Vector3 pos, Vector2 size);
    void Bind(uint32_t ebo, uint32_t vao);
	void Draw();
private:  
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";
    uint32_t EBO, VAO;
	OpenGLShader shader;
};

class OpenGLLine
{
public:
	void Create(Vector3 pos, Vector2 size);
	void Bind();
	void Draw();
private:
	OpenGLShader shader;	
};