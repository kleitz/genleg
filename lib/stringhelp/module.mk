local_dir := lib/stringhelp
local_lib := $(local_dir)/libstringhelp.a
local_src := $(wildcard $(local_dir)/*.cpp)
local_objs := $(subst .cpp,.o,$(local_src))

libraries += $(local_lib)
sources   += $(local_src)

$(local_lib): $(local_objs)
	@echo "Building string helper library..."
	@$(AR) $(ARFLAGS) $@ $^

