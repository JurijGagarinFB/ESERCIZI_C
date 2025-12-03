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
    int network_socket, connection_status, codice;
    char str[DIM];

    // creazione socket
    network_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (network_socket == -1)
    {
        perror("Errore creazione socket\n");
        exit(-1);
    }

    // indirizzo server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // connessione al server
    connection_status = connect(network_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (connection_status == -1)
    {
        perror("Errore connect\n");
        exit(-1);
    }

    printf("Inserisci una stringa: ");
    scanf("%s", str);
    write(network_socket, str, sizeof(str));
    do
    {
        printf("Inserisci il codice (0,1,2,3): ");
        scanf("%d", &codice);
        write(network_socket, &codice, sizeof(codice));
    } while (codice < 0 || codice > 3);

    switch (codice)
    {
    case 0:
        char str_invertita[DIM];
        read(network_socket, str_invertita, sizeof(str_invertita));
        printf("Stringa ricevuta: %s\n", str_invertita);
        break;

    case 1:
        int n_vocali;
        read(network_socket, &n_vocali, sizeof(n_vocali));
        printf("Numero di vocali: %d\n", n_vocali);
        break;

    case 2:
        char str_alfa[DIM];
        read(network_socket, str_alfa, sizeof(str_alfa));
        printf("Stringa alfabetica: %s\n", str_alfa);
        break;

    case 3:
        char str_no_vocali[DIM];
        read(network_socket, str_no_vocali, sizeof(str_no_vocali));
        printf("Stringa senza vocali: %s\n", str_no_vocali);
        break;
    default:
        break;
    }

    close(network_socket);
    return 0;
}