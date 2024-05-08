#ifndef ZED_ENTRYPOINT_H
#define ZED_ENTRYPOINT_H

//#ifdef ZED_PLATFORM_WINDOWS
extern Zed::Application* Zed::CreateApplication();


int main(int argc, char** argv) {
    Zed::Log::Init();
    ZED_CORE_INFO("ZedEngine entryPoint!");

    auto app = Zed::CreateApplication();
    app->Run();
    delete app;
}
//#endif
#endif //ZED_ENTRYPOINT_H