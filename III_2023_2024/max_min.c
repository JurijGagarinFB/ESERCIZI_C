// Dopo aver inserito N numeri interi, con N scelto dall'utente, trovare il massimo ed il minimo
#include <stdio.h>

int main()
{
    int num, max=0, min=0, n, cont;
    do
    {
        printf("Quanti numeri vuoi inserire?\n");
        scanf("%d",&n);
        if (n <= 0)
            printf("Hai inserito un numero errato. Reinserisci\n");
    } while (n <= 0);
    cont=n;
    printf("Inserisci un numero\n");
    scanf("%d",&num);
    max=min=num;
    while (cont>1)
    {
        printf("Inserisci un numero\n");
        scanf("%d",&num);
        if (num>max){
            max=num;
            cont--;
        }else if (num<min){
            min=num;
            cont--;
        }else{
            cont--;
        }
    }
    printf("Il numero massimo e': %d\n", max);
    printf("Il numero minimo e': %d\n", min);
    return 0;
}
