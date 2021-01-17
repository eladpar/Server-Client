# # 046267 Computer Architecture - Winter 20/21 - HW #2


# Makefile for the smash program
CC = g++
# CFLAGS = -g -Wall
CFLAGS =-std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG -g
CCLINK = $(CC)
OBJS = client.o functions.o
RM = rm -f
# Creating the  executable
client: $(OBJS)
	$(CCLINK) $(CFLAGS) -o client $(OBJS)
# Creating the object files
client.o: client.cpp client.hpp functions.hpp
	$(CCLINK) $(CFLAGS)  -c client.cpp
functions.o: functions.cpp client.hpp functions.hpp
	$(CCLINK) $(CFLAGS)  -c functions.cpp
# Cleaning old files before new make
clean:
	$(RM) client *.o *~ "#"* core.*