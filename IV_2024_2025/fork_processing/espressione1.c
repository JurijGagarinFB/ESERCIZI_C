/**
 * @brief Scrivi il codice sorgente di un prg in cui
 * il processo padre P genera due processi figli: F1 e F2.
 * F1 somma 1+2;
 * F2 somma 3+4.
 * Entrambi restituiscono al processo padre P il risultato ottenuto dall'operazione compiuta.
 * Padre P somma tra loro i risultati che i due figli gli hanno restituito e
 * visalizza il valore di tale somma
 *
 * La prima cosa che ciascun processo deve fare, appena genera un processo figlio,
 * è dichiararsi nel modo seguente:
 * "P: mio PID=..., mio figlio F1 ha PID=...
 * La prima cosa che ciascun processo figlio deve fare appena è stato generato,
 * è dichiararsi nel modo seguente:
 * "F1: mio PID=..., mio padre P ha PID=..."
 *
 * Ogni volta che un processo visualizza qualcosa sullo schermo deve dichiararsi nel modo seguente:
 * "P: quello che P deve visualizzare"
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

int main()
{
    int status1, status2;

    printf("P: mio PID=%d, sto generando i processi figli F1 e F2...\n", getpid());

    int f1 = fork();

    if (f1 == 0)
    { // Processo figlio F1
        printf("F1: mio PID=%d, mio padre P ha PID=%d\n", getpid(), getppid());
        int risultato = 1 + 2;
        printf("F1: risultato della somma 1+2 = %d\n", risultato);
        exit(risultato);
    }
    else if (f1 > 0)
    {
        int f2 = fork();

        if (f2 == 0)
        { // Processo figlio F2
            printf("F2: mio PID=%d, mio padre P ha PID=%d\n", getpid(), getppid());
            int risultato = 3 + 4;
            printf("F2: risultato della somma 3+4 = %d\n", risultato);
            exit(risultato);
        }
        else if (f2 > 0)
        {
            // Processo padre attende i figli
            wait(&status1);
            int res1 = WEXITSTATUS(status1);
            wait(&status2);
            int res2 = WEXITSTATUS(status2);

            int totale = res1 + res2;
            printf("P: somma dei risultati ricevuti da F1 e F2 = %d\n", totale);
        }
        else
        {
            printf("Errore nella fork() per F2\n");
        }
    }
    else
    {
        printf("Errore nella fork() per F1\n");
    }

    return 0;
}
