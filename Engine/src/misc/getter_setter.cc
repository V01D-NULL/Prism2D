#include "getter_setter.h"

namespace PrismGlobal
{
    SDL_Surface *window_surface = nullptr;

    SDL_Surface *window_surface_get()
    {
        return window_surface;
    }

    SDL_Surface *window_surface_set(SDL_Surface *setter)
    {
        return (window_surface = setter);
    }
}