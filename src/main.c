#include "entity/include_entity/entity.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(void)
{
    int height = 600;
    int width = 800;
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG);

    SDL_Window *window  = SDL_CreateWindow("<GAME NAME>", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED);

    /* Create player*/
    struct player *p = initplayer(20, 450);

    SDL_Rect floor;
    floor.x = 0;
    floor.y = 500;
    floor.w = 800;
    floor.h = 100;

    SDL_Rect blocks[3];
    blocks[0].x = 65;
    blocks[0].y = 89;
    blocks[0].w = 100;
    blocks[0].h = 35;

    blocks[1].x = 165;
    blocks[1].y = 289;
    blocks[1].w = 100;
    blocks[1].h = 35;

    blocks[2].x = 365;
    blocks[2].y = 289;
    blocks[2].w = 100;
    blocks[2].h = 35;

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
                    p->rect->x -= p->rect->w / 2;
                }
                else if (key == SDLK_RIGHT)
                {
                    p->rect->x += p->rect->w / 2;
                }
            }
        }

        /* Set background color */
        SDL_SetRenderDrawColor(renderer, 155, 155, 155, 255);
        SDL_RenderClear(renderer);

        /* Render floor */
        SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
        SDL_RenderFillRect(renderer, &floor);

        /* Render obstacles */
        SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255);
        SDL_RenderFillRects(renderer, blocks, 3);

        //SDL_RenderClear(renderer);

        /* Create first rectangle */
        SDL_Rect r1;
        r1.x = 0;
        r1.y = 0;
        r1.w = 50;
        r1.h = 50;

        SDL_Surface *surface = p->sprite;
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_RenderCopy(renderer, texture, &r1, p->rect);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(25);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
