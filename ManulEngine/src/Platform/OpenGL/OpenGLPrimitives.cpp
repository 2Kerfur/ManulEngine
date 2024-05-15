#include "mapch.h"
#include "OpenGLPrimitives.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ManulEngine/ResourceManager/ResourceManager.h"

#include "ManulEngine/Core/Window.h"

#include "ManulEngine/Core/Input.h"

GLFWwindow* window;
void OpenGLBox::Create(Vector3 pos, Vector2 size) //TODO: Change box to quad
{
    texture.Create("path");
	shader.Compile(vertexShaderSource, fragmentShaderSource);
    Camera cameraObj(glm::vec3(0.0f, 0.0f, 3.0f));
    camera = &cameraObj;
    window = &ManulEngine::Window::GetInstatnce();
}
float vertices[] = {
    //pos                //texture pos
     0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 
    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f  
};


void OpenGLBox::Bind(uint32_t ebo, uint32_t vao, uint32_t vbo)
{
    EBO = ebo;
    VAO = vao;
    VBO = vbo;

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    texture.Bind();
}
float deltaTime = 0;
float lastFrame = 0.0f;


void OpenGLBox::Draw()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT, deltaTime);



    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
        
    shader.Use();
    glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)800 / (float)600, 0.1f, 100.0f);
    shader.setMat4("projection", projection);

    glm::mat4 view = camera->GetViewMatrix();
    shader.setMat4("view", view);

    glBindVertexArray(VAO);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    float angle = 0.0f;
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    shader.setMat4("model", model);

    glDrawArrays(GL_TRIANGLES, 0, 4);
    //glDrawElements(GL_TRIANGLES, 2, GL_UNSIGNED_INT, 0);
}

void OpenGLLine::Create(Vector3 pos, Vector2 size)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    shader.Compile(vertexShaderSource, fragmentShaderSource);
}

void OpenGLLine::Bind(uint32_t ebo, uint32_t vao, uint32_t vbo)
{
   
    EBO = ebo;
    line.startPoint = glm::vec3(0, 0, 0);
    line.endPoint = glm::vec3(1, 0.5, 1);
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
    glBindVertexArray(0);
}

void OpenGLLine::Draw()
{
    shader.Use();
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "MVP"), 1, GL_FALSE, &line.MVP[0][0]);
    glUniform3fv(glGetUniformLocation(shader.shaderProgram, "color"), 1, &line.lineColor[0]);

    glLineWidth(30.0f);
    glBindVertexArray(VAO);
    
    glDrawArrays(GL_LINES, 0, 2);
}

float cube_vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
glm::vec3 cubePosition = glm::vec3(0.0f,  0.0f,  0.0f);

glm::mat4 OpenGLModel::getProjection()
{
    return projection;
}
glm::mat4 OpenGLModel::getView()
{
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}
glm::vec3 OpenGLModel::getCameraPos()
{
    return cameraPos;
}
void OpenGLModel::Create()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    shader.Compile(vertexShaderSource, fragmentShaderSource);
    
    texture.Create("image.jpg");

    shader.Use();
    shader.setInt("texture1", 0);


}

void OpenGLModel::Bind(uint32_t ebo, uint32_t vao, uint32_t vbo)
{
}

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

void OpenGLModel::Draw()
{
    glActiveTexture(GL_TEXTURE0);
    if (ManulEngine::Input::IsKeyPressed(ManulEngine::Key::A))
        cameraPos.x -= 0.01f;
    if (ManulEngine::Input::IsKeyPressed(ManulEngine::Key::W))
        cameraPos.y += 0.01f;
    if (ManulEngine::Input::IsKeyPressed(ManulEngine::Key::S))
        cameraPos.y -= 0.01f;
    if (ManulEngine::Input::IsKeyPressed(ManulEngine::Key::D))
        cameraPos.x += 0.01f;

    if (ManulEngine::Input::IsKeyPressed(ManulEngine::Key::I))
        MouseY -= 0.05f;
    if (ManulEngine::Input::IsKeyPressed(ManulEngine::Key::K))
        MouseY += 0.05f;

    if (ManulEngine::Input::IsKeyPressed(ManulEngine::Key::L))
        MouseX -= 0.05f;
    if (ManulEngine::Input::IsKeyPressed(ManulEngine::Key::J))
        MouseX += 0.05f;
    

    texture.Bind();
    shader.Use();
    Vector2Uint windowSize = ManulEngine::Window::Get().GetSize();
    projection = glm::perspective(glm::radians(fov), (float)windowSize.x / (float)windowSize.y, 0.1f, 100.0f);
    projection = glm::rotate(projection, glm::radians(MouseY), glm::vec3(0.0f, 0.0f, 1.0f));
    projection = glm::rotate(projection, glm::radians(MouseX), glm::vec3(0.0f, 1.0f, 0.0f));
    shader.setMat4("projection", projection);

    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    shader.setMat4("view", view);

    glBindVertexArray(VAO);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, cubePosition);
    float angle = 0;
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
