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

void remover_obstaculos_fora_da_tela(Obstacle **lista) {
    Obstacle *atual = *lista;
    Obstacle *anterior = NULL;

    while (atual != NULL) {
        if (atual->rect.y > SCREEN_HEIGHT) {
            Obstacle *remover = atual;

            if (anterior == NULL) {
                *lista = atual->next;
                atual = *lista;
            } else {
                anterior->next = atual->next;
                atual = atual->next;
            }

            free(remover);
        } else {
            anterior = atual;
            atual = atual->next;
        }
    }
}

