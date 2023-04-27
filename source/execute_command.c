#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "unistd.h"
#include <string.h>
#include <ctype.h>
#include <signal.h> //for signal handling
#include <sys/wait.h>
int execute_command(char *argv[], int input_fd, int output_fd) {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process

        if (input_fd != STDIN_FILENO) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        if (output_fd != STDOUT_FILENO) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }

        execvp(argv[0], argv);
        perror("exec failed");
        exit(EXIT_FAILURE);
    }
    else if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        return -1;
    }
    else {
        // Parent process
        wait(NULL);
        return 0;
    }
}