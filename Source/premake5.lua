workspace "SunRise"
	architecture "x64"

	configurations{
		"Debug",
		"Release"
	}

	startproject "SunRise"

project "AbyssCore"
	location "AbyssCore"
	kind "StaticLib"
	language "C++"

	targetdir ("Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/")
	objdir ("Temp/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/")

	files{
		"AbyssCore/**.h",
		"AbyssCore/**.c",
		"AbyssCore/**.hpp",
		"AbyssCore/**.cpp"
	}

	includedirs{
		"AbyssCore/3rdParty/glfw/include/",
		"AbyssCore/3rdParty/glad/include/"
	}

	libdirs{
		"Lib/%{cfg.architecture}%{cfg.buildcfg}/"
	}

	filter "system:window"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"

		filter "configurations:Debug"
		defines{
			"ABYSS_DEBUG"
		}

		symbols "On"
		optimize "Off"
		runtime "Debug"

	filter "configurations:Release"
		defines{
			"ABYSS_RELEASE"
		}
		
		symbols "Off"
		optimize "Full"
		runtime "Release"

project "SunRise"
	location "SunRise"
	kind "ConsoleApp"
	language "C++"
	dependson "AbyssCore"

	targetdir ("../Game/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/")
	objdir ("Temp/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/")

	files{
		"SunRise/**.h",
		"SunRise/**.c",
		"SunRise/**.hpp",
		"SunRise/**.cpp"
	}

	includedirs{
		"AbyssCore/"
	}

	libdirs{
		"Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
	}

	links{
		"opengl32",
		"glfw3",
		"AbyssCore",
		"gdi32"
	}

	filter "system:window"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"

		defines{
			"ABYSS_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines{
			"ABYSS_DEBUG"
		}
		
		symbols "On"
		optimize "Off"
		runtime "Debug"

	filter "configurations:Release"
		defines{
			"ABYSS_RELEASE"
		}
		
		symbols "Off"
		optimize "On"
		runtime "Release"