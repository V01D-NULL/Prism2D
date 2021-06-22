#include <Python.h>
#include "../../../logging/log.h"
#include "renderer/module_texture.h"
#include "logging/module_log.h"
#include <GL/glew.h>

/* Exportable python functions */
extern "C"
{
	void Python_console_log(char *msg)
	{
		return cpp_log(msg);
	}

	void Python_clear_color(float r, float g, float b)
	{
		return glClearColor(r, g, b, 1);
	}

	void Python_clear_color_alpha(float r, float g, float b, float a)
	{
		return glClearColor(r, g, b, a);
	}

	void Python_render_texture(char *filename, int x, int y)
	{
		return cpp_render_texture(filename, x, y);
	}
}