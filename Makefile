#OBJS specifies files to compile
OBJS = src/main.o src/game.o src/texture.o src/player.o src/map.o

#CC specifies compiler
CC = g++

#OBJ_NAME specifies object file name
OBJ_NAME = game.out

#specifies compilation flags
COMPILER_FLAGS = -w -g

#specifies the libraries to link against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

#target
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

main.o: src/constants.h src/game.h
game.o: src/constants.h src/texture.h src/map.h src/player.h
texture.o: 
player.o: src/constants.h src/texture.h
map.o: src/constants.h src/texture.h