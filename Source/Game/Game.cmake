add_executable("Game"
  "Game/src/GameApplication.cpp"
  "Game/src/GameApplication.h"
  "Game/src/Main.cpp"
    "Game/src/managers/AudioManager.cpp"
    "Game/src/managers/AudioManager.h"
    "Game/src/managers/GameManager.cpp"
    "Game/src/managers/GameManager.h"
    "Game/src/scenes/MenuScene.cpp"
    "Game/src/scenes/MenuScene.h"
    "Game/src/scenes/PlayScene.cpp"
    "Game/src/scenes/PlayScene.h"
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  add_dependencies("Game"
    "AbyssCore"
  )
  set_target_properties("Game" PROPERTIES
    OUTPUT_NAME "Game"
    ARCHIVE_OUTPUT_DIRECTORY "/home/lekrieg/Documents/Projects/3D2Y/Game/linuxx86_64Debug"
    LIBRARY_OUTPUT_DIRECTORY "/home/lekrieg/Documents/Projects/3D2Y/Game/linuxx86_64Debug"
    RUNTIME_OUTPUT_DIRECTORY "/home/lekrieg/Documents/Projects/3D2Y/Game/linuxx86_64Debug"
  )
endif()
target_include_directories("Game" PRIVATE
  $<$<CONFIG:Debug>:/home/lekrieg/Documents/Projects/3D2Y/Source/AbyssCore/src>
  $<$<CONFIG:Debug>:/home/lekrieg/Documents/Projects/3D2Y/Source/AbyssCore/3rdParty/SFML-3.0.0/include>
  $<$<CONFIG:Debug>:/home/lekrieg/Documents/Projects/3D2Y/Source/AbyssCore/3rdParty/SoLoud/include>
  $<$<CONFIG:Debug>:/home/lekrieg/Documents/Projects/3D2Y/Source/AbyssCore/3rdParty/yaml-cpp/include>
)
target_compile_definitions("Game" PRIVATE
  $<$<CONFIG:Debug>:ABYSS_PLATFORM_LINUX>
  $<$<CONFIG:Debug>:SFML_STATIC>
  $<$<CONFIG:Debug>:ABYSS_DEBUG>
  $<$<CONFIG:Debug>:WITH_MINIAUDIO>
)
target_link_directories("Game" PRIVATE
  $<$<CONFIG:Debug>:/home/lekrieg/Documents/Projects/3D2Y/Source/Lib/linuxx86_64Debug>
)
target_link_libraries("Game"
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
  set_target_properties("Game" PROPERTIES COMPILE_FLAGS "-fPIC ")
endif()
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
    ARCHIVE_OUTPUT_DIRECTORY "/home/lekrieg/Documents/Projects/3D2Y/Game/linuxx86_64Release"
    LIBRARY_OUTPUT_DIRECTORY "/home/lekrieg/Documents/Projects/3D2Y/Game/linuxx86_64Release"
    RUNTIME_OUTPUT_DIRECTORY "/home/lekrieg/Documents/Projects/3D2Y/Game/linuxx86_64Release"
  )
endif()
target_include_directories("Game" PRIVATE
  $<$<CONFIG:Release>:/home/lekrieg/Documents/Projects/3D2Y/Source/AbyssCore/src>
  $<$<CONFIG:Release>:/home/lekrieg/Documents/Projects/3D2Y/Source/AbyssCore/3rdParty/SFML-3.0.0/include>
  $<$<CONFIG:Release>:/home/lekrieg/Documents/Projects/3D2Y/Source/AbyssCore/3rdParty/SoLoud/include>
  $<$<CONFIG:Release>:/home/lekrieg/Documents/Projects/3D2Y/Source/AbyssCore/3rdParty/yaml-cpp/include>
)
target_compile_definitions("Game" PRIVATE
  $<$<CONFIG:Release>:ABYSS_PLATFORM_LINUX>
  $<$<CONFIG:Release>:SFML_STATIC>
  $<$<CONFIG:Release>:ABYSS_RELEASE>
  $<$<CONFIG:Release>:WITH_MINIAUDIO>
)
target_link_directories("Game" PRIVATE
  $<$<CONFIG:Release>:/home/lekrieg/Documents/Projects/3D2Y/Source/Lib/linuxx86_64Release>
)
target_link_libraries("Game"
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
target_compile_options("Game" PRIVATE
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-O2>
)