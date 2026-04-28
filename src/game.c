#include "game.h"
#include "config.h"
#include <stdlib.h>

Game *criar_jogo() {
    Game *game = malloc(sizeof(Game));

    if (game == NULL) {
        return NULL;
    }

    game->player = criar_player();
    game->obstacles = NULL;
    game->timerSpawn = 0;
    game->gameOver = 0;

    return game;
}

void verificar_colisoes(Game *game) {
    Obstacle *atual = game->obstacles;

    while (atual != NULL) {
        if (CheckCollisionRecs(game->player->rect, atual->rect)) {
            game->player->vidas--;

            if (game->player->vidas <= 0) {
                game->gameOver = 1;
            }

            return;
        }

        atual = atual->next;
    }
}

void atualizar_jogo(Game *game, float delta) {
    if (game->gameOver) {
        return;
    }

    game->timerSpawn += delta;

    if (game->timerSpawn >= 1.0f) {
        adicionar_obstaculo(&game->obstacles);
        game->timerSpawn = 0;
    }

    atualizar_player(game->player, delta);
    atualizar_obstaculos(game->obstacles, delta);
    remover_obstaculos_fora_da_tela(&game->obstacles);
    verificar_colisoes(game);
}

void desenhar_jogo(Game *game) {
    DrawRectangle(250, 0, 300, SCREEN_HEIGHT, DARKGRAY);

    desenhar_player(game->player);
    desenhar_obstaculos(game->obstacles);

    DrawText(TextFormat("Vidas: %d", game->player->vidas), 20, 20, 24, BLACK);

    if (game->gameOver) {
        DrawText("GAME OVER", 300, 280, 40, RED);
    }
}

void liberar_jogo(Game *game) {
    liberar_obstaculos(game->obstacles);
    liberar_player(game->player);
    free(game);
}