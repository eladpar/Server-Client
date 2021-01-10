# # 046267 Computer Architecture - Winter 20/21 - HW #2


# Makefile for the smash program
CC = g++
# CFLAGS = -g -Wall
CFLAGS =-std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG -pthread -g
CCLINK = $(CC)
OBJS = client.o
RM = rm -f
# Creating the  executable
client: $(OBJS)
	$(CCLINK) $(CFLAGS) -o client $(OBJS)
# Creating the object files
server.o: client.cpp
	$(CCLINK) $(CFLAGS)  -c client.cpp
# Cleaning old files before new make
clean:
	$(RM) client *.o *~ "#"* core.*