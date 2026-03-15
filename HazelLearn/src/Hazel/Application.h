#pragma once

#include "Core.h"

namespace HL
{
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};
	
	Application* CreateApplication();
}
