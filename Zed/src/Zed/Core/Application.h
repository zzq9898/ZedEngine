#ifndef ZED_APPLICATION_H
#define ZED_APPLICATION_H

#include <memory>
#include "Zed/Core/Window.h"
#include "Zed/Events/Event.h"
namespace Zed{
    class Application {
    public:
        Application();
        virtual ~Application();
        void Run();
    private:
        std::unique_ptr<Window> m_window;
        bool  is_running = true;
    };

    Application* CreateApplication();
}



#endif //ZED_APPLICATION_H