#OBJS specifies files to compile
OBJS = src/main.o src/game.o src/texture.o src/player.o src/map.o src/custom.o

#CC specifies compiler
CC = g++

#OBJ_NAME specifies object file name
OBJ_NAME = game.out

HEADERS = src/custom.h src/constants.h

#specifies compilation flags
COMPILER_FLAGS = -w -g

#specifies the libraries to link against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

#target
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

src/main.o: $(HEADERS) src/game.h
src/game.o: $(HEADERS) src/texture.h src/map.h src/player.h
src/texture.o: $(HEADERS)
src/player.o: $(HEADERS) src/texture.h
src/map.o: $(HEADERS) src/texture.h
src/custom.o: $(HEADERS)
