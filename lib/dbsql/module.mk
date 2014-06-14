local_dir := lib/dbsql
local_lib := $(local_dir)/libdbsql.a
local_src := $(wildcard $(local_dir)/*.cpp)
local_objs := $(subst .cpp,.o,$(local_src))

libraries += $(local_lib)
sources   += $(local_src)

$(local_lib): $(local_objs)
	@echo "Building SQL statements library..."
	@$(AR) $(ARFLAGS) $@ $^

