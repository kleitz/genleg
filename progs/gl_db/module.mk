local_dir  := progs/gl_db
local_src  := $(wildcard $(local_dir)/*.cpp)
local_objs := $(subst .cpp,.o,$(local_src))

sources    += $(local_src)
database_objects += $(local_objs)

