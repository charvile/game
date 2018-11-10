#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct player
{
    SDL_Surface *sprite;
    SDL_Rect *rect;
    struct vec2 *speed;
    int life;
};

struct player *initplayer(int x, int y);

#endif /* ! ENTITY_H*/
