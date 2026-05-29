#include "game.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>

static void carregar_frames_fundo(Jogo *jogo){
    char caminho[64];

    for(int i = 0; i < TOTAL_FRAMES_FUNDO; i++){
        snprintf(caminho, sizeof caminho, "assets/images/fundo/frame_%02d.png", i);
        jogo->frames_fundo[i] = LoadTexture(caminho);
    }
}

static void descarregar_frames_fundo(Jogo *jogo){
    for(int i = 0; i < TOTAL_FRAMES_FUNDO; i++){
        UnloadTexture(jogo->frames_fundo[i]);
    }
}

static int carregar_recorde(void){
    FILE *arquivo = fopen(ARQUIVO_RECORDE, "r");
    int recorde = 0;

    if(arquivo == NULL){
        return 0;
    }

    if(fscanf(arquivo, "%d", &recorde) != 1){
        recorde = 0;
    }

    fclose(arquivo);

    if(recorde < 0){
        return 0;
    }

    return recorde;
}

static void salvar_recorde(int recorde){
    FILE *arquivo = fopen(ARQUIVO_RECORDE, "w");

    if(arquivo == NULL){
        return;
    }

    fprintf(arquivo, "%d\n", recorde);
    fclose(arquivo);
}

static void desenhar_textura_tela(Texture2D textura){
    DrawTexturePro(
        textura,
        (Rectangle){0, 0, (float)textura.width, (float)textura.height},
        (Rectangle){0, 0, LARGURA_TELA, ALTURA_TELA},
        (Vector2){0, 0},
        0,
        WHITE
    );
}

static int tipo_janela(int faixa, int linha){
    return (faixa * 7 + linha * 3) % QTD_TIPOS_JANELA;
}

static void desenhar_janelas(Jogo *jogo){
    static const Rectangle fontes[QTD_TIPOS_JANELA] = {
        {0, 0, TAMANHO_SPRITE_JANELA, TAMANHO_SPRITE_JANELA},
        {TAMANHO_SPRITE_JANELA, 0, TAMANHO_SPRITE_JANELA, TAMANHO_SPRITE_JANELA},
        {0, TAMANHO_SPRITE_JANELA, TAMANHO_SPRITE_JANELA, TAMANHO_SPRITE_JANELA},
        {TAMANHO_SPRITE_JANELA, TAMANHO_SPRITE_JANELA, TAMANHO_SPRITE_JANELA, TAMANHO_SPRITE_JANELA}
    };
    const float tamanho = TAMANHO_JANELA;
    int linha = 0;

    for(float y = jogo->deslocamento_fundo - ESPACO_JANELAS; y < ALTURA_TELA; y += ESPACO_JANELAS){
        for(int faixa = 0; faixa < QTD_FAIXAS; faixa++){
            int tipo = tipo_janela(faixa, linha);
            float x = PREDIO_X + faixa * LARGURA_FAIXA + LARGURA_FAIXA / 2 - tamanho / 2;

            DrawTexturePro(
                jogo->textura_janela,
                fontes[tipo],
                (Rectangle){x, y, tamanho, tamanho},
                (Vector2){0, 0},
                0,
                WHITE
            );
        }

        linha++;
    }
}

static void verificar_colisoes(Jogo *jogo){
    if(jogo->invencibilidade > 0){
        return;
    }

    Obstaculo *atual = jogo->obstaculos;
    Obstaculo *anterior = NULL;

    while(atual != NULL){
        if(CheckCollisionRecs(jogo->jogador->retangulo, atual->retangulo)){
            jogo->jogador->vidas--;
            jogo->invencibilidade = TEMPO_INVENCIBILIDADE;

            if(anterior == NULL){
                jogo->obstaculos = atual->proximo;
            }else{
                anterior->proximo = atual->proximo;
            }

            free(atual);

            if(jogo->jogador->vidas <= 0){
                jogo->tela = FIM_DE_JOGO;

                if(jogo->pontuacao > jogo->recorde){
                    jogo->recorde = jogo->pontuacao;
                    salvar_recorde(jogo->recorde);
                }
            }

            return;
        }

        anterior = atual;
        atual = atual->proximo;
    }
}

Jogo *criar_jogo(void){
    Jogo *jogo = malloc(sizeof *jogo);

    if(jogo == NULL){
        return NULL;
    }

    jogo->jogador = criar_jogador();

    if(jogo->jogador == NULL){
        free(jogo);
        return NULL;
    }

    jogo->obstaculos = NULL;
    jogo->tempo_spawn = 0;
    jogo->invencibilidade = 0;
    jogo->pontuacao = 0;
    jogo->recorde = carregar_recorde();
    jogo->deslocamento_fundo = 0;
    jogo->tela = MENU;
    jogo->frame_fundo = 0;
    jogo->tempo_fundo = 0;

    carregar_frames_fundo(jogo);
    jogo->textura_menu = LoadTexture("assets/images/menu.png");
    jogo->textura_fim_de_jogo = LoadTexture("assets/images/gameover.png");
    jogo->textura_janela = LoadTexture("assets/images/windows.png");
    jogo->musica = LoadMusicStream("assets/soundtrack.mp3");
    jogo->musica.looping = true;

    carregar_texturas_obstaculos();
    PlayMusicStream(jogo->musica);

    return jogo;
}

void atualizar_jogo(Jogo *jogo, float delta){
    UpdateMusicStream(jogo->musica);

    if(jogo->tela == FIM_DE_JOGO){
        if(IsKeyPressed(KEY_R)){
            reiniciar_partida(jogo);
        }

        if(IsKeyPressed(KEY_M)){
            jogo->tela = MENU;
        }

        return;
    }

    if(jogo->tela == MENU){
        if(IsKeyPressed(KEY_ENTER)){
            reiniciar_partida(jogo);
        }

        if(IsKeyPressed(KEY_ESCAPE)){
            CloseWindow();
        }

        return;
    }

    jogo->tempo_fundo += delta;

    if(jogo->tempo_fundo >= TEMPO_FRAME_FUNDO){
        jogo->frame_fundo++;

        if(jogo->frame_fundo >= TOTAL_FRAMES_FUNDO){
            jogo->frame_fundo = 0;
        }

        jogo->tempo_fundo = 0;
    }

    jogo->deslocamento_fundo += VELOCIDADE_FUNDO * delta;

    if(jogo->deslocamento_fundo >= ESPACO_JANELAS){
        jogo->deslocamento_fundo = 0;
    }

    if(jogo->invencibilidade > 0){
        jogo->invencibilidade -= delta;

        if(jogo->invencibilidade < 0){
            jogo->invencibilidade = 0;
        }
    }

    jogo->tempo_spawn += delta;

    if(jogo->tempo_spawn >= INTERVALO_SPAWN){
        adicionar_obstaculo(&jogo->obstaculos);
        jogo->tempo_spawn = 0;
    }

    atualizar_jogador(jogo->jogador, delta);
    atualizar_obstaculos(jogo->obstaculos, delta);
    remover_obstaculos_fora_da_tela(&jogo->obstaculos, &jogo->pontuacao);
    verificar_colisoes(jogo);
}

void desenhar_jogo(Jogo *jogo){
    if(jogo->tela == MENU){
        desenhar_textura_tela(jogo->textura_menu);
        DrawText("ENTER - Iniciar", 300, 250, 24, WHITE);
        DrawText(TextFormat("Recorde: %d", jogo->recorde), 320, 300, 24, WHITE);
        DrawText("ESC - Sair", 330, 350, 24, WHITE);
        return;
    }

    if(jogo->tela == FIM_DE_JOGO){
        desenhar_textura_tela(jogo->textura_fim_de_jogo);
        DrawText(TextFormat("Pontuacao: %d", jogo->pontuacao), 330, 200, 24, WHITE);
        DrawText(TextFormat("Recorde: %d", jogo->recorde), 345, 250, 24, WHITE);
        DrawText("R - Reiniciar", 335, 300, 24, WHITE);
        DrawText("M - Voltar ao Menu", 290, 350, 24, WHITE);
        return;
    }

    Texture2D fundo = jogo->frames_fundo[jogo->frame_fundo];

    desenhar_textura_tela(fundo);
    DrawRectangle(PREDIO_X, 0, LARGURA_PREDIO, ALTURA_TELA, DARKGRAY);
    desenhar_janelas(jogo);

    DrawLine(PREDIO_X + LARGURA_FAIXA, 0, PREDIO_X + LARGURA_FAIXA, ALTURA_TELA, GRAY);
    DrawLine(PREDIO_X + LARGURA_FAIXA * 2, 0, PREDIO_X + LARGURA_FAIXA * 2, ALTURA_TELA, GRAY);

    desenhar_jogador(jogo->jogador, jogo->invencibilidade);
    desenhar_obstaculos(jogo->obstaculos);

    DrawText(TextFormat("Vidas: %d", jogo->jogador->vidas), 20, 20, 24, WHITE);
    DrawText(TextFormat("Pontos: %d", jogo->pontuacao), 20, 50, 24, WHITE);
}

void liberar_jogo(Jogo *jogo){
    if(jogo == NULL){
        return;
    }

    descarregar_texturas_obstaculos();
    liberar_obstaculos(jogo->obstaculos);
    liberar_jogador(jogo->jogador);
    descarregar_frames_fundo(jogo);
    UnloadTexture(jogo->textura_menu);
    UnloadTexture(jogo->textura_fim_de_jogo);
    UnloadTexture(jogo->textura_janela);
    UnloadMusicStream(jogo->musica);
    free(jogo);
}

void reiniciar_partida(Jogo *jogo){
    liberar_obstaculos(jogo->obstaculos);
    liberar_jogador(jogo->jogador);

    jogo->jogador = criar_jogador();
    jogo->obstaculos = NULL;
    jogo->tempo_spawn = 0;
    jogo->invencibilidade = 0;
    jogo->pontuacao = 0;
    jogo->deslocamento_fundo = 0;
    jogo->frame_fundo = 0;
    jogo->tempo_fundo = 0;

    if(jogo->jogador == NULL){
        jogo->tela = FIM_DE_JOGO;
        return;
    }

    jogo->tela = JOGANDO;
}
