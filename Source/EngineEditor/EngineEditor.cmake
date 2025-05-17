add_executable("EngineEditor"
  "EngineEditor/src/EditorApplication.cpp"
  "EngineEditor/src/EditorApplication.h"
  "EngineEditor/src/FileDialogState.h"
  "EngineEditor/src/Main.cpp"
    "EngineEditor/src/imgui/imconfig-SFML.h"
    "EngineEditor/src/imgui/imconfig.h"
    "EngineEditor/src/imgui/imfilebrowser.h"
    "EngineEditor/src/imgui/imgui-SFML.cpp"
    "EngineEditor/src/imgui/imgui-SFML.h"
    "EngineEditor/src/imgui/imgui-SFML_export.h"
    "EngineEditor/src/imgui/imgui.cpp"
    "EngineEditor/src/imgui/imgui.h"
    "EngineEditor/src/imgui/imgui_demo.cpp"
    "EngineEditor/src/imgui/imgui_draw.cpp"
    "EngineEditor/src/imgui/imgui_internal.h"
    "EngineEditor/src/imgui/imgui_tables.cpp"
    "EngineEditor/src/imgui/imgui_widgets.cpp"
    "EngineEditor/src/imgui/imstb_rectpack.h"
    "EngineEditor/src/imgui/imstb_textedit.h"
    "EngineEditor/src/imgui/imstb_truetype.h"
    "EngineEditor/src/scenes/EditorScene.cpp"
    "EngineEditor/src/scenes/EditorScene.h"
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  add_dependencies("EngineEditor"
    "AbyssCore"
  )
  set_target_properties("EngineEditor" PROPERTIES
    OUTPUT_NAME "EngineEditor"
    ARCHIVE_OUTPUT_DIRECTORY "/home/lekrieg/Documents/Projects/3D2Y/EngineEditor/linuxx86_64Debug"
    LIBRARY_OUTPUT_DIRECTORY "/home/lekrieg/Documents/Projects/3D2Y/EngineEditor/linuxx86_64Debug"
    RUNTIME_OUTPUT_DIRECTORY "/home/lekrieg/Documents/Projects/3D2Y/EngineEditor/linuxx86_64Debug"
  )
endif()
target_include_directories("EngineEditor" PRIVATE
  $<$<CONFIG:Debug>:/home/lekrieg/Documents/Projects/3D2Y/Source/AbyssCore/src>
  $<$<CONFIG:Debug>:/home/lekrieg/Documents/Projects/3D2Y/Source/AbyssCore/3rdParty/SFML-3.0.0/include>
  $<$<CONFIG:Debug>:/home/lekrieg/Documents/Projects/3D2Y/Source/AbyssCore/3rdParty/SoLoud/include>
  $<$<CONFIG:Debug>:/home/lekrieg/Documents/Projects/3D2Y/Source/AbyssCore/3rdParty/yaml-cpp/include>
)
target_compile_definitions("EngineEditor" PRIVATE
  $<$<CONFIG:Debug>:ABYSS_PLATFORM_LINUX>
  $<$<CONFIG:Debug>:SFML_STATIC>
  $<$<CONFIG:Debug>:ABYSS_DEBUG>
  $<$<CONFIG:Debug>:WITH_MINIAUDIO>
)
target_link_directories("EngineEditor" PRIVATE
  $<$<CONFIG:Debug>:/home/lekrieg/Documents/Projects/3D2Y/Source/Lib/linuxx86_64Debug>
)
target_link_libraries("EngineEditor"
  $<$<CONFIG:Debug>:AbyssCore>
  $<$<CONFIG:Debug>:sfml-graphics-s-d>
  $<$<CONFIG:Debug>:sfml-audio-s-d>
  $<$<CONFIG:Debug>:sfml-network-s-d>
  $<$<CONFIG:Debug>:sfml-window-s-d>
  $<$<CONFIG:Debug>:sfml-system-s-d>
  $<$<CONFIG:Debug>:yaml-cpp>
  $<$<CONFIG:Debug>:freetype>
  $<$<CONFIG:Debug>:X11>
  $<$<CONFIG:Debug>:Xi>
  $<$<CONFIG:Debug>:Xxf86vm>
  $<$<CONFIG:Debug>:Xrandr>
  $<$<CONFIG:Debug>:Xcursor>
  $<$<CONFIG:Debug>:udev>
  $<$<CONFIG:Debug>:GL>
  $<$<CONFIG:Debug>:openal>
  $<$<CONFIG:Debug>:FLAC>
  $<$<CONFIG:Debug>:ogg>
  $<$<CONFIG:Debug>:vorbis>
  $<$<CONFIG:Debug>:pthread>
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set_target_properties("EngineEditor" PROPERTIES COMPILE_FLAGS "-fPIC ")
endif()
target_compile_options("EngineEditor" PRIVATE
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-O0>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-g>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-O0>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-g>
)
if(CMAKE_BUILD_TYPE STREQUAL Release)
  add_dependencies("EngineEditor"
    "AbyssCore"
  )
  set_target_properties("EngineEditor" PROPERTIES
    OUTPUT_NAME "EngineEditor"
    ARCHIVE_OUTPUT_DIRECTORY "/home/lekrieg/Documents/Projects/3D2Y/EngineEditor/linuxx86_64Release"
    LIBRARY_OUTPUT_DIRECTORY "/home/lekrieg/Documents/Projects/3D2Y/EngineEditor/linuxx86_64Release"
    RUNTIME_OUTPUT_DIRECTORY "/home/lekrieg/Documents/Projects/3D2Y/EngineEditor/linuxx86_64Release"
  )
endif()
target_include_directories("EngineEditor" PRIVATE
  $<$<CONFIG:Release>:/home/lekrieg/Documents/Projects/3D2Y/Source/AbyssCore/src>
  $<$<CONFIG:Release>:/home/lekrieg/Documents/Projects/3D2Y/Source/AbyssCore/3rdParty/SFML-3.0.0/include>
  $<$<CONFIG:Release>:/home/lekrieg/Documents/Projects/3D2Y/Source/AbyssCore/3rdParty/SoLoud/include>
  $<$<CONFIG:Release>:/home/lekrieg/Documents/Projects/3D2Y/Source/AbyssCore/3rdParty/yaml-cpp/include>
)
target_compile_definitions("EngineEditor" PRIVATE
  $<$<CONFIG:Release>:ABYSS_PLATFORM_LINUX>
  $<$<CONFIG:Release>:SFML_STATIC>
  $<$<CONFIG:Release>:ABYSS_RELEASE>
  $<$<CONFIG:Release>:WITH_MINIAUDIO>
)
target_link_directories("EngineEditor" PRIVATE
  $<$<CONFIG:Release>:/home/lekrieg/Documents/Projects/3D2Y/Source/Lib/linuxx86_64Release>
)
target_link_libraries("EngineEditor"
  $<$<CONFIG:Release>:AbyssCore>
  $<$<CONFIG:Release>:sfml-graphics-s>
  $<$<CONFIG:Release>:sfml-audio-s>
  $<$<CONFIG:Release>:sfml-network-s>
  $<$<CONFIG:Release>:sfml-system-s>
  $<$<CONFIG:Release>:sfml-window-s>
  $<$<CONFIG:Release>:yaml-cpp>
  $<$<CONFIG:Release>:freetype>
  $<$<CONFIG:Release>:X11>
  $<$<CONFIG:Release>:Xi>
  $<$<CONFIG:Release>:Xxf86vm>
  $<$<CONFIG:Release>:Xrandr>
  $<$<CONFIG:Release>:Xcursor>
  $<$<CONFIG:Release>:udev>
  $<$<CONFIG:Release>:GL>
  $<$<CONFIG:Release>:openal>
  $<$<CONFIG:Release>:FLAC>
  $<$<CONFIG:Release>:ogg>
  $<$<CONFIG:Release>:vorbis>
  $<$<CONFIG:Release>:pthread>
)
target_compile_options("EngineEditor" PRIVATE
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-O2>
)