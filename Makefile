# ENGG1340/COMP2113 Programming Technologies - Group Project
# Authors: Lui Ka On (3035074610), Ye Zhongzheng (3035782176)
# Group Project: MessyGrid
# Group: 165
#
# Description:
# Makefile to build the main program.
#
######################################################################

# Define variables
######################################################################
CC = g++
ERROR_FLAGS = -Wall -Wextra -Werror -pedantic-errors
CPP_FLAGS = -std=c++11

CPP_SRC_NAMES = $(notdir $(wildcard src/*.cpp))
CPP_OBJ = $(addprefix bin/,$(patsubst %.cpp, %.o, ${CPP_SRC_NAMES}))

TEST_OBJ = $(patsubst %.cpp, %.o, $(wildcard test/test_*.cpp))

# Pre-requisites
######################################################################
# PHONY targets
all run: bin/main

# Main program
bin/main: ${CPP_OBJ}

# Objects
bin/main.o: $(addprefix src/, main.cpp main_menu.h game.h)
bin/clear_screen.o: $(addprefix src/, clear_screen.cpp clear_screen.h)
bin/main_menu.o: $(addprefix src/, main_menu.cpp main_menu.h clear_screen.h)
bin/game.o: $(addprefix src/, game.cpp game.h grid.h clear_screen.h)
bin/grid.o: $(addprefix src/, grid.cpp grid.h)

${CPP_OBJ}: | bin/  # The directory to store them

# Explicit rules to build targets
######################################################################
bin/main:   ; ${CC} ${ERROR_FLAGS} ${CPP_FLAGS} $^ -o $@
${CPP_OBJ}: ; ${CC} ${ERROR_FLAGS} ${CPP_FLAGS} -c $< -o $@

bin/:       ; mkdir -p bin/

# Phony targets
######################################################################
run:   ; bin/main
clean: ; rm -f bin/*.o bin/main ${TAR_FILE} test/*.o test/test_main
tags:  ; ctags --kinds-c++=+p --fields=+iaS --extras=+q --language-force=c++ \
         -R src/
tar:   ; tar -cvzf messygrid.tgz README*.md Makefile src/ doc/ test/test_*.cpp \
         test/test.sh test/acutest.hpp

.PHONY: all run clean tags tar

# Unit tests
######################################################################
.PHONY: test
test: test/test_main
	test/test_main

# Pre-requisites
test/test_main: test/test_main.o test/test_grid.o bin/grid.o
test/test_main.o: $(addprefix test/, test_main.cpp acutest.hpp test_grid.h)
test/test_grid.o: $(addprefix test/, test_grid.cpp acutest.hpp test_grid.h) \
    src/grid.h

# Explcit rules
test/test_main: ; ${CC} ${ERROR_FLAGS} ${CPP_FLAGS} $^ -o $@
${TEST_OBJ}: ; ${CC} ${ERROR_FLAGS} ${CPP_FLAGS} -c $< -o $@
