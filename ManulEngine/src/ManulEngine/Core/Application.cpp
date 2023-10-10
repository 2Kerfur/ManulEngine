#include "Application.h"
#include "ManulEngine/ResourceManager/ResourceLoader.h"
#include "mapch.h"


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

    void Application::Create() {

        
            std::filesystem::path cwd = std::filesystem::current_path();
            //Использовать настройки по умолчанию
            m_Specification.readFromFile = false;
            m_Specification.Name = "Default Name";
            m_Specification.Vendor = "Default Vendor";
            m_Specification.Version = "0.0.1";
            m_Specification.WorkingDirectory = cwd.string();

            m_Specification.fullscreen = false;
            m_Specification.windowSize = {800, 600};
            m_Specification.windowPos = {100, 100};
            
        
        m_Window.Create(m_Specification.windowSize.x, m_Specification.windowSize.y, m_Specification.Name, m_Specification.fullscreen);
    }

}

