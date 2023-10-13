#include "glad/glad.h"
#include "OpenGLBackend.h"

#include "iostream"
void OpenGLBackend::Init(uint32_t windowWidht, uint32_t windowHeight, GLFWwindow *window) {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    
    box.Create({ 0, 0, 0 }, { 3, 3 });
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    box.Bind(EBO, VAO);
}

void OpenGLBackend::Render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    box.Draw();
}

void OpenGLBackend::DrawLine(Vector3 startPos, Vector3 endPos, Vector3Color color)
{

}

void OpenGLBackend::OnWindowResize(int windowWidht, int windowHeigth) {

}

void OpenGLBackend::framebuffer_size_callback(GLFWwindow *window, int width, int height) {

}

void OpenGLBackend::processInput(GLFWwindow *window) {

}
