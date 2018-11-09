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
        }

        /* Set background color */
        SDL_SetRenderDrawColor(renderer, 155, 155, 155, 255);
        SDL_RenderClear(renderer);

        /* Create first rectangle */
        SDL_Rect r1;
        r1.x = 50;
        r1.y = 50;
        r1.w = 50;
        r1.h = 50;

        /* Set color for next render*/
        //SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255);

        /* Render a first rectangle */

        //SDL_RenderFillRect(renderer, &r1);
        /*Render a second rectangle */

        //SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255);
        //r1.x = 100;
        //r1.y = 100;
        //SDL_RenderFillRect(renderer, &r1);
        //SDL_RenderClear(renderer);
        //SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0);

        /* Display a sprit */
        SDL_Surface *surface = IMG_Load("src/ressource/sprit/player.png");
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_Rect character;
        character.x = 50;
        character.y = 50;
        character.w = 50;
        character.h = 50;

        SDL_RenderCopy(renderer, texture, &r1, &character);
        //SDL_RenderFillRect(renderer, &character);

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
