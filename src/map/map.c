#define _XOPEN_SOURCE 700
#include "map.h"
#include "../global.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define BLKW 50;
#define BLKH 50;

SDL_Rect *createblklist(char *map_path, int *size, SDL_Rect *finish)
{
    FILE *f = fopen(map_path, "r");

    if (!f)
    {
        puts("Cannot open map file");
    }

    char *buffer = NULL;
    size_t s = 10;
    int res = getline(&buffer, &s, f);

    if (res == -1)
    {
        return NULL;
    }
    *size = atoi(buffer) - 1;
    printf("Size is %d\n", *size);
    SDL_Rect *list = malloc(sizeof(*list) * *size);

    for (int i = 0; i < *size; i++)
    {
        getline(&buffer, &s, f);
        int x = atoi(buffer);
        getline(&buffer, &s, f);
        int y = atoi(buffer);
        getline(&buffer, &s, f);
        int w = atoi(buffer);
        getline(&buffer, &s, f);
        int h = atoi(buffer);
        getline(&buffer, &s, f);
        //int type = atoi(buffer);


        list[i].x = x;
        list[i].y = y;
        list[i].w = w;
        list[i].h = h;
    }

        getline(&buffer, &s, f);
        int x = atoi(buffer);
        getline(&buffer, &s, f);
        int y = atoi(buffer);
        getline(&buffer, &s, f);
        int w = atoi(buffer);
        getline(&buffer, &s, f);
        int h = atoi(buffer);
        getline(&buffer, &s, f);



        finish->x = x;
        finish->y = y;
        finish->w = w;
        finish->h = h;

        printf("Finish xy is %d;%d\n", x, y);
        printf("Finish hw is %d;%d\n", w, h);


    fclose(f);
    return list;
}

SDL_Rect *createbonuslist(int size)
{
    const float b_width = 25;
    const float b_height = 25;
    const float min_x = 0;
    const float max_x = 1500;
    const float min_y = 100;
    const float max_y = 450;
    int timer = SDL_GetTicks();
    srand(timer);

    SDL_Rect *list = malloc(sizeof(*list) * size);

    for (int i = 0; i < size; i++)
    {
        list[i].x = min_x + (float) rand()/(float) RAND_MAX * (max_x - min_x);
        list[i].y = min_y + (float) rand()/(float) RAND_MAX * (max_y - min_y);
        list[i].w = b_width;
        list[i].h = b_height;
    }
    return list;
}

SDL_Rect *create_spikes(SDL_Rect *blocks, int size, int *spike_num)
{
    const float b_width = 25;
    const float b_height = 25;
    int timer = SDL_GetTicks();
    srand(timer);

    SDL_Rect *list = malloc(sizeof(*list) * size);

    int counter = 0;
    for (int i = 0; i < size; i++)
    {
        int j = rand() % 2;
        if (j == 1)
        {
            list[counter].x = blocks[i].x;// + (float) rand()/(float) RAND_MAX * (list[counter].w);
            list[counter].y = blocks[i].y - b_height;
            list[counter].h = b_height;
            list[counter].w = b_width;
            counter++;
        }
    }
    *spike_num = counter;
    return list;
}
