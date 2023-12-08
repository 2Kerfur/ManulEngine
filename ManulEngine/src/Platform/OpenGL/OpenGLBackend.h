#pragma once
#include "ManulEngine/Core/Math/Math.h"
#include "ManulEngine/Renderer/RendererBackend.h"
#include "GLFW/glfw3.h"
#include "OpenGLPrimitives.h"
#include <string>

namespace ManulEngine
{
    class OpenGLBackend : public RendererBackend {
    public:
        virtual bool Init(Vector2Uint windowSize) override;
        virtual void SetWindowSize(Vector2Uint windowSize) override;
        virtual void Render() override;
        virtual void Shutdown() override;
    private:
        std::vector<std::string> logs;
        uint32_t EBO, VAO, VBO;
    };
}

