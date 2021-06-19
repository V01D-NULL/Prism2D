#pragma once

#include "../../../../renderer/clear_color.h"

void cpp_clear_color(int r, int g, int b)
{
	ClearColor().clear(r, g, b);
}