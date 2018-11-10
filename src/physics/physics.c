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
