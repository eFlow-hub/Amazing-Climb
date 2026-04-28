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
    game->invencibilidade = 0;
    game->score = 0;
    game->bestScore = 0;
    game->screen = MENU;

    return game;
}

void verificar_colisoes(Game *game) {
    if (game->invencibilidade > 0) {
        return;
    }
    Obstacle *atual = game->obstacles;
    Obstacle *anterior = NULL;

    while (atual != NULL) {
        if (CheckCollisionRecs(game->player->rect, atual->rect)) {
            game->player->vidas--;
            game->invencibilidade = 1.0f;

            if (anterior == NULL) {
                game->obstacles = atual->next;
            } else {
                anterior->next = atual->next;
            }

            free(atual);

            if (game->player->vidas <= 0) {
                game->gameOver = GAME_OVER;
                if (game->score > game->bestScore) {
                    game->bestScore = game->score;
                }
            }

            return;
        }

        anterior = atual;
        atual = atual->next;
    }
}

void atualizar_jogo(Game *game, float delta) {
    if (game->screen == GAMEOVER) {
        if (IsKeyPressed(KEY_R)) {
            reiniciar_partida(game);
        }

        if (IsKeyPressed(KEY_M)) {
            game->screen = MENU;
        }

        return;
    }

    if (game->screen == MENU) {
        if (IsKeyPressed(KEY_ENTER)) {
            reiniciar_partida(game);
        }
        if (IsKeyPressed(KEY_ESCAPE)) {
            CloseWindow();
        }

        return;
    }

    if (game->gameOver) {
        return;
    }
    if (game->invencibilidade > 0) {
        game->invencibilidade -= delta;
    }

    game->timerSpawn += delta;

    if (game->timerSpawn >= 1.0f) {
        adicionar_obstaculo(&game->obstacles);
        game->timerSpawn = 0;
    }

    atualizar_player(game->player, delta);
    atualizar_obstaculos(game->obstacles, delta);
    remover_obstaculos_fora_da_tela(&game->obstacles, &game->score);
    verificar_colisoes(game);
}

void desenhar_jogo(Game *game) {

    if (game->screen == MENU) {
        DrawText("HOMEM-ARANHA NO PREDIO", 190, 150, 30, RED);
        DrawText("ENTER - Iniciar", 300, 250, 24, BLACK);
        DrawText(TextFormat("Recorde: %d", game->bestScore), 315, 300, 24, BLACK);
        DrawText("ESC - Sair", 330, 350, 24, BLACK);
        return;
    }

    if (game->screen == GAME_OVER) {
    DrawText("GAME OVER", 290, 220, 40, RED);
    DrawText(TextFormat("Score: %d", game->score), 330, 280, 24, BLACK);
    DrawText(TextFormat("Recorde: %d", game->bestScore), 315, 320, 24, BLACK);
    DrawText("R - Reiniciar", 310, 380, 24, BLACK);
    DrawText("M - Voltar ao Menu", 270, 420, 24, BLACK);
    return;
    }

    DrawRectangle(250, 0, 300, SCREEN_HEIGHT, DARKGRAY);

    desenhar_player(game->player);
    desenhar_obstaculos(game->obstacles);

    DrawText(TextFormat("Vidas: %d", game->player->vidas), 20, 20, 24, BLACK);
    DrawText(TextFormat("Score: %d", game->score), 20, 50, 24, BLACK);

    if (game->gameOver) {
        DrawText("GAME OVER", 300, 280, 40, RED);
    }
}

void liberar_jogo(Game *game) {
    liberar_obstaculos(game->obstacles);
    liberar_player(game->player);
    free(game);
}

void reiniciar_partida(Game *game){
    liberar_obstaculos(game->obstacles);
    liberar_player(game->player);

    game->player = criar_player();
    game->obstacles = NULL;
    game->timerSpawn = 0;
    game->invencibilidade = 0;
    game->score = 0;
    game->gameOver = 0;
    game->screen = PLAYING;
}