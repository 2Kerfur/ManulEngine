#include "OpenGLPrimitives.h"
#include "glad/glad.h"
void OpenGLBox::Create(Vector3 pos, Vector2 size)
{
	shader.Compile(vertexShaderSource, fragmentShaderSource);

}

void OpenGLBox::Bind(uint32_t ebo, uint32_t vao)
{
    EBO = ebo;
    VAO = vao;
    float vertices[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void OpenGLBox::Draw()
{
    glUseProgram(shader.shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void OpenGLLine::Create(Vector3 pos, Vector2 size)
{

}

void OpenGLLine::Draw()
{
	
}
