workspace "HazelLearn"
	architecture "x86_64"
	configurations--配置
	{
		"Debug",
		"Release",
		"Dist"
	}

	platforms
	{
		"Win64","Win32","Xbox360"
	}
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"--输出路径 Debug-windos-x86_64

project "HazelLearn"
	location "HazelLearn"
	kind "SharedLib"
	language "C++"
	
	filter "action:vs*"
        buildoptions { "/utf-8" }
    filter {}
	
	targetdir("bin/" .. outputdir .. "/%{prj.name}")--vs中输出目录 bin/Debug-windos-x64/HazelLearn
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs--include路径配置
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines--预配置宏
		{
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_DLL"
		}

		postbuildcommands 
		{ 
			("{MKDIR} ../bin/" .. outputdir .. "/Sandbox/"),
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/") 
		}
		

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "HZ_RELEASE"
		symbols "On"
		
	filter "configurations:Dist"
		defines "HZ_DIST"
		symbols "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	
	
    filter "action:vs*"
        buildoptions { "/utf-8" }
    filter {}
	
	
	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"HazelLearn/vendor/spdlog/include",
		"HazelLearn/src"
	}

	links
	{
		"HazelLearn"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"


		defines
		{
			"HZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "HZ_RELEASE"
		symbols "On"
		
	filter "configurations:Dist"
		defines "HZ_DIST"
		symbols "On"