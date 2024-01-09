/*
09/01/2024
Dato un numero N intero positivo, stampare la somma dei primi N numeri primi alternati (uno sì e uno no)
*/

#include <stdio.h>

int main() {
    int numeroPrimi, x = 1, somma = 0, contatore = 0;

    // Chiede all'utente di inserire il numero di numeri primi da stampare
    printf("Inserisci un numero");
    scanf("%d", &numeroPrimi);

    // Assicura che il numero sia maggiore di 0
    while (numeroPrimi <= 0) {
        printf("Numero non valido, riprova");
        scanf("%d", &numeroPrimi);
    }

    // Trova e somma i primi numeri primi alternati fino al raggiungimento di numeroPrimi
    while (numeroPrimi > 0) {
        int èPrimo = 1;
        x = x + 1;

        // Verifica se x è un numero primo
        for (int i = 2; i < x; i++) {
            // Controlla il resto della divisione x/i
            if (x % i == 0) {
                èPrimo = 0; // Il numero non è primo
                i = x; // Uscita anticipata dal ciclo for
            }
        }

        // Se x è primo, controlla se il contatore è pari e somma
        if (èPrimo == 1) {
            if (contatore % 2 == 0) {
                printf("%d\n", x);
                numeroPrimi--;
                somma = somma + x;
            }
            contatore++;
        }
    }

    // Stampa la somma
    printf("La somma è: %d", somma);

    return 0;
}
