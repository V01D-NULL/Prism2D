#include <Python.h>
#include "../../../logging/log.h"
#include "renderer/module_texture.h"
#include "logging/module_log.h"

/* Exportable python functions */
extern "C"
{
	void Python_console_log(char *msg)
	{
		return cpp_log(msg);
	}

	void Python_clear_color(int r, int g, int b)
	{
		return al_clear_to_color(al_map_rgb(r, g, b));
	}

	void Python_render_texture(char *filename, int x, int y)
	{
		return cpp_render_texture(filename, x, y);
	}
	
}