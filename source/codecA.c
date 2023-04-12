#include<stdlib.h> 
#include<stdio.h>
#include<string.h>
#include<ctype.h>


void encode(char *message){

    int len =strlen(message);
    for(int i = 0; i < len ; i++){
        if(islower(message[i]))
            message[i]=toupper(message[i]);
        else if(isupper(message[i]))
            message[i]=tolower(message[i]);

    }
}
void decode(char *message){
    encode(message);
}