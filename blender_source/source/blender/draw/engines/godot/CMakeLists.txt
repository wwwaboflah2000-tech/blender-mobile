set(SRC
  godot_engine.cc
  godot_engine.hh
)

set(INC
  ../../
  ../../../../intern/guardedalloc
)

blender_add_lib(bf_draw_engine_godot "${SRC}" "${INC}" "${INC_SYS}" "${LIB}")
