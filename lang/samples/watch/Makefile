# ZZZ: how add other kay for g++
#

SRCS = mysystime.cpp main.cpp noCrossTime.cpp
OBJS = mysystime.o main.o noCrossTime.o
HEAD = mysystime.h
CC = g++
# obj. files

all: main

main: $(OBJS) 
	$(CC) -lrt -o main  $(OBJS)
$(OBJS): $(SRCS)
	$(CC) -lrt -c $(SRCS)

# add
clean:
	rm -f $(OBJS) main
run: 
	./main
