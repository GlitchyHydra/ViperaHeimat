project "assimp"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/assimp/**.h",
        "include/assimp/**.hpp"
	}

	includedirs
	{
		"include"
	}

	links
	{
		"assimp-vc142-mtd.lib"
	}

	filter "system:windows"
        systemversion "latest"

	filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"