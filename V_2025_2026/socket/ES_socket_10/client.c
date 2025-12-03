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

int main()
{
    // Dichiarazione variabili
    struct sockaddr_in server_addr;
    int network_socket, connect_status;
    char str[DIM], str2[DIM];

    // creazione socket
    network_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (network_socket == -1)
    {
        perror("Errore creazione socket\n");
        exit(-1);
    }

    // indirizzo del server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // connessione al server
    connect_status = connect(network_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (connect_status == -1)
    {
        perror("Errore connect\n");
        exit(-1);
    }

    printf("Inserisci una stringa: ");
    fgets(str, DIM, stdin);
    write(network_socket, str, sizeof(str));

    read(network_socket, str2, sizeof(str2));
    printf("Stringa ricevuta: %s", str2);

    close(network_socket);
    return 0;
}