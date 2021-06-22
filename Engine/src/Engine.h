#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "UI/ui.h"
#include "logging/log.h"
#include "language_bindings/python/python.h"
#include <algorithm>
#include "external/config-parser/config/handler.h"
#include "external/imgui/backends/imgui_impl_sdl.h"
#include "OS/os.h"
#include "renderer/clear_color.h"
#include <thread>
#include "renderer/textures/texture.h"
#include "OpenGL/ext/initGL.h"
#include "misc/getter_setter.h"

namespace Prism
{
    class Engine
    {
        public:
            Engine();

        public:
            void read_config_file(const char *file);
            void registerNewScript(std::string name);
            void UnregisterScript(std::string name);
            void SetFPS(int fps);
            void PollEvents();
            void LateUpdate();
            void Update();
            void Render();
            void Enter();
            
        private:
            void RegisterEventSources();
            void shutdown();

        private:
            std::vector<std::string> python_scripts;
            std::string script_path;
            int fps_val = 60;
            int required_delta_time = 1000 / fps_val;
            int delta; //Used for fps control
            UI *ui;

        private:
            OS::display_t display_info;
            SDL_Event event;
    };
}