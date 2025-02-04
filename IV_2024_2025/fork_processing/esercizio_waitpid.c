/**
 * @brief Scrivi il codice sorgente di un prg in cui
 * il processo padre P genera due figli: F1 e  F2.
 *
 * A F1 assegna un tempo t di sleep(t) (ritardo) 2 secondi;
 * F1 deve restituire al padre P il numero 2.
 * A F2 assegna un tempo t di sleep(t) (ritardo) 4 secondi;
 * F2 deve restituire al padre P il numero 4.
 *
 * Padre P deve attendere la terminazione del figlio che dorme di piÃ¹, ossia F2, e
 * deve scrivere quanti secondi ha dormito tale figlio.
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
 * "..."
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
        sleep(2);
        printf("F1: terminato dopo 2 secondi\n");
        exit(2);
    }
    else if (f1 > 0)
    {
        int f2 = fork();

        if (f2 == 0)
        { // Processo figlio F2
            printf("F2: mio PID=%d, mio padre P ha PID=%d\n", getpid(), getppid());
            sleep(4);
            printf("F2: terminato dopo 4 secondi\n");
            exit(4);
        }
        else if (f2 > 0)
        {
            // Processo padre attende la terminazione del figlio che dorme di più (F2)
            waitpid(f2, &status2, 0);
            int res2 = WEXITSTATUS(status2);
            printf("P: il figlio F2 ha dormito %d secondi\n", res2);
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
