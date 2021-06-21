#include "clear_color.h"

namespace renderer
{
    void ClearColor::clear(ALLEGRO_COLOR color)
    {
        al_clear_to_color(color);
    }

    void ClearColor::clear(int r, int g, int b)
    {
        al_clear_to_color(al_map_rgb(r, g, b));
    }
}