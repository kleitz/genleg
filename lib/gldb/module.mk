local_dir := lib/gldb
local_lib := $(local_dir)/libgldb.a
local_src := $(wildcard $(local_dir)/*.cpp)
local_objs := $(subst .cpp,.o,$(local_src))

libraries += $(local_lib)
sources   += $(local_src)

$(local_lib): $(local_objs)
	@echo "Building General Ledger database library..."
	@$(AR) $(ARFLAGS) $@ $^

