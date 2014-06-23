# general_ledger makefile
# =======================
# Copyright 2014 Paul Griffiths
# Email: mail@paulgriffiths.net
#
# Distributed under the terms of the GNU General Public License.
# http://www.gnu.org/licenses/


# Variables section
# =================

# Programs
SED := sed
MV  := mv -f
RM  := rm -f

# Objects, sources and libraries variables
database_program := gl_db
report_program	 := gl_report
user_program	 := gl_user
term_program	 := gl_term
unittest_program := unittests
programs         := $(database_program) $(report_program)
programs         += $(user_program) $(unittest_program)
programs         += $(term_program)

sources      	 := $(wildcard *.cpp)
objects       	  = $(subst .cpp,.o,$(sources))
depends       	  = $(subst .cpp,.d,$(sources))
libraries    	 :=

database_objects :=
report_objects   :=
user_objects     :=
term_objects     :=
unittest_objects :=

# Compile options
database         := mysql

# Compiler flags
CXXFLAGS           = -std=c++11 -pedantic -Wall -Wextra -Ilib
#CXXFLAGS          += -Weffc++
CXX_DEBUG_FLAGS   := -ggdb -DDEBUG -DDEBUG_ALL
CXX_RELEASE_FLAGS := -O3 -DNDEBUG

# Linker flags
LDFLAGS   		:= -lcrypt
BOOST_TEST_LIBS :=-lboost_system -lboost_thread -lboost_unit_test_framework
BOOST_LIBS 		+=-lboost_system -lboost_thread -lboost_filesystem
CURSES_LIBS		:= -lcurses

# Clean files and globs
CLNGLOB  = $(objects) $(libraries) $(depends) $(programs)
CLNGLOB += *~ *.o *.gcov *.out *.gcda *.gcno

# Default target
default: debug

# Included modules
include lib/gldb/module.mk
include lib/dbsql/module.mk
include lib/database_imp/$(database)/module.mk
include lib/database/module.mk
include lib/config/module.mk
include lib/pgcurses/module.mk
include lib/pgutils/module.mk

include progs/gl_db/module.mk
include progs/gl_report/module.mk
include progs/gl_user/module.mk
include progs/gl_term/module.mk
include progs/unittests/module.mk

# Build targets section
# =====================

# debug - builds objects with debugging info
.PHONY: debug
debug: CXXFLAGS += $(CXX_DEBUG_FLAGS)
debug: all

# release - builds with optimizations and without debugging info
.PHONY: release
release: CXXFLAGS += $(CXX_RELEASE_FLAGS)
release: all

# clean - removes ancilliary files from working directory
.PHONY: clean
clean:
	-@$(RM) $(CLNGLOB) 2>/dev/null

# docs - makes Doxygen documentation:
.PHONY: docs
docs:
	@doxygen
	-@cd latex; make; cd ..
	@if [ ! -d docs ]; then \
		mkdir docs; fi
	@echo "Copying reference manual to docs..."
	@cp latex/refman.pdf docs 
	@echo "Done."

# tags - makes tags file
.PHONY: tags
tags:
	@ctags *.cpp *.g


# Executable targets section
# ==========================

# Main executable
.PHONY: all
all: $(programs)

$(database_program): $(database_objects) $(libraries)
	@echo "Building gl_db..."
	$(CXX) -o $@ $^ $(LDFLAGS) $(BOOST_LIBS)

$(report_program): $(report_objects) $(libraries)
	@echo "Building gl_report..."
	$(CXX) -o $@ $^ $(LDFLAGS) $(BOOST_LIBS)

$(user_program): $(user_objects) $(libraries)
	@echo "Building gl_user..."
	$(CXX) -o $@ $^ $(LDFLAGS) $(BOOST_LIBS)

$(term_program): $(term_objects) $(libraries)
	@echo "Building gl_term..."
	$(CXX) -o $@ $^ $(LDFLAGS) $(BOOST_LIBS) $(CURSES_LIBS)

$(unittest_program): $(unittest_objects) $(libraries)
	@echo "Building unit tests..."
	$(CXX) -o $@ $^ $(LDFLAGS) $(BOOST_TEST_LIBS)

# Dependencies
ifneq "$(MAKECMDGOALS)" "clean"
  -include $(depends)
endif

# Build for dependencies
%.d: %.cpp
	@echo "Building dependencies for $<..."
	@$(CXX) $(CXXFLAGS) -M $< | \
		$(SED) 's,\($(notdir $*)\.o\) *:,$(dir $@)\1: ,' > $@.tmp
	@$(MV) $@.tmp $@

