require "clion"

local WIN_DEBUG_LINKS = {
    "sfml-graphics-s-d", "sfml-audio-s-d", "sfml-network-s-d",
    "sfml-window-s-d",   "sfml-system-s-d",
    "yaml-cpp", "freetyped", "opengl32", "winmm", "gdi32",
    "FLACd", "oggd", "vorbisd", "vorbisencd", "vorbisfiled", "ws2_32",
}
local WIN_RELEASE_LINKS = {
    "sfml-graphics-s",  "sfml-audio-s",  "sfml-network-s",
    "sfml-window-s",    "sfml-system-s",
    "yaml-cpp", "freetype", "opengl32", "winmm", "gdi32",
    "FLAC", "ogg", "vorbis", "vorbisenc", "vorbisfile", "ws2_32",
}
local LIN_DEBUG_LINKS = {
    "sfml-graphics-s-d", "sfml-audio-s-d", "sfml-network-s-d",
    "sfml-window-s-d",   "sfml-system-s-d",
    "yaml-cpp", "freetype",
    "X11", "Xi", "Xxf86vm", "Xrandr", "Xcursor", "udev",
    "GL", "openal", "FLAC", "ogg", "vorbis", "pthread",
}
local LIN_RELEASE_LINKS = {
    "sfml-graphics-s",  "sfml-audio-s",  "sfml-network-s",
    "sfml-window-s",    "sfml-system-s",
    "yaml-cpp", "freetype",
    "X11", "Xi", "Xxf86vm", "Xrandr", "Xcursor", "udev",
    "GL", "openal", "FLAC", "ogg", "vorbis", "pthread",
}

local YAML_STATIC = "YAML_CPP_STATIC_DEFINE"

local function applyExeFilters(debugDir, withAbyss)
    local abyssLink = withAbyss and { "AbyssCore" } or {}
    local libOut    = "Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"

    filter { "system:windows", "configurations:Debug" }
        defines       { "ABYSS_PLATFORM_WINDOWS", "SFML_STATIC", "ABYSS_DEBUG", "WITH_MINIAUDIO", YAML_STATIC }
        systemversion "latest"
        symbols       "On"
        optimize      "Off"
        runtime       "Debug"
        libdirs       { "3rdParty/SFML-3.0.0/lib/Debug/", "3rdParty/yaml-cpp/lib/Debug/", libOut }
        links         (WIN_DEBUG_LINKS)
        links         (abyssLink)
        debugdir      (debugDir)

    filter { "system:windows", "configurations:Release" }
        defines       { "ABYSS_PLATFORM_WINDOWS", "SFML_STATIC", "ABYSS_RELEASE", "WITH_MINIAUDIO", YAML_STATIC }
        systemversion "latest"
        symbols       "Off"
        optimize      "On"
        runtime       "Release"
        libdirs       { "3rdParty/SFML-3.0.0/lib/Release/", "3rdParty/yaml-cpp/lib/Release/", libOut }
        links         (WIN_RELEASE_LINKS)
        links         (abyssLink)

    filter { "system:linux", "configurations:Debug" }
        defines       { "ABYSS_PLATFORM_LINUX", "SFML_STATIC", "ABYSS_DEBUG", "WITH_MINIAUDIO", YAML_STATIC }
        buildoptions  { "-fPIC" }
        symbols       "On"
        optimize      "Off"
        runtime       "Debug"
        libdirs       { "3rdParty/SFML-3.0.0/lib/Debug/", "3rdParty/yaml-cpp/lib/Debug/", libOut }
        links         (LIN_DEBUG_LINKS)
        links         (abyssLink)
        debugdir      (debugDir)

    filter { "system:linux", "configurations:Release" }
        defines       { "ABYSS_PLATFORM_LINUX", "SFML_STATIC", "ABYSS_RELEASE", "WITH_MINIAUDIO", YAML_STATIC }
        symbols       "Off"
        optimize      "On"
        runtime       "Release"
        libdirs       { "3rdParty/SFML-3.0.0/lib/Release/", "3rdParty/yaml-cpp/lib/Release/", libOut }
        links         (LIN_RELEASE_LINKS)
        links         (abyssLink)

    filter {}
end

workspace "SunRise"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "Game"

project "AbyssCore"
    location  "AbyssCore"
    kind      "StaticLib"
    language  "C++"
    targetdir "Lib/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
    objdir    "Temp/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"

    files {
        "AbyssCore/**.h",   "AbyssCore/**.c",
        "AbyssCore/**.hpp", "AbyssCore/**.cpp",
    }

    includedirs {
        "3rdParty/SFML-3.0.0/include",
        "3rdParty/SoLoud/include",
        "3rdParty/yaml-cpp/include",
        "3rdParty/openal-soft/include",
    }

    filter { "system:windows", "configurations:Debug" }
        defines       { "ABYSS_PLATFORM_WINDOWS", "SFML_STATIC", "ABYSS_DEBUG", "WITH_MINIAUDIO", YAML_STATIC }
        systemversion "latest"
        symbols       "On"
        optimize      "Off"
        runtime       "Debug"
        libdirs       { "3rdParty/SFML-3.0.0/lib/Debug/", "3rdParty/yaml-cpp/lib/Debug/" }
        links         (WIN_DEBUG_LINKS)
        debugdir      "%{wks.location}../Game/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"

    filter { "system:windows", "configurations:Release" }
        defines       { "ABYSS_PLATFORM_WINDOWS", "SFML_STATIC", "ABYSS_RELEASE", "WITH_MINIAUDIO", YAML_STATIC }
        systemversion "latest"
        symbols       "Off"
        optimize      "On"
        runtime       "Release"
        libdirs       { "3rdParty/SFML-3.0.0/lib/Release/", "3rdParty/yaml-cpp/lib/Release/" }
        links         (WIN_RELEASE_LINKS)

    filter { "system:linux", "configurations:Debug" }
        defines       { "ABYSS_PLATFORM_LINUX", "SFML_STATIC", "ABYSS_DEBUG", "WITH_MINIAUDIO", YAML_STATIC }
        buildoptions  { "-fPIC" }
        symbols       "On"
        optimize      "Off"
        runtime       "Debug"
        libdirs       { "3rdParty/SFML-3.0.0/lib/Debug/", "3rdParty/yaml-cpp/lib/Debug/" }
        links         (LIN_DEBUG_LINKS)
        debugdir      "%{wks.location}../Game/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"

    filter { "system:linux", "configurations:Release" }
        defines       { "ABYSS_PLATFORM_LINUX", "SFML_STATIC", "ABYSS_RELEASE", "WITH_MINIAUDIO", YAML_STATIC }
        symbols       "Off"
        optimize      "On"
        runtime       "Release"
        libdirs       { "3rdParty/SFML-3.0.0/lib/Release/", "3rdParty/yaml-cpp/lib/Release/" }
        links         (LIN_RELEASE_LINKS)

    filter {}

project "EngineEditor"
    location  "EngineEditor"
    kind      "ConsoleApp"
    language  "C++"
    dependson "AbyssCore"
    targetdir "../EngineEditor/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
    objdir    "Temp/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"

    files {
        "EngineEditor/**.h",   "EngineEditor/**.c",
        "EngineEditor/**.hpp", "EngineEditor/**.cpp",
    }

    includedirs {
        "AbyssCore/src",
        "3rdParty/SFML-3.0.0/include",
        "3rdParty/SoLoud/include",
        "3rdParty/yaml-cpp/include",
        "3rdParty/openal-soft/include",
    }

    applyExeFilters(
        "%{wks.location}../EngineEditor/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/",
        true
    )

project "Game"
    location  "Game"
    kind      "ConsoleApp"
    language  "C++"
    dependson "AbyssCore"
    targetdir "../Game/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
    objdir    "Temp/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"

    files {
        "Game/**.h",   "Game/**.c",
        "Game/**.hpp", "Game/**.cpp",
    }

    includedirs {
        "AbyssCore/src",
        "3rdParty/SFML-3.0.0/include",
        "3rdParty/SoLoud/include",
        "3rdParty/yaml-cpp/include",
        "3rdParty/openal-soft/include",
    }

    applyExeFilters(
        "%{wks.location}../Game/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/",
        true
    )

project "AssetCreator"
    location  "AssetCreator"
    kind      "ConsoleApp"
    language  "C++"
    targetdir "../AssetCreator/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"
    objdir    "Temp/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/"

    files {
        "AssetCreator/**.h",   "AssetCreator/**.c",
        "AssetCreator/**.hpp", "AssetCreator/**.cpp",
    }

    includedirs {
        "3rdParty/SFML-3.0.0/include",
        "3rdParty/SoLoud/include",
        "3rdParty/yaml-cpp/include",
        "3rdParty/openal-soft/include",
    }

    applyExeFilters(
        "%{wks.location}/%{cfg.system}%{cfg.architecture}%{cfg.buildcfg}/",
        false
    )