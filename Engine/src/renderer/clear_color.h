#pragma once

#include <allegro5/allegro5.h>

namespace renderer
{
    class ClearColor
    {
    public:
        void clear(ALLEGRO_COLOR color);
        void clear(int r, int g, int b);
    };
}