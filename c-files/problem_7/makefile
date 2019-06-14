
all:run

run: compile
	./problem7

compile: util.o list.o
	gcc -o problem7 util.o list.o problem7.c

# Compiling the library	
util.o:
	gcc -c ../lib/util.h ../lib/util.c

list.o:
	gcc -c ../lib/list.h ../lib/list.c ../lib/debug.h

# Clean the object file before executing, so the changes are visible
clean:
	rm util.o