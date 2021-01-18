# # 046267 Computer Architecture - Winter 20/21 - HW #2


# Makefile for the smash program
CC = g++
# CFLAGS = -g -Wall
CFLAGS =-std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG -g
CCLINK = $(CC)
OBJS = server.o functions.o
RM = rm -f
# Creating the  executable
server: $(OBJS)
	$(CCLINK) $(CFLAGS) -o server $(OBJS)
# Creating the object files
server.o: server.cpp server.hpp functions.hpp 
	$(CCLINK) $(CFLAGS)  -c server.cpp
functions.o: functions.cpp server.hpp functions.hpp
	$(CCLINK) $(CFLAGS)  -c functions.cpp
# Cleaning old files before new make
clean:
	$(RM) server *.o *~ "#"* core.*