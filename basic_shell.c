#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "unistd.h"
#include <string.h>
#include <ctype.h>

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
        if (fwrite(buffer, 1, bytes_read, dest_fp) != bytes_read) {
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
    char *comm0;
	char *comm1;
	char *comm2;
	char *flag;


	while (1) {
	    printf("hello: ");
	    fgets(command, 1024, stdin);
	    command[strlen(command) - 1] = '\0'; // replace \n with \0

		//int res=cmp("Files/a.txt","Files/b.txt");
		//printf("%d\n",res);
   
	 /* parse command line */
		
	    i = 0;
	    token = strtok (command," ");//split when space
		
	    while (token != NULL){
            argv[i] = token;
            if(i==0){
                comm0=token;
            }
            token = strtok (NULL," ");

            if(i==0){
                comm1=token;
            }
            if(i==1){
                comm2=token;
            }
            if(i==2){
                flag=token;
            }
            i++;
	    }
       
        if(!strcmp(comm0,"cmp")){
            if(flag!=NULL){
                cmp_files(comm1,comm2,flag);
            }
            else{
                cmp_files(comm1,comm2,"");
            }
        }
		else if(!strcmp(comm0,"copy")){
            if(!strcmp(flag,"-v")){
                copy_file(comm1,comm2,0,1);
            }
            if(!strcmp(flag,"-f")){
                copy_file(comm1,comm2,1,1);
            }
            
        }
        else if(!strcmp(comm0,"encode"))
        {
            
        }


		//printf("%d\n",res_cmp);
		

	    argv[i] = NULL;
	    /* Is command empty */ 
		
	    if (argv[0] == NULL)
		continue;
	   	
	    /* for commands not part of the shell command language */ 
		/*
	    if (fork() == 0) { 
		execvp(argv[0], argv);
		wait(NULL);
	    }
		*/    
	}
    
}
