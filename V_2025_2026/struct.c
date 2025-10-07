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

typedef struct
{
    char ModelloAuto[50];
    char Marca[50];
    int cilindrata;
    float prezzo;
    int anno_immatricolazione;
    char targa[10];
} Auto;

void stampaAuto(Auto mobile)
{
    printf("Nome: %s\n", p.nome);
    printf("Cognome: %s\n", p.cognome);
    printf("Eta': %d\n", p.eta);
    printf("Altezza: %.2f\n", p.altezza);
}

void aggiornaEta(Auto *p, int nuovaEta)
{
    (*p).eta = nuovaEta;
}

int main()
{
    char menu[] = "AUTO STRUTTURATE\n 1-Inserisci Auto\n 2-Visualizza Auto\n 3-Cerca Auto per Targa\n 4-Prezzo Piu' Alto e Basso\n 5-Ordina per Anno di Immatricolazione\n 6-Visualizza Auto con Prezzo Minimo Scelto\n 7-Media Prezzi Auto\n 8-Visualizza Auto con Anno di Immatricolazione Scelto\n 9-EscI\n";
    int uscita = 0;
    int scelta;
    do{
        printf("%s", menu);
        printf("Scelta: ");
        scanf("%d", &scelta);
        switch (scelta)
        {
        case 1:
            // Inserisci Auto
            break;
        case 2:
        default:
            break;
        }
    }while (uscita != 1);
    
    return 0;
}