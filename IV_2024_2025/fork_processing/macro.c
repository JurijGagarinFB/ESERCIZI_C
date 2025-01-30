/**
 * @brief Scrivi il codice sorgente di un prg in cui
 * il processo padre P genera un processo figlio F,
 * ne recupera il valore di ritorno (25) e
 * verifica se la terminazione è stata volontaria o meno.
 *
 * La prima cosa che ciascun processo deve fare, appena genera un processo figlio,
 * è dichiararsi nel modo seguente:
 * "P: mio PID=..., mio figlio F ha PID=...
 * La prima cosa che ciascun processo figlio deve fare appena è stato generato,
 * è dichiararsi nel modo seguente:
 * "F: mio PID=..., mio padre P ha PID=..."
 *
 * Ogni volta che un processo visualizza qualcosa sullo schermo deve dichiararsi nel modo seguente:
 * "P: quello che P deve visualizzare"
 * "F: quello che F deve visualizzare
 *
 * @param argc numero di parametri passati da linea di comando
 * @param argv array di stringhe che contiene i parametri passati da linea di comando
 *
 * @return 0 il programma ritorna 0
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int pid_figlio;
    int status;
    printf("P: mio PID=%d\n", getpid());
    // Processo padre P
    pid_figlio = fork();

    if (pid_figlio == 0)
    { // Processo figlio F
        printf("F: mio PID=%d, mio padre P ha PID=%d\n", getpid(), getppid());
        exit(25); // Terminazione volontaria con valore 25
    }
    else if (pid_figlio > 0)
    { // Processo padre P
        printf("P: mio PID=%d, mio figlio F ha PID=%d\n", getpid(), pid_figlio);

        wait(&status); // Attende la terminazione del figlio

        if (WIFEXITED(status))
        {
            printf("P: Il figlio F è terminato volontariamente con stato %d\n", WEXITSTATUS(status));
        }
        else
        {
            printf("P: Il figlio F non è terminato volontariamente\n");
        }
    }
    else
    {
        printf("Errore nella fork");
        exit(1);
    }

    return 0;
}