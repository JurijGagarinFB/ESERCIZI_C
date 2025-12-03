#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <ctype.h>

#define SERVERPORT 8080
#define DIM 50

void inverti_stringa(char str[])
{
    int j = strlen(str);
    for (int i = 0; i < j / 2; i++)
    {
        char temp = str[i];
        str[i] = str[j - i - 1];
        str[j - i - 1] = temp;
    }
}

int conta_vocali(char str[])
{
    int cont = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u' ||
            str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U')
            cont++;
    }
    return cont;
}

void str_alfabetica(char str[])
{
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isalpha(str[i]))
        {
            str[j] = str[i];
            j++;
        }
    }

    str[j] = '\0';
}

char *rimuovi_vocali(char str[])
{
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u' ||
            str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U'))
        {
            str[j] = str[i]; // lo scrive
            j++;
        }
    }

    str[j] = '\0';
    return str;
}

int main()
{
    // Dichiarazione variabili
    struct sockaddr_in server_addr;
    int server_socket, client_socket, fromlen, codice;
    char str[DIM];

    // creazione socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        perror("Errore creazione socket\n");
        exit(-1);
    }

    // indirizzo server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    fromlen = sizeof(server_addr);
    bind(server_socket, (struct sockaddr *)&server_addr, fromlen);
    listen(server_socket, 5);

    for (;;)
    {
        printf("[SERVER] In ascolto sulla porta 8080\n");
        client_socket = accept(server_socket, (struct sockaddr *)&server_addr, &fromlen);
        if (client_socket == -1)
        {
            perror("Errore accept\n");
            exit(-1);
        }
        read(client_socket, str, sizeof(str));
        printf("Stringa ricevuta: %s\n", str);
        read(client_socket, &codice, sizeof(codice));
        printf("Codice ricevuto: %d\n", codice);

        switch (codice)
        {
        case 0:
            // inverti stringa
            inverti_stringa(str);
            write(client_socket, str, sizeof(str));
            break;

        case 1:
            // numero di vocali
            int n_vocali = conta_vocali(str);
            write(client_socket, &n_vocali, sizeof(n_vocali));
            break;

        case 2:
            // visualizza stringa alfabetica
            str_alfabetica(str);
            write(client_socket, str, sizeof(str));
            break;

        case 3:
            // stringa con vocali rimosse
            rimuovi_vocali(str);
            write(client_socket, str, sizeof(str));
            break;

        default:
            break;
        }

        close(client_socket);
    }

    return 0;
}