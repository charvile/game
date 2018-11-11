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

int is_on_platform(SDL_Rect *player, SDL_Rect *blocks, int size)
{
    if (player->y >= 450)
    {
        return 1;
    }
    int player_x = player->x + player->w / 2;
    int player_y = player->y + player->h;
    for (int i = 1; i < size; i++)
    {
        int x = blocks[i].x;
        int y = blocks[i].y;
        int w = blocks[i].w;
        //int h = blocks[i].h;

        if (player_x >= x && player_x <= x + w && player_y >= y && player_y <= y + 20)
        {
            return 1;
        }
    }
    return 0;
}

int found_bonus(int x, int y, SDL_Rect *list, int size)
{
    for (int i = 0; i < size; i++)
    {
        int w = list[i].w;
        int h = list[i].h;
        if (x >= list[i].x && x <= list[i].x + w)
        {
            if (y >= list[i].y - 15 && y <= list[i].y + h + 15)
            {
                list[i].w = 0;
                list[i].h = 0;
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
