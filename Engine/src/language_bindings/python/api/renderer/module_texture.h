#pragma once

#include "../../../../renderer/textures/texture.h"

void cpp_render_texture(char *filename, int x, int y)
{
	using namespace renderer;
	Texture *_tex = new Texture(filename);
	_tex->draw_texture(x, y);
	delete _tex;
}