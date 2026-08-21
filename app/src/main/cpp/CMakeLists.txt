cmake_minimum_required(VERSION 3.22.1)
project("blender_core")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    include
    engine
)

add_library(blender_core SHARED
    main.cpp
    engine/godot_engine.cc
    engine/blender_godot_bridge.cc
    engine/godot_viewport_controller.cc
)

find_library(log-lib log)
find_library(android-lib android)
find_library(egl-lib EGL)
find_library(gles-lib GLESv3)

target_link_libraries(blender_core
    ${log-lib}
    ${android-lib}
    ${egl-lib}
    ${gles-lib}
)
