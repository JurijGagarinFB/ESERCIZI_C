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

char *rimuovi_duplicati(char str[])
{
    int j = 1;
    for (int i = 1; str[i] != '\0'; i++)
    {
        if (str[i] != str[i - 1])
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
    int server_socket, client_socket, fromlen;
    char str[DIM];

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
        printf("Stringa ricevuta: %s", str);

        rimuovi_duplicati(str);
        printf("Stringa senza duplicati consecutivi: %s\n", str);
        write(client_socket, str, strlen(str) + 1); // +1 per 'str[j] = '\0';' (riga 28)

        close(client_socket);
    }

    return 0;
}