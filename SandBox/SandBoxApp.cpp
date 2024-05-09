#include <ZedEntry.h>
#include "Zed/ImGui/ImGuiLayer.h"
class ExampleLayer : public Zed::Layer {
public:
    ExampleLayer() : Layer("Example") {

    }

    void OnUpdate() override{
        //ZED_INFO("ExampleLayer::Update");
        if (Zed::Input::IsKeyPressed(ZED_KEY_TAB)) {
            ZED_TRACE("TAB key is pressed(poll)!");
        }
    }

    void OnEvent(Zed::Event& event) override {
        ZED_TRACE("ExampleLayer::OnEvent {0}", event.ToString());
    }
};
class Sandbox : public Zed::Application {
public:
    Sandbox(){
        PushOverlay(new ExampleLayer());
        PushOverlay(new Zed::ImGuiLayer());
    }

    ~Sandbox()
    {

    }
};

Zed::Application* Zed::CreateApplication() {
    return new Sandbox();
}