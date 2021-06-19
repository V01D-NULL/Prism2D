from ctypes import POINTER, c_char, c_char_p, c_wchar_p, cdll, create_string_buffer

class Library:
    def __init__(self) -> None:
        pass

    def load_so(path_to_shared_object_library, realpath):
        dir_path = os.path.dirname(os.path.realpath(realpath))  
        handle = cdll.LoadLibrary(path_to_shared_object_library)
        return handle