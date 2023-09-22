#pragma once
#include <string>
#include "Window.h"
#include "Math/Math.h"

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
            //Command line arguments
        };

        Application();
        ~Application();

        void Create(ApplicationSpecification* applicationSpecification);
        void Update();

        //static Application& Get() { return *s_Instance; }
        //static Window& GetWindow() { return *m_Window; }

        //static const ApplicationSpecification GetSpecification() { return *m_Specification; }

        bool applicationExit = false;
    private:
        //bool OnWindowClose();
        //bool OnWindowResize();

        bool m_Running = true;
        bool m_Minimized = false;

        static Application* s_Instance;

        ApplicationSpecification m_Specification;
        Window m_Window;

    };
}

