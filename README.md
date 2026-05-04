# 🕷️ Amazing Climb

Projeto desenvolvido em linguagem C utilizando a biblioteca **raylib**, com foco em aplicar conceitos fundamentais como:

- Structs
- Ponteiros
- Alocação dinâmica (`malloc` / `free`)
- Lista encadeada
- Organização modular em múltiplos arquivos

---

# 🎮 Descrição do Jogo

O jogador controla o Homem-Aranha subindo um prédio.

- O prédio possui **3 faixas (lanes)**: esquerda, centro e direita.
- O player só pode se mover entre essas faixas.
- Obstáculos caem de cima do prédio.
- O jogador deve desviar para sobreviver.
- Se colidir:
  - perde uma vida
  - obstáculo desaparece
- Se um obstáculo sai da tela:
  - jogador ganha ponto
- O jogo termina quando as vidas chegam a 0.

---

# 🧠 Lógica Geral

Fluxo principal:
main → cria jogo
→ loop principal
→ atualizar_jogo()
→ desenhar_jogo()
→ liberar_jogo()


---

# 🗂️ Estrutura de Pastas
PIF_Game/
├── Makefile
├── README.md
└── src/
├── main.c
├── config.h
├── game.c
├── game.h
├── player.c
├── player.h
├── obstacle.c
└── obstacle.h


---

# ⚙️ Compilação

### Windows (MSYS2 MINGW64)

```bash
make run
Linux / Mac
make
./jogo
📁 Arquivos e Responsabilidades
🧩 main.c
Responsável por:

Inicializar a janela (raylib)

Criar o jogo

Rodar o loop principal

Chamar atualização e renderização

Liberar memória

while (!WindowShouldClose()) {
    atualizar_jogo();
    desenhar_jogo();
}
⚙️ config.h
Armazena constantes globais:

#define SCREEN_WIDTH 800
#define BUILDING_WIDTH 300
#define LANE_COUNT 3
Evita números “hardcoded” no código.

🧍 player.h / player.c
Struct Player:
typedef struct Player {
    Rectangle rect;
    int vidas;
    int lane;
    float velocidade;
} Player;
Lógica:
O player não se move livremente

Ele troca entre 3 faixas:

0 = esquerda
1 = centro
2 = direita
Funções:
Função	Descrição
criar_player	aloca e inicializa
atualizar_player	troca de faixa
desenhar_player	renderiza
liberar_player	libera memória
🧱 obstacle.h / obstacle.c
Struct Obstacle:
typedef struct Obstacle {
    Rectangle rect;
    float velocidade;
    struct Obstacle *next;
} Obstacle;
👉 Isso cria uma lista encadeada

🧠 Lista Encadeada
Estrutura:

[Obstacle] → [Obstacle] → [Obstacle] → NULL
Cada obstáculo aponta para o próximo.

Funções:
adicionar_obstaculo
Cria 1 ou 2 obstáculos

Escolhe faixas aleatórias

Nunca bloqueia as 3 faixas

atualizar_obstaculos
y += velocidade * delta
Faz todos descerem.

remover_obstaculos_fora_da_tela
Remove obstáculos fora da tela

Libera memória (free)

Aumenta score

liberar_obstaculos
Libera toda a lista encadeada.

🎮 game.h / game.c
Struct Game:
typedef struct Game {
    Player *player;
    Obstacle *obstacles;
    float timerSpawn;
    float invencibilidade;
    int score;
    int bestScore;
    int gameOver;
    GameScreen screen;
} Game;
📺 Estados do jogo
typedef enum GameScreen {
    MENU,
    PLAYING,
    GAME_OVER
} GameScreen;
🔁 Funções principais
criar_jogo
Inicializa:

player

lista vazia

score

estado MENU

atualizar_jogo
Responsável por toda a lógica:

MENU → espera clique
PLAYING →
    spawn obstáculos
    mover player
    mover obstáculos
    remover obstáculos
    verificar colisões
GAME_OVER → espera input
verificar_colisoes
Percorre lista:

if (colisão) {
    perde vida
    ativa invencibilidade
    remove obstáculo
    free()
}
👉 Aqui está o uso forte de:

ponteiros

lista encadeada

manipulação de memória

reiniciar_partida
libera memória
cria novo player
zera score
reseta estado
desenhar_jogo
Desenha baseado no estado:

MENU → botões

PLAYING → jogo

GAME OVER → score + opções

🧠 Conceitos aplicados
📌 Ponteiros
Player *player;
Obstacle *lista;
📌 Alocação dinâmica
malloc()
free()
📌 Lista encadeada
struct Obstacle *next;
📌 Modularização
Separação em:

player

obstacle

game

📌 Estrutura de dados dinâmica
Lista cresce e diminui durante execução.

🎯 Mecânicas principais
Movimento por faixas

Spawn controlado de obstáculos

Sempre existe caminho livre

Sistema de vidas

Invencibilidade temporária

Sistema de pontuação

Menu + Game Over

🚀 Possíveis melhorias futuras
Sprites do Homem-Aranha

Animações

Sons

Dificuldade progressiva

Power-ups

Persistência de recorde em arquivo

👨‍💻 Autor
Projeto acadêmico desenvolvido para prática de:

Estruturas de dados

Programação em C

Desenvolvimento de jogos básicos


---

Se quiser, próximo passo a gente pode:

👉 salvar o recorde em arquivo (pra não perder ao fechar o jogo)  
👉 deixar o menu mais bonito (UI melhor)  
👉 adicionar sprite real do Homem-Aranha 🕷️








possiveis proximas atts:

1. Adicionar som de colisão
2. Colocar sprites nos obstáculos
3. Criar tela de vitória ou objetivo final
4. Salvar recorde em arquivo
5. Melhorar menu visual
6. Adicionar dificuldade progressiva leve
7. Adicionar efeito de tela tremendo ao bater
