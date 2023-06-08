#include <time.h>
#include <stdlib.h>

int dice(int qtd_lados) {
  srand(time(NULL));
  return (rand() % qtd_lados) + 1;
}

int aleatorio(int min, int max) {
  srand(time(NULL));
  return min + rand() % (min + max + 1);
}