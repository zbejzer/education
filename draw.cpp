#include "draw.h"

#include "common.h"

SDL_Texture *loadTexture(const char filename[])
{
    SDL_Surface *surface;
    SDL_Texture *texture;

    SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Loading file %s", filename);

    surface = SDL_LoadBMP(filename);

    if (surface == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Error file surface %s: %s", filename, SDL_GetError());
        SDL_FreeSurface(surface);
        return NULL;
    }

    SDL_LogVerbose(SDL_LOG_CATEGORY_VIDEO, "Creating texture from surface %s", filename);

    texture = SDL_CreateTextureFromSurface(app.renderer, surface);

    if (texture == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Error creating texture from surface %s: %s", filename, SDL_GetError());
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        return NULL;
    }

    SDL_FreeSurface(surface);

    return texture;
}