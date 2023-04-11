#include<stdlib.h> 
#include<stdio.h>
#include<string.h>
#include<ctype.h>

void encode(char *message){

    int len = strlen (message);

    for(int i=0 ;i<len ;i++){
        message[i]=message[i]+3;// + 3 to assci table    }
    }
}
void decode(char *message){

    int len = strlen (message);

    for(int i=0 ;i<len ;i++){
        message[i]=message[i]-3;// -3 3 to assci table    }
    }
}