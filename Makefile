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

TAR_FILE = messygrid.tar.gz
TAR_SOURCE = README.md READMEinCHIN.md Makefile *.cpp *.h doc/


# Pre-requisites
######################################################################
all: main
main: main.o main_menu.o game.o grid.o clear_screen.o
main.o: main.cpp main_menu.h game.h

clear_screen.o: clear_screen.cpp clear_screen.h
main_menu.o: main_menu.cpp main_menu.h clear_screen.h
game.o: game.cpp game.h grid.h clear_screen.h
grid.o: grid.cpp grid.h

# Explicit rules to build targets
######################################################################
main: ; g++ ${ERROR_FLAGS} ${CPP_FLAGS} $^ -o $@
%.o:  ; g++ ${ERROR_FLAGS} ${CPP_FLAGS} -c $<

# Phony targets
######################################################################
clean: ; rm -f *.o main ${TAR_FILE}
tags:  ; ctags *.cpp
tar:   ; tar -cvzf ${TAR_FILE} ${TAR_SOURCE}

.PHONY: all clean tags tar
