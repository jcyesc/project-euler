
all:run

run: compile
	./problem16

compile: util.o list.o biginteger.o
	gcc -o problem16 util.o list.o biginteger.o problem16.c

# Compiling the library	
util.o:
	gcc -c ../lib/util.h ../lib/util.c

list.o:
	gcc -c ../lib/list.h ../lib/list.c ../lib/debug.h

biginteger.o:
	gcc -c ../lib/biginteger.h ../lib/biginteger.c

# Clean the object file before executing, so the changes are visible
clean:
	rm util.o