#include "godot_engine.hh"
#include "blender_godot_bridge.hh"
#include "godot_viewport_controller.hh"
#include <android/log.h>

#define LOG_TAG "BlenderGodotRenderer"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

static void GODOT_engine_init(void *vedata) {
    LOGI("🚀 Godot Mobile Viewport Engine: INITIALIZED");
    GodotViewportController::resize_viewport(1920, 1080);
}

static void GODOT_engine_draw_scene(void *vedata) {
    // 1. التقاط مصفوفة الكاميرا من بلندر وتمريرها لمتحكم جودوت
    CameraTransform cam;
    GodotViewportController::sync_camera(cam);

    // 2. رسم المشهد وتصديره للشاشة
    GodotViewportController::present_frame();
}

static void GODOT_engine_free(void *vedata) {
    LOGI("Releasing Godot Mobile Renderer resources...");
}

DrawEngineType draw_engine_godot_type = {
    nullptr,
    nullptr,
    "GODOT_MOBILE",
    GODOT_engine_init,
    GODOT_engine_draw_scene,
    GODOT_engine_free
};
