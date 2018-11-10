#include <stdio.h>
#include "vect.h"

#define GRAV 1

void jump(struct player *plr, float dt)
{

    /* we assume the only force on the player is the gravitation*/
    struct vec2 pos;
    pos.y = plr->rect->y;
    struct vec2 speed;
    speed.y = plr->speed->y;

    /* NOTE: the horizontal speed does not change */
    speed.y = speed.y + GRAV * (dt/dt);
    pos.y += speed.y * dt/dt; //(dt/1000);
    plr->rect->y = pos.y;
    plr->speed->y = speed.y;

    return;
}


void horizontal_move(struct player *plr, int direction, float dt)
{
    /* horizontally, gravity has no impact on acceleration */
    struct vec2 pos;
    pos.x = plr->rect->x;
    struct vec2 speed;
    speed.x = plr->speed->x * direction;
    /* compute the new position, speed, acceleration */
    //speed.x += xlr.x * (dt/1000);
    pos.x += speed.x * (dt/dt);

    plr->rect->x = pos.x;
    //plr->speed->x = speed.x;

    return;
}
