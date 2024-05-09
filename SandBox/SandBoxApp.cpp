#include <ZedEntry.h>
#include "Zed/ImGui/ImGuiLayer.h"

//测试GLM
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
    glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
    glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
    View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
    View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
    return Projection * View * Model;
}

class ExampleLayer : public Zed::Layer {
public:
    ExampleLayer() : Layer("Example") {
        //测试GLM
        auto cam = camera(1.0, glm::vec2());
        ZED_INFO("GLM test ------ {0}", cam[0][0]);
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
    }

    ~Sandbox()
    {

    }
};

Zed::Application* Zed::CreateApplication() {
    return new Sandbox();
}