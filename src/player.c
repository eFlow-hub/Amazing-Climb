#include "player.h"
#include "config.h"
#include <stdlib.h>

Player *criar_player() {
    Player *player = malloc(sizeof(Player));

    if (player == NULL) {
        return NULL;
    }

    player->lane = 1;

    player->rect.width = PLAYER_WIDTH;
    player->rect.height = PLAYER_HEIGHT;

    player->rect.x = BUILDING_X + player->lane * LANE_WIDTH + LANE_WIDTH / 2 - PLAYER_WIDTH / 2;
    player->rect.y = SCREEN_HEIGHT - 120;

    player->vidas = 3;
    player->velocidade = PLAYER_SPEED;

    return player;
}

void atualizar_player(Player *player, float delta) {
    if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && player->lane > 0) {
        player->lane--;
    }

    if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && player->lane < LANE_COUNT - 1) {
        player->lane++;
    }

    player->rect.x = BUILDING_X + player->lane * LANE_WIDTH + LANE_WIDTH / 2 - PLAYER_WIDTH / 2;
}

void desenhar_player(Player *player) {
    DrawRectangleRec(player->rect, RED);
}

void liberar_player(Player *player) {
    free(player);
}