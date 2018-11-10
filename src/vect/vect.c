#include <stdio.h>
#include "vect.h"

#define GRAV 9.8


void jump(struct player *plr, float dt)
{
    
    /* we assume the only force on the player is the gravitation*/
    struct vec2 pos = plr->pos;
    struct vec2 speed = plr->speed;
    
    /* NOTE: the horizontal speed does not change */
    speed.y -= g * dt;
    
    pos.x += speed.x * dt;
    pos.y += speed.y * dt;

    plr->pos.x = pos.x;
    plr->pos.y = pos.y;
    plr->speed.y = speed.y;

    return;
}


void horizontal_move(struct player *plr, float dt)
{
    /* horizontally, gravity has no impact on acceleration */
    struct vec2 pos = plr->pos;
    struct vec2 speed = plr->speed;
    struct vec2 xlr = plr->xlr;

    /* compute the new position, speed, acceleration */
    speed.x += xlr.x * dt;
    pos.x += speed.x * dt;

    plr->pos.x = pos.x;
    plr->speed.x = speed.x;

    return;
}
