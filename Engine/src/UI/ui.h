#pragma once

#include "../external/imgui/backends/imgui_impl_sdl.h"
#include "../external/imgui/backends/imgui_impl_opengl3.h"

class UI
{
    public:
        UI();
        
    public:
        void Update(); //Called once per frame
        void Destroy();
        void Render();
};