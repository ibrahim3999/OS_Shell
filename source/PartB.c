#include<stdlib.h> 
#include<stdio.h>
#include<string.h>
#include<ctype.h>

void codecA(char *message){

    int len =strlen(message);
    for(int i = 0; i < len ; i++){
        if(islower(message[i]))
            message[i]=toupper(message[i]);
        else if(isupper(message[i]))
            message[i]=tolower(message[i]);

    }
}
void codecB(char *message){

    int len = strlen (message);

    for(int i=0 ;i<len ;i++){
        if(isalpha(message[i]))
            message[i]=message[i]+3;// + 3 to assci table    }
    }
}