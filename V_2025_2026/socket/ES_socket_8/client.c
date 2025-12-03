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
    // dichiarazione variabili
    int network_socket;
    struct sockaddr_in server_addr;
    char str[DIM], str_maiuscolo[DIM], str_minuscolo[DIM];

    // creazione socket
    network_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (network_socket == -1)
    {
        perror("Errore creazione socket\n");
        exit(-1);
    }

    // configurazione indirizzo server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // connessione al server
    if (connect(network_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Errore connect\n");
        exit(-1);
    }

    printf("Inserisci una stringa: ");
    scanf("%s", str);
    write(network_socket, str, sizeof(str));

    read(network_socket, str_maiuscolo, sizeof(str_maiuscolo));
    read(network_socket, str_minuscolo, sizeof(str_minuscolo));
    printf("Stringa maiuscola ricevuta dal server: %s\n", str_maiuscolo);
    printf("Stringa minuscola ricevuta dal server: %s\n", str_minuscolo);

    close(network_socket);
    return 0;
}