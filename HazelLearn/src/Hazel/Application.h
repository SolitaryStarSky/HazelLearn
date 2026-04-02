#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Hazel
{
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		/**
		* 安全：自动释放资源，避免泄漏。
		* 明确：独占所有权语义，防止误用。
        * 高效：无运行时开销（与原始指针相同）。
		* 符合 RAII：将资源管理与对象生命周期绑定。
		*/
		std::unique_ptr<Window>m_Window;
		bool m_Running = true;
	};
	
	Application* CreateApplication();
}
