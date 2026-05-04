#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct Player {
    Rectangle rect;
    int vidas;
    int lane;
    float velocidade;

    Texture2D frame1;
    Texture2D frame2;
    int frameAtual;
    float animtimer;
} Player;

Player *criar_player();
void atualizar_player(Player *player, float delta);
void desenhar_player(Player *player);
void liberar_player(Player *player);

#endif