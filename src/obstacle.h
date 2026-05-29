#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "raylib.h"

typedef struct Obstaculo{
    Rectangle retangulo;
    float velocidade;
    int tipo;
    struct Obstaculo *proximo;
} Obstaculo;

void carregar_texturas_obstaculos(void);
void descarregar_texturas_obstaculos(void);
void adicionar_obstaculo(Obstaculo **lista);
void atualizar_obstaculos(Obstaculo *lista, float delta);
void desenhar_obstaculos(Obstaculo *lista);
void remover_obstaculos_fora_da_tela(Obstaculo **lista, int *pontuacao);
void liberar_obstaculos(Obstaculo *lista);

#endif
