#include "../global.h"

int isblock(int x, int y , SDL_Rect *list, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (list[i]->x >= x && list[i]->w <= x)
            return 0;
        if (list[i]->y >= y && list[i]->h <= y)
            return 0;
        if (x <= list[i]->x + list[i]->w && list[i]->y - list[i]->h >= y)
            return 0;
    }
    return 1;
}
