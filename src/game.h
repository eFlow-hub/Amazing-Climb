#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "obstacle.h"

typedef enum GameScreen {
    MENU,
    PLAYING,
    GAME_OVER
} GameScreen;

typedef struct Game {
    Player *player;
    Obstacle *obstacles;
    float timerSpawn;
    float invencibilidade;
    int score;
    int bestScore;
    int gameOver;
    float backgroundOffset;
    GameScreen screen;
    Texture2D fundoframes[10];
    int frameAtualFundo;
    float timerFundo;
    int totalFramesFundo;
    Texture2D menuTexture;
    Texture2D gameOverTexture;
    Texture2D windowTexture;
    Music soundtrack;
} Game;

Game *criar_jogo();
void atualizar_jogo(Game *game, float delta);
void desenhar_jogo(Game *game);
void liberar_jogo(Game *game);
void reiniciar_partida(Game *game);

#endif