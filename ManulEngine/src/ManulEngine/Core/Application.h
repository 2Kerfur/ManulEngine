#pragma once
#include <string>
#include "Window.h"
#include "ManulEngine/Core/Math/Math.h"

namespace ManulEngine {
    class Application {
    public:
        struct ApplicationSpecification
        {
            bool readFromFile;
            std::string Name;
            std::string Version;
            std::string Vendor;
            std::string WorkingDirectory;
            //Window Settings
            bool fullscreen;
            Vector2Int windowSize;
            Vector2Int windowPos;     
        };

        virtual ~Application();
        Application();
        
        static Application& Get() { return *s_Instance; }
        
        void Create();
        void Destroy();
        void Update();
        ApplicationSpecification* GetSpecification() { return &m_Specification; };
        bool applicationExit = false;
        
    private:
        void CreateConsoleWindow();
        bool m_Running = true;
        bool m_Minimized = false;

        static Application* s_Instance;
        
        void WriteSpecToConfigFile(std::vector<std::string> config);
        ApplicationSpecification m_Specification;
        
        Window m_Window;

    };
}

