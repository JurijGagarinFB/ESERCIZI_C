#include <stdio.h>

int main(){
    int num,resto;
    printf("Inserisci un numero da controllare\n");
    scanf("%d",&num);
    resto=num%2;
    if (resto==0){
        printf("il numeor inserito e' pari");
    }else{
        printf("Il numeor inserito e' dispari");
    }
    return 0;
}
