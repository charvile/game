#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../entity/include_entity/entity.h"

void display_texture(const char *image_path, SDL_Rect *src_rect, SDL_Renderer *renderer);


void display_sprite(const char *image_path, SDL_Rect *src_rect, SDL_Renderer *renderer);

void display_sprite_from_texture(SDL_Texture *t, SDL_Rect *src_rect, SDL_Renderer *renderer);

void display_text(int x, int y, char *text, TTF_Font *font, SDL_Renderer *renderer);

SDL_Texture *create_texture_from_image(const char *image_path, SDL_Renderer *renderer);

void display_rect(int x, int y, int w, int h, SDL_Renderer *renderer);

void move_blocks(SDL_Rect *blocks, int offset, int size);

void move_block(SDL_Rect *block, int offset);

void move_player(struct player *p, int offset);

#endif /* ! DISPLAY_H */
