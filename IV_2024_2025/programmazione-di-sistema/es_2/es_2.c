/**
 * @brief Scrivere un programma concorrente che realizzi il seguente comando:
 * cat file.txt | wc 
 * 
 * il processo p2 deve rimandare l'output di wc al padre, il quale lo scriverà
 * su un file chiamato wc.txt
 * il nome del file "file.txt" deve essere passato come argomento in argv[1]
 *
 * @param argc Numero di argomenti passati attraverso la riga di comando
 * @param argv Array di stringhe contenente gli argomenti passati attraverso la riga di comando
 *
 * @returns la funzione restituisce 0
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <syscall.h>
 #include <sys/wait.h>
 
 int main(int argc, char *argv[])
 {
 
     if (argc < 2)
     {
         printf("Numero di argomenti non valido!");
         return -1;
     }
 
     int pid1, pid2, p1p2[2];
     pipe(p1p2);
 
     pid1 = fork();
     if (pid1 == 0)
     {
         close(p1p2[0]);
         close(1);
         dup(p1p2[1]);
         close(p1p2[1]);
         execl("/bin/cat", "cat", argv[1], (char *)0);
         return -1;
     }
 
     pid2 = fork();
     if (pid2 == 0)
     {
         close(p1p2[1]);
         close(0);
         dup(p1p2[0]);
         close(p1p2[0]);
         execl("/bin/wc", "wc", (char *)0);
         return -1;
     }
 
     close(p1p2[0]);
     close(p1p2[1]);
     wait(&pid1);
     wait(&pid2);
 
     return 0;
 }
 