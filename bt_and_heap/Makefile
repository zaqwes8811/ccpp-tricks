all: app.bin

app.bin: main.o heap.o
	g++ -o app.bin main.o heap.o -ldl

main.o: main.cc
	g++ -c main.cc

heap.o: heap.c
	gcc -c heap.c

clean:
	rm *.bin *.o