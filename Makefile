compile: clean dir-create main.o
	gcc main.o utils.o -o bin/npt

dir-create:
	mkdir -p bin

main.o: utils.o
	gcc -o main.o main.c -c

utils.o:
	gcc -o utils.o utils.c -c

clean:
	clear && rm -rf bin/ *.o
