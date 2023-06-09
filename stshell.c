#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "unistd.h"
#include <string.h>
#include <ctype.h>
#include "source/cmp.h"
#include "source/copy.h"
#include "source/codecA.h"
#include "source/codecB.h"
#include "source/execute_command.h"
#include "source/stopTool.h"

#include <signal.h> //for signal handling
#include <sys/wait.h>

#define MAX_ARGS 10

int main() {
	char *argv[MAX_ARGS];
	char command[1024];
	char *token;
    char *saveptr;
    int argCount = 0;
    char *output = NULL;
    int append = 0;
    int input_fd = STDIN_FILENO;
    int output_fd = STDOUT_FILENO;
    int argsCopy=0;
    signal(SIGINT,handle_signal);// register SIGINT singl hanlder
	while (1) {
        printf("$:");
        argCount = 0;
        output = NULL;
        append = 0;
        input_fd = STDIN_FILENO;
        output_fd = STDOUT_FILENO;
	   
	    fgets(command, 1024, stdin);
	    command[strlen(command) - 1] = '\0'; // replace \n with \0
      
	
	    token = strtok_r(command," ",&saveptr);//split when space
		
        while (token != NULL) {

            if (strcmp(token, ">>") == 0) {
                token = strtok_r(NULL, " ", &saveptr);
                if (token != NULL) {
                    output = token;
                    append = 1;
                }
            } else if (strcmp(token, ">") == 0) {
                token = strtok_r(NULL, " ", &saveptr);
                if (token != NULL) {
                    output = token;
                    append = 0;
                }
            }else if (strcmp(token, "|") == 0) {
                // Execute left-hand side of the pipe
                argv[argCount] = NULL;
                int pipefd[2];
                pipe(pipefd);
                execute_command(argv, input_fd, pipefd[1]);
                close(pipefd[1]);
                input_fd = pipefd[0];
                argCount = 0;
            }
            else {
                argv[argCount++] = token;
                argsCopy++;
            }
            token = strtok_r(NULL, " ", &saveptr);
        }
        argv[argCount]=NULL;
         /* set output file descriptor */
        if (output != NULL) {
            if (append) {
                output_fd = open(output, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
            } else {
                output_fd = open(output, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
            }
        }
        /* handle built-in commands */
        if(!strcmp(argv[0],"cmp")){
            if(argv[3]!=NULL){
                cmp_files(argv[1],argv[2],argv[3]);
            }
            else{
                cmp_files(argv[1],argv[2],"");
            }
            continue;
        }
        else if (strcmp(argv[0], "exit") == 0) {
            exit(0);
        }
		else if(!strcmp(argv[0],"copy")){
            if (argsCopy<4){
                printf("\n copy [file1] [file2] -v  copy not  overwirte \n copy [file1] [file2] -f copy  overwirte\n");
                continue;
            }
            if(!strcmp(argv[3],"-v")){
                copy_file(argv[1],argv[2],0,1);
                continue;
            }
            if(!strcmp(argv[3],"-f")){
                copy_file(argv[1],argv[2],1,0);
                continue;
            }  
            continue;
            
        }
        else if(!strcmp(argv[0],"encode") && !strcmp(argv[1],"codecA") )
        {
            char *res=encode_codecA(argv[2]);
            printf("%s\n",res);
            continue;
        }
        else if(!strcmp(argv[0],"encode") && !strcmp(argv[1],"codecB") )
        {
            char *res=encode_codecB(argv[2]);
            printf("%s\n",res);
            continue;
        }
        else if(!strcmp(argv[0],"decode") && !strcmp(argv[1],"codecA") )
        {
            char *res=decode_codecA(argv[2]);
            printf("%s\n",res);
            continue;
        }
         else if(!strcmp(argv[0],"decode") && !strcmp(argv[1],"codecB") )
        {
            char *res=decode_codecB(argv[2]);
            printf("%s\n",res);
            continue;
            
        }
        else if(!strcmp(argv[0],"cd")){
            if(argv[1]==NULL){
                chdir(getenv("HOME"));
            }else{
                if(chdir(argv[1])!=0){
                    perror("cd failed");
                }
            }
            continue;
        }
        else if(!strcmp(argv[0],"--help")){
            // Print help message
            printf("This is a simple shell implementation.\n");
            printf("Supported commands: cd ,ls, cmp , copy , help , pwd \n");
            continue;
        } 
      
	    /* execute command */
        execute_command(argv, input_fd, output_fd);
            
    }
    return 0;
   
}