/*
Esercizio 6
Scrivere il codice in C, di un applicazione Socket CLIENT-SERVER in cui il server riceve in input un
vettore di numeri e dopo aver effettuato gli eventuali ed opportuni controlli (se necessari), rispedisce al
Client il conteggio dei numeri pari e dei numeri dispari contenuti nel vettore.
*/

// SERVER
#include <stdio.h>      //std in-out
#include <stdlib.h>     //per utilizzo di certe funzioni:htonl,rand,....
#include <sys/socket.h> //funz. accept+bind+listen
#include <sys/types.h>  //funz. accept
#include <netinet/in.h> //definiscono la struttura degli indirizzi
#include <netdb.h>      //strutture hostent e servent che identificano l'host tramite iol nome
#include <string.h>     //funz. stringhe
#include <fcntl.h>      //descrittore di file
#include <signal.h>     //consente l'utilizzo delle funzioni per la gestione dei segnali fra processi
#include <errno.h>      //gestioni errori connessione
#include <ctype.h>      //bind
#include <unistd.h>     // file header che consente l'accesso alle API dello standard POSIX

#define DIM 50
#define SERVERPORT 12345

void pari_dispari(int vettore[], int n, char* risultato){
    int pari = 0;
    int dispari = 0;
    for(int i=0; i<n; i++){
        if(vettore[i] % 2 == 0){
            pari++;
        } else {
            dispari++;
        }
    }
    sprintf(risultato, "Numeri pari: %d, Numeri dispari: %d", pari, dispari);
}

int main(){
    struct sockaddr_in servizio, addr_remoto; // record con i dati del server e del client

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    int socketfd, soa, fromlen = sizeof(servizio);
    char risultato[DIM];

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));
    listen(socketfd, 10);

    for(;;)
    {
        printf("\n\nServer in ascolto...\n");
        fflush(stdout);

        soa = accept(socketfd, (struct sockaddr *)&addr_remoto, &fromlen);
        int n;
        read(soa, &n, sizeof(n));
        printf("Grandezza vettore ricevuta: %d\n", n);
        int vettore[n];
        read(soa, vettore, sizeof(vettore));
        printf("Vettore ricevuto: \n");
        for(int i=0; i<n; i++){
            printf("%d ", vettore[i]);
        }

        pari_dispari(vettore, n, risultato);

        printf("\nInvio risposta al client... %s\n", risultato);
        write(soa, risultato, sizeof(risultato));

        close(soa);
    }
    return 0;
}