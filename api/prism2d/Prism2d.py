import sys
import os
import prism2d.lib.loader as so
import ctypes

# Load the game engines shared library with which we can use functions exposed by the engine
engine_handle = so.Library.load_so("./libPrismEngine.so", __file__)

class Console:
    def __init__(self) -> None:
        pass

    def log(msg):
        msg = bytes(msg.encode())
        return engine_handle.Python_console_log(msg)

class Renderer:
    def __init__(self) -> None:
        pass

    # TODO: Add a clear function that takes an image as an argument to draw a background
    def clear(r, g, b):
        return engine_handle.Python_clear_color(
            ctypes.c_float(r),
            ctypes.c_float(g),
            ctypes.c_float(b),
        )

    def clear_alpha(r, g, b, a):
        return engine_handle.Python_clear_color_alpha(
            ctypes.c_float(r),
            ctypes.c_float(g),
            ctypes.c_float(b),
            ctypes.c_float(a)
        )

    def render_texture(filename, x, y):
        filename = bytes(filename.encode())
        return engine_handle.Python_render_texture(filename, x, y)
