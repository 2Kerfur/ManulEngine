#include "Application.h"

#include <filesystem>
#include "Window.h"

namespace ManulEngine
{
    ManulEngine::Application::Application() {

    }
    ManulEngine::Application::~Application() {

    }

    void Application::Update() {

    }

    void Application::Close() {

    }

    void Application::Create(Application::ApplicationSpecification *applicationSpecification) {
        if (applicationSpecification == nullptr)
        {
            std::filesystem::path cwd = std::filesystem::current_path();

            //Use default settings
            m_Specification->Name = "Default Name";
            m_Specification->Vendor = "Default Vendor";
            m_Specification->Version = "0.0.1";
            m_Specification->WorkingDirectory = cwd.string();

            m_Specification->fullscreen = false;
            m_Specification->windowSize = {100, 100};
            m_Specification->windowPos = {100, 100};
        }
        else
        {
            if (applicationSpecification->readFromFile)
            {

            }
            else m_Specification = applicationSpecification;
        }

    }

}

