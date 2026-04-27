#include "obstacle.h"
#include "config.h"
#include <stdlib.h>

void adicionar_obstaculo(Obstacle **lista) {
    Obstacle *novo = malloc(sizeof(Obstacle));

    if (novo == NULL) {
        return;
    }

    novo->rect.x = rand() % (SCREEN_WIDTH - OBSTACLE_WIDTH);
    novo->rect.y = -OBSTACLE_HEIGHT;
    novo->rect.width = OBSTACLE_WIDTH;
    novo->rect.height = OBSTACLE_HEIGHT;

    novo->velocidade = OBSTACLE_SPEED;

    novo->next = *lista;
    *lista = novo;
}