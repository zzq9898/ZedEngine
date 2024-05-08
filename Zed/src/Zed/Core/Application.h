#ifndef ZED_APPLICATION_H
#define ZED_APPLICATION_H

namespace Zed{
    class Application {
    public:
        Application();
        virtual ~Application();
        void Run();
    };

    Application* CreateApplication();
}



#endif //ZED_APPLICATION_H