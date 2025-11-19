/*
applicazione client-server
client invia una stringa, il server restituisce la stringa in cui le vocali sono sotituite dalla lettera X.
esempio: inviata ciao, restituita cXXX.
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
#include <unistd.h>     //file header che consente l'accesso alle API dello standard POSIX

#define DIM 50
#define SERVERPORT 1450

void sostituzione(char stringa[]){
    for(int i = 0; i<strlen(stringa); i++){
        if(stringa[i] == 'a' || stringa[i] == 'e' || stringa[i] == 'i' || stringa[i] == 'o' || stringa[i] == 'u' ||
           stringa[i] == 'A' || stringa[i] == 'E' || stringa[i] == 'I' || stringa[i] == 'O' || stringa[i] == 'U'){
            stringa[i] = 'X';
        }
    }
}

int main(){

    struct sockaddr_in servizio;
    char stringa[DIM];
    int socketFD, socketAccettazione, fromlen = sizeof(servizio);

    //assegnazione valori alla struttura servizio
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);


    //creazione socket
    if((socketFD = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        printf("Chiamata fallita alla systemcall");
        exit(0);
    }


    if(bind(socketFD, (struct sockaddr*) &servizio, sizeof(servizio)) == -1){
        printf("Errore nella system call bind");
        exit(0);
    }


    if (listen(socketFD, 5) == -1){
        printf("Errore nella system call listen");
        exit(0);
    }



    for(;;){
        printf("Server in attesa di richieste...\n");
        fflush(stdout);
        if (socketAccettazione = accept(socketFD, (struct sockaddr*) &servizio, &fromlen) == -1){
            printf("Errore nella system call accept");
            exit(0);
        }

        //leggo stringa dal client usando la socket
        read(socketAccettazione, stringa, sizeof(stringa));
        printf("Stringa ricevuta: %s\n", stringa);

        sostituzione(stringa);

        printf("Stringa modificata: %s\n", stringa);
        write(socketAccettazione, stringa, sizeof(stringa));
        
        close(socketAccettazione);
    }
    return 0;
}