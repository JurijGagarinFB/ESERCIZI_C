#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int p1 = fork();
    
    if (p1 > 0)
    {
        int p2 = fork();
        if (p2 > 0) {
            // Processo padre principale
            printf("Io sono il padre: PID=%d\n", getpid());
            printf("I miei figli hanno PID P1=%d, PID P2=%d\n\n", p1, p2);
        }
        else if (p2 == 0) {
            // Processo figlio P2
            printf("Io sono il figlio P2: PID=%d\n", getpid());
            printf("Mio padre ha PID=%d\n\n", getppid());
            
            // Creazione dei figli P4 e P5
            int p4 = fork();
            if (p4 > 0) {
                int p5 = fork();
                if (p5 > 0) {
                    // Processo P2
                    printf("Io sono P2: PID=%d\n", getpid());
                    printf("Mio figlio P4 ha PID=%d, Mio figlio P5 ha PID=%d\n\n", p4, p5);
                }
                else if (p5 == 0) {
                    // Processo P5
                    printf("Io sono il figlio P5: PID=%d\n", getpid());
                    printf("Mio padre ha PID=%d\n\n", getppid());
                }
                else {
                    printf("Errore nella creazione del figlio P5\n");
                }
            }
            else if (p4 == 0) {
                // Processo P4
                printf("Io sono il figlio P4: PID=%d\n", getpid());
                printf("Mio padre ha PID=%d\n\n", getppid());
            }
            else {
                printf("Errore nella creazione del figlio P4\n");
            }
        }
        else {
            printf("Errore nella creazione del figlio P2\n");
        }
    }
    else if (p1 == 0)
    {
        // Processo figlio P1
        printf("Io sono il figlio P1: PID=%d\n", getpid());
        printf("Mio padre ha PID=%d\n\n", getppid());

        // Creazione del figlio P3
        int p3 = fork();
        if (p3 > 0) {
            // Processo P1
            printf("Io sono P1: PID=%d\n", getpid());
            printf("Mio figlio P3 ha PID=%d\n\n", p3);
        }
        else if (p3 == 0) {
            // Processo P3
            printf("Io sono il figlio P3: PID=%d\n", getpid());
            printf("Mio padre ha PID=%d\n\n", getppid());
        }
        else {
            printf("Errore nella creazione del figlio P3\n");
        }
    }
    else {
        printf("Errore nella creazione del figlio P1\n");
    }
    return 0;
}
