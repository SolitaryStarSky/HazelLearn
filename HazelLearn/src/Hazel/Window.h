#pragma once

#include "hzpch.h"

#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel
{
	//窗口参数配置结构体
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		//结构体构造函数
		WindowProps(const std::string& title = "HazelLearn Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	//基于Window的桌面系统接口
	class HAZEL_API Window
	{
	public:
		//重命名EventCallbackFn
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window 属性
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;


		/*
		*	这是一种工厂方法模式，目的是：
		*	隐藏平台相关的具体窗口类（如 WindowsWindow、GLFWWindow）。
		*	提供统一的创建接口，方便扩展和维护。
		*	支持默认参数，简化常用调用。
		*/
		static Window* Create(const WindowProps& props = WindowProps());

	};
}