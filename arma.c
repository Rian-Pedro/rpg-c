#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Arma {
  char name[50];
  int atk_arma;
  struct Arma *prox;
} Arma;

Arma *getArma(Arma *listaArma, int num) {
  Arma * atual = listaArma;
  int i;
  for(i = 0; i <= num; i++) {
    if(i == num) {
      return atual;
    }
    
    if(atual->prox == NULL) {
      atual = listaArma;
      continue;
    }

    atual = atual->prox;
  }

  return NULL;
}

void insertWeapon(Arma **listaArma, Arma *newItem) {
  if(*listaArma == NULL) {
    *listaArma = newItem;
    return;
  }

  Arma * atual = *listaArma;
  while(atual->prox != NULL) {
    atual = atual->prox;
  }
  atual->prox = newItem;
}

Arma *createWeapon(char name[50], int atk) {
  Arma *newArma = (Arma *)malloc(sizeof(Arma));
  strcpy(newArma->name, name);
  newArma->atk_arma = atk;
  newArma->prox = NULL;

  return newArma;
}
