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
#include <signal.h> //for signal handling
#include <sys/wait.h>


//signal handler function for SIGINT
void handle_signal(int sig) {
    printf("\nCtrl+C detected, quitting the shell.\n");
    exit(EXIT_SUCCESS);
}

int main() {
	char *argv[10];
	char command[1024];
	char *token;
    char *saveptr;
    int argCount = 0;
    char *output = NULL;
    int append = 0;

    signal(SIGINT,handle_signal);// register SIGINT singl hanlder

	while (1) {
        argCount = 0;
        output = NULL;
        append = 0;
	    printf("hello: ");
	    fgets(command, 1024, stdin);
	    command[strlen(command) - 1] = '\0'; // replace \n with \0
      
   
	 /* parse command line */
		
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
        } else {
            argv[argCount++] = token;
        }
        token = strtok_r(NULL, " ", &saveptr);
     }
        argv[argCount]=NULL;

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
            if(!strcmp(argv[3],"-v")){
                copy_file(argv[1],argv[2],0,1);
            }
            if(!strcmp(argv[3],"-f")){
                copy_file(argv[1],argv[2],1,1);
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
      
	    /* for commands not part of the shell command language */ 
		pid_t pid = fork();

        if (pid == 0) { 
            // Child process

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
            execvp(argv[0], argv);
            perror("exec failed");
            exit(EXIT_FAILURE);
        }
        else if (pid < 0) {
            // Fork failed
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        else {
            // Parent process
            wait(NULL);
            // Cleanup
        }
		    
	}
   
}
