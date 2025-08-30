require "clion"

-- WORKSPACE STUFF
workspace "AssetCreator"
    architecture "x64"

    configurations { "Debug", "Release" }

    startproject "AssetCreator"

-- PROJECT STUFF
project "AssetCreator"
    location "AssetCreator"
    kind "ConsoleApp"
    language "C++"


	targetdir ("Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/")
	objdir ("Temp/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/")

    files {
        "AssetCreator/**.h",
        "AssetCreator/**.c",
        "AssetCreator/**.hpp",
        "AssetCreator/**.cpp",
    }

    includedirs {
        "AssetCreator/3rdParty/SFML-3.0.0/include",
        "AssetCreator/3rdParty/SoLoud/include",
        "AssetCreator/3rdParty/yaml-cpp/include",
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
                "cp -R -u %{wks.location}/AssetCreator/3rdParty/SFML-3.0.0/lib/Debug/*.a %{wks.location}/Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
                --"cp -R -u %{wks.location}/AssetCreator/3rdParty/yaml-cpp/lib/Debug/*.a %{wks.location}/Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
                --"cp -R -u %{wks.location}/AssetCreator/3rdParty/SFML-3.0.0/lib/Debug/*.lib %{wks.location}/Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
            }

            --postbuildcommands {
            --    "cp -R -u %{wks.location}/AssetCreator/3rdParty/SFML-3.0.0/bin/Debug/*.dll %{wks.location}../Game/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
            --}

            debugdir "%{wks.location}/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"

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
                "cp -R -u %{wks.location}AbyssCore/3rdParty/SFML-3.0.0/lib/Release/*.a %{wks.location}Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/",
                "cp -R -u %{wks.location}AbyssCore/3rdParty/yaml-cpp/lib/Release/*.a %{wks.location}Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"

                --"cp -R -u %{wks.location}AbyssCore/3rdParty/SFML-3.0.0/lib/Release/*.lib %{wks.location}Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
            }

            --postbuildcommands {
            --    "cp -R -u %{wks.location}AbyssCore/3rdParty/SFML-3.0.0/bin/Release/*.dll %{wks.location}../Game/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
            --}
