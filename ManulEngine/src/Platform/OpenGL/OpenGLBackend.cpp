#include "glad/glad.h"
#include "OpenGLBackend.h"
#include "ManulEngine/Core/Log.h"
#include "ManulEngine/Core/Application.h"
#include "ManulEngine/Core/Window.h"
#include "OpenGLSkybox.h"
#include "ManulEngine/Renderer/Camera.h"
#include "OpenGLShader.h"
#include "glm/glm.hpp"
#include <ManulEngine/Core/Input.h>

namespace ManulEngine {
    static OpenGLBox box;
    static OpenGLLine line;
    static OpenGLModel model;
    static SkyBox skybox;

    const char* SkyboxFragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 TexCoords;\n"
        "uniform samplerCube skybox;\n"
        "void main()\n"
        "{\n"
        "   FragColor = texture(skybox, TexCoords);\n"
        "}\n\0";
    const char* SkyboxVertexShaderSource = "#version 330 core\n"
        "layout(location = 0) in vec3 vertex;\n"
        "out vec3 TexCoords;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "uniform vec3 campos;\n"

        "void main()\n"
        "{\n"
        "   gl_Position = projection * view * vec4(vertex + campos, 1.0f);\n"
        "   TexCoords = vertex;\n"
        "}\n\0";
    static OpenGLShader skyboxShader;
    bool OpenGLBackend::Init(Vector2Uint windowSize) {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }
        const char* glVersion = reinterpret_cast<const char*>(glad_glGetString(GL_VERSION));
        M_CORE_INFO("Graphics API: OpenGL ({})", glVersion);

        const char* graphicsCard = reinterpret_cast<const char*>(glad_glGetString(GL_RENDERER));
        M_CORE_INFO("Graphics card: {}", graphicsCard);

        glEnable(GL_DEPTH_TEST);

        model.Create();
        skybox.InitSkybox(1, "1", VAO);
        skyboxShader.Compile(SkyboxVertexShaderSource, SkyboxFragmentShaderSource);
        return true;
    }
    
    void OpenGLBackend::SetWindowSize(Vector2Uint windowSize)
    {
        glViewport(0, 0, windowSize.x, windowSize.y);
    }
   
    void OpenGLBackend::ClearScreen(Vector4 color)
    {
        glClearColor(color.x, color.y, color.z, color.w);
    }
    
    void OpenGLBackend::Render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //M_CORE_INFO()
        skybox.Draw(skyboxShader, model.getProjection(), model.getView(), model.getCameraPos());
        model.Draw();

        if (ManulEngine::Input::IsKeyPressed(ManulEngine::Key::G))
            screenshot.TakeScreenShot(800, 600);
    }
    void OpenGLBackend::Shutdown()
    {
        
    }
}