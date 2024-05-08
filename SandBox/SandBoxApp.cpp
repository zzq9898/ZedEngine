#include <ZedEntry.h>

class ExampleLayer : public Zed::Layer {
public:
    ExampleLayer() : Layer("Example") {

    }

    void OnUpdate() override{
        ZED_INFO("ExampleLayer::Update");
    }

    void OnEvent(Zed::Event& event) override {
        ZED_TRACE("ExampleLayer::OnEvent {0}", event.ToString());
    }
};
class Sandbox : public Zed::Application {
public:
    Sandbox(){
        PushOverlay(new ExampleLayer());
    }

    ~Sandbox()
    {

    }
};

Zed::Application* Zed::CreateApplication() {
    return new Sandbox();
}