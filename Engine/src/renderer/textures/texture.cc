#include "texture.h"
#include "../../logging/log.h"
#include "../../misc/getter_setter.h"

namespace renderer
{
    Texture::Texture(char *file)
    {
        // this->file = file;

        this->bmp = SDL_LoadBMP(file);
        if (this->bmp == nullptr)
        {
            Log().error("Could not load image, reason: %s", SDL_GetError());
            this->image_load_failed = true;
            return;
        }
        this->image_load_failed = false;
    }

    void Texture::draw_texture(int x, int y)
    {
        if (this->image_load_failed)
        {
            Log().warn("You are trying to draw an image which is null. This is not allowed, please load the image before drawing it");
        }
        
        SDL_BlitSurface(this->bmp, NULL, PrismGlobal::window_surface_get(), NULL);
    }

    Texture::~Texture()
    {
        
    }
}