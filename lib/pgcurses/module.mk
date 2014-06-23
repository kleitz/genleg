local_dir := lib/pgcurses
local_lib := $(local_dir)/libpgcurses.a
local_src := $(wildcard $(local_dir)/*.cpp)
local_objs := $(subst .cpp,.o,$(local_src))

libraries += $(local_lib)
sources   += $(local_src)

$(local_lib): $(local_objs)
	@echo "Building PG curses library..."
	@$(AR) $(ARFLAGS) $@ $^

