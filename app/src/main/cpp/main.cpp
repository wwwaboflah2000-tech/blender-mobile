#include <android/log.h>
#include <android/native_activity.h>

#define LOG_TAG "BlenderMobile"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

static void onStart(ANativeActivity* activity) {
    LOGI("==================================================");
    LOGI("🚀 Blender Mobile Engine Started Successfully!");
    LOGI("📱 Running on Android Native C++ Core (ARM64)");
    LOGI("==================================================");
}

JNIEXPORT void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize) {
    LOGI("🚀 Initializing Blender Mobile Native Core...");
    activity->callbacks->onStart = onStart;
}
