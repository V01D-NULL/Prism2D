import sys
import os 
import lib.loader as so

# Load the game engines shared library with which we can use functions exposed by the engine
engine_handle = so.Library.load_so("./libPrismEngine.so", __file__)

class Console:
    def __init__(self) -> None:
        pass

    def log(msg):
        msg = bytes(msg.encode())
        return engine_handle.Python_console_log(msg)
    
class Native:
    def __init__(self) -> None:
        pass

    def msgbox_notify(title, heading, text):
        title = bytes(title.encode())
        heading = bytes(heading.encode())
        text = bytes(text.encode())
        return engine_handle.Python_messagebox_notify(title, heading, text)