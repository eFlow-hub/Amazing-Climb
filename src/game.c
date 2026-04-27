#include "game.h"
#include "config.h"
#include <stdlib.h>

Game *criar_jogo() {
    Game *game = malloc(sizeof(Game));

    if (game == NULL) return NULL;

    game->player = criar_player();
    game->obstacles = NULL;
    game->timerSpawn = 0;

    return game;
}

void atualizar_jogo(Game *game, float delta) {
    game->timerSpawn += delta;

    if (game->timerSpawn >= 1.0f) {
        adicionar_obstaculo(&game->obstacles);
        game->timerSpawn = 0;
    }

    atualizar_player(game->player, delta);
    atualizar_obstaculos(game->obstacles, delta);
}

void desenhar_jogo(Game *game) {
    DrawRectangle(250, 0, 300, SCREEN_HEIGHT, DARKGRAY);

    desenhar_player(game->player);
    desenhar_obstaculos(game->obstacles);
}

void liberar_jogo(Game *game) {
    liberar_obstaculos(game->obstacles);
    liberar_player(game->player);
    free(game);
}