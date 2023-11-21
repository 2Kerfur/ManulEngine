#pragma once
#include "Math/Math.h"
#include "Window.h"
#include <vector>
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
        std::vector<std::string> config;
        static Application* s_Instance;
        Window* m_Window;
        void WriteSpecToConfigFile(std::vector<std::string> config);
        ApplicationSpecification m_Specification;
    };
}

