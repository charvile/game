CC ?= gcc
CFLAGS = -Wall -Werror -Wextra -std=c99 -pedantic -lSDL2
OBJS = src/main.o
EXEC = game

.PHONY: run clean

run : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(EXEC)
	./$(EXEC)

clean :
	$(RM) $(OBJS) $(EXEC)
