#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


void sigint_handler(int sig)
{
    printf("Received SIGINT signal. Exiting...\n");
    exit(0);
}

int main()
{
    signal(SIGINT, sigint_handler);

    while (1)
    {
        printf("Press Ctrl+C to trigger the SIGINT signal.\n");
        sleep(1);
    }

    return 0;
}