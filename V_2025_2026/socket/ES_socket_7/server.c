#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define SERVER_PORT 8080
#define DIM 100

int conta_parole(char str[])
{
    int cont = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (str[i] != ' ' && (i == 0 || str[i - 1] == ' '))
            cont++;
    }
    return cont;
}

int main()
{
    struct sockaddr_in server_addr;
    int server_socket, fromlen, client_socket, n_parole;
    char str[DIM];

    if (server_socket = socket(AF_INET, SOCK_STREAM, 0) == -1)
    {
        perror("Errore socket\n");
        exit(-1);
    }

    // server_addr
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // fromlen
    fromlen = sizeof(server_addr);

    // bind e listen
    if (bind(server_socket, (struct sockaddr *)&server_addr, fromlen) == -1)
    {
        perror("Errore bind\n");
        exit(-1);
    }
    listen(server_socket, 5);

    for (;;)
    {
        printf("[SERVER] In ascolto sulla porta 8080\n");
        // accept
        client_socket = accept(server_socket, (struct sockaddr *)&server_addr, &fromlen);
        if (client_socket == -1)
        {
            perror("Errore accept\n");
            exit(-1);
        }
        // read stringa
        read(client_socket, str, sizeof(str));
        printf("Stringa ricevuta: %s\n", str);

        // rispedisco al client
        n_parole = conta_parole(str);
        write(client_socket, &n_parole, sizeof(int));

        close(client_socket);
    }

    return 0;
}