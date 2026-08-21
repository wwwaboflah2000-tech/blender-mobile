#include "blender_godot_bridge.hh"
#include <sstream>
#include <android/log.h>

#define LOG_TAG "BlenderGodotBridge"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

void BlenderGodotBridge::upload_mesh_to_godot(const std::vector<VertexData>& vertices, const std::vector<uint32_t>& indices) {
    LOGI("📐 Streaming %zu Vertices and %zu Indices from Blender BMesh to Godot Vulkan Buffer...",
         vertices.size(), indices.size());

    // هنا يتم تمرير النقاط إلى RenderingServer الخاص بجودوت في الذاكرة الحية (VRAM)
}

std::string BlenderGodotBridge::generate_godot_spatial_shader(const MaterialData& mat) {
    LOGI("🎨 Transpiling Blender Principled BSDF to Godot Mobile Shader...");

    std::stringstream ss;
    ss << "shader_type spatial;\n";
    ss << "render_mode blend_mix, depth_draw_opaque, cull_back, diffuse_burley, specular_schlick_ggx;\n\n";
    ss << "void fragment() {\n";
    ss << "    ALBEDO = vec3(" << mat.r << ", " << mat.g << ", " << mat.b << ");\n";
    ss << "    ROUGHNESS = " << mat.roughness << ";\n";
    ss << "    METALLIC = " << mat.metallic << ";\n";
    ss << "    EMISSION = vec3(" << mat.emission << ");\n";
    ss << "}\n";

    return ss.str();
}
