GMOCK=../extern/gmock-1.6.0/fused-src

INCLUDE=-I$(GMOCK)

all: app.bin

app.bin: gmock-gtest-all.o main.o
	g++ -o app.bin main.o gmock-gtest-all.o -lpthread

main.o: main.cc
	g++ -c -g main.cc

gmock-gtest-all.o: $(GMOCK)/gmock-gtest-all.cc
	g++ -c -g $(INCLUDE) $(GMOCK)/gmock-gtest-all.cc

clean:
	rm *.bin *.o
	
