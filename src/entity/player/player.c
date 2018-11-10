#include "../include_entity/entity.h"
#include <stdlib.h>

#define HEIGHT 50
#define WIDTH 50

struct vec2
{
    int x;
    int y;
};

struct player *initplayer(int x, int y)
{
    struct player *player = malloc(sizeof(struct player));
    player->sprite = IMG_Load("src/ressource/sprit/player.png");

    player->rect = malloc(sizeof(SDL_Rect));
    player->rect->x = x;
    player->rect->y = y;
    player->rect->w = WIDTH;
    player->rect->h = HEIGHT;

    player->speed = malloc(sizeof(struct vec2));
    player->speed->x = 0;
    player->speed->y = 0;
    player->life = 100;
    return player;
}

void moveapply(struct player *player, struct vec2 vec, SDL_Surface *src, SDL_Surface *dst)
{
    SDL_Rect *rect = player->rect;
    player->rect->x = vec.x;
    player->rect->y = vec.y;
    SDL_BlitSurface(src, NULL, dst, rect);
}

void writesprite(struct player *player, struct vec2 dst, struct vec2 pos, SDL_Surface *posx, SDL_Surface *finsh)
{
    SDL_Rect *src = player->rect;
    src->x = pos.x;
    src->y = pos.y;

    SDL_Rect resdst;
    resdst.x = dst.x;
    resdst.y = dst.y;

    SDL_BlitSurface(posx, src, finsh, &resdst);
}
