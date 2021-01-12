# # 046267 Computer Architecture - Winter 20/21 - HW #2


# Makefile for the smash program
CC = g++
# CFLAGS = -g -Wall
CFLAGS =-std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG -g
CCLINK = $(CC)
OBJS = server.o
RM = rm -f
# Creating the  executable
server: $(OBJS)
	$(CCLINK) $(CFLAGS) -o server $(OBJS)
# Creating the object files
server.o: server.cpp
	$(CCLINK) $(CFLAGS)  -c server.cpp
# Cleaning old files before new make
clean:
	$(RM) server *.o *~ "#"* core.*