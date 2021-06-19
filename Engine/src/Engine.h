#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include <vector>
#include "UI/ui.h"

namespace Prism
{
    class Engine
    {
        public:
            Engine(int w=1280, int h=720);

        public:
            void read_config_file(const char *file);
            void registerNewScript(std::string name);
            void UnregisterScript(std::string name);
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
            double fps_val = 60.0;
            UI *ui;

        private:
            ALLEGRO_DISPLAY *display;
            ALLEGRO_EVENT_QUEUE *queue;
            ALLEGRO_TIMER *fps;
    };
}
