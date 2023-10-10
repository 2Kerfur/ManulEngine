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

        Application();
        ~Application();

        void Create();
        void Update();

        bool applicationExit = false;
    private:

        bool m_Running = true;
        bool m_Minimized = false;

        static Application* s_Instance;

        ApplicationSpecification m_Specification;
        Window m_Window;

    };
}

