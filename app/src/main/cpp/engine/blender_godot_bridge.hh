#pragma once
#include <vector>
#include <string>
#include <cstdint>

struct VertexData {
    float x, y, z;
    float nx, ny, nz;
    float u, v;
};

struct MaterialData {
    float r = 0.8f, g = 0.8f, b = 0.8f;
    float roughness = 0.5f;
    float metallic = 0.0f;
    float emission = 0.0f;
};

class BlenderGodotBridge {
public:
    static void upload_mesh_to_godot(const std::vector<VertexData>& vertices, const std::vector<uint32_t>& indices);
    static std::string generate_godot_spatial_shader(const MaterialData& mat);
};
