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
    if (equal==1 && (!strcmp(flag,"-v") || !strcmp(flag,"-i")) ) {
        printf("equal\n");
    } else if  (!strcmp(flag,"-v")){
        printf("distinct\n");
    }

    fclose(fp1);
    fclose(fp2);
    return equal ? 0 : 1;
}
