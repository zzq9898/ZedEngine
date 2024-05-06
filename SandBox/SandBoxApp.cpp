#include <ZedEntry.h>
class Sandbox : public Zed::Application {
public:
    Sandbox(){

    }

    ~Sandbox()
    {

    }
};

Zed::Application* Zed::CreateApplication() {
    return new Sandbox();
}