CC ?= gcc
CFLAGS = -Wall -Werror -Wextra -std=c99 -pedantic -lSDL2 -lSDL2_image
OBJS = src/main.o src/entity/player/player.o src/physics/physics.o
EXEC = game

.PHONY: run clean

run : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(EXEC)
	./$(EXEC)

clean :
	$(RM) $(OBJS) $(EXEC)
