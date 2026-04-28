#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "obstacle.h"

typedef struct Game {
    Player *player;
    Obstacle *obstacles;
    float timerSpawn;
} Game;

Game *criar_jogo();
void atualizar_jogo(Game *game, float delta);
void desenhar_jogo(Game *game);
void liberar_jogo(Game *game);

#endif