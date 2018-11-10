#define _XOPEN_SOURCE 700
#include "map.h"
#include "../global.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#define BLKW 50;
#define BLKH 50;

struct blk
{
    int w;
    int h;
    int type;
    SDL_Rect *mesh;
};

char** readmap(char *path, int *w, int *h)
{
    FILE *fd = fopen(path, "r");

    char *bufferh = NULL;
    size_t len = 5;
    ssize_t test = getline(&bufferh, &len, fd);
    int sizeh = atoi(bufferh);
    free(bufferh);
    if (test == -1)
        return NULL;

    char *bufferw = NULL;
    ssize_t test2 = getline(&bufferw, &len, fd);
    int sizew = atoi(bufferw);
    free(bufferw);
    if (test2 == -1)
        return NULL;

    ssize_t err = 0;
    int x = 0;
    char *buffer = NULL;
    size_t maxlen = 1024;
    char **buffy = malloc(sizeof(void*)*sizeh);
    while((err = getline(&buffer, &maxlen,fd)) != -1)
    {
        buffy[x] = malloc(sizeof(char)*sizew);
        for(int y = 0 ; buffer[y] != '\n'; y++)
        {
            buffy[x][y] = buffer[y];
        }
        x++;
    }
    *w = sizew;
    *h = sizeh;
    free(buffer);
    fclose(fd);
    return buffy;
}

struct blk *createblklist(char **map, int w, int h)
{
    struct blk *list = malloc(sizeof(struct blk)*w*h);
    for(int i = 0; i < h; i++)
    {
        for( int j = 0; j < w; j++)
        {
            list[i + j*w].mesh = malloc(sizeof(SDL_Rect));
            list[i + j*w].h = h;
            list[i + j*w].w = w;
            list[i + j*w].mesh->x = i;
            list[i + j*w].mesh->y = j;
            list[i + j*w].mesh->w = BLKW;
            list[i + j*w].mesh->h = BLKH;
            list[i + j*w].type = map[i][j];
        }
    }
    return list;
}

void destroymat(char **map, int w)
{
    for(int i = 0; i < w; i++)
    {
        free(map[i]);
    }
    free(map);
}

void destroyblk(struct blk *list)
{
    int w = list[0].w;
    int h = list[0].h;
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w ; j++)
        {
            free(list[i+j*w].mesh);
        }
    }
    free(list);
}

int main(void)
{
    int h = 0;
    int w = 0;
    char** map = readmap("test",&w,&h);
    printf("%c\n",map[0][0]);
    struct blk *list = createblklist(map, w, h);
    destroymat(map, w);
    if (list != NULL)
    {
        destroyblk(list);
        return 1;
    }
    return 0;
}
/*void makeblk(char type, int x, int y, SDL_Renderer *rend)
  {
  return;
  }*/
