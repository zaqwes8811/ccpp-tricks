all: app.bin

app.bin: main.o heap.o
	g++ -o app.bin main.o heap.o -ldl -lunwind

main.o: main.cc
	g++ -c -g main.cc

heap.o: heap.c
	gcc -c -g heap.c

clean:
	rm *.bin *.o