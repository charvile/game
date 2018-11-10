#include "entity/include_entity/entity.h"
#include "graphics/display.h"
#include "global.h"
#include "map/map.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define FONT_SIZE 50
#define FONT_SIZE_S 25
#define HEIGHT 600
#define WIDTH 800

#define TIME_DELTA 100


#define INITIAL_VERTICAL_SPEED  800

unsigned int_width(int i)
{
    unsigned res = 0;
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
char *itoa(int x)
{
    char *res = malloc(10);
    int width = int_width(x);

    int cursor = width - 1;

    while(x > 0)
    {
        res[cursor--] = x % 10 + '0';
        x /= 10;
    }

    res[width] = '\0';

    return res;
}

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG || IMG_INIT_PNG);
    TTF_Init();

    TTF_Font *font = TTF_OpenFont("src/ressource/font/xpressive-regular.ttf", FONT_SIZE);

    TTF_Font *font_s = TTF_OpenFont("src/ressource/font/xpressive-regular.ttf", FONT_SIZE_S);

    SDL_Window *window  = SDL_CreateWindow("<RUN WITH THE BEAT>", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED);


    uint64_t last_update = SDL_GetPerformanceCounter();

    /* Create player and ennemy*/
    struct player *p = initplayer(20, 450, renderer);
    struct player *bad = initennemy(50,450, renderer);
    p->speed->y = -15;

    SDL_Surface *rot = bad->sprite_mirror;
    SDL_Surface *normalsprite = bad->sprite;

    SDL_Texture *floor_texture = create_texture_from_image("src/ressource/texture/floor.png", renderer);
    SDL_Texture *welcome_texture = create_texture_from_image("src/ressource/texture/sound-wave.jpg", renderer);
    SDL_Texture *background_texture = create_texture_from_image("src/ressource/texture/background.png", renderer);

    SDL_Rect floor;
    floor.x = 0;
    floor.y = 500;
    floor.w = 800;
    floor.h = 500;

    SDL_Rect full_screen;
    full_screen.x = 0;
    full_screen.y = 0;
    full_screen.w = 800;
    full_screen.h = 600;

    SDL_Rect hole;
    hole.x = 400;
    hole.y = 490;
    hole.w = 50;
    hole.h = 10;

    int num_blocks;
    SDL_Rect *blocks = createblklist("src/ressource/map/map1.map", &num_blocks);

    //display_sprite_from_texture(background_texture, &full_screen, renderer);


    int subroutmaker = 0;
    int isrot = 0;

    bool running = true;
    bool playing = false;
    SDL_Event event;
    while (running)
    {
        if (p->is_in_jump)
        {
            //double dt = delta_time(&last_update);
            jump(p, 1);
            if (p->rect->y >= (floor.y - p->rect->h))
            {
                p->is_in_jump = 0;
                p->speed->y = -15;

            }
        }
        while (SDL_PollEvent(&event))
        {
            if (!playing)
            {
                if (event.type == SDL_MOUSEBUTTONUP)
                {
                    int x = event.button.x;
                    int y = event.button.y;

                    if (x >= 300 && x <= 500 && y >= 300 && y <= 350)
                    {
                        playing = true;
                        continue;
                    }
                    if (x >= 300 && x <= 500 && y >= 375 && y <= 425)
                    {
                        running = false;
                        break;
                    }
                }
            }
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            if (playing && event.type == SDL_KEYDOWN)
            {
                double player_delta =  delta_time(&last_update);
                int key =  event.key.keysym.sym;
                if (key == SDLK_UP)
                {
                    p->is_in_jump = 1;
                }
                if (key == SDLK_LEFT)
                {
                    int offset = p->rect->w * player_delta / -TIME_DELTA;
                    if (p->pos->x <= 50)
                    {

                    }
                    else if (p->rect->x < 50)
                    {
                        move_blocks(blocks, offset, num_blocks);
                        move_player(bad, offset);
                        p->pos->x += offset;

                        move_block(&hole, offset);
                    }
                    else
                    {
                        if (!isblock(p->rect->x - p->rect->w, p->rect->y, blocks, num_blocks))
                        {
                            p->rect->x += offset;
                            p->pos->x += offset;
                        }
                        if (isHit(bad, p->rect->x - p->rect->w, p->rect->y))
                        {
                            p->life -= 1;
                        }

                    }
                }
                else if (key == SDLK_RIGHT)
                {
                    int offset = p->rect->w * player_delta / TIME_DELTA;
                    if (p->rect->x > 700)
                    {
                        move_blocks(blocks, offset, num_blocks);
                        move_player(bad, offset);
                        move_block(&hole, offset);
                        p->pos->x += offset;
                    }
                    else
                    {
                        printf("Going right by %d\n", offset);
                        if (!isblock(p->rect->x + p->rect->w, p->rect->y, blocks, num_blocks))
                        {
                            p->rect->x += offset;
                            p->pos->x += offset;
                        }
                        if (isHit(bad, p->rect->x + p->rect->w, p->rect->y))
                        {
                            p->life -= 1;
                        }
                    }

                }
            }
        }

        /* Display welcome screen */
        if (!playing)
        {
            display_sprite_from_texture(welcome_texture, &full_screen, renderer);
            display_text(250, 100, "RUN WITH THE BEAT", font, renderer);
            SDL_SetRenderDrawColor(renderer, 50, 50, 150, 155);
            display_rect(300, 300, 200, 50, renderer);
            display_rect(300, 375, 200, 50, renderer);

            display_text(340, 310, "Play game", font_s, renderer);
            display_text(370, 385, "Quit", font_s, renderer);

            SDL_RenderPresent(renderer);

            continue;
        }
        /* Display game over screen */
        if (p->life <= 0)
        {
            display_texture("src/ressource/texture/Gameover.png", &full_screen,
                renderer);

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
        {
            bad->sprite = rot;
        }

        /* Set background color */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        /* Render floor */
        display_sprite_from_texture(floor_texture, &floor, renderer);
        //display_texture("src/ressource/texture/floor.png", &floor, renderer);

        /* Display obstacles */
        SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255);
        SDL_RenderFillRects(renderer, blocks, num_blocks);

        /* Render spike*/
        display_sprite_from_texture(floor_texture, &hole, renderer);
        //display_sprite("src/ressource/texture/floor.png", &hole, renderer);

       /* Display player */
        display_sprite_from_texture(p->texture, p->rect, renderer);

        /* Display ennemy */
        display_sprite_from_texture(bad->texture, bad->rect, renderer);

        /* Display life */

        char *life = itoa(p->life);
        char *hp = "HP : ";
        display_text(10, 0 , hp, font_s, renderer);
        display_text(50, 0, life, font_s, renderer);
        display_text(700, 0, "Player 1", font_s, renderer);
        /* Display screen */
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(25);

        //running = false;

    }

    /* Cleanup */
    SDL_DestroyTexture(floor_texture);
    SDL_DestroyTexture(welcome_texture);
    SDL_DestroyTexture(background_texture);
    destroy_player(p);
    destroy_player(bad);
    TTF_CloseFont(font);
    TTF_CloseFont(font_s);
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
