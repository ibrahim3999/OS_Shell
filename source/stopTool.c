#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "unistd.h"
#include <string.h>
#include <ctype.h>
#include <signal.h> //for signal handling
#include <sys/wait.h>
//signal handler function for SIGINT
void handle_signal() {
    printf("\nCtrl+C detected, quitting the tool.\n");
   // exit(0);  
}