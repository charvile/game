#include "../include_entity/entity.h"
#include <stdlib.h>

#define HEIGHT 50
#define WIDTH 50

struct player *initplayer(int x, int y, SDL_Renderer *renderer)
{
    struct player *player = malloc(sizeof(struct player));
    player->sprite = IMG_Load("src/ressource/sprit/morty_right_1.png");
    player->sprite_mirror = IMG_Load("src/ressource/sprit/morty_left_1.png");
    player->texture = SDL_CreateTextureFromSurface(renderer, player->sprite);
    player->texture_mirror = SDL_CreateTextureFromSurface(renderer, player->sprite_mirror);

    player->rect = malloc(sizeof(SDL_Rect));
    player->rect->x = x;
    player->rect->y = y;
    player->rect->w = WIDTH;
    player->rect->h = HEIGHT;

    player->pos = malloc(sizeof(struct vec2));
    player->pos->x = x;
    player->pos->y = y;

    player->speed = malloc(sizeof(struct vec2));
    player->speed->x = 0;
    player->speed->y = 0;
    player->life = 100;
    return player;
}

void destroy_player(struct player *p)
{
    SDL_DestroyTexture(p->texture);
    SDL_FreeSurface(p->sprite);
    free(p->rect);
    free(p->speed);

    free(p);
}
