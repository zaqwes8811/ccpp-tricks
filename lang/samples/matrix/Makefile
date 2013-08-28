# ZZZ: how add other kay for g++
#

SRCS = main.cpp matrixFirst.cpp
OBJS = main.o matrixFirst.o
CC = c++
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
