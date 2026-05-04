#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "raylib.h"

typedef struct Obstacle {
    Rectangle rect;
    float velocidade;
    int tipo;
    struct Obstacle *next;
} Obstacle;

void adicionar_obstaculo(Obstacle **lista);
void atualizar_obstaculos(Obstacle *lista, float delta);
void desenhar_obstaculos(Obstacle *lista);
void remover_obstaculos_fora_da_tela(Obstacle **lista, int *score);
void liberar_obstaculos(Obstacle *lista);
void carregar_texturas_obstaculos();
void descarregar_texturas_obstaculos();
#endif