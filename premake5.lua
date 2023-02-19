workspace "OpenGL"
    architecture "x64"
    startproject "OpenGL"
    configurations {"Debug", "Release"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "OpenGL/vendor/GLFW/include"
IncludeDir["Glad"] = "OpenGL/vendor/Glad/include"
IncludeDir["ImGui"] = "OpenGL/vendor/imgui"
IncludeDir["glm"] = "OpenGL/vendor/glm"
IncludeDir["assimp"] = "OpenGL/vendor/assimp/include"
IncludeDir["stb_image"] = "OpenGL/vendor/stb_image/include"

group "Dependecies"
    include "OpenGL/vendor/imgui"
    include "OpenGL/vendor/GLFW"
    include "OpenGL/vendor/Glad"
    include "OpenGL/vendor/stb_image"
    --include "OpenGL/vendor/assimp"

group ""

project "OpenGL"
    location "OpenGL"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.ini",
        "%{prj.name}/res/shaders/**.shader"
    }
    
    defines
	{
		"GLFW_INCLUDE_NONE"
	}

    libdirs
    {
        "%{prj.name}/vendor/assimp"
	}

    includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.assimp}",
        "%{IncludeDir.stb_image}"
    }
    
    links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
        "stb_image",
		"opengl32.lib",
        "assimp-vc142-mtd"
    }
    
    filter "system:windows"
		systemversion "latest"


    filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		runtime "Release"
		optimize "on"