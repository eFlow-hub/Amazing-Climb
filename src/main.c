#include "raylib.h"
#include "config.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);
    SetTargetFPS(60);

    srand(time(NULL));

    Game *game = criar_jogo();

    while (!WindowShouldClose()) {
        float delta = GetFrameTime();

        atualizar_jogo(game, delta);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        desenhar_jogo(game);

        EndDrawing();
    }

    liberar_jogo(game);

    CloseWindow();

    return 0;
}