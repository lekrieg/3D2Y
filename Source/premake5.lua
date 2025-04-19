-- WORKSPACE STUFF
workspace "SunRise"
    architecture "x64"

    configurations { "Debug", "Release" }

    startproject "Game"

-- PROJECT STUFF
project "AbyssCore"
    location "AbyssCore"
    kind "StaticLib"
    language "C++"


	targetdir ("Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/")
	objdir ("Temp/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/")

    files {
        "AbyssCore/**.h",
        "AbyssCore/**.c",
        "AbyssCore/**.hpp",
        "AbyssCore/**.cpp",
    }

    includedirs {
        "AbyssCore/3rdParty/SFML-3.0.0/include",
        "AbyssCore/3rdParty/SoLoud/include",
        "AbyssCore/3rdParty/yaml-cpp/include",
    }

    libdirs {
        "Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
    }

    filter "system:linux"
        defines { "ABYSS_PLATFORM_LINUX", "SFML_STATIC" }
        -- cppdialect "C++17"
		-- systemversion "latest"

        filter "configurations:Debug"
            links {
                "sfml-graphics-s-d",
                "sfml-audio-s-d",
                "sfml-network-s-d",
                "sfml-window-s-d",
                "sfml-system-s-d",
                "yaml-cpp",
                "freetype",
                "X11",
                "Xi",
                "Xxf86vm",
                "Xrandr",
                "Xcursor",
                "udev",
                "GL",
                "openal",
                "FLAC",
                "ogg",
                "vorbis",
                "pthread",
                -- "Xinerama",
            }
            buildoptions { "-fPIC" }

            defines { "ABYSS_DEBUG", "WITH_MINIAUDIO" }
            symbols "On"
            optimize "Off"
            runtime "Debug"
            prebuildcommands {
                "cp -R -u %{wks.location}/AbyssCore/3rdParty/SFML-3.0.0/lib/Debug/*.a %{wks.location}/Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
                --"cp -R -u %{wks.location}/AbyssCore/3rdParty/yaml-cpp/lib/Debug/*.a %{wks.location}/Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
                --"cp -R -u %{wks.location}/AbyssCore/3rdParty/SFML-3.0.0/lib/Debug/*.lib %{wks.location}/Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
            }

            --postbuildcommands {
            --    "cp -R -u %{wks.location}/AbyssCore/3rdParty/SFML-3.0.0/bin/Debug/*.dll %{wks.location}../Game/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
            --}

            debugdir "%{wks.location}../Game/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"

        filter "configurations:Release"
            links {
                "sfml-graphics-s",
                "sfml-audio-s",
                "sfml-network-s",
                "sfml-system-s",
                "sfml-window-s",
                "yaml-cpp",
                "freetype",
                "X11",
                "Xi",
                "Xxf86vm",
                "Xrandr",
                "Xcursor",
                "udev",
                "GL",
                "openal",
                "FLAC",
                "ogg",
                "vorbis",
                "pthread",
                -- "Xinerama",
            }

            defines { "ABYSS_RELEASE", "WITH_MINIAUDIO" }
            symbols "Off"
            optimize "On"
            runtime "Release"
            prebuildcommands {
                "cp -R -u %{wks.location}AbyssCore/3rdParty/SFML-3.0.0/lib/Release/*.a %{wks.location}Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
                "cp -R -u %{wks.location}AbyssCore/3rdParty/yaml-cpp/lib/Release/*.a %{wks.location}Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"

                --"cp -R -u %{wks.location}AbyssCore/3rdParty/SFML-3.0.0/lib/Release/*.lib %{wks.location}Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
            }

            --postbuildcommands {
            --    "cp -R -u %{wks.location}AbyssCore/3rdParty/SFML-3.0.0/bin/Release/*.dll %{wks.location}../Game/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
            --}

-- -------------------------------------
project "EngineEditor"
    location "EngineEditor"
    kind "ConsoleApp"
    language "C++"
    dependson "AbyssCore"

    targetdir("../EngineEditor/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/")
    objdir("Temp/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/")

    files {
        "EngineEditor/**.h",
        "EngineEditor/**.c",
        "EngineEditor/**.hpp",
        "EngineEditor/**.cpp",
    }

    includedirs {
        "AbyssCore/src",
        "AbyssCore/3rdParty/SFML-3.0.0/include",
        "AbyssCore/3rdParty/SoLoud/include",
        "AbyssCore/3rdParty/yaml-cpp/include",
    }

    libdirs {
        "Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
    }

    filter "system:linux"
        defines { "ABYSS_PLATFORM_LINUX", "SFML_STATIC" }
        -- cppdialect "C++17"
		-- systemversion "latest"

        filter "configurations:Debug"
            links {
                "sfml-graphics-s-d",
                "sfml-audio-s-d",
                "sfml-network-s-d",
                "sfml-window-s-d",
                "sfml-system-s-d",
                "yaml-cpp",
                "freetype",
                "X11",
                "Xi",
                "Xxf86vm",
                "Xrandr",
                "Xcursor",
                "udev",
                "GL",
                "openal",
                "FLAC",
                "ogg",
                "vorbis",
                "pthread",
                -- "Xinerama",
                "AbyssCore"
            }
            buildoptions { "-fPIC" }

            defines { "ABYSS_DEBUG", "WITH_MINIAUDIO" }
            symbols "On"
            optimize "Off"
            runtime "Debug"

            debugdir "%{wks.location}../EngineEditor/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"

        filter "configurations:Release"
            links {
                "sfml-graphics-s",
                "sfml-audio-s",
                "sfml-network-s",
                "sfml-system-s",
                "sfml-window-s",
                "yaml-cpp",
                "freetype",
                "X11",
                "Xi",
                "Xxf86vm",
                "Xrandr",
                "Xcursor",
                "udev",
                "GL",
                "openal",
                "FLAC",
                "ogg",
                "vorbis",
                "pthread",
                -- "Xinerama",
                "AbyssCore"
            }

            defines { "ABYSS_RELEASE", "WITH_MINIAUDIO" }
            symbols "Off"
            optimize "On"
            runtime "Release"

-- -------------------------------------
project "Game"
    location "Game"
    kind "ConsoleApp"
    language "C++"
    dependson "AbyssCore"

    targetdir("../Game/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/")
    objdir("Temp/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/")

    files {
        "Game/**.h",
        "Game/**.c",
        "Game/**.hpp",
        "Game/**.cpp",
    }

    includedirs {
        "AbyssCore/src",
        "AbyssCore/3rdParty/SFML-3.0.0/include",
        "AbyssCore/3rdParty/SoLoud/include",
        "AbyssCore/3rdParty/yaml-cpp/include",
    }

    libdirs {
        "Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
    }

    filter "system:linux"
        defines { "ABYSS_PLATFORM_LINUX", "SFML_STATIC" }
        -- cppdialect "C++17"
		-- systemversion "latest"

        filter "configurations:Debug"
            links {
                "sfml-graphics-s-d",
                "sfml-audio-s-d",
                "sfml-network-s-d",
                "sfml-window-s-d",
                "sfml-system-s-d",
                "yaml-cpp",
                "freetype",
                "X11",
                "Xi",
                "Xxf86vm",
                "Xrandr",
                "Xcursor",
                "udev",
                "GL",
                "openal",
                "FLAC",
                "ogg",
                "vorbis",
                "pthread",
                -- "Xinerama",
                "AbyssCore"
            }
            buildoptions { "-fPIC" }

            defines { "ABYSS_DEBUG", "WITH_MINIAUDIO" }
            symbols "On"
            optimize "Off"
            runtime "Debug"

            debugdir "%{wks.location}../Game/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"

        filter "configurations:Release"
            links {
                "sfml-graphics-s",
                "sfml-audio-s",
                "sfml-network-s",
                "sfml-system-s",
                "sfml-window-s",
                "yaml-cpp",
                "freetype",
                "X11",
                "Xi",
                "Xxf86vm",
                "Xrandr",
                "Xcursor",
                "udev",
                "GL",
                "openal",
                "FLAC",
                "ogg",
                "vorbis",
                "pthread",
                -- "Xinerama",
                "AbyssCore"
            }

            defines { "ABYSS_RELEASE", "WITH_MINIAUDIO" }
            symbols "Off"
            optimize "On"
            runtime "Release"
