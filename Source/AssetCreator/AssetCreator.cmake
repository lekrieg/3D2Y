add_executable("AssetCreator"
  "AssetCreator/src/Application.cpp"
  "AssetCreator/src/Application.h"
    "AssetCreator/src/Archiver/Defines.h"
    "AssetCreator/src/Archiver/EndianOrderHelper.cpp"
    "AssetCreator/src/Archiver/EndianOrderHelper.h"
    "AssetCreator/src/Archiver/FileArchiverHelper.cpp"
    "AssetCreator/src/Archiver/FileArchiverHelper.h"
    "AssetCreator/src/Archiver/FileHelper.cpp"
    "AssetCreator/src/Archiver/FileHelper.h"
    "AssetCreator/src/AssetInfo/Animation.h"
    "AssetCreator/src/AssetInfo/AudioAsset.h"
    "AssetCreator/src/AssetInfo/BaseAsset.cpp"
    "AssetCreator/src/AssetInfo/BaseAsset.h"
    "AssetCreator/src/AssetInfo/FontAsset.h"
    "AssetCreator/src/AssetInfo/Frame.h"
    "AssetCreator/src/AssetInfo/SpriteAsset.cpp"
    "AssetCreator/src/AssetInfo/SpriteAsset.h"
  "AssetCreator/src/Logger.h"
    "AssetCreator/src/Serialization/Serializer.cpp"
    "AssetCreator/src/Serialization/Serializer.h"
    "AssetCreator/src/Serialization/Yaml.h"
    "AssetCreator/src/UIStuff/ImGuiArea.h"
    "AssetCreator/src/UIStuff/LeftArea.cpp"
    "AssetCreator/src/UIStuff/LeftArea.h"
    "AssetCreator/src/UIStuff/RightArea.cpp"
    "AssetCreator/src/UIStuff/RightArea.h"
    "AssetCreator/src/Utils/FileDialogType.h"
    "AssetCreator/src/Utils/SpriteType.cpp"
    "AssetCreator/src/Utils/SpriteType.h"
    "AssetCreator/src/imgui/imconfig-SFML.h"
    "AssetCreator/src/imgui/imconfig.h"
    "AssetCreator/src/imgui/imfilebrowser.h"
    "AssetCreator/src/imgui/imgui-SFML.cpp"
    "AssetCreator/src/imgui/imgui-SFML.h"
    "AssetCreator/src/imgui/imgui-SFML_export.h"
    "AssetCreator/src/imgui/imgui.cpp"
    "AssetCreator/src/imgui/imgui.h"
    "AssetCreator/src/imgui/imgui_demo.cpp"
    "AssetCreator/src/imgui/imgui_draw.cpp"
    "AssetCreator/src/imgui/imgui_internal.h"
    "AssetCreator/src/imgui/imgui_tables.cpp"
    "AssetCreator/src/imgui/imgui_widgets.cpp"
    "AssetCreator/src/imgui/imstb_rectpack.h"
    "AssetCreator/src/imgui/imstb_textedit.h"
    "AssetCreator/src/imgui/imstb_truetype.h"
  "AssetCreator/src/main.cpp"
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set_target_properties("AssetCreator" PROPERTIES
    OUTPUT_NAME "AssetCreator"
    ARCHIVE_OUTPUT_DIRECTORY "C:/MyStuff/Projects/3D2Y/AssetCreator/windowsx86_64Debug"
    LIBRARY_OUTPUT_DIRECTORY "C:/MyStuff/Projects/3D2Y/AssetCreator/windowsx86_64Debug"
    RUNTIME_OUTPUT_DIRECTORY "C:/MyStuff/Projects/3D2Y/AssetCreator/windowsx86_64Debug"
  )
endif()
target_include_directories("AssetCreator" PRIVATE
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/SFML-3.0.0/include>
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/SoLoud/include>
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/yaml-cpp/include>
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/openal-soft/include>
)
target_compile_definitions("AssetCreator" PRIVATE
  $<$<CONFIG:Debug>:ABYSS_PLATFORM_WINDOWS>
  $<$<CONFIG:Debug>:SFML_STATIC>
  $<$<CONFIG:Debug>:ABYSS_DEBUG>
  $<$<CONFIG:Debug>:WITH_MINIAUDIO>
  $<$<CONFIG:Debug>:YAML_CPP_STATIC_DEFINE>
)
target_link_directories("AssetCreator" PRIVATE
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/SFML-3.0.0/lib/Debug>
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/yaml-cpp/lib/Debug>
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/Lib/windowsx86_64Debug>
)
target_link_libraries("AssetCreator"
  $<$<CONFIG:Debug>:sfml-graphics-s-d>
  $<$<CONFIG:Debug>:sfml-audio-s-d>
  $<$<CONFIG:Debug>:sfml-network-s-d>
  $<$<CONFIG:Debug>:sfml-window-s-d>
  $<$<CONFIG:Debug>:sfml-system-s-d>
  $<$<CONFIG:Debug>:yaml-cpp>
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
target_compile_options("AssetCreator" PRIVATE
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-O0>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-g>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-O0>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-g>
)
if(CMAKE_BUILD_TYPE STREQUAL Release)
  set_target_properties("AssetCreator" PROPERTIES
    OUTPUT_NAME "AssetCreator"
    ARCHIVE_OUTPUT_DIRECTORY "C:/MyStuff/Projects/3D2Y/AssetCreator/windowsx86_64Release"
    LIBRARY_OUTPUT_DIRECTORY "C:/MyStuff/Projects/3D2Y/AssetCreator/windowsx86_64Release"
    RUNTIME_OUTPUT_DIRECTORY "C:/MyStuff/Projects/3D2Y/AssetCreator/windowsx86_64Release"
  )
endif()
target_include_directories("AssetCreator" PRIVATE
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/SFML-3.0.0/include>
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/SoLoud/include>
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/yaml-cpp/include>
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/openal-soft/include>
)
target_compile_definitions("AssetCreator" PRIVATE
  $<$<CONFIG:Release>:ABYSS_PLATFORM_WINDOWS>
  $<$<CONFIG:Release>:SFML_STATIC>
  $<$<CONFIG:Release>:ABYSS_RELEASE>
  $<$<CONFIG:Release>:WITH_MINIAUDIO>
  $<$<CONFIG:Release>:YAML_CPP_STATIC_DEFINE>
)
target_link_directories("AssetCreator" PRIVATE
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/SFML-3.0.0/lib/Release>
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/yaml-cpp/lib/Release>
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/Lib/windowsx86_64Release>
)
target_link_libraries("AssetCreator"
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
target_compile_options("AssetCreator" PRIVATE
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-O2>
)