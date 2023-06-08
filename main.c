#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "inimigo.c"
#include "personagem.c"

void clearList(Arma** head) {
    Arma* current = *head;
    Arma* next;

    while (current != NULL) {
        next = current->prox;
        free(current);
        current = next;
    }

    *head = NULL;
}

void printMap(int posX, int posY, char perso) {

  printf("Mapa: \n");

  int i;
  for(i = 0; i < 5; i++) {
    int j;
    for(j = 0; j < 5; j++) {
      if(j == posX && i == posY) {
        printf("[%c]", perso);
      } else {
        printf("[ ]");
      }
    }
    printf("\n");
  }

}

void move(Personagem *personagem) {
  char choice;
  int posX = personagem->posX;
  int posY = personagem->posY;

  printf("Escolha para onde vai:\n");
  if(posX >= 0 && posX < 5){
    printf("Direita (D) ");
  }

  if(posX < 5 && posX > 0) {
    printf("Esquerda (A) ");
  }

  if(posY > 0 && posY < 5) {
    printf("Cima (W) ");
  }

  if(posY >= 0 && posY < 5) {
    printf("Baixo (S)");
  }

  printf(": ");
  scanf(" %c", &choice);

  if(choice == 'd' || choice == 'D') {
    posX++;
  } else if(choice == 'a' || choice == 'A') {
    posX--;
  } else if(choice == 's' || choice == 'S') {
    posY++;
  } else if(choice == 'w' || choice == 'W') {
    posY--;
  }

  if(posX >= 0 && posX < 5 && posY >= 0 && posY < 5) {
    personagem->posX = posX;
    personagem->posY = posY;
  }

}

void getArmaMap(Personagem *personagem, Arma *mapArma[5][5], int posX, int posY) {
  if (mapArma[posX][posY] != NULL) {
    Arma *arma = mapArma[posX][posY];
    printf("Você encontrou uma arma:\n");
    printf("Nome: %s\n", arma->name);
    printf("Seu ataque atual: %d\n", personagem->atk);
    printf("Seu ataque com essa arma vai ser: %d\n", (personagem->atk - personagem->arma->atk_arma) + arma->atk_arma);
    
    char choice;
    printf("Deseja trocar a arma atual por essa? (S/N): ");
    scanf(" %c", &choice);

    if(choice == 's' || choice == 'S') {
      personagem->atk -= personagem->arma->atk_arma;
      personagem->arma = arma;
      personagem->atk += personagem->arma->atk_arma;
      mapArma[posX][posY] = NULL;
    } 

  }
}

void attack(Personagem *personagem, Inimigo *inimigo) {

  int dado = dice(20);
  printf("Você tirou %d no dado de 20 lados\n", dado);
  if(dado <= 3) {
    printf("Você errou!\n");
  }

  if(dado > 3 && dado <= 8) {
    printf("Você causou %d pontos de dano:\n", personagem->atk - inimigo->def);
    printf("Status: %d - %d (atk do personagem - def do inimigo)\n", personagem->atk, inimigo->def);
    inimigo->life -= personagem->atk - inimigo->def <= 0 ? 0 : personagem->atk - inimigo->def;
  }

  if(dado > 8 && dado < 20) {
    printf("Você acertou em cheio, causando %d pontos de dano\n", personagem->atk);
    inimigo->life -= personagem->atk;
  }

  if(dado == 20) {
    printf("Você acertou critico!\n");
    printf("Você causou %d pontos de dano:\n", personagem->atk * 2);
    printf("Status: %d * 2 (atk do personagem * 2)\n", personagem->atk);
    inimigo->life -= personagem->atk * 2;
  }

  printf("Sua vida: %d\n", personagem->life);
  printf("Vida do seu inimigo: %d\n", inimigo->life < 0 ? 0 : inimigo->life);

  system("pause");

}

void battle(Personagem *personagem, Inimigo *mapEnemy[5][5], int posX, int posY) {
  if(mapEnemy[posX][posY] != NULL) {
    Inimigo *inimigo = mapEnemy[posX][posY];
    printf("Você encontrou um inimigo:\n");

    bool game = true;
    int choice;

    while(personagem->life > 0 && inimigo->life > 0) {
      printf("====================\n");
      printf("Nome: %s\n", inimigo->name);
      printf("Ataque: %d\n", inimigo->atk);
      printf("Defesa: %d\n", inimigo->def);
      printf("====================\n\n");
      printf("O que você faz?\n");
      printf("1 - Atacar  2 - Defesa\n");
      scanf(" %d", &choice);

      if(choice == 1) {
        attack(personagem, inimigo);
      }

      game = false;
    }
  }
}


void startGame(Personagem *personagem, Arma *mapArma[5][5], Inimigo *mapEnemy[5][5]) {

  int count = 0;

  while(personagem->life > 0) {

    printPersonagem(personagem);
    printMap(personagem->posX, personagem->posY, personagem->name[0]);
    move(personagem);
    getArmaMap(personagem, mapArma, personagem->posX, personagem->posY);
    battle(personagem, mapEnemy, personagem->posX, personagem->posY);
    count++;
    system("cls");

  }

}

void play() {

  Personagem *personagem;

  Arma *listaArma = NULL;

  Arma *graveto = createWeapon("graveto", 3);
  Arma *espada = createWeapon("Espada", 10);
  Arma *machado = createWeapon("Machado", 15);
  Arma *arco = createWeapon("Arco", 8);
  Arma *foice = createWeapon("Foice", 18);
  Arma *lanca = createWeapon("Lança", 10);
  Arma *faca = createWeapon("Faca", 5);
  Arma *manopla = createWeapon("Manopla", 10);
  Arma *tridente = createWeapon("Tridente", 10);
  Arma *espada_curta = createWeapon("Espada Curta", 10);
  Arma *garras = createWeapon("Garras", 10);
  Arma *bastao = createWeapon("Bastão", 10);

  insertWeapon(&listaArma, graveto);
  insertWeapon(&listaArma, espada);
  insertWeapon(&listaArma, machado);
  insertWeapon(&listaArma, arco);
  insertWeapon(&listaArma, foice);
  insertWeapon(&listaArma, lanca);
  insertWeapon(&listaArma, faca);
  insertWeapon(&listaArma, manopla);
  insertWeapon(&listaArma, tridente);
  insertWeapon(&listaArma, espada_curta);
  insertWeapon(&listaArma, garras);
  insertWeapon(&listaArma, bastao);

  Inimigo *listaInimigo = NULL;

  Inimigo *goblin = createEnemy("Goblin", 5, 15, 80);
  Inimigo *esqueleto = createEnemy("Esqueleto", 8, 5, 50);
  Inimigo *zumbi = createEnemy("Zumbi", 10, 8, 100);
  Inimigo *slime = createEnemy("Slime", 5, 5, 30);
  Inimigo *ladrao = createEnemy("Ladrão", 10, 10, 100);
  Inimigo *rato_mutante = createEnemy("Rato mutante", 10, 5, 85);
  Inimigo *barata_gigante = createEnemy("Barata gigante", 5, 15, 40);

  insertEnemy(&listaInimigo, goblin);
  insertEnemy(&listaInimigo, esqueleto);
  insertEnemy(&listaInimigo, zumbi);
  insertEnemy(&listaInimigo, slime);
  insertEnemy(&listaInimigo, ladrao);
  insertEnemy(&listaInimigo, rato_mutante);
  insertEnemy(&listaInimigo, barata_gigante);

  char map[5][5] = {
    {' ', ' ', ' ',' ', ' '},
    {' ', ' ', ' ',' ', ' '},
    {' ', ' ', ' ',' ', ' '},
    {' ', ' ', ' ',' ', ' '},
    {' ', ' ', ' ',' ', ' '}
  };

  int dado = dice(10);
  int i;

  Arma *mapArma[5][5];
  for(i = 0; i < 5; i++) {
    int j;
    for(j = 0; j < 5; j++) {
      if(dado > 3 && i != 0 && j != 0) {
        mapArma[i][j] = getArma(listaArma, dice(20));
        dado = dice(10);
      } else {
        mapArma[i][j] = NULL;
      }
    }
  }

  dado = dice(10);
  Inimigo *mapEnemy[5][5];
  for(i = 0; i < 5; i++) {
    int j;
    for(j = 0; j < 5; j++) {
      if(dado <= 3 && i != 0 && j != 0 && mapArma[i][j] == NULL) {
        mapEnemy[i][j] = getEnemy(listaInimigo, dice(20));
        dado = dice(10);
      } else {
        mapEnemy[i][j] = NULL;
      }
    }
  }

  dado = dice(10);

  printf("---------- Bem vindo ----------\n");
  printf("1 - Iniciar Jogo\n2 - Sair\n");
  int choice;
  scanf("%d", &choice);

  if(choice == 1) {
    char name[50];
    printf("Insira o nome do seu personagem: ");
    scanf("%s", &name);
    personagem = createCharacter(name);
    personagem->arma = graveto;

    startGame(personagem, mapArma, mapEnemy);
  }

  free(personagem);
  clearList(&listaArma);
  clearList(&listaInimigo);
  
}

int main() {

  play();

  return 0;

}