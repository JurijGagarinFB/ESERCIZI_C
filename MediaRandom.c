/*
Partire da un array di dimensione voluta dall'utente, generare randomicamente dei numeri interi, ordinare l'array,
creare un nuovo array senza doppioni. Fare la media dei due array finali (con doppioni ordinato e senza doppioni)
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));  // Inizializza il generatore di numeri casuali (srand indica da dove inizia il generatore di numeri casuali, con argomento )
    int lunghezza;
    float mediaArrayNoDoppioni, mediaArray;

    printf("Inserisci la lunghezza dell'array \n");
    scanf("%d", &lunghezza);

    int array[lunghezza];
    for (int i = 0; i < lunghezza; i++) {
        array[i] = rand() % 10;  // Popola l'array con numeri casuali tra 0 e 9
    }

    // Ordinamento dell'array usando Bubble Sort
    for (int i = 0; i < lunghezza - 1; i++) {
        for (int j = 0; j < lunghezza - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }

    int arrayNoDoppioni[lunghezza];
    int lunghezzaNoDoppioni = 0;

    // Rimuove i doppioni dall'array ordinato
    arrayNoDoppioni[0] = array[0];
    lunghezzaNoDoppioni = 1;

    for (int i = 1; i < lunghezza; i++) {
        if (array[i] != array[i - 1]) {
            arrayNoDoppioni[lunghezzaNoDoppioni] = array[i];
            lunghezzaNoDoppioni++;
        }
    }

    float sommaMedia = 0;
    for (int i = 0; i < lunghezza; i++) {
        sommaMedia += array[i];
    }

    mediaArray = sommaMedia / lunghezza;
    sommaMedia = 0;

    for (int i = 0; i < lunghezzaNoDoppioni; i++) {
        sommaMedia += arrayNoDoppioni[i];
    }

    mediaArrayNoDoppioni = sommaMedia / lunghezzaNoDoppioni;

    printf("Media array con doppioni: %f \n", mediaArray);
    printf("Media array senza doppioni: %f \n", mediaArrayNoDoppioni);
    if (mediaArray>mediaArrayNoDoppioni){
        printf("La media maggiore è quella con doppioni");
    }else{
        printf("La media maggiore è quella senza doppioni");
    }
  
    return 0;
}
