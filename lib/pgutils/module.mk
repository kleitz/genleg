local_dir := lib/pgutils
local_lib := $(local_dir)/libpgutils.a
local_src := $(wildcard $(local_dir)/*.cpp)
local_objs := $(subst .cpp,.o,$(local_src))

libraries += $(local_lib)
sources   += $(local_src)

$(local_lib): $(local_objs)
	@echo "Building utilities library..."
	@$(AR) $(ARFLAGS) $@ $^

