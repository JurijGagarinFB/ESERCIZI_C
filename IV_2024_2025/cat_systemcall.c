/**
 * @brief Utilizzando le system call open, read, write, close leggere il file
 * rfc1918.txt e stamparlo a video. Il programa deve essere cosi invocato:
 * $./a.out rfc1918.txt
 * Consiglio: leggere un carratere per volta
 *
 * @param argc numero di parametri passati da linea di comando
 * @param argv array di stringhe che contiene i parametri passati da linea di comando
 *
 * @return 0 il programma ritorna 0
 */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  int fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    printf("Errore apertura file\n");
    exit(0);
  } else {
    char x;
    int n_letto;
    int n_scritto;
    while (n_letto = read(fd, &x, sizeof(x)) > 0) {
      n_scritto = write(1, &x, n_letto);
    }
  }
  return 0;
}