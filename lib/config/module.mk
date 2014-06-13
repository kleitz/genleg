local_dir := lib/config
local_lib := $(local_dir)/libconfig.a
local_src := $(wildcard $(local_dir)/*.cpp)
local_objs := $(subst .cpp,.o,$(local_src))

libraries += $(local_lib)
sources   += $(local_src)

$(local_lib): $(local_objs)
	@echo "Building configuration library..."
	@$(AR) $(ARFLAGS) $@ $^

