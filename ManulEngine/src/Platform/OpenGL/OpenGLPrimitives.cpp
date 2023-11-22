#include "mapch.h"
#include "OpenGLPrimitives.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glad/glad.h"
#include "ManulEngine/ResourceManager/ResourceManager.h"
void OpenGLBox::Create(Vector3 pos, Vector2 size)
{
	shader.Compile(vertexShaderSource, fragmentShaderSource);
    texture.Create("path");
}
float vertices[] = {
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
};
unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
};
void OpenGLBox::Bind(uint32_t ebo, uint32_t vao, uint32_t vbo)
{
    EBO = ebo;
    VAO = vao;
    VBO = vbo;

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    texture.Bind();
}

void OpenGLBox::Draw()
{
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
        
    shader.Use();
    glm::mat4 projection = glm::perspective(glm::radians(fov), (float)800 / (float)600, 0.1f, 100.0f);
    shader.setMat4("projection", projection);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void OpenGLLine::Create(Vector3 pos, Vector2 size)
{
    shader.Compile(vertexShaderSource, fragmentShaderSource);
}

void OpenGLLine::Bind(uint32_t ebo, uint32_t vao, uint32_t vbo)
{
    EBO = ebo;
    VAO = vao;
    VBO = vbo;
    line.startPoint = glm::vec3(0, 0, 0);
    line.endPoint = glm::vec3(-1, 1, 1);
    line.lineColor = glm::vec3(1, 1, 1);
    line.MVP = glm::mat4(1.0f);
    line.vertices = {
             line.startPoint.x, line.startPoint.y, line.startPoint.z,
             line.endPoint.x, line.endPoint.y, line.endPoint.z,
    };

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), line.vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
}

void OpenGLLine::Draw()
{
    shader.Use();
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "MVP"), 1, GL_FALSE, &line.MVP[0][0]);
    glUniform3fv(glGetUniformLocation(shader.shaderProgram, "color"), 1, &line.lineColor[0]);

    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);
}
