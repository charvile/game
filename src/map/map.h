#include <stdlib.h>
#include <stdio.h>

char ** readmap(char *path, int *w, int *h);
struct blk *createblklist(char **map, int w, int h);
