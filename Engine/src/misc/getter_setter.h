#pragma once

#include <SDL2/SDL.h>

/* Getter and setter for global variables */
namespace PrismGlobal
{
    extern SDL_Surface *window_surface_get();
    extern SDL_Surface *window_surface_set(SDL_Surface *setter);
}