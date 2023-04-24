#include "codecB.h"
#include<stdlib.h> 
#include<stdio.h>
#include<string.h>
#include<ctype.h>

char* encode_codecB(char* message) {
    int len = strlen (message);

    for(int i=0 ;i<len ;i++){
        message[i]=(message[i]+3)%128;// + 3 to assci table    }
    }
    return message; 
    
}
char* decode_codecB(char* message) {
int len = strlen (message);

    for(int i=0 ;i<len ;i++){
        message[i]=(message[i]-3)%128;// -3 3 to assci table    }
    }
return message;
}

