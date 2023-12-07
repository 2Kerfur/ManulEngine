#include "mapch.h"
#include "OpenGLShader.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
int OpenGLShader::Compile(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        M_CORE_ERROR("Shader compilation failed");
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        M_CORE_ERROR(infoLog);
        return false;
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        M_CORE_ERROR("Shader compilation failed");
        M_CORE_ERROR(infoLog);
        return false;
    }
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        M_CORE_ERROR("Shader compilation failed");
        M_CORE_ERROR(infoLog);
        return false;
    }   

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return true;
}

void OpenGLShader::Use()
{
    glUseProgram(shaderProgram);
}

void OpenGLShader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
}
void OpenGLShader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}
void OpenGLShader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}
void OpenGLShader::setVec2(const std::string& name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
}
void OpenGLShader::setVec2(const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), x, y);
}
void OpenGLShader::setVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
}
void OpenGLShader::setVec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z);
}
void OpenGLShader::setVec4(const std::string& name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
}
void OpenGLShader::setVec4(const std::string& name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z, w);
}
void OpenGLShader::setMat2(const std::string& name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void OpenGLShader::setMat3(const std::string& name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void OpenGLShader::setMat4(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}