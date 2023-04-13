void encode_codecA(char* str) {
    while (*str != '\0') {
        if (islower(*str)) {
            *str = toupper(*str);
        }
        else if (isupper(*str)) {
            *str = tolower(*str);
        }
        str++;
    }
}

void decode_codecA(char* str) {
    while (*str != '\0') {
        if (islower(*str)) {
            *str = toupper(*str);
        }
        else if (isupper(*str)) {
            *str = tolower(*str);
        }
        str++;
    }
}