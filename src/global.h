#ifndef GLOBAL_H
#define GLOBAL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "vect/vect.h"

int isblock(int x, int y , SDL_Rect *list, int size);
double delta_time(uint64_t *last_update_time);

#endif /* ! GLOBAL_H */
