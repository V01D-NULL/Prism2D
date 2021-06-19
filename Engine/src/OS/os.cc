#include "os.h"
#include <experimental/filesystem>
#include <cstring>
#include <allegro5/allegro5.h>

namespace OS
{
    /* Filesystem start */
    namespace fs = std::experimental::filesystem;

    FileSystem::FileSystem()
    {
        
    }

    void FileSystem::registerExecutablePath(const char *argv0)
    {
        std::string exe = this->get_cwd();
        exe.append(argv0);
        this->executable_path = exe;
    }

    std::string FileSystem::get_cwd()
    {
        return fs::current_path();
    }

    bool FileSystem::exists(const char *file)
    {
        return fs::exists(file);
    }

    bool FileSystem::python_script_exists(const char *file)
    {
        /* The python API expects filenames to not have an extension when being loaded in C++. Here we just append .py to check if the file `file`.py exists */
        std::string script_with_extension = file;
        script_with_extension.append(".py");
        return fs::exists(script_with_extension);
    }

    /* A file may not have a .py extension when loaded by the python api so we check for it */
    bool FileSystem::python_script_has_extension(const char *file)
    {
        if (std::strcmp(fs::path(file).extension().c_str(), ".py") == 0)
        {
            return true;
        }
        return false;
    }

    FileSystem::~FileSystem()
    {

    }
    /* Filesystem end */

    /* Display start */
    display_t Display::get_display_info()
    {
        display_t display_info;

        ALLEGRO_MONITOR_INFO info;
        al_get_monitor_info(0, &info); 
        
        display_info.width = info.x2 - info.x1;
        display_info.height = info.y2 - info.y1;

        return display_info;
    }
    /* Display end */
}   