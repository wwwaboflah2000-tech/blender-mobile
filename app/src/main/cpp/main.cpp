#include <android/log.h>
#include <android/native_activity.h>
#include <android/native_window.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <thread>
#include <atomic>

#define LOG_TAG "BlenderMobile"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

struct AppContext {
    ANativeWindow* window = nullptr;
    EGLDisplay display = EGL_NO_DISPLAY;
    EGLSurface surface = EGL_NO_SURFACE;
    EGLContext context = EGL_NO_CONTEXT;
    std::atomic<bool> running{false};
    std::thread render_thread;
};

static AppContext g_ctx;

// حلقة الرسم اللحظية (Render Loop - 60 FPS)
void renderLoop() {
    LOGI("🎨 Starting Blender Viewport Render Loop...");

    // 1. إعداد واجهة EGL للرسم على الشاشة
    g_ctx.display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(g_ctx.display, nullptr, nullptr);

    const EGLint attribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_NONE
    };

    EGLConfig config;
    EGLint numConfigs;
    eglChooseConfig(g_ctx.display, attribs, &config, 1, &numConfigs);

    EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };
    g_ctx.context = eglCreateContext(g_ctx.display, config, EGL_NO_CONTEXT, contextAttribs);
    g_ctx.surface = eglCreateWindowSurface(g_ctx.display, config, g_ctx.window, nullptr);

    eglMakeCurrent(g_ctx.display, g_ctx.surface, g_ctx.surface, g_ctx.context);

    // 2. حلقة الرسم المستمرة
    while (g_ctx.running) {
        // تلوين مساحة العمل بلون واجهة بلندر الداكنة (Blender Dark Charcoal)
        glClearColor(0.18f, 0.18f, 0.18f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // هنا يتم تصدير الفريم للشاشة
        eglSwapBuffers(g_ctx.display, g_ctx.surface);
    }

    // تنظيف الموارد عند الإغلاق
    eglMakeCurrent(g_ctx.display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(g_ctx.display, g_ctx.context);
    eglDestroySurface(g_ctx.display, g_ctx.surface);
    eglTerminate(g_ctx.display);
    LOGI("Render Loop Terminated cleanly.");
}

static void onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window) {
    LOGI("🖥️ Android Window Created. Activating 3D Viewport...");
    g_ctx.window = window;
    g_ctx.running = true;
    g_ctx.render_thread = std::thread(renderLoop);
}

static void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window) {
    LOGI("Closing Android Window...");
    g_ctx.running = false;
    if (g_ctx.render_thread.joinable()) {
        g_ctx.render_thread.join();
    }
    g_ctx.window = nullptr;
}

JNIEXPORT void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize) {
    LOGI("🚀 Blender Mobile Engine Started!");
    activity->callbacks->onNativeWindowCreated = onNativeWindowCreated;
    activity->callbacks->onNativeWindowDestroyed = onNativeWindowDestroyed;
}
