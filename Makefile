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
ERROR_FLAGS = -Wall -Wextra -Werror -pedantic-errors
CPP_FLAGS = -std=c++11
C_FLAGS = -std=c11

TAR_FILE = messygrid.tgz
TAR_SOURCE = README.md README_zh.md Makefile src/* doc/

SRC_FILES = $(notdir $(wildcard src/*.cpp))
OBJ = $(addprefix bin/,$(patsubst %.cpp, %.o, ${SRC_FILES}))

# Pre-requisites
######################################################################
all: bin/main
bin/main: ${OBJ}

bin/main.o: $(addprefix src/, main.cpp main_menu.h game.h)
bin/clear_screen.o: $(addprefix src/, clear_screen.cpp clear_screen.h)
bin/main_menu.o: $(addprefix src/, main_menu.cpp main_menu.h clear_screen.h)
bin/game.o: $(addprefix src/, game.cpp game.h grid.h clear_screen.h)
bin/grid.o: $(addprefix src/, grid.cpp grid.h)

${OBJ}: bin/  # The directory to store them

# Explicit rules to build targets
######################################################################
bin/main: ; g++ ${ERROR_FLAGS} ${CPP_FLAGS} $^ -o $@
%.o:  ; g++ ${ERROR_FLAGS} ${CPP_FLAGS} -c $< -o $@

bin/: ; mkdir -p bin/

# Phony targets
######################################################################
clean: ; rm -f bin/*.o bin/main ${TAR_FILE}
tags:  ; ctags src/*.cpp
tar:   ; tar -cvzf ${TAR_FILE} ${TAR_SOURCE}

.PHONY: all clean tags tar
