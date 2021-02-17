compile: dir-create
	gcc npt.c -o bin/npt

dir-create:
	mkdir -p bin

clean:
	rm -rf bin/ *.o
