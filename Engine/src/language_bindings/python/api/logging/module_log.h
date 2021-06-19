#pragma once

#include "../../../../logging/log.h"

void cpp_log(char *msg)
{
	Log().info("%s\n", msg);
}