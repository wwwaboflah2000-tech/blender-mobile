#include "godot_engine.hh"
#include "blender_godot_bridge.hh"
#include "godot_viewport_controller.hh"
#include <android/log.h>

#define LOG_TAG "BlenderGodotRenderer"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

static void GODOT_engine_init(void *vedata) {
    LOGI("🚀 Godot Mobile Viewport Engine: INITIALIZED (Vulkan Native Mode)");
    GodotViewportController::resize_viewport(1920, 1080);
}

static void GODOT_engine_draw_scene(void *vedata) {
    CameraTransform cam;
    GodotViewportController::sync_camera(cam);
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

void DRW_engine_register(DrawEngineType *engine_type) {
    LOGI("Registered Draw Engine: %s", engine_type ? engine_type->name : "Unknown");
}
