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
    ARCHIVE_OUTPUT_DIRECTORY "C:/MyStuff/Projects/3D2Y/EngineEditor/windowsx86_64Debug"
    LIBRARY_OUTPUT_DIRECTORY "C:/MyStuff/Projects/3D2Y/EngineEditor/windowsx86_64Debug"
    RUNTIME_OUTPUT_DIRECTORY "C:/MyStuff/Projects/3D2Y/EngineEditor/windowsx86_64Debug"
  )
endif()
target_include_directories("EngineEditor" PRIVATE
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/AbyssCore/src>
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/SFML-3.0.0/include>
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/SoLoud/include>
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/yaml-cpp/include>
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/openal-soft/include>
)
target_compile_definitions("EngineEditor" PRIVATE
  $<$<CONFIG:Debug>:ABYSS_PLATFORM_WINDOWS>
  $<$<CONFIG:Debug>:SFML_STATIC>
  $<$<CONFIG:Debug>:ABYSS_DEBUG>
  $<$<CONFIG:Debug>:WITH_MINIAUDIO>
  $<$<CONFIG:Debug>:YAML_CPP_STATIC_DEFINE>
)
target_link_directories("EngineEditor" PRIVATE
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/SFML-3.0.0/lib/Debug>
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/yaml-cpp/lib/Debug>
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/Lib/windowsx86_64Debug>
)
target_link_libraries("EngineEditor"
  $<$<CONFIG:Debug>:AbyssCore>
  $<$<CONFIG:Debug>:sfml-graphics-s-d>
  $<$<CONFIG:Debug>:sfml-audio-s-d>
  $<$<CONFIG:Debug>:sfml-network-s-d>
  $<$<CONFIG:Debug>:sfml-window-s-d>
  $<$<CONFIG:Debug>:sfml-system-s-d>
  $<$<CONFIG:Debug>:yaml-cppd>
  $<$<CONFIG:Debug>:freetyped>
  $<$<CONFIG:Debug>:opengl32>
  $<$<CONFIG:Debug>:winmm>
  $<$<CONFIG:Debug>:gdi32>
  $<$<CONFIG:Debug>:FLACd>
  $<$<CONFIG:Debug>:oggd>
  $<$<CONFIG:Debug>:vorbisd>
  $<$<CONFIG:Debug>:vorbisencd>
  $<$<CONFIG:Debug>:vorbisfiled>
  $<$<CONFIG:Debug>:ws2_32>
)
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
    ARCHIVE_OUTPUT_DIRECTORY "C:/MyStuff/Projects/3D2Y/EngineEditor/windowsx86_64Release"
    LIBRARY_OUTPUT_DIRECTORY "C:/MyStuff/Projects/3D2Y/EngineEditor/windowsx86_64Release"
    RUNTIME_OUTPUT_DIRECTORY "C:/MyStuff/Projects/3D2Y/EngineEditor/windowsx86_64Release"
  )
endif()
target_include_directories("EngineEditor" PRIVATE
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/AbyssCore/src>
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/SFML-3.0.0/include>
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/SoLoud/include>
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/yaml-cpp/include>
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/openal-soft/include>
)
target_compile_definitions("EngineEditor" PRIVATE
  $<$<CONFIG:Release>:ABYSS_PLATFORM_WINDOWS>
  $<$<CONFIG:Release>:SFML_STATIC>
  $<$<CONFIG:Release>:ABYSS_RELEASE>
  $<$<CONFIG:Release>:WITH_MINIAUDIO>
  $<$<CONFIG:Release>:YAML_CPP_STATIC_DEFINE>
)
target_link_directories("EngineEditor" PRIVATE
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/SFML-3.0.0/lib/Release>
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/yaml-cpp/lib/Release>
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/Lib/windowsx86_64Release>
)
target_link_libraries("EngineEditor"
  $<$<CONFIG:Release>:AbyssCore>
  $<$<CONFIG:Release>:sfml-graphics-s>
  $<$<CONFIG:Release>:sfml-audio-s>
  $<$<CONFIG:Release>:sfml-network-s>
  $<$<CONFIG:Release>:sfml-window-s>
  $<$<CONFIG:Release>:sfml-system-s>
  $<$<CONFIG:Release>:yaml-cpp>
  $<$<CONFIG:Release>:freetype>
  $<$<CONFIG:Release>:opengl32>
  $<$<CONFIG:Release>:winmm>
  $<$<CONFIG:Release>:gdi32>
  $<$<CONFIG:Release>:FLAC>
  $<$<CONFIG:Release>:ogg>
  $<$<CONFIG:Release>:vorbis>
  $<$<CONFIG:Release>:vorbisenc>
  $<$<CONFIG:Release>:vorbisfile>
  $<$<CONFIG:Release>:ws2_32>
)
target_compile_options("EngineEditor" PRIVATE
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-O2>
)