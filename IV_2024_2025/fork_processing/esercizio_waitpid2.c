/**
 * @brief Scrivi il codice
 * sorgente di un programma in cui il processo padre P1 genera un processo figlio P2
 * P2
 * genera un vettore v[] di 5 numeri interi, forniti in input dall’utente >> N.B.
 * Fare attenzione!!!
 * visualizza il
 * contenuto del vettore
 * calcola la somma dei numeri del vettore che, però, verrà visualizzata dal padre P1
 * successivamente, genera il processo figlio P3
 * P3
 * calcola il valore minimo tra i numeri del vettore
 * P2
 * attende la terminazione di P3 e visualizza il valore minimo
 * successivamente, genera il processo figlio P4
 * P4
 * calcola il valore massimo tra i numeri del vettore
 * P2
 * attende la terminazione di P4 e visualizza il valore massimo
 * successivamente, genera il processo figlio P5
 * P5
 * calcola il valore medio tra i numeri del vettore
 * P2
 * attende la terminazione di P5 e visualizza il valore medio
 *
 * \La prima cosa che ciascun processo deve fare, appena genera un processo figlio,
 * è dichiararsi nel modo seguente:
 * "P1: mio PID=..., mio figlio P2 ha PID=..."
 * La prima cosa che ciascun processo figlio deve fare appena è stato generato,
 * è dichiararsi nel modo seguente:
 * "P2: mio PID=..., mio padre P1 ha PID=..."
 *
 * Ogni volta che un processo visualizza qualcosa sullo schermo deve dichiararsi nel modo seguente:
 * "P1 mio PID=...: quello che P1 deve visualizzare"
 * "Pn mio PID=...: quello che Pn deve visualizzare"
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
    int v[5];
    int P2, P3, P4, P5;
    int somma = 0, min, max;
    float media;

    P2 = fork();
    if (P2 < 0)
    {
        printf("Fork fallita");
        exit(1);
    }
    else if (P2 == 0)
    { // P2
        printf("P2: mio PID= %d, mio padre P1 ha PID= %d\n", getpid(), getppid());

        // Input vettore
        printf("P2 mio PID= %d: Inserisci %d numeri interi:\n", getpid(), 5);
        for (int i = 0; i < 5; i++)
        {
            scanf("%d", &v[i]);
        }

        // Visualizzazione del vettore
        printf("P2 mio PID=%d: Contenuto del vettore:", getpid());
        for (int i = 0; i < 5; i++)
        {
            printf(" %d", v[i]);
        }
        printf("\n");

        // Creazione di P3
        P3 = fork();
        if (P3 == 0)
        { // P3
            printf("P3: mio PID= %d, mio padre P2 ha PID= %d\n", getpid(), getppid());

            min = v[0];
            for (int i = 1; i < 5; i++)
            {
                if (v[i] < min)
                    min = v[i];
            }
            exit(min);
        }

        int status;
        waitpid(P3, &status, 0);
        min = WEXITSTATUS(status);
        printf("P2 mio PID= %d: Valore minimo= %d\n", getpid(), min);

        // Creazione di P4
        P4 = fork();
        if (P4 == 0)
        { // P4
            printf("P4: mio PID= %d, mio padre P2 ha PID= %d\n", getpid(), getppid());

            max = v[0];
            for (int i = 1; i < 5; i++)
            {
                if (v[i] > max)
                    max = v[i];
            }
            exit(max);
        }

        waitpid(P4, &status, 0);
        max = WEXITSTATUS(status);
        printf("P2 mio PID= %d: Valore massimo= %d\n", getpid(), max);

        // Creazione di P5
        P5 = fork();
        if (P5 == 0)
        { // P5
            printf("P5: mio PID= %d, mio padre P2 ha PID= %d\n", getpid(), getppid());

            int somma = 0;
            for (int i = 0; i < 5; i++)
            {
                somma += v[i];
            }
            media = (float)somma / 5;
            exit((int)(media));
        }

        waitpid(P5, &status, 0);
        media = WEXITSTATUS(status);
        printf("P2 mio PID= %d: Valore medio= %.1f\n", getpid(), media);

        exit(0);
    }

    // Processo padre P1 attende P2
    int status;
    waitpid(P2, &status, 0);
    printf("P1 mio PID= %d: Processo P2 terminato\n", getpid());

    return 0;
}
