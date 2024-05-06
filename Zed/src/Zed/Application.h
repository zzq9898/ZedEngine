#ifndef SANDBOX_APPLICATION_H
#define SANDBOX_APPLICATION_H

namespace Zed{
    class Application {
    public:
        Application();
        virtual ~Application();
        void Run();
    };

    Application* CreateApplication();
}



#endif //SANDBOX_APPLICATION_H