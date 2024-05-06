#ifndef SANDBOX_ENTRYPOINT_H
#define SANDBOX_ENTRYPOINT_H

//#ifdef ZED_PLATFORM_WINDOWS
extern Zed::Application* Zed::CreateApplication();


int main(int argc, char** argv) {

    auto app = Zed::CreateApplication();
    app->Run();
    delete app;
}
//#endif
#endif //SANDBOX_ENTRYPOINT_H