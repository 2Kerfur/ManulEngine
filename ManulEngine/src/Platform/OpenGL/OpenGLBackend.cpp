#include "glad/glad.h"
#include "OpenGLBackend.h"
#include "ManulEngine/Core/Log.h"
#include "ManulEngine/Core/Application.h"
#include "ManulEngine/Core/Window.h"
#include "iostream"
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height); //TODO: Перенести в renderer   
}

static OpenGLBox box;
static OpenGLLine line;

void OpenGLBackend::DrawQuad()
{
    
}
void OpenGLBackend::DrawLine()
{
    
}
uint32_t EBO, VAO, VBO;
void OpenGLBackend::Init(uint32_t windowWidht, uint32_t windowHeight) {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    const char* glVersion = reinterpret_cast<const char*>(glad_glGetString(GL_VERSION));
    M_CORE_INFO("Graphics API: OpenGL ({})", glVersion);
    
    const char* graphicsCard = reinterpret_cast<const char*>(glad_glGetString(GL_RENDERER));
    M_CORE_INFO("Graphics card: {}", graphicsCard);
    
    glfwSetFramebufferSizeCallback(&ManulEngine::Window::GetInstatnce(), framebuffer_size_callback);
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    //Create everythig in scene
    box.Create({ 0, 0, 0 }, { 3, 3 });
    //line.Create({ 0, 0, 0 }, { 3, 3 });

    
        
    //line.Bind(EBO, VAO, VBO);
    box.Bind(EBO, VAO, VBO);
}

void OpenGLBackend::SetWindowSize(uint32_t windowWidht, uint32_t windowHeigth)
{
    glViewport(0, 0, windowWidht, windowHeigth);
    
}

void OpenGLBackend::Render() {
    glClearColor(0.8f, 0.3f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
   //line.Bind(EBO, VAO, VBO);
    //line.Draw();
    //box.Bind(EBO, VAO, VBO);
    box.Draw();
}

void OpenGLBackend::DrawLine(Vector3 startPos, Vector3 endPos, Vector3Color color)
{

}



void OpenGLBackend::processInput(GLFWwindow *window) {

}
