#include "getter_setter.h"

namespace PrismGlobal
{
#pragma region window surface
    SDL_Surface *window_surface = nullptr;
    SDL_Surface *window_surface_get()
    {
        return window_surface;
    }

    SDL_Surface *window_surface_set(SDL_Surface *setter)
    {
        return (window_surface = setter);
    }
#pragma endregion

#pragma region gl context
    SDL_GLContext glContext = nullptr;
    SDL_GLContext glContext_get()
    {
        return glContext;
    }

    SDL_GLContext glContext_set(SDL_GLContext setter)
    {
        return (glContext = setter);
    }
#pragma endregion

#pragma region window
    SDL_Window *window = nullptr;
    SDL_Window *window_get()
    {
        return window;
    }
    SDL_Window *window_set(SDL_Window *setter)
    {
        return (window = setter);
    }
#pragma endregion
}