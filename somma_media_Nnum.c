// Dopo aver inserito N numeri interi, con N scelto dall'utente, sommarli e derminare la media
#include <stdio.h>

int main()
{
    int num,n,somma=0,cont;
    float media;
    do
    {
        printf("Quanti numeri vuoi inserire?\n");
        scanf("%d",&n);
        if (n <= 0)
            printf("Hai inserito un numero errato. Reinserisci\n");
    } while (n <= 0);
    cont=n;
    while (cont>0)
    {
        printf("Inserisci un numero\n");
        scanf("%d",&num);
        somma=somma+num;
        cont--;
    }
    media = (float) somma/n;
    printf("La somma e' uguale a %d\n", somma);
    printf("La media e' %f\n", media);
    return 0;
}
