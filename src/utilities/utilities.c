#include "../global.h"

unsigned int_width(int i)
{
    unsigned res = 0;

    if (!i)
    {
        return 1;
    }
    if (i < 1)
    {
        res = 1;
        i *= -1;
    }

    while (i > 0)
    {
        i /= 10;
        res += 1;
    }

    return res;
}
char *itoa(int x, char *res)
{
    int width = int_width(x);

    int cursor = width - 1;

    if (!x)
    {
        res = "0\0";
        return res;
    }

    while(x != 0)
    {
        res[cursor--] = x % 10 + '0';
        x /= 10;
    }

    res[width] = '\0';

    return res;
}


