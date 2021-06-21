#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

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
            ALLEGRO_BITMAP *bmp;
            bool image_load_failed = false;
    };
}