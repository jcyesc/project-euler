
all:run

run: compile
	./problem8

compile: util.o list.o
	gcc -o problem8 util.o list.o problem8.c

# Compiling the library	
util.o:
	gcc -c ../lib/util.h ../lib/util.c

list.o:
	gcc -c ../lib/list.h ../lib/list.c ../lib/debug.h

# Clean the object file before executing, so the changes are visible
clean:
	rm util.o