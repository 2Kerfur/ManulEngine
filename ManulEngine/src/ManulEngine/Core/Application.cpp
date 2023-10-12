#include "Application.h"
#include "ManulEngine/ResourceManager/ResourceManager.h"
#include "mapch.h"


namespace ManulEngine
{
    ManulEngine::Application::Application() {

    }
    ManulEngine::Application::~Application() {

    }

    void Application::Update() {
        applicationExit = m_Window.windowShouldClose;
        m_Window.Update();
    }

    void Application::Create() {
        std::vector<std::string> config;
        if (ResourceManager::LoadConfig(config, ResourceManager::GetWorkingDirectory() + "/application.cfg"))
        {
            m_Specification.readFromFile = std::stoi(config[0]);
            m_Specification.Name = config[1];
            m_Specification.Vendor = config[2];
            m_Specification.Version = config[3];
            m_Specification.WorkingDirectory = config[4];

            m_Specification.fullscreen = std::stoi(config[5]);
            m_Specification.windowSize = { std::stoi(config[6]), std::stoi(config[7])};
            m_Specification.windowPos = { std::stoi(config[8]), std::stoi(config[9]) };
        }   
        else {
            //Использовать настройки по умолчанию
            //TODO: Много навалил надо переделать
            m_Specification.readFromFile = false;
            m_Specification.Name = "Default Name";
            m_Specification.Vendor = "Default Vendor";
            m_Specification.Version = "0.0.1";
            m_Specification.WorkingDirectory = ResourceManager::GetWorkingDirectory();

            m_Specification.fullscreen = false;
            m_Specification.windowSize = { 800, 600 };
            m_Specification.windowPos = { 100, 100 };

            config.push_back(std::to_string(m_Specification.readFromFile));
            config.push_back(m_Specification.Name);
            config.push_back(m_Specification.Vendor);
            config.push_back(m_Specification.Version);
            config.push_back(m_Specification.WorkingDirectory);
            config.push_back(std::to_string(m_Specification.fullscreen));
            config.push_back(std::to_string(m_Specification.windowSize.x));
            config.push_back(std::to_string(m_Specification.windowSize.y));
            config.push_back(std::to_string(m_Specification.windowPos.x));
            config.push_back(std::to_string(m_Specification.windowPos.y));

            ResourceManager::CreateConfig(config, ResourceManager::GetWorkingDirectory() + "/application.cfg");
        }
        m_Window.Create(m_Specification.windowSize.x, m_Specification.windowSize.y, m_Specification.Name, m_Specification.fullscreen);
    }

}

