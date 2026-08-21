#include "godot_viewport_controller.hh"
#include <android/log.h>

#define LOG_TAG "BlenderGodotCamera"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

void GodotViewportController::resize_viewport(int32_t width, int32_t height) {
    LOGI("🖥️ Viewport Size: %d x %d (Vulkan Active)", width, height);
}

void GodotViewportController::sync_camera(const CameraTransform& cam) {
    // مزامنة زوايا كاميرا الماوس
}

void GodotViewportController::present_frame() {
    // رسم الفريم على الشاشة
}
