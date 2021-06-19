#include "ui.h"

UI::UI(ALLEGRO_DISPLAY *display)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplAllegro5_Init(display);
}

