/*
Esercizio Gestione del Vettore
Scrivere un programma in C che effettui, attraverso un menÃ¹, le seguenti operazione sugli array:
1) Visualizzi a video gli elementi dellâ€™array inseriti o generati casualmente;
2) Visualizzi a video lâ€™array invertito, cioÃ¨, sostituendo il primo elemento con lâ€™ultimo, il secondo con il
penultimo e cosÃ¬ via;
3) Visualizzi a video la somma e media degli elementi del vettore;
4) Visualizzi a video tutti i numeri pari;
5) Visualizzi a video tutti i numeri dispari;
6) Ricerchi un numero (letto in input) nellâ€™array;
7) Elimini un elemento (letto in input) dellâ€™array (se esistente);
8) Alterni (o scambi) a due a due le posizioni del vettore: esempio
vettore: 1,2,3,4 vettore alternato: 2,1,4,3 (attenzione se lungo dispari);
9) Ordini il vettore (ordinamento a scelta).
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char *argv[])
{
    //inizializzo la funzione per randomizzare
    srand(time(NULL));
    //inizializzo la lunghezza del vettore generata randomicamente
    int lunghezzaVettore = rand() % 100 + 1;
    //dichiaro il vettore di lunghezza lunghezzaVettore
    int vettore[lunghezzaVettore];

    printf("MENU \n 1)Genera e visualizza un array \n");
    //ciclo for che riempe il vettore con numeri generati randomicamente (consegna 1)
    for (int i = 0; i < lunghezzaVettore; i++){
        vettore[i] = rand() % 100 + 1;
        printf("%d", vettore[i]);
    }



    return 0;
}
