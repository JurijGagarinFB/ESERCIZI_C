#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int p;
int status;

int main()
{
    p = fork();

    if (p == 0) //figlio
    {

    }
    else if (p > 0) //padre
    {
    }
    else //errore
    {
    }
    return 0;
}