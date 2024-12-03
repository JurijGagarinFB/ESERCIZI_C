/**
 * @brief Scrivi il codice sorgente di un programma in cui il processo padre
 * genera tre processi figli. I processi dovranno visualizzare rispettivamente:
 * "Io sono il padre A, il mio PID=..."
 * "Io sono il figlio B, il mio PID=..., il mio nome è Qui"
 * "Io sono il figlio C, il mio PID=..., il mio nome è Quo"
 * "Io sono il figlio D, il mio PID=..., il mio nome è Qua"
 * @param argc Numero di argomenti passati attraverso la riga di comando
 * @param argv Array di stringhe contenente gli argomenti passati attraverso la
 * riga di comando
 *
 * @returns la funzione restituisce 0
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int b, c, d;
  b = fork();
  if (b < 0) {
    printf("Errore generazione figlio\n");
    exit(-1);
  } else if (b == 0) {
    printf("Io sono il figlio B, il mio PID= %d, il mio nome è Qui\n", getpid());
    printf("Mio padre è= %d\n", getppid());
    exit(0);
  } else {
    wait(&b);
    printf("Io sono il padre A, il mio PID= %d\n", getpid());
    c = fork();
    if (c < 0) {
      printf("Errore generazione figlio\n");
      exit(-1);
    } else if (c == 0) {
      printf("Io sono il figlio C, il mio PID= %d, il mio nome è Quo\n", getpid());
      printf("Mio padre è= %d\n", getppid());
      exit(0);
    } else {
      wait(&c);
      d = fork();
      if (d < 0) {
        printf("Errore generazione figlio\n");
        exit(-1);
      } else if (d == 0) {
        printf("Io sono il figlio D, il mio PID= %d, il mio nome è Qua\n", getpid());
        printf("Mio padre è= %d\n", getppid());
        exit(0);
      } else {
        wait(&d);
      }
    }
  }
  printf("programma terminato\n");
  return 0;
}