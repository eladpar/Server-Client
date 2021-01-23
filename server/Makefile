# # 046267 Computer Architecture - Winter 20/21 - HW #2


# Makefile for the smash program
CC = g++
# CFLAGS = -g -Wall
CFLAGS =-std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG -g
CCLINK = $(CC)
OBJS = ttftps.o functions.o
RM = rm -f
# Creating the  executable
ttftps: $(OBJS)
	$(CCLINK) $(CFLAGS) -o ttftps $(OBJS)
# Creating the object files
ttftps.o: ttftps.cpp ttftps.hpp functions.hpp 
	$(CCLINK) $(CFLAGS)  -c ttftps.cpp
functions.o: functions.cpp ttftps.hpp functions.hpp
	$(CCLINK) $(CFLAGS)  -c functions.cpp
# Cleaning old files before new make
clean:
	$(RM) ttftps *.o *~ "#"* core.*