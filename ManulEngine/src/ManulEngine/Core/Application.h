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
            int args;
            char *argv[];
        };

        Application();
        ~Application();

        void Create(ApplicationSpecification *applicationSpecification);
        void Update();
        void Close();

        static Application& Get() { return *s_Instance; }
        static Window& GetWindow() { return *m_Window; }

        static const ApplicationSpecification GetSpecification() { return *m_Specification; }

        bool applicationExit = false;
    private:
        bool OnWindowClose();
        bool OnWindowResize();

        bool m_Running = true;
        bool m_Minimized = false;

        static ApplicationSpecification* m_Specification;
        static Application* s_Instance;
        static Window* m_Window;

    };
}

