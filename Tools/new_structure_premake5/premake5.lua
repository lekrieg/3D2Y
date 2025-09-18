require "clion"

-- aux methods
local systems = { "windows", "linux" }
local architectures = { "x86_64" }
local buildcfgs = { "Debug", "Release" }

function createOutputDirs(targetFolder)
    for _, sys in ipairs(systems) do
        for _, arch in ipairs(architectures) do
            for _, cfg in ipairs(buildcfgs) do
                local dir = path.join(targetFolder, sys .. arch .. cfg)
                if not os.isdir(dir) then
                    os.mkdir(dir)
                end
            end
        end
    end
end

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

    createOutputDirs("Lib");

	targetdir ("Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/")
	objdir ("Temp/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/")

    files {
        "AbyssCore/**.h",
        "AbyssCore/**.c",
        "AbyssCore/**.hpp",
        "AbyssCore/**.cpp",
    }

    includedirs {
        "3rdParty/SFML-3.0.0/include",
        "3rdParty/SoLoud/include",
        "3rdParty/yaml-cpp/include",
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
                "cp -R -u %{wks.location}/3rdParty/SFML-3.0.0/lib/Debug/*.a %{wks.location}/Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
                --"cp -R -u %{wks.location}/3rdParty/yaml-cpp/lib/Debug/*.a %{wks.location}/Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
                --"cp -R -u %{wks.location}/3rdParty/SFML-3.0.0/lib/Debug/*.lib %{wks.location}/Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
            }

            --postbuildcommands {
            --    "cp -R -u %{wks.location}/3rdParty/SFML-3.0.0/bin/Debug/*.dll %{wks.location}../Game/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
            --}

            debugdir "%{wks.location}../Game/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"

        filter "configurations:Release"
            links {
                "sfml-graphics-s",
                "sfml-audio-s",
                "sfml-network-s",
                "sfml-window-s",
                "sfml-system-s",
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
                "cp -R -u %{wks.location}3rdParty/SFML-3.0.0/lib/Release/*.a %{wks.location}Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/",
                "cp -R -u %{wks.location}3rdParty/yaml-cpp/lib/Release/*.a %{wks.location}Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"

                --"cp -R -u %{wks.location}3rdParty/SFML-3.0.0/lib/Release/*.lib %{wks.location}Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
            }

            --postbuildcommands {
            --    "cp -R -u %{wks.location}3rdParty/SFML-3.0.0/bin/Release/*.dll %{wks.location}../Game/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
            --}

-- -------------------------------------
project "EngineEditor"
    location "EngineEditor"
    kind "ConsoleApp"
    language "C++"
    dependson "AbyssCore"

    createOutputDirs("../EngineEditor");

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
        "3rdParty/SFML-3.0.0/include",
        "3rdParty/SoLoud/include",
        "3rdParty/yaml-cpp/include",
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

    createOutputDirs("../Game");

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
        "3rdParty/SFML-3.0.0/include",
        "3rdParty/SoLoud/include",
        "3rdParty/yaml-cpp/include",
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
                "X11",
                "sfml-graphics-s",
                "sfml-audio-s",
                "sfml-network-s",
                "sfml-window-s",
                "sfml-system-s",
                "yaml-cpp",
                "freetype",
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
            -- buildoptions { "-O3" }

            defines { "ABYSS_RELEASE", "WITH_MINIAUDIO" }
            symbols "Off"
            optimize "On"
            runtime "Release"

-- -------------------------------------
project "AssetCreator"
    location "AssetCreator"
    kind "ConsoleApp"
    language "C++"

    createOutputDirs("../AssetCreator");

	targetdir ("../AssetCreator/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/")
	objdir ("Temp/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/")

    files {
        "AssetCreator/**.h",
        "AssetCreator/**.c",
        "AssetCreator/**.hpp",
        "AssetCreator/**.cpp",
    }

    includedirs {
        "3rdParty/SFML-3.0.0/include",
        "3rdParty/SoLoud/include",
        "3rdParty/yaml-cpp/include",
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
                "cp -R -u %{wks.location}/3rdParty/SFML-3.0.0/lib/Debug/*.a %{wks.location}/Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
                --"cp -R -u %{wks.location}/3rdParty/yaml-cpp/lib/Debug/*.a %{wks.location}/Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
                --"cp -R -u %{wks.location}/3rdParty/SFML-3.0.0/lib/Debug/*.lib %{wks.location}/Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
            }

            --postbuildcommands {
            --    "cp -R -u %{wks.location}/3rdParty/SFML-3.0.0/bin/Debug/*.dll %{wks.location}../Game/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
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
                "cp -R -u %{wks.location}3rdParty/SFML-3.0.0/lib/Release/*.a %{wks.location}Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/",
                "cp -R -u %{wks.location}3rdParty/yaml-cpp/lib/Release/*.a %{wks.location}Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"

                --"cp -R -u %{wks.location}3rdParty/SFML-3.0.0/lib/Release/*.lib %{wks.location}Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
            }

            --postbuildcommands {
            --    "cp -R -u %{wks.location}3rdParty/SFML-3.0.0/bin/Release/*.dll %{wks.location}../Game/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
            --}
