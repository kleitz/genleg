# general_ledger makefile
# =======================
# Copyright 2014 Paul Griffiths
# Email: mail@paulgriffiths.net
#
# Distributed under the terms of the GNU General Public License.
# http://www.gnu.org/licenses/


# Variables section
# =================

# Files
report_program	 := gl_report
unittest_program := unittests
sources      	 := $(wildcard *.cpp)
libraries    	 :=
objects       	  = $(subst .cpp,.o,$(sources))
depends       	  = $(subst .cpp,.d,$(sources))
report_objects   :=
unittest_objects :=

# Compile options
database     := mysql

# Compiler flags
CXXFLAGS = -std=c++11 -pedantic -Wall -Wextra -Weffc++ -Ilib
CXX_DEBUG_FLAGS   := -ggdb -DDEBUG -DDEBUG_ALL
CXX_RELEASE_FLAGS := -O3 -DNDEBUG

# Linker flags
LDFLAGS :=
BOOSTLIBS :=-lboost_system -lboost_thread -lboost_unit_test_framework

# Clean files and globs
CLNGLOB=$(objects) $(libraries) $(depends)
CLNGLOB+=$(report_program) $(unittest_program)
CLNGLOB+=*~ *.o *.gcov *.out *.gcda *.gcno


# Build targets section
# =====================

default: debug

# debug - builds objects with debugging info
.PHONY: debug
debug: CXXFLAGS+=$(CXX_DEBUG_FLAGS)
debug: all

# release - builds with optimizations and without debugging info
.PHONY: release
release: CXXFLAGS+=$(CXX_RELEASE_FLAGS)
release: all

# clean - removes ancilliary files from working directory
.PHONY: clean
clean:
	-@rm $(CLNGLOB) 2>/dev/null

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
all: $(report_program) $(unittest_program)

include lib/database_imp/$(database)/module.mk
include lib/database/module.mk
include lib/config/module.mk
include lib/stringhelp/module.mk

include progs/gl_report/module.mk
include progs/unittests/module.mk

$(report_program): $(report_objects) $(libraries)
	@echo "Building gl_report..."
	$(CXX) -o $@ $^ $(LDFLAGS)
	@echo "Done."

$(unittest_program): $(unittest_objects) $(libraries)
	@echo "Building unit tests..."
	$(CXX) -o $@ $^ $(LDFLAGS) $(BOOSTLIBS)
	@echo "Done."


# Dependencies
# ============

-include $(depends)

%.d: %.cpp
	@echo "Building dependencies for $<..."
	@$(CXX) -M $(CXXFLAGS) $< > $@.tmp; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.tmp > $@; \
		rm -f $@.tmp

