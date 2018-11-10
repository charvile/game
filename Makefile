CC ?= gcc
CFLAGS = -Wall -g -Wextra -std=c99 -pedantic -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
OBJS = src/main.o src/entity/player/player.o src/physics/physics.o src/entity/ennemie/ennemy.o src/graphics/display.o src/map/map.o src/vect/vect.o src/utilities/utilities.o
EXEC = game

.PHONY: run clean

run : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(EXEC)
	./$(EXEC)

clean :
	$(RM) $(OBJS) $(EXEC)
