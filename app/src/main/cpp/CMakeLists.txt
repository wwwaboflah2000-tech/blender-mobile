cmake_minimum_required(VERSION 3.22.1)
project("blender_core")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# مسارات كود بلندر المصدري الأصلي
set(BLENDER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../blender_source)

include_directories(
    ${BLENDER_DIR}/source/blender/blenlib
    ${BLENDER_DIR}/source/blender/bmesh
    ${BLENDER_DIR}/source/blender/makesdna
    ${BLENDER_DIR}/intern/guardedalloc
)

add_library(blender_core SHARED
    main.cpp
)

find_library(log-lib log)
find_library(android-lib android)

target_link_libraries(blender_core
    ${log-lib}
    ${android-lib}
)
