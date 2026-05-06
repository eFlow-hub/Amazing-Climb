#include "game.h"
#include "config.h"
#include <stdlib.h>

Game *criar_jogo() {
    Game *game = malloc(sizeof(Game));

    if (game == NULL) {
        return NULL;
    }
    game->menuTexture = LoadTexture("assets/images/menu.png");
    game->player = criar_player();
    game->obstacles = NULL;
    game->timerSpawn = 0;
    game->gameOver = 0;
    game->invencibilidade = 0;
    game->score = 0;
    game->bestScore = 0;
    game->screen = MENU;
    game->backgroundOffset = 0;
    game->totalFramesFundo = 10;
    game->fundoframes[0] = LoadTexture("assets/images/fundo/frame_00.png");
    game->fundoframes[1] = LoadTexture("assets/images/fundo/frame_01.png");
    game->fundoframes[2] = LoadTexture("assets/images/fundo/frame_02.png");
    game->fundoframes[3] = LoadTexture("assets/images/fundo/frame_03.png");
    game->fundoframes[4] = LoadTexture("assets/images/fundo/frame_04.png");
    game->fundoframes[5] = LoadTexture("assets/images/fundo/frame_05.png");
    game->fundoframes[6] = LoadTexture("assets/images/fundo/frame_06.png");
    game->fundoframes[7] = LoadTexture("assets/images/fundo/frame_07.png");
    game->fundoframes[8] = LoadTexture("assets/images/fundo/frame_08.png");
    game->fundoframes[9] = LoadTexture("assets/images/fundo/frame_09.png");
    game->frameAtualFundo = 0;
    game->timerFundo = 0;
    carregar_texturas_obstaculos();

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
                game->gameOver = 1;
                game->screen = GAME_OVER;
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
    if (game->screen == GAME_OVER) {
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

    game->timerFundo += delta;

    if (game->timerFundo >= 0.1f) {
        game ->frameAtualFundo++;
        if (game->frameAtualFundo >= game->totalFramesFundo) {
            game->frameAtualFundo = 0;
        }
        game->timerFundo = 0;
    }


    game->backgroundOffset += 120 * delta;

    if (game->backgroundOffset >= 90){
        game->backgroundOffset = 0;
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
        DrawTexturePro(
        game->menuTexture,
        (Rectangle){0, 0, game->menuTexture.width, game->menuTexture.height},
        (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT},
        (Vector2){0, 0},
        0,
        WHITE
    );
        DrawText("AMAZING CLIMB", 270, 150, 30, RED);
        DrawText("ENTER - Iniciar", 300, 250, 24, WHITE);
        DrawText(TextFormat("Recorde: %d", game->bestScore), 320, 300, 24, WHITE);
        DrawText("ESC - Sair", 330, 350, 24, WHITE);
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
    
    
    Texture2D fundo = game->fundoframes[game->frameAtualFundo];
    DrawTexturePro(
        fundo,
        (Rectangle){0, 0, fundo.width, fundo.height},
        (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT},
        (Vector2){0, 0},
        0,
        WHITE
    );

    DrawTexturePro(
        fundo,
        (Rectangle){0, 0, fundo.width, fundo.height},
        (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT},
        (Vector2){0, 0},
        0,
        WHITE
    );

    DrawRectangle(BUILDING_X, 0, BUILDING_WIDTH, SCREEN_HEIGHT, DARKGRAY);

    for (int y = game->backgroundOffset - 90; y < SCREEN_HEIGHT; y += 90) {
        for (int lane = 0; lane < LANE_COUNT; lane++) {
            int x = BUILDING_X + lane * LANE_WIDTH + 30;

            DrawRectangle(x, y, 40, 35, YELLOW);
            DrawRectangleLines(x, y, 40, 35, BLACK);
        }
    }

    DrawLine(BUILDING_X + LANE_WIDTH, 0,
             BUILDING_X + LANE_WIDTH, SCREEN_HEIGHT, GRAY);

    DrawLine(BUILDING_X + LANE_WIDTH * 2, 0,
             BUILDING_X + LANE_WIDTH * 2, SCREEN_HEIGHT, GRAY);

    desenhar_player(game->player, game->invencibilidade);
    desenhar_obstaculos(game->obstacles);

    DrawText(TextFormat("Vidas: %d", game->player->vidas), 20, 20, 24, WHITE);
    DrawText(TextFormat("Score: %d", game->score), 20, 50, 24, WHITE);
}
void liberar_jogo(Game *game) {
    descarregar_texturas_obstaculos();
    liberar_obstaculos(game->obstacles);
    liberar_player(game->player);
    for (int i = 0; i < game->totalFramesFundo; i++) {
        UnloadTexture(game->fundoframes[i]);
    }
    UnloadTexture(game->menuTexture);
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