#pragma once

#include "Event.h"
#include <sstream>

namespace Hazel
{
	// 窗口大小改变事件
	class HAZEL_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) :m_Width(width), m_Height(height){}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		// 重写ToString以提供自定义描述
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		// 使用宏定义事件类型和类别
		EVENT_CLASS_TYPE(WindowResize)               // 事件类型为 WindowResize
		EVENT_CLASS_CATEGORY(EventCategoryApplication) // 属于 Application 类别
	private:
		unsigned int m_Width, m_Height;  // 新窗口的宽度和高度
	};

	//窗口关闭事件(无额外数据)
	class HAZEL_API WindowCloseEvent : public Event
	{
	public:
		/*
		* = default 让编译器生成最符合语言规则的默认构造函数，保留了类型的许多优化可能性（平凡、聚合、常量初始化等）。
		* {} 是用户显式定义的空实现，虽然行为上往往等价，但会改变类型的属性，且可能带来额外的代码生成开销。
		*/
		WindowCloseEvent() = default;
		
		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	// 应用程序 Tick 事件（每帧定时触发）
	class HAZEL_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	// 应用程序 Update 事件（每帧更新逻辑）
	class HAZEL_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	// 应用程序 Render 事件（每帧渲染）
	class HAZEL_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}