#include "player.h"
#include "config.h"
#include <stdlib.h>

Player *criar_player() {
    Player *player = malloc(sizeof(Player));

    if (player == NULL) {
        return NULL;
    }

    player->rect.x = SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2;
    player->rect.y = SCREEN_HEIGHT - 120;
    player->rect.width = PLAYER_WIDTH;
    player->rect.height = PLAYER_HEIGHT;

    player->vidas = 3;
    player->velocidade = PLAYER_SPEED;

    return player;
}

void atualizar_player(Player *player, float delta) {
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        player->rect.x -= player->velocidade * delta;
    }

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        player->rect.x += player->velocidade * delta;
    }

    if (player->rect.x < 0) {
        player->rect.x = 0;
    }

    if (player->rect.x + player->rect.width > SCREEN_WIDTH) {
        player->rect.x = SCREEN_WIDTH - player->rect.width;
    }
}

void desenhar_player(Player *player) {
    DrawRectangleRec(player->rect, RED);
}

void liberar_player(Player *player) {
    free(player);
}