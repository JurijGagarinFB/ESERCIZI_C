/**
 * @brief Scrivere un programma in linguaggio C che usa il comando
 * della shell rm per eliminare tutti files presenti
 * nell'intervallo [argv[1], argv[argc-1]]
 *
 * esempio:
 * $ ./a.out /tmp/1.txt /tmp/3.txt /tmp/2.txt
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
    if (argc < 2)
    {
        printf("Inserisci una quantità valida di argomenti\n");
        exit(2);
    }

    for (int i = 1; i < argc; i++)
    {
        int test = fork();
        if (test == 0)
        {
            execlp("rm", "rm", argv[i], NULL);
        }
    }
    return 0;
}