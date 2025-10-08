/**
 * @file struct.c
 * @brief Programma di esempio per la gestione di una struct di automobili (Auto).
 *
 * Esempio didattico che mostra come definire una struttura per rappresentare
 * un'autovettura e funzioni di utilità per inserire, ricercare, visualizzare,
 * ordinare e calcolare statistiche sulle auto.
 *
 * Funzionalità implementate:
 * - Inserimento di una nuova auto (con controllo sulla targa duplicata e limite massimo di elementi)
 * - Visualizzazione di tutte le auto
 * - Ricerca di un'auto per targa
 * - Ricerca del prezzo minimo e massimo
 * - Ordinamento per anno di immatricolazione
 * - Visualizzazione delle auto con prezzo minimo scelto
 * - Calcolo della media dei prezzi
 * - Visualizzazione delle auto con un anno di immatricolazione specifico
 *
 * @author JurijGagarinFB
 * @date 08-10-2025
 */

#include <stdio.h>
#include <string.h>

/**
 * @brief Rappresenta i dati principali di un'automobile.
 *
 * Campi:
 * - modelloAuto: nome/modello dell'auto
 * - marca: casa costruttrice
 * - cilindrata: cilindrata in cc
 * - prezzo: prezzo in valuta (float)
 * - anno_immatricolazione: anno di prima immatricolazione
 * - targa: targa dell'auto
 */

typedef struct
{
    char modelloAuto[50];
    char marca[50];
    int cilindrata;
    float prezzo;
    int anno_immatricolazione;
    char targa[8];
} Auto;


/**
 * @brief Stampa su stdout tutti i campi di una singola Auto.
 * @param auto1 Struttura Auto da stampare.
 */

// Funzione di Stampa Auto
void stampaAuto(Auto auto1)
{
    printf("Modello: %s\n", auto1.modelloAuto);
    printf("Marca: %s\n", auto1.marca);
    printf("Cilindrata: %d\n", auto1.cilindrata);
    printf("Prezzo: %.2f\n", auto1.prezzo);
    printf("Anno di Immatricolazione: %d\n", auto1.anno_immatricolazione);
    printf("Targa: %s\n\n", auto1.targa);
}


/**
 * @brief Cerca un'auto nell'array data la sua targa.
 *
 * Scorre l'array di Auto e confronta il campo targa con la stringa fornita.
 *
 * @param autoArray Array di Auto in cui effettuare la ricerca.
 * @param autoCount Numero di elementi validi nell'array.
 * @param targa Stringa contenente la targa da cercare.
 * @return Indice dell'auto trovata nell'array, oppure -1 se non trovata.
 */

// Ricerca Auto per Targa
int cercaAutoPerTarga(Auto autoArray[], int autoCount, char targa[])
{
    for (int i = 0; i < autoCount; i++)
    {
        if (strcmp(autoArray[i].targa, targa) == 0)
        {
            return i;
        }
    }
    return -1; // Non trovata
}


/**
 * @brief Inserisce una nuova Auto nell'array se possibile.
 *
 * Controlla che non si superi il limite massimo (10) e che la targa non sia
 * già presente. In caso di successo copia i dati nella prossima posizione libera.
 *
 * @param nuovoModello Nome/modello dell'auto da inserire.
 * @param nuovaMarca Marca dell'auto.
 * @param nuovaCilindrata Cilindrata (int).
 * @param nuovoPrezzo Prezzo (float).
 * @param nuovoAnno Anno di immatricolazione (int).
 * @param nuovaTarga Targa (string)
 * @param autoArray Array di Auto dove inserire il nuovo elemento.
 * @param autoCount Puntatore al contatore di elementi nell'array; viene incrementato in caso di successo.
 * @return 0 se inserimento avvenuto con successo, -1 se array pieno, -2 se targa già esistente.
 */

// Inserimento Auto
int inserisciAuto(char nuovoModello[], char nuovaMarca[], int nuovaCilindrata, float nuovoPrezzo, int nuovoAnno, char nuovaTarga[], Auto autoArray[], int *autoCount)
{
    if (*autoCount >= 10)
    {
        return -1; // Fallimento
    }

    if (cercaAutoPerTarga(autoArray, *autoCount, nuovaTarga) != -1)
    {
        return -2; // Fallimento
    }
    Auto newAuto;
    strcpy(newAuto.modelloAuto, nuovoModello);
    strcpy(newAuto.marca, nuovaMarca);
    newAuto.cilindrata = nuovaCilindrata;
    newAuto.prezzo = nuovoPrezzo;
    newAuto.anno_immatricolazione = nuovoAnno;
    strcpy(newAuto.targa, nuovaTarga);
    autoArray[*autoCount] = newAuto;
    (*autoCount)++;
    return 0; // Successo
}


/**
 * @brief Visualizza tutte le auto presenti nell'array su stdout.
 * @param autoArray Array di Auto da visualizzare.
 * @param autoCount Numero di elementi validi nell'array.
 */

// Visualizzazione Auto
void visualizzaAuto(Auto autoArray[], int autoCount)
{
    for (int i = 0; i < autoCount; i++)
    {
        printf("Auto %d:\n", i + 1);
        stampaAuto(autoArray[i]);
        printf("\n\n");
    }
}


/**
 * @brief Trova gli indici delle auto con prezzo minimo e massimo.
 *
 * Assuma che autoCount >= 1.
 *
 * @param autoArray Array di Auto da analizzare.
 * @param autoCount Numero di elementi validi nell'array.
 * @param indiceMin Puntatore a intero dove verrà salvato l'indice del prezzo minimo.
 * @param indiceMax Puntatore a intero dove verrà salvato l'indice del prezzo massimo.
 */

// Prezzo Piu' Alto e Basso
void prezzoAltoBasso(Auto autoArray[], int autoCount, int *indiceMin, int *indiceMax)
{
    float prezzoMin = autoArray[0].prezzo;
    float prezzoMax = autoArray[0].prezzo;
    *indiceMin = 0;
    *indiceMax = 0;

    for (int i = 1; i < autoCount; i++)
    {
        if (autoArray[i].prezzo < prezzoMin)
        {
            prezzoMin = autoArray[i].prezzo;
            *indiceMin = i;
        }
        if (autoArray[i].prezzo > prezzoMax)
        {
            prezzoMax = autoArray[i].prezzo;
            *indiceMax = i;
        }
    }
}


/**
 * @brief Ordina l'array di Auto in ordine crescente per anno di immatricolazione.
 * @param autoArray Array di Auto da ordinare.
 * @param autoCount Numero di elementi validi nell'array.
 */

// Ordina per Anno di Immatricolazione
void ordinaPerAnno(Auto autoArray[], int autoCount)
{
    for (int i = 0; i < autoCount - 1; i++)
    {
        for (int j = i + 1; j < autoCount; j++)
        {
            if (autoArray[i].anno_immatricolazione > autoArray[j].anno_immatricolazione)
            {
                Auto temp = autoArray[i];
                autoArray[i] = autoArray[j];
                autoArray[j] = temp;
            }
        }
    }
}


/**
 * @brief Visualizza tutte le auto con prezzo maggiore o uguale a quello indicato.
 * @param autoArray Array di Auto da filtrare.
 * @param autoCount Numero di elementi validi nell'array.
 * @param prezzoMinimo Soglia di prezzo (inclusiva).
 */

// Visualizza Auto con Prezzo Massimo Scelto
void visualizzaAutoConPrezzoMinimo(Auto autoArray[], int autoCount, float prezzoMinimo)
{
    for (int i = 0; i < autoCount; i++)
    {
        if (autoArray[i].prezzo >= prezzoMinimo)
        {
            stampaAuto(autoArray[i]);
            printf("\n\n");
        }
    }
}


/**
 * @brief Calcola la media aritmetica dei prezzi delle auto nell'array.
 * @param autoArray Array di Auto.
 * @param autoCount Numero di elementi validi nell'array.
 * @return Media dei prezzi (float).
 */

// Media Prezzi Auto
float mediaPrezziAuto(Auto autoArray[], int autoCount)
{
    float somma = 0.0;
    for (int i = 0; i < autoCount; i++)
    {
        somma += autoArray[i].prezzo;
    }
    return somma / autoCount;
}


/**
 * @brief Mostra tutte le auto la cui data di immatricolazione corrisponde all'anno fornito.
 * @param autoArray Array di Auto da filtrare.
 * @param autoCount Numero di elementi validi nell'array.
 * @param annoScelto Anno di immatricolazione da cercare.
 */

// Visualizza Auto con Anno di Immatricolazione Scelto
void visualizzaAutoConAnnoScelto(Auto autoArray[], int autoCount, int annoScelto)
{
    for (int i = 0; i < autoCount; i++)
    {
        if (autoArray[i].anno_immatricolazione == annoScelto)
        {
            stampaAuto(autoArray[i]);
            printf("\n\n");
        }
    }
}


/**
 * @brief Punto d'ingresso del programma: gestisce un piccolo menu testuale per l'utente.
 *
 * Il menu permette di eseguire le operazioni implementate dalle funzioni sopra.
 * Non prende argomenti da linea di comando.
 *
 * @return 0 in caso di terminazione corretta.
 */

int main()
{
    //------ Variabili Menu ------
    char menu[] = "AUTO STRUTTURATE\n 1-Inserisci Auto\n 2-Visualizza Auto\n 3-Cerca Auto per Targa\n 4-Prezzo Piu' Alto e Basso\n 5-Ordina per Anno di Immatricolazione\n 6-Visualizza Auto con Prezzo Minimo Scelto\n 7-Media Prezzi Auto\n 8-Visualizza Auto con Anno di Immatricolazione Scelto\n 9-Esci\n";
    int uscita = 0;
    int scelta;
    //------ Variabili Menu ------

    Auto autoArray[10];
    int autoCount = 0;
    do
    {
        printf("%s", menu);
        printf("Scelta: \n");
        scanf("%d", &scelta);
        switch (scelta)
        {
        case 1:
            // Inserisci Auto
            char nuovoModello[50];
            printf("Inserisci Modello Auto: \n");
            scanf("%s", nuovoModello);

            char nuovaMarca[50];
            printf("Inserisci Marca: \n");
            scanf("%s", nuovaMarca);

            int nuovaCilindrata;
            printf("Inserisci Cilindrata: \n");
            scanf("%d", &nuovaCilindrata);

            float nuovoPrezzo;
            printf("Inserisci Prezzo: \n");
            scanf("%f", &nuovoPrezzo);

            int nuovoAnno;
            printf("Inserisci Anno di Immatricolazione: \n");
            scanf("%d", &nuovoAnno);

            char nuovaTarga[7];
            printf("Inserisci Targa (7 caratteri): \n");
            scanf("%s", nuovaTarga);
            int risultato = inserisciAuto(nuovoModello, nuovaMarca, nuovaCilindrata, nuovoPrezzo, nuovoAnno, nuovaTarga, autoArray, &autoCount);
            if (risultato == 0)
            {
                printf("Auto numero %d inserita con successo.\n\n", autoCount);
                stampaAuto(autoArray[autoCount - 1]);
            }
            else if (risultato == -1)
            {
                printf("Errore: Limite massimo di auto raggiunto.\n\n");
            }
            else if (risultato == -2)
            {
                printf("Errore: Targa gia' esistente.\n\n");
            }
            break;

        case 2:
            // Visualizza Auto
            if (autoCount == 0)
            {
                printf("Nessuna auto inserita.\n\n");
                break;
            }
            visualizzaAuto(autoArray, autoCount);
            break;

        case 3:
            // Cerca Auto per Targa
            if (autoCount == 0)
            {
                printf("Nessuna auto inserita.\n\n");
                break;
            }
            char targaCercata[7];
            printf("Inserisci Targa da Cercare: \n");
            scanf("%s", targaCercata);
            int indice = cercaAutoPerTarga(autoArray, autoCount, targaCercata);
            if (indice != -1)
            {
                printf("Auto trovata:\n");
                stampaAuto(autoArray[indice]);
            }
            else
            {
                printf("Auto con targa %s non trovata.\n\n", targaCercata);
            }
            break;

        case 4:
            // Prezzo Piu' Alto e Basso
            if (autoCount == 0)
            {
                printf("Nessuna auto inserita.\n\n");
                break;
            }

            int indiceMin, indiceMax;
            prezzoAltoBasso(autoArray, autoCount, &indiceMin, &indiceMax);
            printf("Auto con Prezzo Minimo:\n");
            stampaAuto(autoArray[indiceMin]);
            printf("Auto con Prezzo Massimo:\n");
            stampaAuto(autoArray[indiceMax]);
            break;

        case 5:
            // Ordina per Anno di Immatricolazione
            if (autoCount == 0)
            {
                printf("Nessuna auto inserita.\n\n");
                break;
            }
            ordinaPerAnno(autoArray, autoCount);
            printf("Auto ordinate per Anno di Immatricolazione:\n");
            visualizzaAuto(autoArray, autoCount);
            break;

        case 6:
            // Visualizza Auto con Prezzo Minimo Scelto
            if (autoCount == 0)
            {
                printf("Nessuna auto inserita.\n\n");
                break;
            }
            float prezzoMinimo;
            printf("Inserisci Prezzo Minimo: \n");
            scanf("%f", &prezzoMinimo);
            printf("Auto con Prezzo Minimo di %.2f:\n", prezzoMinimo);
            visualizzaAutoConPrezzoMinimo(autoArray, autoCount, prezzoMinimo);
            break;

        case 7:
            // Media Prezzi Auto
            if (autoCount == 0)
            {
                printf("Nessuna auto inserita.\n\n");
                break;
            }
            float mediaPrezzi = mediaPrezziAuto(autoArray, autoCount);
            printf("Media dei Prezzi delle Auto: %.2f\n", mediaPrezzi);
            break;

        case 8:
            // Visualizza Auto con Anno di Immatricolazione Scelto
            if (autoCount == 0)
            {
                printf("Nessuna auto inserita.\n\n");
                break;
            }
            int annoScelto;
            printf("Inserisci Anno di Immatricolazione da Cercare: \n");
            scanf("%d", &annoScelto);
            printf("Auto con Anno di Immatricolazione %d:\n", annoScelto);
            visualizzaAutoConAnnoScelto(autoArray, autoCount, annoScelto);
            break;

        case 9:
            uscita = 1;
            printf("Uscita dal programma.\n\n");
            break;

        default:
            printf("Scelta non valida. Riprova.\n\n");
            break;
        }
    } while (uscita != 1);

    return 0;
}