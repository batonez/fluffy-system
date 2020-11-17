squasher: squasher.o io.o syscalls.o builddir
	ld -lSystem build/squasher.o build/io.o build/syscalls.o -o build/squasher

squasher.o: squasher.c builddir
	gcc -c squasher.c -o build/squasher.o

io.o: io.c builddir
	gcc -c io.c -o build/io.o

syscalls.o: syscalls.s builddir
	as syscalls.s -o build/syscalls.o

builddir: 
	mkdir -p build
