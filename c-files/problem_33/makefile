
all:run

run: compile
	./problem33

compile: hash.o util.o list.o biginteger.o
	gcc -o problem33 util.o list.o biginteger.o hash.o problem33.c

# Compiling the library	

hash.o:
	gcc -c ../lib/hash.h ../lib/hash.c 

util.o:
	gcc -c ../lib/util.h ../lib/util.c

list.o:
	gcc -c ../lib/list.h ../lib/list.c ../lib/debug.h

biginteger.o:
	gcc -c ../lib/biginteger.h ../lib/biginteger.c

# Clean the object file before executing, so the changes are visible
clean:
	rm util.o