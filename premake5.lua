workspace "Genesis"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Genesis/vendor/GLFW/include"
IncludeDir["Glad"] = "Genesis/vendor/Glad/include"
IncludeDir["ImGui"] = "Genesis/vendor/imgui"
IncludeDir["glm"] = "Genesis/vendor/glm"

group "Dependencies"
	include "Genesis/vendor/GLFW"
	include "Genesis/vendor/Glad"
	include "Genesis/vendor/imgui"
group ""

project "Genesis"
	location "Genesis"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "gspch.h"
	pchsource "Genesis/src/gspch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	defines
	{
		"_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS",
		"_CRT_SECURE_NO_WARNINGS",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GS_PLATFORM_WINDOWS",
			"GS_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "GS_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GS_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GS_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Genesis/vendor/spdlog/include",
		"Genesis/src",
		"%{IncludeDir.glm}",
		"Genesis/vendor"
	}

	links
	{
		"Genesis"
	}

	defines
	{
		"_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GS_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GS_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GS_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GS_DIST"
		runtime "Release"
		optimize "on"