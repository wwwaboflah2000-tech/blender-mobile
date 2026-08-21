#pragma once

#include <cstdint>
#include <android/log.h>

struct CameraTransform {
    float view_matrix[16];       // مصفوفة موقع وزاوية الكاميرا
    float projection_matrix[16]; // مصفوفة المنظور (FOV / Perspective)
    float fov = 50.0f;
    float near_clip = 0.1f;
    float far_clip = 1000.0f;
};

class GodotViewportController {
public:
    // تحديث أبعاد نافذة العرض عند تدوير الهاتف أو تغيير حجم النافذة
    static void resize_viewport(int32_t width, int32_t height);

    // مزامنة كاميرا بلندر مع كاميرا جودوت ثلاثية الأبعاد
    static void sync_camera(const CameraTransform& cam);

    // رسم الإطار النهائي على شاشة الأندرويد
    static void present_frame();
};
