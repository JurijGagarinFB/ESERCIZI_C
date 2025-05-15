#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if(argc!=2){
        printf("Argomenti insufficienti\n");
        exit(1);
    }
    
    int f1, f2, status1, status2;
    char contenuto[500];
    FILE *fileLettura1, *fileLettura2, *fileScrittura;

    f1 = fork();
    if (f1 < 0)
    {
        printf("Errore F1\n");
        exit(1);
    }
    if (f1 == 0)
    {
        fileScrittura = fopen("titolo.txt", "w");
        if(fileScrittura == NULL){
            printf("Errore titolo.txt\n");
            exit(1);
        }

        sprintf(contenuto, "%s", "Il mistero della montagna");
        fwrite(contenuto, strlen(contenuto), 1, fileScrittura);
        fclose(fileScrittura);
        exit(0);
    }

    f2 = fork();
    if (f2 < 0)
    {
        printf("Errore F2\n");
        exit(1);
    }
    if (f2 == 0)
    {
        fileScrittura = fopen("opera.txt", "w");
        if (fileScrittura == NULL)
        {
            printf("Errore opera.txt\n");
            exit(1);
        }

        sprintf(contenuto, "%s", argv[1]);

        fwrite(contenuto, strlen(contenuto), 1, fileScrittura);
        fclose(destinationFile);
        exit(0);
    }

    waitpid(f1, &status1, 0);
    waitpid(f2, &status2, 0);

    fileLettura1 = fopen("titolo.txt", "r");
    fileScrittura = fopen("finale.txt", "w");
    if (fileLettura1 == NULL || WEXITSTATUS(status1) == 1)
    {
        printf("Errore titolo.txt");
        exit(1);
    }
    
    if (fileScrittura == NULL)
    {
        printf("Errore finale.txt");
        exit(1);
    }

    while(!feof(fileLettura1)){
        fread(contenuto, sizeof(contenuto), 1, fileLettura1);
        fwrite(contenuto, strlen(contenuto), 1, fileScrittura);
    }

    fclose(fileLettura1);
    fputc('\n', fileScrittura);
    
    fileLettura2 = fopen("opera.txt", "r");
    if (fileLettura2 == NULL || WEXITSTATUS(status2) == 1)
    {
        printf("Errore opera.txt");
        exit(1);
    }

    while (!feof(fileLettura2))
    {
        fread(contenuto, sizeof(contenuto), 1, fileLettura2);
        fwrite(contenutoFile, strlen(contenuto), 1, fileScrittura);
    }

    fclose(fileLettura2);
    fclose(fileScrittura);

    return 0;
}
