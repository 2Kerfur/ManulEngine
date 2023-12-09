#include "glad/glad.h"
#include "OpenGLBackend.h"
#include "ManulEngine/Core/Log.h"
#include "ManulEngine/Core/Application.h"
#include "ManulEngine/Core/Window.h"

#include "ManulEngine/Renderer/Camera.h"


namespace ManulEngine {
    static OpenGLBox box;
    static OpenGLLine line;
    static OpenGLModel model;
    
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

        return true;
    }

    void OpenGLBackend::SetWindowSize(Vector2Uint windowSize)
    {
        glViewport(0, 0, windowSize.x, windowSize.y);
    }
   
    void OpenGLBackend::Render() {
        glClearColor(0.8f, 0.3f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        model.Draw();
    }
    void OpenGLBackend::Shutdown()
    {
        
    }
}