#pragma once

#include <vector>
#include <string>
#include <cstdint>

/* هياكل بيانات لنقل المجسمات من بلندر إلى رندر جودوت */
struct VertexData {
    float x, y, z;       // الموقع
    float nx, ny, nz;    // اتجاه السطح (Normal)
    float u, v;          // إحداثيات الـ UV
};

struct MaterialData {
    float r = 0.8f, g = 0.8f, b = 0.8f; // Base Color
    float roughness = 0.5f;               // اللمعان
    float metallic = 0.0f;                // المعدنية
    float emission = 0.0f;                // التوهج
};

class BlenderGodotBridge {
public:
    // تحويل مضلعات بلندر إلى مصفوفات يفهمها رندر جودوت Vulkan
    static void upload_mesh_to_godot(const std::vector<VertexData>& vertices, const std::vector<uint32_t>& indices);

    // ترجمة نودات بلندر Principled BSDF إلى كود شيدر جودوت المخصص للموبايل
    static std::string generate_godot_spatial_shader(const MaterialData& mat);
};
