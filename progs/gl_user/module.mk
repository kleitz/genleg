local_dir  := progs/gl_user
local_src  := $(wildcard $(local_dir)/*.cpp)
local_objs := $(subst .cpp,.o,$(local_src))

sources    += $(local_src)
user_objects += $(local_objs)

