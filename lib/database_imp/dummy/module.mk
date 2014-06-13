local_dir := lib/database_imp/dummy
local_lib := $(local_dir)/libdatabase_dummy.a
local_src := $(wildcard $(local_dir)/*.cpp)
local_objs := $(subst .cpp,.o,$(local_src))

libraries += $(local_lib)
sources   += $(local_src)

$(local_lib): $(local_objs)
	@echo "Building dummy database library..."
	@$(AR) $(ARFLAGS) $@ $^

