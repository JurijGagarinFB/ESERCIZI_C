/*
applicazione client-server
client invia una stringa, il server restituisce la stringa in cui le vocali sono sotituite dalla lettera X.
esempio: inviata ciao, restituita cXXX.
*/

// CLIENT
#include <stdio.h>      //std in-out
#include <stdlib.h>     //per utilizzo di certe funzioni:htonl,rand,....
#include <sys/socket.h> //funz. accept+bind+listen
#include <sys/types.h>  //funz. accept
#include <netinet/in.h> //definiscono la struttura degli indirizzi
#include <string.h>     //funz. stringhe
#include <errno.h>      //gestioni errori connessione
#include <ctype.h>      //bind
#include <unistd.h>     //file header che consente l'accesso alle API dello standard POSIX

#define DIM 50
#define SERVERPORT 1450

int main(){

    struct sockaddr_in servizio;
    char stringa[DIM];
    int socketFD, fromlen = sizeof(servizio);

    //assegnazione valori alla struttura servizio
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);


    //creazione socket
    if((socketFD = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        printf("Chiamata fallita alla systemcall");
        exit(0);
    }


    if(connect(socketFD, (struct sockaddr*) &servizio, sizeof(servizio)) == -1){
        printf("Errore nella system call connect");
        exit(0);
    }

    printf("Inserisci una stringa da inviare al server: \n");
    scanf("%s", stringa);

    write(socketFD, stringa, sizeof(stringa));
    read(socketFD, stringa, sizeof(stringa));
    printf("Stringa ricevuta dal server: %s\n", stringa);
    close(socketFD);

    return 0;
}