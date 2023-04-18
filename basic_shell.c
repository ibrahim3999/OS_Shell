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


int main() {
	int i;
	char *argv[10];
	char command[1024];
	char *token;


	while (1) {
	    printf("hello: ");
	    fgets(command, 1024, stdin);
	    command[strlen(command) - 1] = '\0'; // replace \n with \0

   
	 /* parse command line */
		
	    i = 0;
	    token = strtok (command," ");//split when space
		
	    while (token != NULL){
            argv[i] = token;
            i++;
            token = strtok(NULL, " ");//next
	    }
 
        if(!strcmp(argv[0],"cmp")){
            if(argv[3]!=NULL){
                cmp_files(argv[1],argv[2],argv[3]);
            }
            else{
                cmp_files(argv[1],argv[2],"");
            }
            continue;
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
            printf("Supported commands: cd ,ls, cmp , copy , help.\n");
            continue;
        } 

	    argv[i] = NULL;
	    /* Is command empty */ 
		
	    if (argv[0] == NULL)
		    continue;
	   	
	    /* for commands not part of the shell command language */ 
		pid_t pid =fork();

	    if (pid == 0) { 
        //Child process
            if(execvp(argv[0], argv)==-1){
                perror("exec failed");
                exit(EXIT_FAILURE);
            }
		
	    }
        else if(pid < 0){
            // Fork falied
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        else{
            // Parent process
            wait(NULL);
        }
		    
	}
    
}
