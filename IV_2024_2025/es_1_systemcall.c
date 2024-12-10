

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * @brief Utilizzando le system call open, read, write, close leggere il file rfc1918.txt e stamparlo a video.
 * Il programa deve essere cosi invocato:
 * $./a.out rfc1918.txt
 * Consiglio: leggere un carratere per volta
 *
 * @param argc Numero di argomenti passati attraverso la riga di comando
 * @param argv Array di stringhe contenente gli argomenti passati attraverso la riga di comando
 *
 * @return il programma ritorna 0
 */

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Numero di argomenti inseriti non valido\n");
        return 1;
    }
    char pathname[] = {'r', 'f', 'c', '1', '9', '1', '8', '.', 't', 'x', 't'};
    int sus = open(&pathname, O_RDWR);
    int pos = read(sus, 0, 22.269);
    for (int i=0; i<pos; i++){
        printf("%d", sus);
    }
    int chiusura = close(sus);
    return 0;
}