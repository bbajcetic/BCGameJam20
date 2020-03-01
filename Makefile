#OBJS specifies files to compile
OBJS = src/main.o src/game.o src/texture.o src/player.o src/map.o src/custom.o src/timer.o src/zone.o src/network.o src/client.o src/server.o src/collision.o src/SDL_shapes.o

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
src/game.o: $(HEADERS) src/texture.h src/map.h src/player.h src/timer.h src/zone.h src/network.h
src/texture.o: $(HEADERS)
src/player.o: $(HEADERS) src/texture.h
src/map.o: $(HEADERS) src/texture.h
src/custom.o: $(HEADERS)
src/timer.o: $(HEADERS)
src/zone.o: $(HEADERS) src/collision.h
src/network.o: $(HEADERS) src/client.h src/server.h
src/client.o: $(HEADERS)
src/server.o: $(HEADERS)
src/collision.o: $(HEADERS) src/SDL_shapes.h
src/SDL_shapes.o: $(HEADERS)
