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
        void ViewportRender();

    private:
        /* Ignore this, we just need it becuase otherwise ImGui would throw an error saying CreateContext() has not been called */
        // ImGuiContext *_ = ImGui::CreateContext(); 
        // ImGuiIO &io = ImGui::GetIO(); //It's a hacky way of letting ImGuiIO be available in the whole class but it works

};