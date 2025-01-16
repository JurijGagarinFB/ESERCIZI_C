/**
 * @brief Data una stringa letta da riga di comando si scriva un programma in linguaggio C
 * che istanzi un processo figlio il quale converta la stringa da minuscolo a maiuscolo
 *
 * esempio di esecuzione:
 * $./a.out ciao
 * la stringa in maiuscolo è CIAO
 * 
 * @param argc Numero di argomenti passati attraverso la riga di comando
 * @param argv Array di stringhe contenente gli argomenti passati attraverso la riga di comando
 * 
 * @returns la funzione restituisce 0
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/fcntl.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int p;
    p = fork();

    if (p < 0)
    {
        printf("Errore nella generazione del figlio\n");
        exit(-1);
    }
    else if (p == 0)
    {
        char stringa[strlen(argv[1])];
        for (int i=0; i<strlen(argv[1]); i++){
            stringa[i] = toupper(argv[1][i]);
        }

        for (int i=0; i<strlen(argv[1]); i++){
            printf(stringa[i]);
        }

        exit(0);
    }
    else
    {
        wait(&p);
    }

    printf("Programma terminato");
    return 0;
}