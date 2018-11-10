#include "entity/include_entity/entity.h"
#include "global.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct vec2
{
    int x;
    int y;
};

int main(void)
{
    int height = 600;
    int width = 800;
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG|| IMG_INIT_PNG);

    SDL_Window *window  = SDL_CreateWindow("<GAME NAME>", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED);

    uint64_t last_update = SDL_GetPerformanceCounter();
    /* Create player*/
    struct player *p = initplayer(20, 450);
    struct player *bad = initennemy(50,450);

    SDL_Surface *rot = bad->sprite_mirror;
    SDL_Surface *normalsprite = bad->sprite;

    SDL_Rect floor;
    floor.x = 0;
    floor.y = 500;
    floor.w = 500;
    floor.h = 500;

    SDL_Rect Game_Over;
    Game_Over.x = 10;
    Game_Over.y = 10;
    Game_Over.w = 800;
    Game_Over.h = 600;

    SDL_Rect hole;
    hole.x = 400;
    hole.y = 490;
    hole.w = 50;
    hole.h = 10;

    SDL_Rect blocks[4];
    blocks[0].x = 500;
    blocks[0].y = 400;
    blocks[0].w = 100;
    blocks[0].h = 350;

    blocks[1].x = 165;
    blocks[1].y = 289;
    blocks[1].w = 100;
    blocks[1].h = 35;

    blocks[2].x = 365;
    blocks[2].y = 289;
    blocks[2].w = 100;
    blocks[2].h = 35;

    blocks[3].x = 65;
    blocks[3].y = 89;
    blocks[3].w = 100;
    blocks[3].h = 35;

    int subroutmaker = 0;
    int isrot = 0;

    bool running = true;
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            if (event.type == SDL_KEYDOWN)
            {
                int key =  event.key.keysym.sym;
                if (key == SDLK_LEFT)
                {
                    if (!isblock(p->rect->x - p->rect->w, p->rect->y, blocks, 4))
                    {
                        p->rect->x -= p->rect->w;
                    }
                    if (! isHit(bad, p->rect->x - p->rect->w, p->rect->y))
                    {
                        p->life -= 10;
                    }
                }
                else if (key == SDLK_RIGHT)
                {
                    if (!isblock(p->rect->x + p->rect->w, p->rect->y, blocks, 4))
                    {
                        p->rect->x += p->rect->w;
                    }
                    if (! isHit(bad, p->rect->x + p->rect->w, p->rect->y))
                    {
                        p->life -= 10;
                    }
                }
            }
        }
        if (p->life <= 0)
        {
            SDL_RenderClear(renderer);
            SDL_Surface *over = IMG_Load("src/ressource/texture/Gameover.png");
            SDL_Texture *textuover = SDL_CreateTextureFromSurface(renderer, over);
            SDL_RenderCopy(renderer, textuover, NULL, &Game_Over);

            SDL_RenderPresent(renderer);
            continue;
        }
        double delta = delta_time(&last_update);
        struct vec2 sub = subroutine(bad, &subroutmaker, isrot, delta);
        bad->rect->x = sub.y;
        isrot = sub.x;
        if (sub.x == 1)
        {
            bad->sprite = normalsprite;
        }
        else
            bad->sprite = rot;

        /* Set background color */
        SDL_SetRenderDrawColor(renderer, 155, 155, 155, 255);
        SDL_RenderClear(renderer);

        /* Render floor */
        //SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
        //SDL_RenderFillRect(renderer, &floor);
        SDL_Surface *flor = IMG_Load("src/ressource/texture/floor.png");
        SDL_Texture *textuflor = SDL_CreateTextureFromSurface(renderer, flor);
        SDL_RenderCopy(renderer, textuflor, NULL, &floor);

        /* Render obstacles */
        SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255);
        SDL_RenderFillRects(renderer, blocks, 4);

        /* Render spike*/
        SDL_Surface *holy = IMG_Load("src/ressource/texture/floor.png");

        SDL_Texture *textuhole = SDL_CreateTextureFromSurface(renderer, holy);
        //SDL_FreeSurface(holy);
        SDL_RenderCopy(renderer, textuhole, NULL, &hole);
        //SDL_RenderClear(renderer);
       /* Create first rectangle */
        SDL_Rect r1;
        r1.x = 0;
        r1.y = 0;
        r1.w = 50;
        r1.h = 50;

        SDL_Surface *surface = p->sprite;
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        //SDL_FreeSurface(surface);
        SDL_RenderCopy(renderer, texture, &r1, p->rect);

        /* create ennemy */
        SDL_Rect r2;
        r2.x = 0;
        r2.y = 0;
        r2.w = 50;
        r2.h = 50;
        SDL_Surface *surface2 = bad->sprite;
        SDL_Texture *texture2 = SDL_CreateTextureFromSurface(renderer, surface2);

        SDL_RenderCopy(renderer, texture2, &r2, bad->rect);

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(25);

    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
