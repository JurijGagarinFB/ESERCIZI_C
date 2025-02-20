/**
 * @brief Scrivi il codice sorgente di un prg in cui:
 * _ il processo PADRE
 * _visualizza il proprio PID
 * _genera 4 figli: F1, F2, F3, F4
 * _ genera 2 numeri interi random, n1, n2
 * compresi tra 1 e 20
 * necessariamente diversi tra loro
 * _visualizza n1 ed n2:
 * a prescindere dal valore di n1 ed n2, 
 * F2 dovrà dormire per un numero di secondi pari a n1 e
 * restituire al padre un numero n2_dim intero compreso tra 2 e 6 estremi compresi;
 * F3  dovrà dormire per un numero di secondi pari a n2 e
 * restituire al padre un numero n3_dim intero compreso tra 2 e 10 estremi inclusi;
 * non si sa chi dormirà di meno o di più ossia
 * non si sa chi tra F2 ed F3 terminerà per primo.
 * _ solo dopo avere generato entrambi (sia F2 e sia F3),
 * attende la loro terminazione:
 * il numero intero restituito da F2 rappresenterà la dimensione dim  del vettore che F1 dovrà generare
 * _per ciascun figlio, il padre visualizza il proprio PID e il PID del proprio figlio
 * 
 * CIASCUN FIGLIO deve:
 * identificrsi dicendo se è F1 o F2 o F3 o F4
 * _ visualizzare il proprio PID e il PID del proprio padre
 * 
 * F1 deve:
 * _ generare il vettore v[ ] di numeri interi di dimensione dim fornito in ingresso dall'utente e compresi tra 1 e 10 estremi inclusi
 * _ calcolarne la somma (somma)
 * 
 * F4 deve:
 * _ calcolare il valore medio (media) dei numeri  fornito in ingresso dall'utente e memorizzati nel vettore e
 * _ restituirlo al padre
 * 
 * Il PADRE deve:
 * visualizzare il proprio PID e il valore restituitogli da F4 
 * con un chiaro messaggio in cui precisa ciò che esso rappresenta:
 * "Sono il padre, il mio PID = ... , il valore medio dei numeri con cui hai popolato il vettore vale ..."
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

int main() {
    int F1, F2, F3, F4;
    int n1, n2, n2_dim, n3_dim, dim;
    float media;
    
    srand(time(NULL));
    
    // Generazione di n1 e n2, assicurandosi che siano diversi
    do {
        n1 = rand() % 20 + 1;
        n2 = rand() % 20 + 1;
    } while (n1 == n2);
    
    printf("Sono il padre, PID = %d, ho generato n1 = %d e n2 = %d\n", getpid(), n1, n2);
    
    // Creazione di F2
    if ((F2 = fork()) == 0) {
        printf("Sono F2, PID = %d, figlio di %d. Dormo %d secondi.\n", getpid(), getppid(), n1);
        sleep(n1);
        n2_dim = rand() % 5 + 2;
        exit(n2_dim);
    }
    
    // Creazione di F3
    if ((F3 = fork()) == 0) {
        printf("Sono F3, PID = %d, figlio di %d. Dormo %d secondi.\n", getpid(), getppid(), n2);
        sleep(n2);
        n3_dim = rand() % 9 + 2;
        exit(n3_dim);
    }
    
    // Attendere terminazione di F2 e F3
    int status;
    waitpid(F2, &status, 0);
    dim = WEXITSTATUS(status);
    printf("F2 terminato, ha restituito dim = %d\n", dim);
    
    waitpid(F3, &status, 0);
    printf("F3 terminato, ha restituito %d\n", WEXITSTATUS(status));
    
    // Creazione di F1
    if ((F1 = fork()) == 0) {
        printf("Sono F1, PID = %d, figlio di %d. Genero un vettore di dimensione %d.\n", getpid(), getppid(), dim);
        int v[dim], somma = 0;
        for (int i = 0; i < dim; i++) {
            v[i] = rand() % 10 + 1;
            somma += v[i];
        }
        printf("F1: Somma degli elementi del vettore = %d\n", somma);
        exit(0);
    }
    waitpid(F1, NULL, 0);
    
    // Creazione di F4
    if ((F4 = fork()) == 0) {
        printf("Sono F4, PID = %d, figlio di %d. Calcolo la media.\n", getpid(), getppid());
        int somma = 0, num;
        for (int i = 0; i < dim; i++) {
            num = rand() % 10 + 1;
            somma += num;
        }
        media = (float)somma / dim;
        exit((int)(media));
    }
    
    waitpid(F4, &status, 0);
    media = WEXITSTATUS(status);
    printf("Sono il padre, il mio PID = %d, il valore medio dei numeri con cui hai popolato il vettore vale %.2f\n", getpid(), media);
    
    return 0;
}
