#include <stdio.h>
#include <stdlib.h>
int main(){
    int i;
    char v_nomi[20];
    FILE* nomi;
    nomi=fopen("nomi.txt", "w"); //w per scrivere, r per leggere, a per appendere
    
    if(nomi==NULL){
        printf("\nErrore apertura file");
        exit(1);
    }else{
        printf("\nFile aperto correttamente");
        for(i=0; i<3; i++){
            printf("Inserisci il nome %d: ", i+1);
            scanf("%s", v_nomi);
            fputs(v_nomi, nomi); //fputs scrive una stringa in un file
            fputc('\n', nomi); //fputc scrive un carattere in un file
        }
    }
    fclose(nomi); //chiude il file
    return 0;
}