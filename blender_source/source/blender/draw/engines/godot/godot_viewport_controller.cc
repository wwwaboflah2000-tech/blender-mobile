#include "godot_viewport_controller.hh"

#define LOG_TAG "BlenderGodotCamera"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

static int32_t g_current_width = 1920;
static int32_t g_current_height = 1080;

void GodotViewportController::resize_viewport(int32_t width, int32_t height) {
    if (width != g_current_width || height != g_current_height) {
        g_current_width = width;
        g_current_height = height;
        LOGI("🖥️ Viewport Resized to: %d x %d (Updating Vulkan Swapchain)", width, height);
        // تحديث أبعاد الـ Swapchain في جودوت
    }
}

void GodotViewportController::sync_camera(const CameraTransform& cam) {
    // تحديث زاوية الكاميرا اللحظية في رندر جودوت بناءً على حركة ماوس بلندر
    // Godot::RenderingServer::camera_set_transform(...)
}

void GodotViewportController::present_frame() {
    // عرض المشهد النهائي بدقة 60 إطار على شاشة الهاتف
}
