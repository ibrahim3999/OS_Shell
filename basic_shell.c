#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "unistd.h"
#include <string.h>
#include <ctype.h>
#include "source/codecA.h"
#include "source/codecB.h"

int cmp_files(const char *file1, const char *file2, const char *flag) {
    FILE *fp1, *fp2;
    int byte1, byte2;
    int line = 1, pos = 0;
    int equal = 1;

    fp1 = fopen(file1, "r");
    fp2 = fopen(file2, "r");

    if (fp1 == NULL) {
        printf("Could not open %s\n", file1);
        return 1;
    }

    if (fp2 == NULL) {
        printf("Could not open %s\n", file2);
        fclose(fp1);
        return 1;
    }

    while ((byte1 = getc(fp1)) != EOF && (byte2 = getc(fp2)) != EOF) {
        pos++;

        if (byte1 == '\n' && byte2 == '\n') {
            line++;
            pos = 0;
        }

        if (!strcmp(flag,"-i")) {
            byte1 = tolower(byte1);
            byte2 = tolower(byte2);
        }

        if (byte1 != byte2) {
            equal = 0;
            break;
        }
    }
    if (equal==1 && !strcmp(flag,"-v")) {
        printf("equal\n");
    } else if  (!strcmp(flag,"-v")){
        printf("distinct\n");
    }

    fclose(fp1);
    fclose(fp2);
    return equal ? 0 : 1;
}


int copy_file(const char* source_file, const char* dest_file, int force_flag, int verbose_flag) {
    FILE* source_fp;
    FILE* dest_fp;
    char buffer[1024];
    int bytes_read;
    int success = 0;

    if (access(dest_file, F_OK) != -1 && verbose_flag) {
      printf("target file exist\n");
      return 0;
   }

    source_fp = fopen(source_file, "rb");
    if (source_fp == NULL) {
        fprintf(stderr, "Error opening source file '%s': %s\n", source_file, strerror(errno));
        return -1;
    }

    dest_fp = fopen(dest_file, force_flag ? "wb" : "ab");
    if (dest_fp == NULL) {
        fprintf(stderr, "Error opening destination file '%s': %s\n", dest_file, strerror(errno));
        fclose(source_fp);
        return -1;
    }

    if (!force_flag && ftell(dest_fp) > 0) {
        fprintf(stderr, "Target file '%s' already exists. Use -f flag to overwrite.\n", dest_file);
        fclose(source_fp);
        fclose(dest_fp);
        return 1;
    }

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source_fp)) > 0) {
        if (fwrite(buffer, 1, bytes_read, dest_fp) != (size_t) bytes_read) {
            fprintf(stderr, "Error writing to destination file '%s': %s\n", dest_file, strerror(errno));
            success = 1;
            break;
        }
    }

    if (ferror(source_fp)) {
        fprintf(stderr, "Error reading from source file '%s': %s\n", source_file, strerror(errno));
        success = 1;
    }

    if (fclose(source_fp) != 0) {
        fprintf(stderr, "Error closing source file '%s': %s\n", source_file, strerror(errno));
        success = 1;
    }

    if (fclose(dest_fp) != 0) {
        fprintf(stderr, "Error closing destination file '%s': %s\n", dest_file, strerror(errno));
        success = 1;
    }

    if (success == 0 && verbose_flag) {
        printf("success\n");
    }else if (success && verbose_flag)
    {
        printf("general failure\n");
    }
    
    return success;
}

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
        }
		else if(!strcmp(argv[0],"copy")){
            if(!strcmp(argv[3],"-v")){
                copy_file(argv[1],argv[2],0,1);
            }
            if(!strcmp(argv[3],"-f")){
                copy_file(argv[1],argv[2],1,1);
            }
            
        }
        else if(!strcmp(argv[0],"encode") && !strcmp(argv[1],"codecA") )
        {
            char *res=encode_codecA(argv[2]);
            printf("%s\n",res);
        }
        else if(!strcmp(argv[0],"encode") && !strcmp(argv[1],"codecB") )
        {
            char *res=encode_codecB(argv[2]);
            printf("%s\n",res);
        }
        else if(!strcmp(argv[0],"decode") && !strcmp(argv[1],"codecA") )
        {
            char *res=decode_codecA(argv[2]);
            printf("%s\n",res);
        }
         else if(!strcmp(argv[0],"decode") && !strcmp(argv[1],"codecB") )
        {
            char *res=decode_codecB(argv[2]);
            printf("%s\n",res);
            
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
        else if(!strcmp(argv[0],"help")){
            // Print help message
            printf("This is a simple shell implementation.\n");
            printf("Supported commands: cd , cmp , copy , help.\n");
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
