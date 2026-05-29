#include "obstacle.h"
#include "config.h"
#include <stdlib.h>

static Texture2D texturas_obstaculos[QTD_TEXTURAS_OBSTACULOS];

static float posicao_x_obstaculo(int faixa){
    return PREDIO_X + faixa * LARGURA_FAIXA + LARGURA_FAIXA / 2 - LARGURA_OBSTACULO / 2;
}

void carregar_texturas_obstaculos(void){
    for(int i = 0; i < QTD_TEXTURAS_OBSTACULOS; i++){
        texturas_obstaculos[i] = LoadTexture(TextFormat("assets/images/obstaculo%d.png", i + 1));
    }
}

void descarregar_texturas_obstaculos(void){
    for(int i = 0; i < QTD_TEXTURAS_OBSTACULOS; i++){
        UnloadTexture(texturas_obstaculos[i]);
    }
}

void adicionar_obstaculo(Obstaculo **lista){
    int quantidade = GetRandomValue(MIN_OBSTACULOS_SPAWN, MAX_OBSTACULOS_SPAWN);
    int faixa_1 = GetRandomValue(0, QTD_FAIXAS - 1);
    int faixa_2 = faixa_1;

    if(quantidade == 2){
        do{
            faixa_2 = GetRandomValue(0, QTD_FAIXAS - 1);
        }while(faixa_2 == faixa_1);
    }

    int faixas[2] = {faixa_1, faixa_2};

    for(int i = 0; i < quantidade; i++){
        int faixa = faixas[i];
        Obstaculo *novo = malloc(sizeof *novo);

        if(novo == NULL){
            return;
        }

        novo->retangulo = (Rectangle){
            posicao_x_obstaculo(faixa),
            -ALTURA_OBSTACULO,
            LARGURA_OBSTACULO,
            ALTURA_OBSTACULO
        };
        novo->velocidade = VELOCIDADE_OBSTACULO;
        novo->tipo = GetRandomValue(0, QTD_TEXTURAS_OBSTACULOS - 1);
        novo->proximo = *lista;
        *lista = novo;
    }
}

void atualizar_obstaculos(Obstaculo *lista, float delta){
    Obstaculo *atual = lista;

    while(atual != NULL){
        atual->retangulo.y += atual->velocidade * delta;
        atual = atual->proximo;
    }
}

void desenhar_obstaculos(Obstaculo *lista){
    Obstaculo *atual = lista;

    while(atual != NULL){
        Texture2D textura = texturas_obstaculos[atual->tipo];

        DrawTexturePro(
            textura,
            (Rectangle){0, 0, (float)textura.width, (float)textura.height},
            atual->retangulo,
            (Vector2){0, 0},
            0,
            WHITE
        );

        atual = atual->proximo;
    }
}

void remover_obstaculos_fora_da_tela(Obstaculo **lista, int *pontuacao){
    Obstaculo *atual = *lista;
    Obstaculo *anterior = NULL;

    while(atual != NULL){
        if(atual->retangulo.y > ALTURA_TELA){
            Obstaculo *remover = atual;

            if(anterior == NULL){
                *lista = atual->proximo;
                atual = *lista;
            }else{
                anterior->proximo = atual->proximo;
                atual = atual->proximo;
            }

            free(remover);
            (*pontuacao)++;
        }else{
            anterior = atual;
            atual = atual->proximo;
        }
    }
}

void liberar_obstaculos(Obstaculo *lista){
    Obstaculo *atual = lista;

    while(atual != NULL){
        Obstaculo *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}
