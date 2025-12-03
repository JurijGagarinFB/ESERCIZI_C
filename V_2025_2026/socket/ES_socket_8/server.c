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

void maiuscolo(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = toupper(str[i]);
    }
}

void minuscolo(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = tolower(str[i]);
    }
}

int main()
{
    // dichiarazione variabili
    int server_socket, client_socket, fromlen;
    struct sockaddr_in server_addr;
    char str[DIM], str_maiuscolo[DIM], str_minuscolo[DIM];

    // creazione socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        perror("Errore creazione socket\n");
        exit(-1);
    }

    // configurazione indirizzo server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    fromlen = sizeof(server_addr);

    bind(server_socket, (struct sockaddr *)&server_addr, fromlen); // associazione indirizzo e porta alla socket
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

        strcpy(str_maiuscolo, str);
        maiuscolo(str_maiuscolo);
        printf("Stringa maiuscola: %s\n", str_maiuscolo);

        strcpy(str_minuscolo, str);
        minuscolo(str_minuscolo);
        printf("Stringa minuscola: %s\n", str_minuscolo);

        write(client_socket, str_maiuscolo, sizeof(str_maiuscolo));
        write(client_socket, str_minuscolo, sizeof(str_minuscolo));

        close(client_socket);
    }

    return 0;
}