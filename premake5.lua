require "os"
local os = package.loaded['os']

workspace "Vipera"
	architecture "x64"
--	startproject "Sandbox"
	startproject "Vipera"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

vulkan_sdk_path = os.getenv("VULKAN_SDK") 

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Vipera/vendor/glfw/include"
IncludeDir["Glad"] = "Vipera/vendor/Glad/include"
--IncludeDir["ImGui"] = "Vipera/vendor/imgui"
IncludeDir["glm"] = "Vipera/vendor/glm"
--IncludeDir["stb_image"] = "Vipera/vendor/stb_image/include"
--IncludeDir["assimp"] = "Vipera/vendor/assimp/include"
IncludeDir["Vulkan"] = "%{vulkan_sdk_path}/include"

group "Dependencies"
--	include "Vipera/vendor/glfw"
--	include "Vipera/vendor/glad"
--	include "Vipera/vendor/imgui"
--	include "Vipera/vendor/assimp"

group ""

project "Vipera"
	location "Vipera"
--	kind "StaticLib" --SharedLib for dll
	kind "WindowedApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on" --staticruntime off for dll

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "Vipera/src/hzpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.ini",
		"%{prj.name}/vendor/stb_image/include/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/include/stb_image/**.cpp"
	}

	defines 
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
--		"%{IncludeDir.GLFW}",
--		"%{IncludeDir.Glad}",
--		"%{IncludeDir.ImGui}",
--		"%{IncludeDir.glm}",
--		"%{IncludeDir.stb_image}",
--		"%{IncludeDir.assimp}",
--		"%{IncludeDir.Vulkan}"
	}

	links 
	{ 
--		"GLFW",
--		"Glad",
--		"ImGui",
--		"assimp",
--		"opengl32.lib",
--		"vulkan-1",
--		"VkLayer_utils"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"VIPERA_PLATFORM_WINDOWS",
			"VIPERA_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
		--postbuildcommands
		--{
		--	("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		--}

	filter "configurations:Debug"
		defines "VIPERA_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VIPERA_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "VIPERA_DIST"
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
		"Vipera/vendor/spdlog/include",
		"Vipera/src",
		"Vipera/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
--		"Vipera"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"VIPERA_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "VIPERA_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VIPERA_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "VIPERA_DIST"
		runtime "Release"
		optimize "on"