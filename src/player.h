#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct Jogador{
    Rectangle retangulo;
    int vidas;
    int faixa;

    Texture2D textura_1;
    Texture2D textura_2;
    int frame_atual;
    float tempo_animacao;
} Jogador;

Jogador *criar_jogador(void);
void atualizar_jogador(Jogador *jogador, float delta);
void desenhar_jogador(Jogador *jogador, float invencibilidade);
void liberar_jogador(Jogador *jogador);

#endif
