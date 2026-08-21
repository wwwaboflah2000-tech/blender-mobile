#include "godot_engine.hh"
#include "blender_godot_bridge.hh"
#include "godot_viewport_controller.hh"
#include "cube_mesh.hh"
#include <android/log.h>
#include <vector>

#define LOG_TAG "BlenderGodotRenderer"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

static std::vector<VertexData> g_cube_vertices;
static std::vector<uint32_t> g_cube_indices;
static MaterialData g_blender_gray_material;

static void GODOT_engine_init(void *vedata) {
    LOGI("==================================================");
    LOGI("🚀 Initializing Blender Default Scene in Godot Viewport...");
    
    // 1. إنشاء مضلعات مكعب بلندر الشهير
    BlenderCubeGenerator::generate_default_cube(g_cube_vertices, g_cube_indices);
    LOGI("🧊 Blender Default Cube Created: %zu Vertices, %zu Triangles", 
         g_cube_vertices.size(), g_cube_indices.size() / 3);

    // 2. إعداد خامة بلندر الرمادية الأصلية (Principled BSDF Gray)
    g_blender_gray_material.r = 0.8f;
    g_blender_gray_material.g = 0.8f;
    g_blender_gray_material.b = 0.8f;
    g_blender_gray_material.roughness = 0.5f;
    g_blender_gray_material.metallic = 0.0f;

    // 3. رفع المجسم والماتريال إلى رندر جودوت Vulkan
    BlenderGodotBridge::upload_mesh_to_godot(g_cube_vertices, g_cube_indices);
    std::string shader_code = BlenderGodotBridge::generate_godot_spatial_shader(g_blender_gray_material);
    
    LOGI("🎨 Blender Studio Material Compiled Successfully!");
    GodotViewportController::resize_viewport(1920, 1080);
}

static void GODOT_engine_draw_scene(void *vedata) {
    CameraTransform cam;
    GodotViewportController::sync_camera(cam);
    GodotViewportController::present_frame();
}

static void GODOT_engine_free(void *vedata) {
    LOGI("Releasing Default Cube resources...");
    g_cube_vertices.clear();
    g_cube_indices.clear();
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
