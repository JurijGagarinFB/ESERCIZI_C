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

int conta_lettere(char str[])
{
    int cont = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isalpha(str[i]))
            cont++;
    }
    return cont;
}

int conta_cifre(char str[])
{
    int cont = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isdigit(str[i]))
            cont++;
    }
    return cont;
}

int conta_spazi(char str[])
{
    int cont = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ' ')
            cont++;
    }
    return cont;
}

int conta_speciali(char str[])
{
    int cont = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (isgraph(str[i]) && !isalnum(str[i]))
            cont++;
    }
    return cont;
}

int main()
{
    // Dichiarazione variabili
    struct sockaddr_in server_addr;
    int server_socket, client_socket, fromlen;
    int lettere, cifre, spazi, speciali;
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

        // numero di lettere
        lettere = conta_lettere(str);
        write(client_socket, &lettere, sizeof(lettere));
        // numero di cifre
        cifre = conta_cifre(str);
        write(client_socket, &cifre, sizeof(cifre));
        // numero di spazi
        spazi = conta_spazi(str);
        write(client_socket, &spazi, sizeof(spazi));
        // numero di caratteri speciali
        speciali = conta_speciali(str);
        write(client_socket, &speciali, sizeof(speciali));

        close(client_socket);
    }

    return 0;
}