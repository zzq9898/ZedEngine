#ifndef ZED_WINDOWSWINDOW_H
#define ZED_WINDOWSWINDOW_H

#include "Zed/Core/Window.h"
#include "Zed/Renderer/GraphicsContext.h"
namespace Zed{
    class WindowsWindow : public Window{
    public:
        WindowsWindow(const WindowProps& props);

        virtual ~WindowsWindow();

        void OnUpdate() override;

        inline unsigned int GetWidth() const override {return m_Data.Width;}
        inline unsigned  int GetHeight() const override {return m_Data.Height;}

        GLFWwindow* GetNativeWindow() {
            return m_Window;
        }

        // Window attributes
        inline void SetEventCallback(const EventCallbackFn& callback) override {
            m_Data.EventCallback = callback;
        }

        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();


    private:
        GLFWwindow* m_Window;
        GraphicsContext* m_Context;

        struct WindowData {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;
            EventCallbackFn EventCallback;
        };

        WindowData  m_Data;
    };
}


#endif //ZED_WINDOWSWINDOW_H