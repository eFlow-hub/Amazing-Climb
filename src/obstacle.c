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

void atualizar_obstaculos(Obstacle *lista, float delta) {
    Obstacle *atual = lista;

    while (atual != NULL) {
        atual->rect.y += atual->velocidade * delta;
        atual = atual->next;
    }
}

void desenhar_obstaculos(Obstacle *lista) {
    Obstacle *atual = lista;

    while (atual != NULL) {
        DrawRectangleRec(atual->rect, BLACK);
        atual = atual->next;
    }
}

void liberar_obstaculos(Obstacle *lista) {
    Obstacle *atual = lista;

    while (atual != NULL) {
        Obstacle *proximo = atual->next;
        free(atual);
        atual = proximo;
    }
}