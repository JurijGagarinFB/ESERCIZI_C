#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define SERVER_PORT 8080
#define DIM 100

int main()
{
    struct sockaddr_in server_addr;
    int network_socket, n_parole;
    char str[DIM];

    // socket
    if (network_socket = socket(AF_INET, SOCK_STREAM, 0) == -1)
    {
        perror("Errore socket\n");
        exit(-1);
    }

    // server_addr
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // connect
    if (connect(network_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Errore connect\n");
        exit(-1);
    }

    // inserimento stringa
    printf("Inserisci una stringa: ");
    fgets(str, DIM, stdin);
    // write su fd
    write(network_socket, str, sizeof(str));

    // riceve risposta da socket
    read(network_socket, &n_parole, sizeof(int));
    printf("Numero di parole nella stringa: %d\n", n_parole);

    close(network_socket);
    return 0;
}