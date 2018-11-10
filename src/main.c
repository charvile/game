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
#include <SDL2/SDL_mixer.h>

#define FONT_SIZE 50
#define FONT_SIZE_S 25
#define HEIGHT 600
#define WIDTH 800

#define TIME_DELTA 100


#define INITIAL_VERTICAL_SPEED  -22
#define INITIAL_HORIZONTAL_SPEED 2



int main(void)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_JPG || IMG_INIT_PNG);
    TTF_Init();

    int flags = MIX_INIT_OGG | MIX_INIT_MP3;
    int initted = Mix_Init(flags);
    if (initted & flags != flags)
    {
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(2);
    }
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY*2, MIX_DEFAULT_FORMAT, 2, 1024);

    Mix_Music *backgroundSound = Mix_LoadMUS("src/ressource/sound/sound.mp3");
    Mix_Chunk *applause = Mix_LoadWAV("src/ressource/sound/applause_y.wav");
    Mix_Chunk *airplane = Mix_LoadWAV("src/ressource/sound/airplane_chime_x.wav");


    TTF_Font *font = TTF_OpenFont("src/ressource/font/xpressive-regular.ttf", FONT_SIZE);

    TTF_Font *font_s = TTF_OpenFont("src/ressource/font/xpressive-regular.ttf", FONT_SIZE_S);

    SDL_Window *window  = SDL_CreateWindow("Morty the Mortal", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED);


    uint64_t last_update = SDL_GetPerformanceCounter();

    /* Create player and ennemy*/
    struct player *p = initplayer(200, 450, renderer);
    struct player *bad = initennemy(50,450, renderer);
    p->speed->y = INITIAL_VERTICAL_SPEED;
    p->speed->x = INITIAL_HORIZONTAL_SPEED;

    /* Initialize timer */
    int TIME = 60;
    int int_timer = TIME;
    SDL_Surface *rot = bad->sprite_mirror;
    SDL_Surface *normalsprite = bad->sprite;

    SDL_Texture *floor_texture = create_texture_from_image("src/ressource/texture/floor.png", renderer);
    SDL_Texture *welcome_texture = create_texture_from_image("src/ressource/texture/Welcome_2.jpg", renderer);
    SDL_Texture *background_texture = create_texture_from_image("src/ressource/texture/background.png", renderer);
    SDL_Texture *finish_texture = create_texture_from_image("src/ressource/sprit/space-lander.png", renderer);
    SDL_Texture *victory_texture = create_texture_from_image("src/ressource/texture/victory.jpg", renderer);
    SDL_Texture *gameover_texture = create_texture_from_image("src/ressource/texture/Gameover.jpg", renderer);


    SDL_Rect floor = { 0, 500, 800, 500 };

    SDL_Rect full_screen = { 0, 0, 800, 600 };

    SDL_Rect hole = { 400, 490, 50, 10 };

    int num_blocks;
    SDL_Rect finish;
    SDL_Rect *blocks = createblklist("src/ressource/map/map1.map", &num_blocks, &finish);

    //display_sprite_from_texture(background_texture, &full_screen, renderer);


    int subroutmaker = 0;
    int isrot = 0;

    bool running = true;
    bool playing = false;
    bool win = false;
    SDL_Event event;

    Mix_PlayMusic(backgroundSound, -1);
    while (running)
    {
        if (p->is_in_jump)
        {
            //double dt = delta_time(&last_update);
            jump(p, 1);
            if (p->rect->y >= (floor.y - p->rect->h)
                || is_on_platform(p->rect, blocks, num_blocks))
            {
                p->is_in_jump = 0;
                p->speed->y = INITIAL_VERTICAL_SPEED;

            }
        }
        if (p->is_going_right)
        {
            horizontal_move(p, p->is_going_right, 1);
        }

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
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
            if (win)
            {
                continue;
            }
            if (playing && event.type == SDL_KEYUP)
            {
                p->is_going_right = 0;
            }

            if (playing && !win && event.type == SDL_KEYDOWN)
            {
                double player_delta =  delta_time(&last_update);
                int key =  event.key.keysym.sym;
                if (key == SDLK_UP)
                {
                    p->is_in_jump = 1;
                }
                if (key == SDLK_LEFT)
                {
                    p->is_going_right = -1;
                    int offset = p->rect->w * player_delta / -TIME_DELTA;
                    if (isblock(p->rect->x + p->rect->w, p->rect->y, &finish, 1))
                    {
                        win = true;
                    }
                    if (p->pos->x <= 50)
                    {

                    }
                    else if (p->rect->x < 300)
                    {
                        move_blocks(blocks, offset * 2, num_blocks);
                        move_player(bad, offset * 2);
                        //p->pos->x += offset * 2;

                        move_block(&hole, offset * 2);
                        move_block(&finish, offset * 2);
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
                            Mix_PlayChannel(-1, applause, 0);
                            p->life -= 10;
                        }

                    }
                }
                else if (playing && !win && key == SDLK_RIGHT)
                {
                    p->is_going_right = 1;
                    int offset = p->rect->w * player_delta / TIME_DELTA;

                    if (isblock(p->rect->x + p->rect->w, p->rect->y, &finish, 1))
                    {
                        win = true;
                    }
                    if (p->rect->x > 400)
                    {
                        puts("Move blocks to the right");
                        move_blocks(blocks, offset * 2, num_blocks);
                        move_player(bad, offset * 2);
                        move_block(&hole, offset * 2);
                        move_block(&finish, offset * 2);
                        //p->pos->x += offset * 2;
                    }
                    else
                    {
                        printf("Going right by %d\n", offset);
                        if (!isblock(p->rect->x + p->rect->w, p->rect->y, blocks, num_blocks))
                        {
                            p->rect->x += offset;
                            //p->pos->x += offset;
                        }
                        if (isHit(bad, p->rect->x + p->rect->w, p->rect->y))
                        {
                            Mix_PlayChannel(-1, applause, 0);
                            p->life -= 10;
                        }
                    }

                }
            }
        }

        if (int_timer)
        {
            Uint32 timer = SDL_GetTicks();
            int_timer = TIME - timer/1000;
        }

        /* Display welcome screen */
        if (!playing)
        {
            display_sprite_from_texture(welcome_texture, &full_screen, renderer);
            display_text(250, 100, "Morty the Mortal", font, renderer);
            SDL_SetRenderDrawColor(renderer, 50, 50, 150, 155);
            display_rect(300, 300, 200, 50, renderer);
            display_rect(300, 375, 200, 50, renderer);

            display_text(340, 310, "Play game", font_s, renderer);
            display_text(370, 385, "Quit", font_s, renderer);

            SDL_RenderPresent(renderer);

            SDL_Delay(200);
            continue;
        }
        /* Display game over screen */
        if (p->life <= 0 || !int_timer)
        {
            display_sprite_from_texture(gameover_texture, &full_screen, renderer);
            display_rect(300, 380, 200, 50, renderer);
            display_rect(300, 450, 200, 50, renderer);
            display_rect(300, 520, 200, 50, renderer);

            display_text(250, 200, "GAME OVER!", font, renderer);
            display_text(370, 390, "Restart", font_s, renderer);
            display_text(375, 455, "Menu", font_s, renderer);
            display_text(378, 525, "Quit", font_s, renderer);

            if (!int_timer)
            {
                display_text(250, 50, "Ran out of time!", font, renderer);
            }

            SDL_RenderPresent(renderer);
            SDL_Delay(200);
            continue;
        }

        /* Display victory screen */
        if (win)
        {
            display_sprite_from_texture(victory_texture, &full_screen, renderer);

            display_text(250, 100, "LEVEL COMPLETED", font, renderer);
            SDL_SetRenderDrawColor(renderer, 50, 50, 150, 155);
            display_rect(300, 300, 200, 50, renderer);
            display_rect(300, 375, 200, 50, renderer);

            display_text(340, 310, "Next level", font_s, renderer);
            display_text(370, 385, "Quit", font_s, renderer);
            SDL_RenderPresent(renderer);
            SDL_Delay(200);
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
        SDL_SetRenderDrawColor(renderer, 112, 115, 114, 255);
        SDL_RenderFillRects(renderer, blocks, num_blocks);

        /* Render spike*/
        display_sprite_from_texture(floor_texture, &hole, renderer);
        //display_sprite("src/ressource/texture/floor.png", &hole, renderer);

       /* Display player */
        display_sprite_from_texture(p->texture, p->rect, renderer);

        /* Display ennemy */
        display_sprite_from_texture(bad->texture, bad->rect, renderer);

        /* Display finish line */
        display_sprite_from_texture(finish_texture, &finish, renderer);

        /* Display life */

        char *life = itoa(p->life);
        char *hp = "HP : ";
        display_text(10, 0 , hp, font_s, renderer);
        display_text(50, 0, life, font_s, renderer);
        display_text(700, 0, "Player 1", font_s, renderer);

        /* Display timer */
        char *char_timer = "Time left : ";
        char *time = itoa(int_timer);

        display_text(10, 25 , char_timer, font_s, renderer);
        display_text(100, 25, time, font_s, renderer);

        /* Display screen */
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(25);

        //running = false;

    }

    /* Cleanup */
    free(blocks);
    SDL_DestroyTexture(floor_texture);
    SDL_DestroyTexture(welcome_texture);
    SDL_DestroyTexture(background_texture);
    SDL_DestroyTexture(gameover_texture);
    SDL_DestroyTexture(background_texture);
    destroy_player(p);
    destroy_player(bad);
    TTF_CloseFont(font);
    TTF_CloseFont(font_s);
    TTF_Quit();
    Mix_FreeMusic(backgroundSound);
    Mix_FreeChunk(applause);
    Mix_FreeChunk(airplane);
    Mix_CloseAudio;
    Mix_Quit();

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
