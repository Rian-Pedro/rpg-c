#include "arma.c"
#include "escudo.c"

typedef struct Personagem {
  char name[50];
  int life;
  int atk;
  int def;  
  struct Arma *arma;
  struct Escudo *escudo;
  int posX;
  int posY;
} Personagem;

Personagem *createCharacter(char name[50]) {
  Personagem *newPersonagem = (Personagem *)malloc(sizeof(Personagem));
  strcpy(newPersonagem->name, name);
  newPersonagem->life = 100;
  newPersonagem->atk = aleatorio(5, 20);
  newPersonagem->def = aleatorio(5, 20);
  newPersonagem->arma = NULL;
  newPersonagem->escudo = NULL;
  newPersonagem->posX = 0;
  newPersonagem->posY = 0;
  
  return newPersonagem;
}

void printPersonagem(Personagem *personagem) {

  printf("====================\n");
  printf("Nome: %s\n", personagem->name);
  printf("Vida: %d\n", personagem->life);

  if(personagem->arma == NULL) {
    printf("Ataque: %d\n", personagem->atk);
  } else {
    printf("Ataque: %d (%d + bonus de %d)\n", personagem->atk + personagem->arma->atk_arma, personagem->atk, personagem->arma->atk_arma);
  }

  if(personagem->escudo == NULL) {
    printf("Defesa: %d\n", personagem->def);
  } else {
    printf("Defesa: %d (%d + bonus de %d)\n", personagem->def + personagem->escudo->def_escudo, personagem->def + personagem->escudo->def_escudo, personagem->escudo->def_escudo);
  }

  printf("Inventario:\n");
  printf("- Arma: %s\n", personagem->arma == NULL ? "(Vazio)" : personagem->arma->name);
  printf("- Escudo: %s\n", personagem->escudo == NULL ? "(Vazio)" : personagem->escudo->name);
  printf("====================\n");

}