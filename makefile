CC = gcc
CFLAGS = -Wall -Wextra -pedantic

all: basic_shell 

basic_shell: objects/basic_shell.o objects/codecA.o objects/codecB.o objects/copy.o objects/cmp.o
	$(CC) -o bin/basic_shell objects/basic_shell.o objects/codecA.o objects/codecB.o objects/copy.o objects/cmp.o
	./bin/basic_shell   # execute the basic_shell command here

objects/basic_shell.o: basic_shell.c 
	$(CC) $(CFLAGS) -c basic_shell.c -o objects/basic_shell.o

objects/codecA.o: source/codecA.c source/codecA.h
	$(CC) $(CFLAGS) -c source/codecA.c -o objects/codecA.o

objects/codecB.o: source/codecB.c source/codecB.h
	$(CC) $(CFLAGS) -c source/codecB.c -o objects/codecB.o

objects/cmp.o: source/cmp.c source/cmp.h
	$(CC) $(CFLAGS) -c source/cmp.c -o objects/cmp.o

objects/copy.o: source/copy.c source/copy.h
	$(CC) $(CFLAGS) -c source/copy.c -o objects/copy.o

clean:
	rm -f bin/basic_shell bin/codecA bin/codecB  bin/copy  bin/cmp *.o