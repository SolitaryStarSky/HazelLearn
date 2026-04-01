#pragma once

#include "hzpch.h"
#include"Hazel/Core.h"

namespace Hazel
{
	//定义EventType枚举
	//所有可能事件类型枚举
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	//定义EventCategory枚举
	/*
	*	使用BIT(n)宏为每个类分配独立位
	*	类别：Application、Input、Keyboard、Mouse、MouseButton
	*	支持按键组合（如 EventCategoryKeyboard | EventCategoryInput）
	*/
	//事件类别枚举，使用位掩码（每个位代表一个类别）
	//BIT(n)宏在别处定义为(1<<n)
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication		= BIT(0),		//应用程序事件（窗口、AppTick等）
		EventCategoryInput				= BIT(1),		//输入事件（键盘、鼠标等）
		EventCategoryKeyboard			= BIT(2),		//键盘事件
		EventCategoryMouse				= BIT(3),		//鼠标事件（移动、滚动）
		EventCategoryMouseButton		= BIT(4),		//鼠标按钮事件
	};


	//编写两个关键宏（简化派生类实现）
	/*
	*	EVENT_CLASS_TYPE(type)
	*	── 生成静态方法 GetStaticType()
	*	── 重写虚函数 GetEventType() 和 GetName()
	*	── #type 将枚举名转为字符串
	*/

	// 宏：为具体事件类生成获取事件类型所需的静态方法和虚方法
	// type 参数是 EventType 枚举中的一个值（不带作用域）
	// #type 将 type 转换为字符串，用于 GetName()
	#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::KeyTyped; }\
									virtual EventType GetEventType() const override { return GetStaticType(); }\
									virtual const char* GetName() const override { return #type; }

	/*
	*	EVENT_CLASS_CATEGORY(category)
	*	── 重写虚函数 GetCategoryFlags() 返回类别位掩码
	*/
	// 宏：为具体事件类生成获取类别标志的虚方法
	// category 参数是一个位掩码组合（如 EventCategoryApplication | EventCategoryInput）
	#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override{ return category; }


	class HAZEL_API Event
	{
		friend class EventDispatcher;
	public:
		//virtual ~Event() = default;

		
		
		//返回具体的事件类型(需在派生类中实现)
		virtual EventType GetEventType() const = 0;
		//返回事件名称字符串(需在派生类中实现)
		virtual const char* GetName() const = 0;
		//返回事件类别位掩码(需在派生类中实现)
		virtual int GetCategoryFlags() const = 0;
		//将事件信息格式化为字符串，默认返回名称
		virtual std::string ToString() const { return  GetName(); }

		//判断事件是否属于某个类别
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
		
	protected:
		bool m_Handled = false;			//标记事件是否已被处理，用于阻塞传播
	};


	// 事件分发器：用于将事件路由到具体的处理函数
	// 采用模板方法，在编译时根据事件类型匹配处理函数
	class EventDispatcher
	{
	//public:
	//	EventDispatcher(Event& event): m_Event(event)
	//	{

	//	}

	//	// 模板方法：T 是具体的事件类型（如 WindowResizeEvent）
	//	// F 是可调用对象类型（如 lambda 或函数），其参数应为 T&，返回 bool
	//	// 如果当前事件类型与 T::GetStaticType() 匹配，则调用 func 并累加 Handled 标志
	//	template<typename T, typename F>
	//	bool Dispatch(const F& func)
	//	{
	//		if (m_Event.GetEventType() == T::GetStaticType())
	//		{
	//			// 将 m_Event 强制转换为 T& 并传递给处理函数
	//			// 使用 |= 以便多个处理函数可以共同决定事件是否被处理（只要有一个返回 true 即认为已处理）
	//			m_Event.Handled |= func(static_cast<T&>(m_Event));
	//			return true;
	//		}
	//		return false;
	//	}

	//private:
	//	Event& m_Event;

		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	//重载 << 运算符，方便将事件直接输出到流（如std::cout）
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}