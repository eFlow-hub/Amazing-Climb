CC = gcc
SRC = src/main.c src/player.c src/obstacle.c src/game.c
OUT = jogo

ifeq ($(OS),Windows_NT)
	LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
	EXEC = $(OUT).exe
	RUN = ./$(EXEC)
	RM = rm -f
else
	LIBS = -lraylib -lm -ldl -lpthread
	EXEC = $(OUT)
	RUN = ./$(EXEC)
	RM = rm -f
endif

all:
	$(CC) $(SRC) -o $(EXEC) $(LIBS)

run: all
	$(RUN)

clean:
	$(RM) jogo jogo.exe