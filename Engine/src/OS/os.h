#pragma once

#include <string>
#include <SDL2/SDL.h>

#define MAIN_MONITOR 0

namespace OS
{
    class FileSystem
    {
        public:
            FileSystem();
            ~FileSystem();

        public:
            std::string get_cwd();
            bool exists(const char *file);
            bool python_script_exists(const char *file);
            bool python_script_has_extension(const char *file);
            void registerExecutablePath(const char *argv0);

        public:
            std::string executable_path;
    };

    typedef struct
    {
        int width;
        int height;
        int refresh_rate;
    }
    display_t;
    class Display
    {
        public:
            display_t get_display_info(int display_indx); //Get display information
    };
}