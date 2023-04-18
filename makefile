CC = gcc
CFLAGS = -Wall -Wextra -pedantic

all: basic_shell 

basic_shell: basic_shell.o codecA.o codecB.o copy.o cmp.o
	$(CC) -o bin/basic_shell basic_shell.o codecA.o codecB.o copy.o cmp.o
	./bin/basic_shell   # execute the basic_shell command here

basic_shell.o: basic_shell.c 
	$(CC) $(CFLAGS) -c basic_shell.c -o basic_shell.o

codecA.o: source/codecA.c source/codecA.h
	$(CC) $(CFLAGS) -c source/codecA.c -o codecA.o

codecB.o: source/codecB.c source/codecB.h
	$(CC) $(CFLAGS) -c source/codecB.c -o codecB.o

cmp.o: source/cmp.c source/cmp.h
	$(CC) $(CFLAGS) -c source/cmp.c -o cmp.o

copy.o: source/copy.c source/copy.h
	$(CC) $(CFLAGS) -c source/copy.c -o copy.o

clean:
	rm -f bin/basic_shell bin/codecA bin/codecB  bin/copy  bin/cmp *.o