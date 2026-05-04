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

    player->frame1 = LoadTexture("assets/images/spider1.png");
    player->frame2 = LoadTexture("assets/images/spider2.png");
    
    player->frameAtual = 0;
    player->animtimer = 0;

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

    player->animtimer += delta;
    if (player->animtimer >= 0.2f) {
        player->frameAtual = !player->frameAtual;
        player->animtimer = 0;
    }
}

void desenhar_player(Player *player) {
    Texture2D textura;

    if (player->frameAtual == 0) {
        textura = player->frame1;
    } else {
        textura = player->frame2;
    }

    DrawTexturePro(
        textura,
        (Rectangle){0, 0, textura.width, textura.height},
        player->rect,
        (Vector2){0, 0},
        0,
        WHITE
    );
}

void liberar_player(Player *player) {
    UnloadTexture(player->frame1);
    UnloadTexture(player->frame2);
    free(player);
}