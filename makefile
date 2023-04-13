CC = gcc
CFLAGS = -Wall -Wextra -pedantic

all: basic_shell 

basic_shell: basic_shell.o
	$(CC) -o bin/basic_shell basic_shell.o
	./bin/basic_shell   # execute the basic_shell command here

basic_shell.o: basic_shell.c 
	$(CC) $(CFLAGS) -c basic_shell.c -o basic_shell.o

codecA: codecA.o
	$(CC) -o bin/codecA codecA.o

codecA.o: source/codecA.c source/codecA.h
	$(CC) $(CFLAGS) -c source/codecA.c -o codecA.o

codecB: codecB.o
	$(CC) -o bin/codecB codecB.o

codecB.o: source/codecB.c source/codecB.h
	$(CC) $(CFLAGS) -c source/codecB.c -o codecB.o

clean:
	rm -f bin/basic_shell bin/codecA bin/codecB *.o