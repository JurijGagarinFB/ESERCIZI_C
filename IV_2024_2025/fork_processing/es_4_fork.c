

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int ricerca(int numero, int array[], int dim)
{
    for (int i = 0; i < dim; i++)
    {
        if (array[i] == numero)
        {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Scriva un programma C che dato un array prestabilito, prenda in input da
 * riga di comando un numero e lo ricerchi all'interno dell'array.
 * La ricerca deve essere demandata ad un processo figlio e deve essere
 * implementata attraverso un'apposita funzione di nome ricerca.
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
    int array[] = {1, 2, 3, 7, 9};
    int dim = sizeof(array);

    int pid = fork();
    if (pid == -1)
    {
        printf("Errore nella fork");
        return 2;
    }

    if (pid == 0)
    {
        int trovato = ricerca(atoi(argv[1]), array, dim);
        if (trovato == -1)
        {
            printf("Numero non trovato\n");
        }
        else
        {
            printf("Numero trovato in posizione %d\n", trovato);
        }
        exit(0);
    }
    else
    {
        wait(&pid);
        printf("\n\nMio figlio ha terminato\n\n");
    }

    return 0;
}