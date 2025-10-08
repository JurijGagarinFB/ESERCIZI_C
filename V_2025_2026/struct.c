/*
Esercizio - Strutture
Scrivere un programma in C che dopo aver dichiarato una struttura denominata Auto con i seguenti
campi: ModelloAuto, marca, cilindrata, prezzo, anno_immatricolazione, targa; determini:
1) Il prezzo + alto e quello + basso visualizzando anche il modello dell&#39;auto;
2) Ordinare la lista delle auto in base all&#39;anno d&#39;immatricolazione;
3) Visualizzare il nome delle auto a partire da un prezzo scelto dall&#39;utente.
4) Ricerchi un Auto scelta dall’utente (utilizzare il campo targa): visualizzando tutti i campi;
5) La media dei prezzi delle auto inserite;
6) Visualizzare le Auto con anno di immatricolazione scelto dall’utente;
*/

#include <stdio.h>
#include <string.h>

#define PANDA 500

typedef struct
{
    char modelloAuto[PANDA];
    char marca[50];
    int cilindrata;
    float prezzo;
    int anno_immatricolazione;
    char targa[7];
} Auto;

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