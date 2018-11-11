#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct vec2
{
    int x;
    int y;
};

struct player
{
    SDL_Surface *sprite;
    SDL_Surface *sprite_mirror;
    SDL_Texture *texture;
    SDL_Texture *texture_mirror;
    SDL_Rect *rect;
    struct vec2 *speed;
    struct vec2 *pos;
    int life;
    int is_in_jump;
    int is_going_right;
};

int isHit(struct player *bad, int x, int y);
struct player *initennemy(int x, int y, SDL_Renderer *renderer);

struct player *initplayer(int x, int y, SDL_Renderer *renderer);
void destroy_player(struct player *p);
struct vec2 subroutine(struct player *bad, int *i, int rot, double delta);

#endif /* ! ENTITY_H*/
