#ifndef GAME_H
#define GAME_H

#include "config.h"
#include "player.h"
#include "obstacle.h"

typedef enum TelaJogo{
    MENU,
    JOGANDO,
    FIM_DE_JOGO
} TelaJogo;

typedef struct Jogo{
    Jogador *jogador;
    Obstaculo *obstaculos;
    float tempo_spawn;
    float invencibilidade;
    int pontuacao;
    int recorde;
    float deslocamento_fundo;
    TelaJogo tela;
    Texture2D frames_fundo[TOTAL_FRAMES_FUNDO];
    int frame_fundo;
    float tempo_fundo;
    Texture2D textura_menu;
    Texture2D textura_fim_de_jogo;
    Texture2D textura_janela;
    Music musica;
} Jogo;

Jogo *criar_jogo(void);
void atualizar_jogo(Jogo *jogo, float delta);
void desenhar_jogo(Jogo *jogo);
void liberar_jogo(Jogo *jogo);
void reiniciar_partida(Jogo *jogo);

#endif
