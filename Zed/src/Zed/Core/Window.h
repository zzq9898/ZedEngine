#pragma once
#include <sstream>
#include <stdint.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Zed/Core/Base.h"
#include "Zed/Events/Event.h"

namespace Zed {

	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "Zed Engine",
			        uint32_t width = 1200,
			        uint32_t height = 800)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	// Interface representing a desktop system based Window
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual GLFWwindow* GetNativeWindow(){return nullptr;};

		static Window* Create(const WindowProps& props = WindowProps());
	};

}
