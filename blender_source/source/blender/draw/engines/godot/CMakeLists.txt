set(SRC
  godot_engine.cc
  godot_engine.hh
  blender_godot_bridge.cc
  blender_godot_bridge.hh
)

set(INC
  ../../
  ../../../../intern/guardedalloc
)

blender_add_lib(bf_draw_engine_godot "${SRC}" "${INC}" "${INC_SYS}" "${LIB}")
