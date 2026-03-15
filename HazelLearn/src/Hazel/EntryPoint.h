#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern HL::Application* HL::CreateApplication();

int main(int argc, char** argv)
{
	auto app = HL::CreateApplication();
	app->Run();
	delete app;
}

#endif // HZ_PLATFORM_WINDOWS
