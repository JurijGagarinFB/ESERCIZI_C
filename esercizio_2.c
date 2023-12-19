/******************************************************************************
19/12/2023
Su una somma di denaro (relativa all'acquito di un prodotto) si vuole applicare uno sconto in base all'importo inserito seguendo il seguente schema:
            da 0 a 500€ sconto del 10%;
            da 501 a 1000 sconto del 20%;
            oltre i 1001 sconto 30%;
 Il programma dopo aver calcolato e visualizzato a video lo sconto ed il prezzo netto deve permettere di re-inserire
 ulteriori somme di denaro.

*******************************************************************************/
#include <stdio.h>

int main()
{
    int spesa, scelta, scontrino;
    do{
        do{
            printf("Quanto ha speso il cliente?\n");
            scanf("%d",&spesa);
            if (spesa < 0)
                printf("Hai inserito un numero errato. Reinserisci\n");
        } while (spesa < 0);
        if (spesa<501){
            scontrino=spesa-((spesa/100)*10);
        }else if (spesa<1001){
            scontrino=spesa-((spesa/100)*20);
        }else{
            scontrino=spesa-((spesa/100)*30);
        }
        printf("Il cliente deve pagare %d euro\n", scontrino);
        printf("C'e' un'altro cliente? 1=si\n");
        scanf("%d",&scelta);
    } while (scelta==1);
    return 0;
}
