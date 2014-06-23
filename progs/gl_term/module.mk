local_dir  := progs/gl_term
local_src  := $(wildcard $(local_dir)/*.cpp)
local_objs := $(subst .cpp,.o,$(local_src))

sources    += $(local_src)
term_objects += $(local_objs)

