#include <ctype.h>
#include <stdio.h>
#include <string.h>
char* encode_codecA(char* message) {
    
   int len =strlen(message);
    for(int i = 0; i < len ; i++){
        if(islower(message[i]))
            message[i]=toupper(message[i]);
        else if(isupper(message[i]))
            message[i]=tolower(message[i]);

    }
    return message;
}

char * decode_codecA(char* message) {

   return encode_codecA(message);
}