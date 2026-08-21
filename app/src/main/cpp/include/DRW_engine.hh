#pragma once
#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

struct DrawEngineType {
    void *draw_engine;
    void *draw_data;
    const char *name;
    void (*engine_init)(void *vedata);
    void (*draw_scene)(void *vedata);
    void (*engine_free)(void *vedata);
};

void DRW_engine_register(DrawEngineType *engine_type);

#ifdef __cplusplus
}
#endif
