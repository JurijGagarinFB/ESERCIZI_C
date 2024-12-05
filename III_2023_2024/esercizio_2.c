/******************************************************************************
19/12/2023
Su una somma di denaro (relativa all'acquisto di un prodotto) si vuole applicare
uno sconto in base all'importo inserito seguendo il seguente schema:
            da 0 a 500€ sconto del 10%;
            da 501 a 1000 sconto del 20%;
            oltre i 1001 sconto 30%;
Il programma dopo aver calcolato e visualizzato a video lo sconto ed il prezzo
netto deve permettere di re-inserire ulteriori somme di denaro.
*******************************************************************************/

#include <stdio.h>

int main()
{
    // Dichiarazione delle variabili
    int spesa, scelta, scontrino;

    do {
        do {
            // Richiesta dell'importo speso al cliente con validazione dell'input
            printf("Quanto ha speso il cliente?\n");
            scanf("%d", &spesa);

            // Validazione dell'input per assicurarsi che l'importo sia positivo
            if (spesa < 0)
                printf("Hai inserito un numero errato. Reinserisci\n");

        } while (spesa < 0);

        // Calcolo dello sconto in base all'importo della spesa
        if (spesa < 501) {
            // Sconto del 10% per spese fino a 500€
            scontrino = spesa - ((spesa / 100) * 10);
        } else if (spesa < 1001) {
            // Sconto del 20% per spese da 501€ a 1000€
            scontrino = spesa - ((spesa / 100) * 20);
        } else {
            // Sconto del 30% per spese superiori a 1000€
            scontrino = spesa - ((spesa / 100) * 30);
        }

        // Visualizzazione del prezzo netto dopo lo sconto
        printf("Il cliente deve pagare %d euro\n", scontrino);

        // Chiede all'utente se desidera inserire un altro importo
        printf("C'e' un'altro cliente? 1=si\n");
        scanf("%d", &scelta);

    } while (scelta == 1);

    return 0;
}
