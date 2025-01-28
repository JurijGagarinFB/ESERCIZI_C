/**
 * @brief Scrivere un programma in linguaggio C che legge da argv una serie di stringhe,
 * le ordina in senso crescente o decrescente in funzione del flag usato in argv[2].
 * Si utilizzi un algoritmo di ordinamento a scelta. Si scriva il risultato
 * sia a video che su un file il cui nome risiede in argv[1].
 *
 * Esempio:
 * $ ./a.out file.txt --asc ciao a tutti
 * a
 * ciao
 * tutti
 *
 * $ cat file.txt
 * a
 * ciao
 * tutti
 *
 * Esempio:
 * $ ./a.out file.txt --desc ciao a tutti
 * tutti
 * ciao
 * a
 *
 * $ cat file.txt
 * tutti
 * ciao
 * a
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
#include <sys/types.h>
#include <string.h>

void swapAsc(int argc, char *argv[])
{
    int i, j;
    char *temp;

    for (i = 3; i < argc - 1; i++)
    {
        for (j = 3; j < argc - (i - 2); j++)
        {
            if (strcmp(argv[j], argv[j + 1]) > 0)
            {
                temp = argv[j];
                argv[j] = argv[j + 1];
                argv[j + 1] = temp;
            }
        }
    }
}

void swapDesc(int argc, char *argv[])
{
    int i, j;
    char *temp;

    for (i = 3; i < argc - 1; i++)
    {
        for (j = 3; j < argc - (i - 2); j++)
        {
            if (strcmp(argv[j], argv[j + 1]) < 0)
            {
                temp = argv[j];
                argv[j] = argv[j + 1];
                argv[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[])
{

    if (argc < 5)
    {
        printf("Numero argomenti sbagliato\n");
        exit(1);
    }

    if (strcmp(argv[2], "--desc") == 0)
    {
        swapDesc(argc, argv);
    }
    else if (strcmp(argv[2], "--asc") == 0)
    {
        swapAsc(argc, argv);
    }
    else
    {
        printf("Flag Sbagliata\n");
        exit(1);
    }

    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    for (int i = 3; i < argc; i++)
    {
        write(fd, argv[i], strlen(argv[i]));
        write(fd, "\n", strlen("\n"));

        write(1, argv[i], strlen(argv[i]));
        write(1, "\n", strlen("\n"));
    }
    close(fd);

    return 0;
}