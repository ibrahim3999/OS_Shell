CC = gcc
CFLAGS = -Wall -Wextra -pedantic

all: stshell 

stshell: objects/stshell.o objects/codecA.o objects/codecB.o objects/copy.o objects/cmp.o objects/stopTool.o objects/execute_command.o
	$(CC) -o bin/stshell objects/stshell.o objects/codecA.o objects/codecB.o objects/copy.o objects/cmp.o objects/stopTool.o objects/execute_command.o
	./bin/stshell   # execute the stshell command here

objects/stshell.o: stshell.c 
	$(CC) $(CFLAGS) -c stshell.c -o objects/stshell.o

objects/codecA.o: source/codecA.c source/codecA.h
	$(CC) $(CFLAGS) -c source/codecA.c -o objects/codecA.o

objects/codecB.o: source/codecB.c source/codecB.h
	$(CC) $(CFLAGS) -c source/codecB.c -o objects/codecB.o

objects/cmp.o: source/cmp.c source/cmp.h
	$(CC) $(CFLAGS) -c source/cmp.c -o objects/cmp.o

objects/copy.o: source/copy.c source/copy.h
	$(CC) $(CFLAGS) -c source/copy.c -o objects/copy.o

objects/execute_command.o: source/execute_command.c source/execute_command.h
	$(CC) $(CFLAGS) -c source/execute_command.c -o objects/execute_command.o

objects/stopTool.o: source/stopTool.c source/stopTool.h
	$(CC) $(CFLAGS) -c source/stopTool.c -o objects/stopTool.o

clean:
	rm -f bin/stshell bin/codecA bin/codecB  bin/copy  bin/cmp bin/stopTool bin/execute_command *.o