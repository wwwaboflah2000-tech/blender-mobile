#pragma once
#include <cstdint>

struct CameraTransform {
    float view_matrix[16];
    float projection_matrix[16];
};

class GodotViewportController {
public:
    static void resize_viewport(int32_t width, int32_t height);
    static void sync_camera(const CameraTransform& cam);
    static void present_frame();
};
