local_dir  := progs/gl_report
local_src  := $(wildcard $(local_dir)/*.cpp)
local_objs := $(subst .cpp,.o,$(local_src))

sources    += $(local_src)
report_objects += $(local_objs)

