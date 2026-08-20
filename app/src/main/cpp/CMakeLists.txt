cmake_minimum_required(VERSION 3.22.1)
project("blender_core")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(blender_core SHARED
    main.cpp
)

find_library(log-lib log)
find_library(android-lib android)

target_link_libraries(blender_core
    ${log-lib}
    ${android-lib}
)
