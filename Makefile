CC ?= gcc
CFLAGS = -Wall -g -Werror -Wextra -std=c99 -pedantic -lSDL2 -lSDL2_image -lSDL2_ttf -fsanitize=address
OBJS = src/main.o src/entity/player/player.o src/physics/physics.o src/entity/ennemie/ennemy.o src/graphics/display.o
EXEC = game

.PHONY: run clean

run : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(EXEC)
	./$(EXEC)

clean :
	$(RM) $(OBJS) $(EXEC)
