#include "raylib.h"
#include "config.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>

int main(void){
    InitWindow(LARGURA_TELA, ALTURA_TELA, TITULO_JOGO);
    SetTargetFPS(60);
    InitAudioDevice();

    srand(time(NULL));

    Jogo *jogo = criar_jogo();

    if(jogo == NULL){
        CloseAudioDevice();
        CloseWindow();
        return 1;
    }

    while(!WindowShouldClose()){
        float delta = GetFrameTime();

        atualizar_jogo(jogo, delta);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        desenhar_jogo(jogo);

        EndDrawing();
    }

    liberar_jogo(jogo);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
