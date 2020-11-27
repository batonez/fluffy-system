all: squasher memorytest bmptest gradient bresenham lines readlinetest

######################

render-gradient: gradient
	rm -f picture.bmp
	../build/gradient
	../build/gradient
	open picture.bmp

render-bresenham: bresenham
	rm -f picture.bmp
	../build/bresenham
	open picture.bmp

render-lines: lines
	rm -f picture.bmp
	../build/lines
	open picture.bmp

######################

gradient: gradient.o base.o syscalls.o bmp.o ../builddir
	ld -lSystem ../build/bmp.o ../build/gradient.o ../build/base.o ../build/syscalls.o -o ../build/gradient

bresenham: bresenham.o base.o syscalls.o bmp.o ../builddir
	ld -lSystem ../build/bmp.o ../build/bresenham.o ../build/base.o ../build/syscalls.o -o ../build/bresenham

lines: lines.o base.o syscalls.o bmp.o ../builddir
	ld -lSystem ../build/bmp.o ../build/lines.o ../build/base.o ../build/syscalls.o -o ../build/lines

bmptest: bmptest.o bmp.o base.o syscalls.o ../builddir
	ld -lSystem ../build/bmptest.o ../build/bmp.o ../build/base.o ../build/syscalls.o -o ../build/bmptest

memorytest: memorytest.o base.o syscalls.o ../builddir
	ld -lSystem ../build/memorytest.o ../build/base.o ../build/syscalls.o -o ../build/memorytest

squasher: squasher.o base.o syscalls.o ../builddir
	ld -lSystem ../build/squasher.o ../build/base.o ../build/syscalls.o -o ../build/squasher

readlinetest: readlinetest.o base.o syscalls.o ../builddir
	ld -lSystem ../build/readlinetest.o ../build/base.o ../build/syscalls.o -o ../build/readlinetest

######################

bmp.o: ../builddir
	gcc -c bmp.c -o ../build/bmp.o

gradient.o: ../builddir
	gcc -c gradient.c -o ../build/gradient.o

bresenham.o: ../builddir
	gcc -c bresenham.c -o ../build/bresenham.o

lines.o: ../builddir
	gcc -c lines.c -o ../build/lines.o

bmptest.o: ../builddir
	gcc -c bmptest.c -o ../build/bmptest.o

memorytest.o: ../builddir
	gcc -c memorytest.c -o ../build/memorytest.o

squasher.o: ../builddir
	gcc -c squasher.c -o ../build/squasher.o

readlinetest.o: ../builddir
	gcc -c readlinetest.c -o ../build/readlinetest.o

base.o: ../builddir
	gcc -c base.c -o ../build/base.o

syscalls.o: ../builddir
	as syscalls.s -o ../build/syscalls.o

######################

../builddir: 
	mkdir -p ../build

clean:
	rm -rf ../build
