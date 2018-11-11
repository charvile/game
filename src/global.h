#ifndef GLOBAL_H
#define GLOBAL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "vect/vect.h"

int isblock(int x, int y , SDL_Rect *list, int size);
double delta_time(uint64_t *last_update_time);
int is_on_platform(SDL_Rect *player, SDL_Rect *blocks, int size);
int found_bonus(int x, int y, SDL_Rect *list, int size);
unsigned int_width(int i);

char *itoa(int x, char *res);

#endif /* ! GLOBAL_H */
