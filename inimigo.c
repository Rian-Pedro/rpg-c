#include <string.h>
#include "dice.c"

typedef struct Inimigo {
  char name[50];
  int life;
  int atk;
  int def;
  struct Inimigo *prox;
} Inimigo;

Inimigo *createEnemy(char name[50], int atk, int def, int life) {
  Inimigo *newEnemy = (Inimigo *)malloc(sizeof(Inimigo));
  strcpy(newEnemy->name, name);
  newEnemy->life = life;
  newEnemy->atk = atk;
  newEnemy->def = def;
  newEnemy->prox = NULL;
  
  return newEnemy;
}

void insertEnemy(Inimigo **enemyList, Inimigo *newEnemy) {
  if(*enemyList == NULL) {
    *enemyList = newEnemy;
    return;
  }

  Inimigo * atual = *enemyList;
  while(atual->prox != NULL) {
    atual = atual->prox;
  }
  atual->prox = newEnemy;
}

Inimigo *getEnemy(Inimigo *enemyList, int num) {
  Inimigo * atual = enemyList;
  int i;
  for(i = 0; i <= num; i++) {
    if(i == num) {
      return atual;
    }
    
    if(atual->prox == NULL) {
      atual = enemyList;
      continue;
    }

    atual = atual->prox;
  }

  return NULL;
}