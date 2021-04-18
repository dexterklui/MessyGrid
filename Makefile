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

TEST_DIR = test
UNIT_DIR = ${TEST_DIR}/unit
UNIT_OBJ = $(patsubst %.cpp, %.o, $(wildcard ${UNIT_DIR}/test_*.cpp))
TEST_GAME_DIR = ${TEST_DIR}/game

TAR_FILE = messygrid.tgz

# Pre-requisites
######################################################################
# PHONY targets
all run: bin/main

# Main program
bin/main: ${CPP_OBJ}

# Objects
bin/main.o: $(addprefix src/, main.cpp main_menu.h game.h clear_screen.h)
bin/clear_screen.o: $(addprefix src/, clear_screen.cpp clear_screen.h)
bin/main_menu.o: $(addprefix src/, main_menu.cpp main_menu.h)
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

clean: ; @ rm -f \
         bin/main \
         bin/*.o \
         ${TAR_FILE} \
         ${UNIT_DIR}/test_main \
         ${UNIT_DIR}/*.o

tags:  ; ctags --kinds-c++=+p --fields=+iaS --extras=+q --language-force=c++ \
         -R src/

tar:   ; tar -cvzf ${TAR_FILE} README*.md Makefile src/ doc/ \
	 $(addprefix ${UNIT_DIR}/, test_*.h test_*.cpp acutest.hpp) \
	 $(addprefix ${TEST_GAME_DIR}/, input output post test.sh)

.PHONY: all run clean tags tar

# Tests
######################################################################
.PHONY: test test_unit test_game
test: test_unit test_game

# Unit tests
########################################
test_unit: ${UNIT_DIR}/test_main
	timeout 5s ${UNIT_DIR}/test_main -t

# Pre-requisites
${UNIT_DIR}/test_main: ${UNIT_OBJ} \
    $(addprefix bin/, grid.o game.o clear_screen.o)

${UNIT_DIR}/test_main.o: \
    ${UNIT_DIR}/test_main.cpp \
    ${UNIT_DIR}/acutest.hpp \
    ${UNIT_DIR}/test_grid.h \
    ${UNIT_DIR}/test_game.h \

${UNIT_DIR}/test_grid.o: \
    $(addprefix ${UNIT_DIR}/, test_grid.cpp test_grid.h acutest.hpp) \
    src/grid.h

${UNIT_DIR}/test_game.o: \
    $(addprefix ${UNIT_DIR}/, test_game.cpp test_game.h acutest.hpp) \
    src/game.h

# Explcit rules
${UNIT_DIR}/test_main: ; ${CC} ${ERROR_FLAGS} ${CPP_FLAGS} $^ -o $@
${UNIT_OBJ}: ; ${CC} ${ERROR_FLAGS} ${CPP_FLAGS} -c $< -o $@

# Game tests
########################################
test_game: ${TEST_GAME_DIR}/test.sh bin/main
	timeout 5s ${TEST_GAME_DIR}/test.sh
