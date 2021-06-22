#include "initGL.h"
#include "../../logging/log.h"

void GL::init()
{
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
}

void GL::init_glew()
{
    GLenum err;
    if ((err = glewInit()) != GLEW_OK)
    {
        Log().error("Could not initialize glew, Reason: %s", glewGetErrorString(err));
        Log().fatal("");
    }
}