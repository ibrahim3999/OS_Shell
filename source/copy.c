#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "unistd.h"
#include <string.h>
#include <ctype.h>

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
