#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(void)
{
    char input[BUFFER_SIZE];
    char *args[BUFFER_SIZE];
    int argCount;
    char *output = NULL;
    int append = 0;
    char *token;
    char *saveptr;

    while (1) {
        argCount = 0;
        output = NULL;
        append = 0;

        printf("$ ");
        fgets(input, BUFFER_SIZE, stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove the trailing newline character

        token = strtok_r(input, " ", &saveptr);
        while (token != NULL) {
            if (strcmp(token, ">>") == 0) {
                token = strtok_r(NULL, " ", &saveptr);
                if (token != NULL) {
                    output = token;
                    append = 1;
                }
            } else {
                args[argCount++] = token;
            }
            token = strtok_r(NULL, " ", &saveptr);
        }
        args[argCount] = NULL;

        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        pid_t pid = fork();
        if (pid == 0) {
            if (output != NULL) {
                int flags = O_CREAT | O_WRONLY;
                if (append) {
                    flags |= O_APPEND;
                } else {
                    flags |= O_TRUNC;
                }
                int fd = open(output, flags, 0644);
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }
            execvp(args[0], args);
            exit(1);
        } else if (pid > 0) {
            wait(NULL);
        } else {
            fprintf(stderr, "Failed to fork.\n");
            exit(1);
        }
    }

    return 0;
}