#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "raylib.h"

typedef struct Obstacle {
    Rectangle rect;
    float velocidade;
    struct Obstacle *next;
} Obstacle;

void adicionar_obstaculo(Obstacle **lista);
void atualizar_obstaculos(Obstacle *lista, float delta);
void desenhar_obstaculos(Obstacle *lista);
void liberar_obstaculos(Obstacle *lista);

#endif