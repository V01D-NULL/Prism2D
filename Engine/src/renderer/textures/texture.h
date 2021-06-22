#pragma once

#include <SDL2/SDL.h>

namespace renderer
{
    class Texture
    {
        public:
            Texture(char *file);
            ~Texture();
            
        public:
            void draw_texture(int x, int y);

        private:
            char *file;
            SDL_Surface *bmp = nullptr;
            bool image_load_failed = false;
    };
}