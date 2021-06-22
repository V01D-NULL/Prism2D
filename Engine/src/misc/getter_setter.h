#pragma once

#include <SDL2/SDL.h>

/* Getter and setter for global variables */
namespace PrismGlobal
{
    extern SDL_Surface *window_surface_get();
    extern SDL_Surface *window_surface_set(SDL_Surface *setter);
    
    extern SDL_GLContext glContext_get();
    extern SDL_GLContext glContext_set(SDL_GLContext setter);
    
    extern SDL_Window *window_get();
    extern SDL_Window *window_set(SDL_Window *setter);
}