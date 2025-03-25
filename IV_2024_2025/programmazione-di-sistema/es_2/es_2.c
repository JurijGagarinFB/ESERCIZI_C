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
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Uso: %s <file.txt>\n", argv[0]);
        return -1;
    }

    int p1p2[2], p0p2[2];

    int pid1 = fork();
    if (pid1 == 0)
    {
        // Processo p1 (cat)
        close(p1p2[0]);
        dup(p1p2[1]);
        close(p1p2[1]);

        execl("/bin/cat", "cat", argv[1], (char *)NULL);
        return -1;
    }

    int pid2 = fork();
    if (pid2 == 0)
    {
        // Processo p2 (wc)
        close(p0p2[0]); // Chiude lettura pipe padre <-> p2
        dup(p0p2[1]);
        close(p0p2[1]);

        close(p1p2[1]); // Chiude scrittura della pipe p1 -> p2
        dup(p1p2[0]);
        close(p1p2[0]);

        execl("/usr/bin/wc", "wc", (char *)NULL);
        return -1;
    }

    // Processo padre
    close(p1p2[0]);
    close(p1p2[1]);
    close(p0p2[1]); // Chiude scrittura pipe padre <-> p2

    int file = open("wc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);

    dup(p0p2[0]);
    close(p0p2[0]);

    dup(file);
    close(file);

    execl("/usr/bin/tee", "tee", (char *)NULL);
    // Attesa della terminazione dei figli
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
