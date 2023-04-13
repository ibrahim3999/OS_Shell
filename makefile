CC = gcc
CFLAGS = -Wall -Wextra -pedantic

all: basic_shell 

basic_shell: basic_shell.o
	$(CC) -o bin/basic_shell basic_shell.o
	./bin/basic_shell   # execute the basic_shell command here

basic_shell.o: basic_shell.c 
	$(CC) $(CFLAGS) -c basic_shell.c -o basic_shell.o

PartB: PartB.o
	$(CC) -o bin/PartB PartB.o

PartB.o: source/PartB.c source/PartB.h
	$(CC) $(CFLAGS) -c source/PartB.c -o PartB.o

clean:
	rm -f bin/basic_shell bin/PartB *.o