#include <stdio.h>
#include <string.h>

/*
struct Persona
{
    char nome[50];
    char cognome[50];
    int eta;
    float altezza;
};
*/

typedef struct
{
    char nome[50];
    char cognome[50];
    int eta;
    float altezza;
} Persona;

void stampaPersona(Persona p)
{
    printf("Nome: %s\n", p.nome);
    printf("Cognome: %s\n", p.cognome);
    printf("Eta': %d\n", p.eta);
    printf("Altezza: %.2f\n", p.altezza);
}

void aggiornaEta(Persona *p, int nuovaEta)
{
    (*p).eta = nuovaEta;
}

int main()
{
    Persona p1 = {"Mario", "Rossi", 30, 1.75};
    pritf("Età prima della modifica: %d\n", p1.eta);
    aggiornaEta(&p1, 31);
    printf("Età dopo la modifica: %d\n", p1.eta);
    return 0;
}