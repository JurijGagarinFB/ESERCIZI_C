/**
 * @brief Scrivere un programma in linguaggio C che scriva l'alfabeto su un file
 * il cui nome deve essere letto da argv[1]
 *
 * @param argc numero di parametri passati da linea di comando
 * @param argv array di stringhe che contiene i parametri passati da linea di comando
 *
 * @return 0 il programma ritorna 0
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{

    char alfabeto[] = "a b c d e f g h i j k l m n o p q r s t u v w x y z";

    if (argc != 2)
    {
        printf("Errore: devi passare il nome del file come argomento.\n");
        exit(2);
    }

    int fd = open(argv[1], O_WRONLY | O_CREAT, 0777);
    if (fd == -1)
    {
        perror("Errore nell'aprire il file");
        exit(1);
    }

    int n_scritto = write(fd, alfabeto, strlen(alfabeto));
    close(fd);
    return 0;
}
