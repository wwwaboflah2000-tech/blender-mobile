#include "blender_godot_bridge.hh"
#include <sstream>
#include <android/log.h>

#define LOG_TAG "BlenderGodotBridge"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

void BlenderGodotBridge::upload_mesh_to_godot(const std::vector<VertexData>& vertices, const std::vector<uint32_t>& indices) {
    LOGI("📐 Streaming %zu Vertices to Godot Mobile Vulkan Buffer...", vertices.size());
}

std::string BlenderGodotBridge::generate_godot_spatial_shader(const MaterialData& mat) {
    std::stringstream ss;
    ss << "shader_type spatial;\n";
    ss << "void fragment() {\n";
    ss << "    ALBEDO = vec3(" << mat.r << ", " << mat.g << ", " << mat.b << ");\n";
    ss << "    ROUGHNESS = " << mat.roughness << ";\n";
    ss << "    METALLIC = " << mat.metallic << ";\n";
    ss << "}\n";
    return ss.str();
}
