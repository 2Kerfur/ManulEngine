#pragma once
#include "OpenGLShader.h"
#include "ManulEngine/Core/Math/Math.h"
#include <cstdint>
class OpenGLBox
{
public:
	void Create(Vector3 pos, Vector2 size);
    void Bind(uint32_t ebo, uint32_t vao, uint32_t vbo);
	void Draw(); 
    const char* vertexShaderSource = "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "layout(location = 1) in vec3 aColor;\n"
        "layout(location = 2) in vec2 aTexCoord;\n"
        "out vec3 ourColor;\n"
        "out vec2 TexCoord;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "   ourColor = aColor;\n"
        "   TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
        "}\0";

    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 ourColor;\n"
        "in vec2 TexCoord;\n"
        "uniform sampler2D m_Texture;\n"
        "void main()\n"
        "{\n"
        "   FragColor = texture(m_Texture, TexCoord);\n"
        "}\n\0";
    uint32_t EBO, VAO, VBO;
    uint32_t texture;
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