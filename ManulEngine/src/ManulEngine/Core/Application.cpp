#include "mapch.h"
#include "Application.h"
#include "ManulEngine/ResourceManager/ResourceManager.h"

namespace ManulEngine
{
    Application* Application::s_Instance = nullptr;

    void Application::Update() {
        applicationExit = m_Window.windowShouldClose;
        if (applicationExit) Destroy();
        m_Window.Update();
    }

    Application::~Application()
    {
        Destroy();
    }

    Application::Application()
    {
        s_Instance = this;
    }
    void Application::CreateConsoleWindow()
    {
        AllocConsole();
        //freopen("conin$", "r", stdin);
        //freopen("conout$", "w", stdout);
        //freopen("conout$", "w", stderr);
    }
    void Application::Create() {
        CreateConsoleWindow();
        Log::Init();
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
            WriteSpecToConfigFile(config);
        }
        if (!m_Window.Create(m_Specification.windowSize.x, m_Specification.windowSize.y,
            m_Specification.Name, m_Specification.fullscreen))
        {
            M_CORE_CRITICAL("Failed to initialize window");
        }
    }
    void Application::WriteSpecToConfigFile(std::vector<std::string> config)
    {
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
    void Application::Destroy()
    {
        std::vector<std::string> config;
        WriteSpecToConfigFile(config);
    }

}

