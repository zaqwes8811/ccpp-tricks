# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

CC=g++
APP=string_and_streams_app
BOOST=/home/zaqwes/work/third_party/boost_1_55_0
LOKI=../../third_party/loki-0.1.7/include
CCFLAGS=-I$(BOOST) -I$(LOKI) -O2 

# http://stackoverflow.com/questions/10363646/compiling-c11-with-g
all:
	$(CC) -std=c++11 -Wall -Wno-deprecated -c -pg $(APP).cc $(CCFLAGS)
	$(CC) -o $(APP).app $(APP).o -pg -ltbb
	
run:
	./$(APP).app
	
clean:
	rm *.o *.app
	
benchmark:
	#valgrind --tool=callgrind ./$(APP).app
	time ./$(APP).app