#include "obstacle.h"
#include "config.h"
#include <stdlib.h>
static Texture2D obstaculoTexturas[3];

void carregar_texturas_obstaculos() {
    obstaculoTexturas[0] = LoadTexture("assets/images/obstaculo1.png");
    obstaculoTexturas[1] = LoadTexture("assets/images/obstaculo2.png");
    obstaculoTexturas[2] = LoadTexture("assets/images/obstaculo3.png");
}

void descarregar_texturas_obstaculos() {
    for (int i = 0; i < 3; i++) {
        UnloadTexture(obstaculoTexturas[i]);
    }
}

void adicionar_obstaculo(Obstacle **lista) {
    int quantidade = GetRandomValue(1, 2); 
    int faixaBloqueada1 = GetRandomValue(0, LANE_COUNT - 1);
    int faixaBloqueada2 = faixaBloqueada1;

    if (quantidade == 2) {
        do {
            faixaBloqueada2 = GetRandomValue(0, LANE_COUNT - 1);
        } while (faixaBloqueada2 == faixaBloqueada1);
    }

    for (int i = 0; i < quantidade; i++) {
        int lane;

        if (i == 0) {
            lane = faixaBloqueada1;
        } else {
            lane = faixaBloqueada2;
        }

        Obstacle *novo = malloc(sizeof(Obstacle));

        if (novo == NULL) {
            return;
        }

        novo->rect.width = OBSTACLE_WIDTH;
        novo->rect.height = OBSTACLE_HEIGHT;

        novo->rect.x = BUILDING_X + lane * LANE_WIDTH + LANE_WIDTH / 2 - OBSTACLE_WIDTH / 2;
        novo->rect.y = -OBSTACLE_HEIGHT;

        novo->velocidade = OBSTACLE_SPEED;

        novo->tipo = GetRandomValue(0, 2);

        novo->next = *lista;
        *lista = novo;
    }
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
        Texture2D textura = obstaculoTexturas[atual->tipo];

        DrawTexturePro(
            textura,
            (Rectangle){0, 0, textura.width, textura.height},
            atual->rect,
            (Vector2){0, 0},
            0,
            WHITE
        );

        atual = atual->next;
    }
}

void remover_obstaculos_fora_da_tela(Obstacle **lista, int *score) {
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
            (*score)++;
        } else {
            anterior = atual;
            atual = atual->next;
        }
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