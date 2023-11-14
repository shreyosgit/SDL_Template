workspace "SDL Template"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

	startproject "SDL Template"

arch = "%{cfg.architecture}"
config = "%{cfg.buildcfg}"

project "SDL Template"
	location "SDL Template"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"

	targetdir ("bin/" .. arch .. "/" .. config)
	objdir ("bin/intermediates/" .. arch .. "/" .. config )

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"deps/include"
	}
	
	libdirs
	{
		"deps/lib/" .. arch,
		"$(ProjectDir)/SDL2/bin"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines { "DEBUG" }
		runtime "Debug"
		symbols "On"
		optimize "Off"
		buildoptions "/MTd"
		links
		{
			"SDL2.lib",
			"SDL2main.lib",
			"SDL2test.lib"
		}

	filter "configurations:Release"
		defines { "RELEASE" }
		runtime "Release"
		symbols "Off"
		optimize "On"
		buildoptions "/MT"
		links
		{
			"SDL2.lib",
			"SDL2main.lib",
		}

	vstudio = {  }

	vstudio.toolset = "latest"

	vstudio.vc2022 = {
		includeDirs = { 
			"deps/include"
		}
	}

	vstudio.vc2022["Debug"] = {
		libDirs = { 
			"deps/lib"
		},
		links = { 
			"SDL2.lib",
			"SDL2main.lib",
			"SDL2test.lib"
		}
	}

	vstudio.vc2022["Release"] = {
		libDirs = { 
			"deps/lib"
		},
		links = { 
			"SDL2.lib",
			"SDL2main.lib"
		}
	}