/**
 * @brief Scrivi il codice sorgente di un programma in
 * cui il processo padre P1 genera un vettore V[3] di
 * tre numeri interi casuali appartenenti all'intervallo [0;5] estremi compresi.
 * Successivamente, P1 genera due processi figli: P2 e P3.
 *
 * P2 genera due figli, P4 e P5:
 * P4 calcola e visualizza il prodotto delle componenti del vettore V[];
 * P5 calcola e visualizza la media delle componenti del vettore V[].
 *
 * P3 visualizza le componenti del vettore V[], genera un figlio P6 che calcola la somma delle
 * componenti di V[] e restituisce il risultato al padre P3 che la visualizza.
 *
 * La prima cosa che ciascun processo deve fare, appena genera un processo figlio,
 * è dichiararsi nel modo seguente (esempio): "P1: mio PID=..., mio figlio P2 ha PID=..."
 * La prima cosa che ciascun processo figlio deve fare appena è stato generato,
 * è dichiararsi nel modo seguente: "P2: mio PID=..., mio padre P1 ha PID=..."
 * Ogni volta che un processo visualizza qualcosa sullo schermo deve dichiararsi nel modo seguente:
 * "P4: quello che P4 deve visualizzare" "P5: quello che P4 deve visualizzare"
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
#include <time.h>

int main(int argc, char *argv[])
{
    int V[3]; // Vettore di 3 numeri interi
    int status;

    // Generazione del vettore di numeri casuali
    srand(time(NULL));
    for (int i = 0; i < 3; i++)
    {
        V[i] = rand() % 6; // Numeri casuali nell'intervallo [0, 5]
    }

    printf("P1: mio PID=%d, sto generando i processi figli P2 e P3...\n", getpid());

    int p2 = fork();

    if (p2 == 0)
    { // Processo P2
        printf("P2: mio PID=%d, mio padre P1 ha PID=%d\n", getpid(), getppid());

        int p4 = fork();

        if (p4 == 0)
        { // Processo P4
            printf("P4: mio PID=%d, mio padre P2 ha PID=%d\n", getpid(), getppid());
            int prodotto = 1;
            for (int i = 0; i < 3; i++)
            {
                prodotto *= V[i];
            }
            printf("P4: il prodotto delle componenti del vettore V[] = %d\n", prodotto);
            exit(0);
        }
        else if (p4 > 0)
        {
            int p5 = fork();

            if (p5 == 0)
            { // Processo P5
                printf("P5: mio PID=%d, mio padre P2 ha PID=%d\n", getpid(), getppid());
                float media = 0;
                for (int i = 0; i < 3; i++)
                {
                    media += V[i];
                }
                media /= 3;
                printf("P5: la media delle componenti del vettore V[] = %.2f\n", media);
                exit(0);
            }
            else if (p5 > 0)
            {
                wait(&status); // Attende la terminazione di P4
                wait(&status); // Attende la terminazione di P5
                exit(0);
            }
            else
            {
                printf("Errore nella fork() per P5\n");
            }
        }
        else
        {
            printf("Errore nella fork() per P4\n");
        }
    }
    else if (p2 > 0)
    {
        int p3 = fork();

        if (p3 == 0)
        { // Processo P3
            printf("P3: mio PID=%d, mio padre P1 ha PID=%d\n", getpid(), getppid());
            printf("P3: le componenti del vettore V[] = [%d, %d, %d]\n", V[0], V[1], V[2]);

            int p6 = fork();

            if (p6 == 0)
            { // Processo P6
                printf("P6: mio PID=%d, mio padre P3 ha PID=%d\n", getpid(), getppid());
                int somma = 0;
                for (int i = 0; i < 3; i++)
                {
                    somma += V[i];
                }
                printf("P6: la somma delle componenti del vettore V[] = %d\n", somma);
                exit(somma); // Restituisce la somma al padre P3
            }
            else if (p6 > 0)
            {
                wait(&status); // Attende la terminazione di P6
                int somma = WEXITSTATUS(status);
                printf("P3: mio figlio P6 mi ha passato la somma = %d\n", somma);
                exit(0);
            }
            else
            {
                printf("Errore nella fork() per P6\n");
            }
        }
        else if (p3 > 0)
        {
            wait(&status); // Attende la terminazione di P2
            wait(&status); // Attende la terminazione di P3
        }
        else
        {
            printf("Errore nella fork() per P3\n");
        }
    }
    else
    {
        printf("Errore nella fork() per P2\n");
    }

    return 0;
}
