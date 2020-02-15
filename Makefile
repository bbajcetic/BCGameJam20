#OBJS specifies files to compile
OBJS = src/main.o

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

main.o: src/constants.h