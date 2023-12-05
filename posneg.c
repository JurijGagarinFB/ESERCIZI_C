#include <stdio.h>

int main(){
    int num;
    printf("Inserisci un numero da controllare\n");
    scanf("%d",&num);
    if (num>0){
        printf("Il numero e' positivo\n");
    }else if (num<0){
        printf("Il numero e' negativo\n");
    }else{
        printf("Il numero e' 0\n");
    }
    return 0;
}
