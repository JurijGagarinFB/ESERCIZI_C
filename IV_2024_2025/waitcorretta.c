/**
 * @brief Esempio utilizzo funzione "wait()"" con corretto uso dell'argomento "status"
 *
 * @param argc numero di parametri passati da linea di comando
 * @param argv array di stringhe che contiene i parametri passati da linea di comando
 *
 * @return 0 il programma ritorna 0
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   //serve per la fork()
#include <sys/wait.h> //serve per la wait()

int p;
int status;

int main(int argc, char *argv[])
{
    p = fork();

    if (p == 0) // figlio
    {
        printf("1. Sono il figlio PID=%d \n", getpid());
        printf("2. Sono il figlio PID=%d mio padre ha PID=%d \n", getpid(), getppid());
        exit(255);
    }
    else if (p > 0) // padre
    {
        printf("4. Sono il padre PID=%d \n", getpid());
        printf("5. Sono il padre PID=%d mio figlio ha PID=%d \n", getpid(), p);
        printf("Padre %d attendo la terminazione di mio figlio %d \n", getpid(), wait(&status));
        printf("Mio figlio mi ha passato il valore %d \n", WEXITSTATUS(status));
    }
    else // errore
    {
        printf("Errore fork \n");
    }
    return 0;
}