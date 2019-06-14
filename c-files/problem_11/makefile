
all:run

run: compile
	./problem11

compile: util.o list.o
	gcc -o problem11 util.o list.o problem11.c

# Compiling the library	
util.o:
	gcc -c ../lib/util.h ../lib/util.c

list.o:
	gcc -c ../lib/list.h ../lib/list.c ../lib/debug.h

# Clean the object file before executing, so the changes are visible
clean:
	rm util.o