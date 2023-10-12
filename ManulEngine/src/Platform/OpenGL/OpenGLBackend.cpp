#include "glad/glad.h"
#include "OpenGLBackend.h"

#include "iostream"
void OpenGLBackend::Init(uint32_t windowWidht, uint32_t windowHeight, GLFWwindow *window) {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    
    const char *vertexShaderSource = "#version 330 core\n"
                                            "layout (location = 0) in vec3 aPos;\n"
                                            "void main()\n"
                                            "{\n"
                                            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                            "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
                                              "out vec4 FragColor;\n"
                                              "void main()\n"
                                              "{\n"
                                              "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                              "}\n\0";
    
    shader.Compile(vertexShaderSource, fragmentShaderSource);
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

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void OpenGLBackend::Render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader.shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
