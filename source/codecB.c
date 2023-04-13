#include "codecB.h"

void encode_codecB(char* str) {
    while (*str != '\0') {
        *str = (*str + 3) % 128;//+3 in assci table
        str++;
    }
}

void decode_codecB(char* str) {
    while (*str != '\0') {
        *str = (*str - 3 + 128) % 128;//-3 in assci table
        str++;
    }
}