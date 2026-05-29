# Amazing Climb

Jogo simples feito em C com raylib. O jogador controla o Homem-Aranha subindo um prédio enquanto desvia de obstáculos que caem pelas faixas.

O projeto foi organizado para praticar estruturas, ponteiros, alocação dinâmica, lista encadeada e separação de código em módulos.

# Gameplay do jogo

[![Gameplay do Amazing Climb](https://img.youtube.com/vi/ZonGtKrhyEs/0.jpg)](https://www.youtube.com/watch?v=ZonGtKrhyEs)

Clique na imagem para assistir ao gameplay.

## Como jogar

- `ENTER`: iniciar a partida
- `A` ou seta esquerda: mover para a faixa da esquerda
- `D` ou seta direita: mover para a faixa da direita
- `R`: reiniciar depois do fim de jogo
- `M`: voltar ao menu depois do fim de jogo
- `ESC`: sair pelo menu

O prédio tem três faixas. Os obstáculos aparecem em uma ou duas faixas por vez, deixando sempre pelo menos uma passagem livre. Cada obstáculo evitado soma ponto. Ao bater, o jogador perde uma vida e fica invencível por um curto período.

O recorde é salvo em `score.txt`, na pasta do jogo, e carregado de novo na próxima execução.

## Compilação

No Windows com MSYS2/MINGW64:

```sh
make run
```

No Linux ou macOS:

```sh
make
./jogo
```

## Estrutura

```text
PIF_Game/
├── Makefile
├── README.md
├── assets/
└── src/
    ├── config.h
    ├── game.c
    ├── game.h
    ├── main.c
    ├── obstacle.c
    ├── obstacle.h
    ├── player.c
    └── player.h
```

## Arquivos principais

`main.c` inicializa a janela, o áudio, cria o jogo e mantém o loop principal.

`config.h` concentra as constantes usadas pelo jogo: tamanho da tela, dimensões dos sprites, velocidade dos obstáculos, intervalos de animação e medidas do prédio.

`player.c` guarda a lógica do jogador: criação, troca de faixa, animação, desenho e liberação das texturas.

`obstacle.c` trabalha com uma lista encadeada de obstáculos. Ele cria novos obstáculos, atualiza a posição, desenha, remove os que saíram da tela e libera a memória no fim.

`game.c` coordena os estados do jogo, colisões, pontuação, recorde, menu, fim de jogo, música e desenho geral da cena.

## Ideias futuras

- Adicionar som de colisão
- Aumentar a dificuldade aos poucos
- Melhorar a tela de menu
