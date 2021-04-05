# ENGG1340/COMP2113 Programming Technologies - Group Project
# Authors: Lui Ka On (3035074610), Ye Zhongzheng (3035782176)
# Group Project: MessyGrid
# Group: 165
#
# Description:
# Makefile to build the main program.
#
######################################################################

# Define compile flags
######################################################################
ERROR_FLAGS = -Wall -Wextra -Werror -pedantic-errors
CPP_FLAGS = -std=c++11
C_FLAGS = -std=c11


# Pre-requisites
######################################################################
main: main.o clear_screen.o main_menu.o
main.o: main.cpp main_menu.h

clear_screen.o: clear_screen.cpp clear_screen.h
main_menu.o: main_menu.cpp main_menu.h clear_screen.h

# Explicit rules to build targets
######################################################################
main:   ; g++ ${ERROR_FLAGS} ${CPP_FLAGS} $^ -o $@
main.o: ; g++ ${ERROR_FLAGS} ${CPP_FLAGS} -c $<

clear_screen.o: ; g++ ${ERROR_FLAGS} ${CPP_FLAGS} -c $<
main_menu.o:    ; g++ ${ERROR_FLAGS} ${CPP_FLAGS} -c $<

# Phony targets
######################################################################
.PHONY: clean
clean: ; rm -f *.out *.o main
