#include "display.h"

void display_texture(const char *image_path, SDL_Rect *src_rect, SDL_Renderer *renderer)
{
            SDL_RenderClear(renderer);
            SDL_Surface *s = IMG_Load(image_path);
            SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, s);
            SDL_RenderCopy(renderer, t, NULL, src_rect);
}

void display_sprite(const char *image_path, SDL_Rect *src_rect, SDL_Renderer *renderer)
{
            SDL_Surface *s = IMG_Load(image_path);
            SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, s);
            SDL_RenderCopy(renderer, t, NULL, src_rect);
}

void display_sprite_from_texture(SDL_Texture *t, SDL_Rect *src_rect, SDL_Renderer *renderer)
{
            SDL_RenderCopy(renderer, t, NULL, src_rect);
}

SDL_Texture *create_texture_from_image(const char *image_path, SDL_Renderer *renderer)
{
            SDL_Surface *s = IMG_Load(image_path);
            SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, s);
            SDL_FreeSurface(s);
            return t;

}

void display_text(int x, int y, char *text, TTF_Font *font, SDL_Renderer *renderer)
{
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, text, white);
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    int text_height;
    int text_width;
    SDL_QueryTexture(text_texture, NULL, NULL, &text_width, &text_height);
    SDL_Rect text_rect = { x, y, text_width, text_height };

    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

}
