#include "entity/include_entity/entity.h"
#include "graphics/display.h"
#include "global.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define FONT_SIZE 25
#define HEIGHT 600
#define WIDTH 800

struct vec2
{
    int x;
    int y;
};

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG || IMG_INIT_PNG);
    TTF_Init();

    TTF_Font *font = TTF_OpenFont("src/ressource/font/Xanadu.ttf", FONT_SIZE);

    SDL_Window *window  = SDL_CreateWindow("<GAME NAME>", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED);


    uint64_t last_update = SDL_GetPerformanceCounter();

    /* Create player and ennemy*/
    struct player *p = initplayer(20, 450, renderer);
    struct player *bad = initennemy(50,450, renderer);

    SDL_Surface *rot = bad->sprite_mirror;
    SDL_Surface *normalsprite = bad->sprite;

    SDL_Texture *floor_texture = create_texture_from_image("src/ressource/texture/floor.png", renderer);


    SDL_Rect floor;
    floor.x = 0;
    floor.y = 500;
    floor.w = 800;
    floor.h = 500;

    //SDL_Rect Game_Over;
    //Game_Over.x = 0;
    //Game_Over.y = 0;
    //Game_Over.w = 800;
    //Game_Over.h = 600;

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
    bool playing = true;
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            if (playing && event.type == SDL_KEYDOWN)
            {
                int key =  event.key.keysym.sym;
                if (key == SDLK_LEFT)
                {
                    if (!isblock(p->rect->x - p->rect->w, p->rect->y, blocks, 4))
                    {
                        p->rect->x -= p->rect->w / 2;
                    }
                    if (isHit(bad, p->rect->x - p->rect->w, p->rect->y))
                    {
                        p->life -= 10;
                    }
                }
                else if (key == SDLK_RIGHT)
                {
                    if (!isblock(p->rect->x + p->rect->w, p->rect->y, blocks, 4))
                    {
                        p->rect->x += p->rect->w / 2;
                    }
                    if (isHit(bad, p->rect->x + p->rect->w, p->rect->y))
                    {
                        p->life -= 10;
                    }
                }
            }
        }
        /* Display welcome screen */
        if (!playing)
        {
            //display_texture("src/ressource/texture/Welcome.jpg", &Game_Over,
                //renderer);
            SDL_RenderPresent(renderer);
            continue;
        }
        /* Display game over screen */
        if (p->life <= 0)
        {
            //display_texture("src/ressource/texture/Gameover.png", &Game_Over,
                //renderer);

            //SDL_RenderPresent(renderer);
            //continue;
            break;
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
        {
            bad->sprite = rot;
        }

        /* Set background color */
        SDL_SetRenderDrawColor(renderer, 155, 155, 155, 255);
        SDL_RenderClear(renderer);

        /* Render floor */
        display_sprite_from_texture(floor_texture, &floor, renderer);
        //display_texture("src/ressource/texture/floor.png", &floor, renderer);

        /* Display obstacles */
        SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255);
        SDL_RenderFillRects(renderer, blocks, 4);

        /* Render spike*/
        display_sprite_from_texture(floor_texture, &hole, renderer);
        //display_sprite("src/ressource/texture/floor.png", &hole, renderer);

       /* Display player */
        display_sprite_from_texture(p->texture, p->rect, renderer);

        /* Display ennemy */
        display_sprite_from_texture(bad->texture, bad->rect, renderer);

        /* Display text */
        display_text(0, 0, "Player 1", font, renderer);

        /* Display screen */
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(25);

        //running = false;

    }

    /* Cleanup */
    SDL_DestroyTexture(floor_texture);
    destroy_player(p);
    destroy_player(bad);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
