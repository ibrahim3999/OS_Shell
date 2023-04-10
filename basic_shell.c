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

int main() {
	int i;
	char *argv[10];
	char command[1024];
	char *token;
	char *file1;
	char *file2;
	char *flag;
	

	while (1) {
	    printf("hello: ");
	    fgets(command, 1024, stdin);
	    command[strlen(command) - 1] = '\0'; // replace \n with \0

		//int res=cmp("Files/a.txt","Files/b.txt");
		//printf("%d\n",res);
		   
	 /* parse command line */
		
	    i = 0;
	    token = strtok (command," ");
		
	    while (token != NULL){
		argv[i] = token;
		token = strtok (NULL, " ");

		if(i==0){
			file1=token;
		}
		if(i==1){
			file2=token;
		}
		if(i==2){
			flag=token;
		}
		i++;
	    }
		if(flag!=NULL){
			cmp_files(file1,file2,flag);
		}
		else{
			cmp_files(file1,file2,"");
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
