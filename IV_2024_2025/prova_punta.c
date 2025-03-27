#include <stdio.h>
int main()
{
    char car;
    printf("\nInserisci un carattere da tastiera >>");
    // getc() Legge un singolo carattere da file o dallo standard di input >> tastiera
    car = getc(stdin); // Legge un singolo carattere dallo standard di input >> tastiera
    printf("\nHai inserito: %c\n", car);
    // putc() scrive un singolo carattere su un file o su un dispositivo di output specifico >> monitor
    putc(car, stdout); // Scrive un singolo carattere sullo standard di otput >> monitor

    // Scrivo un singolo carattere su file
    FILE *fp;
    fp = fopen("output.txt", "w");
    if (fp != NULL) // apertura file avvenuta con successo
    {
        printf("\nApertura file avvenuta con successo\n\n");
        putc(car, fp);
        fclose(fp);
    }
    else
        printf("\nImpossibile aprire il file\n\n");
    // Scriveo un singolo carattere su un dispositivo di output specifico >> monitor
    putchar(car);
    printf("\n");
    return 0;
}