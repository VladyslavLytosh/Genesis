workspace "Genesis"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Genesis"
	location "Genesis"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"Genesis/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++14"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"GS_PLATFORM_WINDOWS",
			"GS_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines
		{
			"GS_DEBUG"
		}
		symbols "On"
	filter "configurations:Release"
		defines
		{
			"GS_RELEASE"
		}
		optimize "On"
	filter "configurations:Dist"
		defines
		{
			"GS_DIST"
		}
		optimize "On"

project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
		}
	
		includedirs
		{
			"Genesis/vendor/spdlog/include",
			"Genesis/src"
		}

		links
		{
			"Genesis"
		}
	
		filter "system:windows"
			cppdialect "C++14"
			staticruntime "On"
			systemversion "latest"
			
			defines
			{
				"GS_PLATFORM_WINDOWS",
			}

		filter "configurations:Debug"
			defines
			{
				"GS_DEBUG"
			}
			symbols "On"
		filter "configurations:Release"
			defines
			{
				"GS_RELEASE"
			}
			optimize "On"
		filter "configurations:Dist"
			defines
			{
				"GS_DIST"
			}
			optimize "On"