#include "texture.h"
#include "../../logging/log.h"

namespace renderer
{
    Texture::Texture(char *file)
    {
        this->file = file;

        if (!al_init_image_addon())
        {
            Log().fatal("Failed to load the image addon, textures cannot be loaded.");
            return;
        }
        
        this->bmp = al_load_bitmap(file);        
        if (!this->bmp)
        {
            Log().warn("Could not load image `%s'\n", file);
            this->image_load_failed = true;
            return;
        }
    }

    void Texture::draw_texture(int x, int y)
    {
        if (this->image_load_failed)
        {
            Log().warn("You are trying to draw an image which is null. This is not allowed, please load the image before drawing it");
        }
        al_draw_bitmap(this->bmp, x, y, 0);
    }

    Texture::~Texture()
    {
        al_destroy_bitmap(this->bmp);
    }
}