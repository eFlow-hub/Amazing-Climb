#include "player.h"
#include "config.h"
#include <stdlib.h>

static float posicao_x_jogador(int faixa){
    return PREDIO_X + faixa * LARGURA_FAIXA + LARGURA_FAIXA / 2 - LARGURA_JOGADOR / 2;
}

Jogador *criar_jogador(void){
    Jogador *jogador = malloc(sizeof *jogador);

    if(jogador == NULL){
        return NULL;
    }

    jogador->faixa = FAIXA_INICIAL_JOGADOR;
    jogador->retangulo = (Rectangle){
        posicao_x_jogador(jogador->faixa),
        ALTURA_TELA - MARGEM_INFERIOR_JOGADOR,
        LARGURA_JOGADOR,
        ALTURA_JOGADOR
    };
    jogador->vidas = VIDAS_INICIAIS;

    jogador->textura_1 = LoadTexture("assets/images/spider1.png");
    jogador->textura_2 = LoadTexture("assets/images/spider2.png");
    jogador->frame_atual = 0;
    jogador->tempo_animacao = 0;

    return jogador;
}

void atualizar_jogador(Jogador *jogador, float delta){
    if((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && jogador->faixa > 0){
        jogador->faixa--;
    }

    if((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && jogador->faixa < QTD_FAIXAS - 1){
        jogador->faixa++;
    }

    jogador->retangulo.x = posicao_x_jogador(jogador->faixa);
    jogador->tempo_animacao += delta;

    if(jogador->tempo_animacao >= TEMPO_ANIMACAO_JOGADOR){
        jogador->frame_atual = !jogador->frame_atual;
        jogador->tempo_animacao = 0;
    }
}

void desenhar_jogador(Jogador *jogador, float invencibilidade){
    if(invencibilidade > 0){
        int piscar = ((int)(invencibilidade * 10)) % 2;

        if(piscar == 0){
            return;
        }
    }

    Texture2D textura = jogador->frame_atual == 0
        ? jogador->textura_1
        : jogador->textura_2;

    DrawTexturePro(
        textura,
        (Rectangle){0, 0, (float)textura.width, (float)textura.height},
        jogador->retangulo,
        (Vector2){0, 0},
        0,
        WHITE
    );
}

void liberar_jogador(Jogador *jogador){
    if(jogador == NULL){
        return;
    }

    UnloadTexture(jogador->textura_1);
    UnloadTexture(jogador->textura_2);
    free(jogador);
}
