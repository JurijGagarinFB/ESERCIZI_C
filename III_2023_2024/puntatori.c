//Dopo aver letto un vettore di N elementi utilizzando i puntatori calcolare la media del vettore e determinare il massimo ed il minimo.

#include <stdio.h>
int main(){
    int lunghezza, max, min, somma=0;
    float media;
    printf("Inserire lunghezza del vettore");
    scanf("%d",&lunghezza);
    int vettore[lunghezza];
    int* puntatore = vettore;
    printf("Inserisci gli elementi del vettore");
    for (int i=0; i<lunghezza; i++){
        scanf("%d",puntatore);
        puntatore++;
    }
    for (int i=0; i<lunghezza; i++){
        printf(" %d", vettore[i]);
    }
    printf(" \n");
    puntatore=vettore;
    for (int i=0; i<lunghezza; i++){
        somma += *(puntatore+i);
    }
    printf("%d\n", somma);
    media = (float)somma/lunghezza;
    max = min = vettore[0];
    for (int i=0; i<lunghezza; i++){
        if (*puntatore > max){
            max = *puntatore;
        }
        if (*puntatore < min){
            min = *puntatore;
        }
        puntatore++;
    }
    printf("%d\n", max);
    printf("%d\n", min);
    return 0;
}