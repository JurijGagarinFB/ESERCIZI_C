/**
 * @brief Si vuole realizzare in linguaggio C un software monoprocesso che implementi il seguente comando:
 * $ cat file1.txt file2.txt file3.txt | grep “c”
 *
 * Dove file[N].txt con N maggiore uguale a 1 sono una serie di files e il carattere "c" è a scopo esemplificativo e potrebbe essere
 * qualsiasi carattere.
 *
 * Si utilizzino le system call al fine di leggere tutti i file di testo e, per ogni file, ricercare il carattere.
 * Al termine dell’esecuzione il software dovrà mostrare a video il numero di occorrenze del carattere trovate nei files e
 * dovrà contemporaneamente scrivere l’output su un file di testo il cui path sarà letto da argv.
 *
 * Esempio:
 * $ ./a.out file1.txt file2.txt file3.txt k occorrenze.txt
 * $ Il carattere k compare 10 volte nei files: file1.txt, file2.txt, file3.txt
 * $ cat occorrenze.txt
 * $ Il carattere k compare 10 volte nei files: file1.txt, file2.txt, file3.txt
 *
 * Osservazioni:
 * essendo il software monoprocesso non è necessario usare le pipe
 * prestare attenzione all’uso corretto di argv
 * si ricorda che il software deve funzionare per un numero arbitrario di files.
 * i percorsi dei files possono essere sia assoluti che relativi
 *
 *
 * Suggerimento:
 * Per facilitare la ricerca è possibile leggere un singolo carattere per volta usando la funzione read.
 *
 * @param argc numero di parametri passati da linea di comando
 * @param argv array di stringhe che contiene i parametri passati da linea di comando
 *
 * @return 0 il programma ritorna 0
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 4) // Verifica che ci siano almeno 3 file + carattere + file di output
    {
        printf("Numero argomenti sbagliato");
        exit(1);
    }

    char carattereDaCercare = argv[argc - 2][0]; // Penultimo argomento è il carattere da cercare
    char *outputPath = argv[argc - 1];          // Ultimo argomento è il file di output

    int occorrenzeTotali = 0;

    // Apri il file di output
    int outputFd = open(outputPath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outputFd == -1)
    {
        printf("Errore apertura file di output");
        exit(1);
    }

    // Itera sui file di input
    for (int i = 1; i < argc - 2; i++)
    {
        int fileFd = open(argv[i], O_RDONLY);
        if (fileFd == -1)
        {
            printf("Errore apertura file di input");
            continue; // Passa al prossimo file
        }

        char buffer[1024];
        int bytesLetti;
        int occorrenzeFile = 0;

        // Leggi il file in blocchi
        while ((bytesLetti = read(fileFd, buffer, sizeof(buffer))) > 0)
        {
            for (int j = 0; j < bytesLetti; j++)
            {
                if (buffer[j] == carattereDaCercare)
                {
                    occorrenzeFile++;
                }
            }
        }

        if (bytesLetti == -1)
        {
            printf("Errore durante la lettura del file");
        }

        close(fileFd);

        // Scrivi il risultato nel file di output
        char risultato[256];
        snprintf(risultato, sizeof(risultato),
                 "Il carattere '%c' compare %d volte nel file %s\n",
                 carattereDaCercare, occorrenzeFile, argv[i]);

        if (write(outputFd, risultato, strlen(risultato)) == -1)
        {
            perror("Errore durante la scrittura nel file di output");
        }

        occorrenzeTotali += occorrenzeFile;
    }

    // Scrivi il risultato totale nel file di output
    char risultatoTotale[256];
    snprintf(risultatoTotale, sizeof(risultatoTotale),
             "Il carattere '%c' compare %d volte nei files forniti.\n",
             carattereDaCercare, occorrenzeTotali);

    if (write(outputFd, risultatoTotale, strlen(risultatoTotale)) == -1)
    {
        perror("Errore durante la scrittura del risultato totale nel file di output");
    }

    // Mostra il risultato totale sullo schermo
    printf("%s", risultatoTotale);

    return 0;
}
