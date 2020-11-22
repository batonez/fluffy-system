all: squasher memorytest bmptest

render: bmptest builddir
	build/bmptest
	open picture.bmp

bmptest: bmptest.o base.o syscalls.o builddir
	ld -lSystem build/bmptest.o build/base.o build/syscalls.o -o build/bmptest

memorytest: memorytest.o base.o syscalls.o builddir
	ld -lSystem build/memorytest.o build/base.o build/syscalls.o -o build/memorytest

squasher: squasher.o base.o syscalls.o builddir
	ld -lSystem build/squasher.o build/base.o build/syscalls.o -o build/squasher

bmptest.o: bmptest.c builddir
	gcc -c bmptest.c -o build/bmptest.o

memorytest.o: memorytest.c builddir
	gcc -c memorytest.c -o build/memorytest.o

squasher.o: squasher.c builddir
	gcc -c squasher.c -o build/squasher.o

base.o: base.c builddir
	gcc -c base.c -o build/base.o

syscalls.o: syscalls.s builddir
	as syscalls.s -o build/syscalls.o

builddir: 
	mkdir -p build

clean:
	rm -rf build
