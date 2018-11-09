#include "../include_entity/entity.h"$

#define HEIGHT 50
#define WIDTH 50

struct player
{
    SDL_Surface *sprite;
    SDL_Rect *rect;
    struct vec2 *speed;
    int life;
    struct vec2 xlr;
    struct vec2 pos;
    struct vec2 vecwh;
};

struct player *initplayer(int x, int y)
{
    struct player *playerone = malloc(sizeof(struct player));
    player->sprite = SDL_Load("../../ressource/sprit/player.png");
    player->rect.x = x;
    player->rect.y = y;
    pos.x = x;
    pos.y = y;
    vecwh.x = HEIGHT;
    vecwh.y = WIDTH;
    player->speed.x = 0;
    player->speed.y = 0;
    player.life = 100;
    return player;
}

void moveapply(struct player *player, struct vec2 vec, SDL_Surface *src, SDL_Surface *dst)
{
    SDL_Rect rect = player->rect;
    player->rect.x = vec.x;
    player->rect.y = vec.y
    player->vec.x = vec.x;
    player->vec.y = vec.y;
    SDL_BlitSurface(src, NULL, dst, rect);
}

void writesprite(struct player *player, struct vec2 dst, struct vec2 pos, SDL_Surface *posx, SDL_Surface *finsh)
{
    SDL_Rect *src = player->rect;
    src.x = pos.x;
    src.y = pos.y;

    SDL_Rect resdst;
    resdst.x = dst.x;
    resdst.y = dst.y;

    SDL_BlitSurface(posx, src, finsh, &resdst);
}
