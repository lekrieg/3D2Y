add_library("AbyssCore" STATIC
  "AbyssCore/src/Action.h"
  "AbyssCore/src/Animation.h"
  "AbyssCore/src/Application.h"
  "AbyssCore/src/Assets.cpp"
  "AbyssCore/src/Assets.h"
  "AbyssCore/src/ComponentArray.h"
  "AbyssCore/src/ComponentManager.h"
  "AbyssCore/src/CustomSprite.cpp"
  "AbyssCore/src/CustomSprite.h"
  "AbyssCore/src/Entity.h"
  "AbyssCore/src/EntityManager.cpp"
  "AbyssCore/src/EntityManager.h"
  "AbyssCore/src/Enums.cpp"
  "AbyssCore/src/Enums.h"
  "AbyssCore/src/FileData.h"
  "AbyssCore/src/Frame.h"
  "AbyssCore/src/Logger.h"
    "AbyssCore/src/ParticleSystem/ParticleSystem.h"
  "AbyssCore/src/Physics.h"
  "AbyssCore/src/Scene.cpp"
  "AbyssCore/src/Scene.h"
    "AbyssCore/src/archiver/Defines.h"
    "AbyssCore/src/archiver/EndianOrderHelper.cpp"
    "AbyssCore/src/archiver/EndianOrderHelper.h"
    "AbyssCore/src/archiver/FileArchiverHelper.cpp"
    "AbyssCore/src/archiver/FileArchiverHelper.h"
    "AbyssCore/src/archiver/FileHelper.cpp"
    "AbyssCore/src/archiver/FileHelper.h"
    "AbyssCore/src/assets/AudioAsset.h"
    "AbyssCore/src/assets/BaseAsset.h"
    "AbyssCore/src/assets/FontAsset.h"
    "AbyssCore/src/assets/SpriteAsset.h"
    "AbyssCore/src/components/Anim.h"
    "AbyssCore/src/components/BoundingBox.h"
    "AbyssCore/src/components/CircleCollision.h"
    "AbyssCore/src/components/Component.h"
    "AbyssCore/src/components/FollowPlayer.h"
    "AbyssCore/src/components/Gravity.h"
    "AbyssCore/src/components/Input.h"
    "AbyssCore/src/components/Jump.h"
    "AbyssCore/src/components/Lifespan.h"
    "AbyssCore/src/components/Name.h"
    "AbyssCore/src/components/Patrol.h"
    "AbyssCore/src/components/Score.h"
    "AbyssCore/src/components/Shape.h"
    "AbyssCore/src/components/State.h"
    "AbyssCore/src/components/Transform.h"
    "AbyssCore/src/math/MathFunc.h"
    "AbyssCore/src/math/Vectors.h"
    "AbyssCore/src/profiler/Profiler.h"
    "AbyssCore/src/serialization/Serializer.cpp"
    "AbyssCore/src/serialization/Serializer.h"
    "AbyssCore/src/serialization/Yaml.h"
    "AbyssCore/src/shaders/ShaderExample.cpp"
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set_target_properties("AbyssCore" PROPERTIES
    OUTPUT_NAME "AbyssCore"
    ARCHIVE_OUTPUT_DIRECTORY "C:/MyStuff/Projects/3D2Y/Source/Lib/windowsx86_64Debug"
    LIBRARY_OUTPUT_DIRECTORY "C:/MyStuff/Projects/3D2Y/Source/Lib/windowsx86_64Debug"
    RUNTIME_OUTPUT_DIRECTORY "C:/MyStuff/Projects/3D2Y/Source/Lib/windowsx86_64Debug"
  )
endif()
target_include_directories("AbyssCore" PRIVATE
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/SFML-3.0.0/include>
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/SoLoud/include>
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/yaml-cpp/include>
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/openal-soft/include>
)
target_compile_definitions("AbyssCore" PRIVATE
  $<$<CONFIG:Debug>:ABYSS_PLATFORM_WINDOWS>
  $<$<CONFIG:Debug>:SFML_STATIC>
  $<$<CONFIG:Debug>:ABYSS_DEBUG>
  $<$<CONFIG:Debug>:WITH_MINIAUDIO>
  $<$<CONFIG:Debug>:YAML_CPP_STATIC_DEFINE>
)
target_link_directories("AbyssCore" PRIVATE
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/SFML-3.0.0/lib/Debug>
  $<$<CONFIG:Debug>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/yaml-cpp/lib/Debug>
)
target_link_libraries("AbyssCore"
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
target_compile_options("AbyssCore" PRIVATE
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-O0>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-g>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-O0>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-g>
)
if(CMAKE_BUILD_TYPE STREQUAL Release)
  set_target_properties("AbyssCore" PROPERTIES
    OUTPUT_NAME "AbyssCore"
    ARCHIVE_OUTPUT_DIRECTORY "C:/MyStuff/Projects/3D2Y/Source/Lib/windowsx86_64Release"
    LIBRARY_OUTPUT_DIRECTORY "C:/MyStuff/Projects/3D2Y/Source/Lib/windowsx86_64Release"
    RUNTIME_OUTPUT_DIRECTORY "C:/MyStuff/Projects/3D2Y/Source/Lib/windowsx86_64Release"
  )
endif()
target_include_directories("AbyssCore" PRIVATE
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/SFML-3.0.0/include>
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/SoLoud/include>
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/yaml-cpp/include>
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/openal-soft/include>
)
target_compile_definitions("AbyssCore" PRIVATE
  $<$<CONFIG:Release>:ABYSS_PLATFORM_WINDOWS>
  $<$<CONFIG:Release>:SFML_STATIC>
  $<$<CONFIG:Release>:ABYSS_RELEASE>
  $<$<CONFIG:Release>:WITH_MINIAUDIO>
  $<$<CONFIG:Release>:YAML_CPP_STATIC_DEFINE>
)
target_link_directories("AbyssCore" PRIVATE
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/SFML-3.0.0/lib/Release>
  $<$<CONFIG:Release>:C:/MyStuff/Projects/3D2Y/Source/3rdParty/yaml-cpp/lib/Release>
)
target_link_libraries("AbyssCore"
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
target_compile_options("AbyssCore" PRIVATE
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-O2>
)