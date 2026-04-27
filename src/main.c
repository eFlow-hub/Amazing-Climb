#include "raylib.h"
#include "config.h"
#include "player.h"
#include "obstacle.h"
#include <stdlib.h>
#include <time.h>

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);
    SetTargetFPS(60);

    srand(time(NULL));

    Player *player = criar_player();
    Obstacle *obstacles = NULL;

    float timerSpawn = 0;

    while (!WindowShouldClose()) {
        float delta = GetFrameTime();

        timerSpawn += delta;

        if (timerSpawn >= 1.0f) {
            adicionar_obstaculo(&obstacles);
            timerSpawn = 0;
        }

        atualizar_player(player, delta);
        atualizar_obstaculos(obstacles, delta);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangle(250, 0, 300, SCREEN_HEIGHT, DARKGRAY);

        desenhar_player(player);
        desenhar_obstaculos(obstacles);

        EndDrawing();
    }

    liberar_obstaculos(obstacles);
    liberar_player(player);

    CloseWindow();

    return 0;
}