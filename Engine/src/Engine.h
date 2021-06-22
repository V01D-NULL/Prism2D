#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "UI/ui.h"

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
            SDL_Window *window = nullptr;
            SDL_Event event;
    };
}
