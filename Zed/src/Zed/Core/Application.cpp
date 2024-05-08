
#include "Zed/Core/Application.h"
#include "Zed/Core/Log.h"

#include "Zed/Events/ApplicationEvent.h"


namespace Zed{
    Application::Application() {

    }

    Application::~Application() {

    }

    void Application::Run() {
        WindowResizeEvent e(1200, 720);
        if (e.IsInCategory(EventCategoryApplication)) {
            ZED_TRACE(e.ToString());
        }

        if (e.IsInCategory(EventCategoryInput)) {
            ZED_TRACE(e.ToString());
        }

        while(true) {

        }
    }

}