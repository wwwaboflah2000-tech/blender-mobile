#pragma once
#include "../engines/godot/godot_engine.hh"

/* دالة تسجيل محرك جودوت داخل نواة بلندر */
static inline void DRW_engine_register_godot() {
    DRW_engine_register(&draw_engine_godot_type);
}
