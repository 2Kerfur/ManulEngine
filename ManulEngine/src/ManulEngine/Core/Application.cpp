#include "Application.h"

#include <filesystem>

namespace ManulEngine
{
    ManulEngine::Application::Application() {

    }
    ManulEngine::Application::~Application() {

    }

    void Application::Update() {
        m_Window.Update();
        applicationExit = m_Window.windowShouldClose;
    }

    void Application::Create(ApplicationSpecification* applicationSpecification) {
        if (applicationSpecification == nullptr)
        {
            std::filesystem::path cwd = std::filesystem::current_path();

            //Use default settings
            m_Specification.readFromFile = false;
            m_Specification.Name = "Default Name";
            m_Specification.Vendor = "Default Vendor";
            m_Specification.Version = "0.0.1";
            m_Specification.WorkingDirectory = cwd.string();

            m_Specification.fullscreen = false;
            m_Specification.windowSize = {800, 600};
            m_Specification.windowPos = {100, 100};
        }
        else
        {
            if (applicationSpecification->readFromFile)
            {
                //TODO: Считать конфиг с файла
            }
            else
            {
                //TODO: Иправить это говно
                m_Specification.readFromFile = applicationSpecification->readFromFile;
                m_Specification.Name = applicationSpecification->Name;
                m_Specification.Vendor = applicationSpecification->Vendor;
                m_Specification.Version = applicationSpecification->Version;
                m_Specification.WorkingDirectory = applicationSpecification->WorkingDirectory;

                m_Specification.fullscreen = applicationSpecification->fullscreen;
                m_Specification.windowSize = applicationSpecification->windowSize;
                m_Specification.windowPos = applicationSpecification->windowPos;
            }
        }
        m_Window.Create(m_Specification.windowSize.x, m_Specification.windowSize.y, m_Specification.Name, m_Specification.fullscreen);
    }

}

