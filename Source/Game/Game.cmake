add_executable("Game"
  "Game/src/GameApplication.cpp"
  "Game/src/GameApplication.h"
  "Game/src/Main.cpp"
    "Game/src/gameData/GameData.h"
    "Game/src/managers/AudioManager.cpp"
    "Game/src/managers/AudioManager.h"
    "Game/src/managers/GameManager.cpp"
    "Game/src/managers/GameManager.h"
    "Game/src/scenes/PlayScene.cpp"
    "Game/src/scenes/PlayScene.h"
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  add_dependencies("Game"
    "AbyssCore"
  )
  set_target_properties("Game" PROPERTIES
    OUTPUT_NAME "Game"
    ARCHIVE_OUTPUT_DIRECTORY "C:/MyStuff/Projects/3D2Y/Game/windowsx86_64Debug"
    LIBRARY_OUTPUT_DIRECTORY "C:/MyStuff/Projects/3D2Y/Game/windowsx86_64Debug"
    RUNTIME_OUTPUT_DIRECTORY "C:/MyStuff/Projects/3D2Y/Game/windowsx86_64Debug"
  )
endif()
target_include_directories("Game" PRIVATE
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/AbyssCore/src>
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/SFML-3.0.0/include>
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/SoLoud/include>
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/yaml-cpp/include>
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/openal-soft/include>
)
target_compile_definitions("Game" PRIVATE
  $<$<CONFIG:Debug>:ABYSS_PLATFORM_WINDOWS>
  $<$<CONFIG:Debug>:SFML_STATIC>
  $<$<CONFIG:Debug>:ABYSS_DEBUG>
  $<$<CONFIG:Debug>:WITH_MINIAUDIO>
  $<$<CONFIG:Debug>:YAML_CPP_STATIC_DEFINE>
)
target_link_directories("Game" PRIVATE
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/SFML-3.0.0/lib/Debug>
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/yaml-cpp/lib/Debug>
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/Lib/windowsx86_64Debug>
)
target_link_libraries("Game"
  $<$<CONFIG:Debug>:AbyssCore>
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
target_compile_options("Game" PRIVATE
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-O0>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-g>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-O0>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-g>
)
if(CMAKE_BUILD_TYPE STREQUAL Release)
  add_dependencies("Game"
    "AbyssCore"
  )
  set_target_properties("Game" PROPERTIES
    OUTPUT_NAME "Game"
    ARCHIVE_OUTPUT_DIRECTORY "C:/MyStuff/Projects/3D2Y/Game/windowsx86_64Release"
    LIBRARY_OUTPUT_DIRECTORY "C:/MyStuff/Projects/3D2Y/Game/windowsx86_64Release"
    RUNTIME_OUTPUT_DIRECTORY "C:/MyStuff/Projects/3D2Y/Game/windowsx86_64Release"
  )
endif()
target_include_directories("Game" PRIVATE
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/AbyssCore/src>
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/SFML-3.0.0/include>
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/SoLoud/include>
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/yaml-cpp/include>
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/openal-soft/include>
)
target_compile_definitions("Game" PRIVATE
  $<$<CONFIG:Release>:ABYSS_PLATFORM_WINDOWS>
  $<$<CONFIG:Release>:SFML_STATIC>
  $<$<CONFIG:Release>:ABYSS_RELEASE>
  $<$<CONFIG:Release>:WITH_MINIAUDIO>
  $<$<CONFIG:Release>:YAML_CPP_STATIC_DEFINE>
)
target_link_directories("Game" PRIVATE
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/SFML-3.0.0/lib/Release>
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/yaml-cpp/lib/Release>
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/Lib/windowsx86_64Release>
)
target_link_libraries("Game"
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
target_compile_options("Game" PRIVATE
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-O2>
)