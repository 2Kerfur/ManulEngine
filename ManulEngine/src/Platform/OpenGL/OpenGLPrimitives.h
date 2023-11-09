#pragma once
#include "OpenGLShader.h"
#include "OpenGLTexture.h"

#include "ManulEngine/Core/Math/Math.h"
#include <cstdint>
#include <glm/ext/matrix_float4x4.hpp>
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
	OpenGLShader shader;
    OpenGLTexture texture;
};
struct Line {
    int shaderProgram;
    unsigned int VBO, VAO;
    std::vector<float> vertices;
    glm::vec3 startPoint;
    glm::vec3 endPoint;
    glm::mat4 MVP;
    glm::vec3 lineColor;
};
class OpenGLLine
{
public:
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "uniform mat4 MVP;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec3 color;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(color, 1.0f);\n"
        "}\n\0";
	void Create(Vector3 pos, Vector2 size);
	void Bind(uint32_t ebo, uint32_t vao, uint32_t vbo);
	void Draw();
    Line line;
    uint32_t EBO, VAO, VBO;
private:
	OpenGLShader shader;	
};