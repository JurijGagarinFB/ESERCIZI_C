/**
 * @brief Scrivere un programma in linguaggio C che usa il comando 
 * della shell cp per copiare un file da una posizione 
 * sorgente ad una posizione destinazione
 * 
 * esempio:
 * $ ./a.out costituzione.txt /tmp/costituzione.txt
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
    if (argc != 3)
    {
        printf("Inserisci una quantità valida di argomenti\n");
        exit(2);
    }

    execlp("cp", "cp", argv[1], argv[2], NULL);

    return 0;
}