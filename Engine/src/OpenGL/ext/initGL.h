#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>

/* Used by `SDL_GL_SetSwapInterval()` */
#define PRISM_GL_IMMEDIATE_UPDATE   0
#define PRISM_GL_VSYNC_UPDATE       1

class GL
{
    public:
        void init();
        void init_glew();
};