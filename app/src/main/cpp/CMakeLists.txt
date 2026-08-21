cmake_minimum_required(VERSION 3.22.1)
project("blender_core")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# مسار مجلد كود بلندر الأصلي
set(BLENDER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../blender_source)

# تضمين ترويسات ومكتبات بلندر ورندر جودوت
include_directories(
    ${BLENDER_DIR}/source/blender/blenlib
    ${BLENDER_DIR}/source/blender/bmesh
    ${BLENDER_DIR}/source/blender/makesdna
    ${BLENDER_DIR}/source/blender/draw
    ${BLENDER_DIR}/source/blender/draw/engines/godot
    ${BLENDER_DIR}/intern/guardedalloc
    ${BLENDER_DIR}/intern/ghost
)

# تجميع ملفات الربط الأساسية ومحرك جودوت
add_library(blender_core SHARED
    main.cpp
    ${BLENDER_DIR}/source/blender/draw/engines/godot/godot_engine.cc
    ${BLENDER_DIR}/source/blender/draw/engines/godot/blender_godot_bridge.cc
    ${BLENDER_DIR}/source/blender/draw/engines/godot/godot_viewport_controller.cc
)

# ربط مكتبات الأندرويد الرسمية (الماوس والشاشة وVulkan)
find_library(log-lib log)
find_library(android-lib android)
find_library(vulkan-lib vulkan)

target_link_libraries(blender_core
    ${log-lib}
    ${android-lib}
    ${vulkan-lib}
)
