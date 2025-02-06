/**
 * @brief Scrivere un programma in linguaggio C che usa il comando
 * della shell cat per mostrare a video un file di testo
 * presente in argv[1]
 *
 * esempio:
 * $ ./a.out costituzione.txt
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
#include <string.h>
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Inserisci una quantità valida di argomenti\n");
        exit(2);
    }

    execlp("cat", "cat", argv[1], NULL);

    return 0;
}