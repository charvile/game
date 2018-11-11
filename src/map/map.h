#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "../global.h"

//char ** readmap(char *path, int *w, int *h);
SDL_Rect *createblklist(char *map_path, int *size, SDL_Rect *finish);

SDL_Rect *createbonuslist(int size);

SDL_Rect *create_spikes(SDL_Rect *block, int size, int *spike_num);
