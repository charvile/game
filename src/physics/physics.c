#include "../global.h"

int isblock(int x, int y , SDL_Rect *list, int size)
{
    for (int i = 0; i < size; i++)
    {
        int w = list[i].w;
        int h = list[i].h;
        if (x >= list[i].x && x <= list[i].x + w)
        {
            if (y >= list[i].y && y <= list[i].y + h)
            {
                return 1;
            }
        }
    }
    return 0;
}

double delta_time(uint64_t *last_update_time)
{
    double frec = SDL_GetPerformanceFrequency();
    uint64_t last = *last_update_time;
    uint64_t now = SDL_GetPerformanceCounter();

    *(last_update_time) = now;
    return (now - last)* 1000 / frec;
}
