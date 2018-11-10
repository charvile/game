#include "../include_entity/entity.h"
#include <stdlib.h>

#define HEIGHT 50
#define WIDTH 50

struct vec2
{
    int x;
    int y;
};

struct player *initennemy(int x, int y)
{
    struct player *en = malloc(sizeof(struct player));
    en->sprite = IMG_Load("src/ressource/sprit/ennemy_mirror.png");
    en->sprite_mirror = IMG_Load("src/ressource/sprit/ennemy_mirror.png");

    en->rect = malloc(sizeof(SDL_Rect));
    en->rect->x = x;
    en->rect->y = y;
    en->rect->w = WIDTH;
    en->rect->h = HEIGHT;

    en->speed = malloc(sizeof(struct vec2));
    en->speed->x = 0;
    en->speed->y = 0;
    en->life = 100;
    return en;
}

struct vec2 subroutine(struct player *bad, int *i, int rot, double delta)
{
    struct vec2 sub;
    sub.x = rot;
    sub.y = bad->rect->x;
    int move = bad->rect->w*(delta/1000);
    if (rot == 1)
    {
        if (*i == 30)
        {
            (*i)--;
            sub.x = 0;
            sub.y = bad->rect->x  - move;
            return sub;
        }
        else
        {
            (*i)++;
            sub.x = 1;
            sub.y = bad->rect->x +  move;
            return sub;
        }
    }
    else
    {
        if (*i == 0)
        {
            (*i)++;
            sub.x = 1;
            sub.y = bad->rect->x +  move;
            return sub;
        }
        else
        {
            (*i)--;
            sub.x = 0;
            sub.y = bad->rect->x - move;
        }
    }
    return sub;
}

int isHit(struct player *bad, int x, int y)
{
    if (x >= bad->rect->x &&
            x <= bad->rect->x + HEIGHT)
    {
        if (y >= bad->rect->y
                && y <= bad->rect->y + HEIGHT)
        {
            return 1;
        }
    }
    return 0;
}
