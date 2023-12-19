/*
19/12/2023
  Scrivere un programma in C che, dopo aver letto N numeri (n scelto dall'utente) calcoli e visualizzi a video la somma dei numeri positivi, la somma dei numeri negativi in valore assoluto, il conteggio dei numeri negativi e positivi, la media dei numeri positivi e negativi.
*/
#include <stdio.h>

int main() {
  int n, numero, somma_positivi = 0, somma_negativi = 0, conteggio_positivi = 0, conteggio_negativi = 0;
  float media_positivi = 0, media_negativi = 0;
  printf("Quanti numeri vuoi inserire? ");
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    printf("Inserisci il %d° numero: ", i + 1);
    scanf("%d", &numero);
    if (numero > 0) {
      conteggio_positivi++;
      somma_positivi = somma_positivi + numero;
    } else if (numero < 0) {
      conteggio_negativi++;
      somma_negativi = somma_negativi + -numero;
    }
  }
  if (conteggio_positivi > 0) {
    media_positivi = (float)somma_positivi / conteggio_positivi;
  }
  if (conteggio_negativi > 0) {
    media_negativi = (float)somma_negativi / conteggio_negativi;
  }
  printf("La somma dei numeri positivi è: %d\n", somma_positivi);
  printf("La somma dei numeri negativi in valore assoluto è: %d\n", somma_negativi);
  printf("Il conteggio dei numeri negativi è: %d\n", conteggio_negativi);
  printf("La media dei numeri positivi è: %.2f\n", media_positivi);
  printf("La media dei numeri negativi è: %.2f\n", media_negativi);
  return 0;
}
