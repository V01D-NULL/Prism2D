#include "Engine.h"
#include "logging/log.h"
#include <allegro5/allegro_native_dialog.h>
#include "language_bindings/python/python.h"
#include <algorithm>
#include "external/config-parser/config/handler.h"
#include "external/imgui/backends/imgui_impl_allegro5.h"
#include "OS/os.h"
#include "renderer/clear_color.h"
#include <thread>
#include "renderer/textures/texture.h"

namespace Prism
{
    Engine::Engine(int w, int h)
    {
        Log().info("Initializing allegro5");
        al_init();
        al_install_keyboard();
        al_install_mouse();
        al_init_primitives_addon();
        al_set_new_display_flags(ALLEGRO_RESIZABLE);
        Log().info("Initialized allegro5");

        /* Setup a display */
        OS::display_t disp = OS::Display().get_display_info();
        Log().info("Display size (%d,%d)\n", disp.width, disp.height);
        this->display = al_create_display(disp.width, disp.height);
        al_set_window_title(this->display, "⧋ Prism2D ⧋");

        /* Setup the framerate */
        this->fps = al_create_timer(1.0 / this->fps_val);

        /* Register events */
        this->queue = al_create_event_queue();
        this->RegisterEventSources();

        /* Init UI */
        UI _ui(this->display);
        (*this->ui) = _ui;

        Py_Initialize();
    }

    void Engine::RegisterEventSources()
    {
        al_register_event_source(this->queue, al_get_display_event_source(this->display));
        al_register_event_source(this->queue, al_get_keyboard_event_source());
        al_register_event_source(this->queue, al_get_timer_event_source(this->fps));
        al_register_event_source(this->queue, al_get_mouse_event_source());
    }

    void Engine::PollEvents()
    {
        ALLEGRO_EVENT ev;
        bool redraw = false;

        while (al_get_next_event(this->queue, &ev))
        {
            ImGui_ImplAllegro5_ProcessEvent(&ev);
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                this->shutdown();
                exit(0);
            }

            else if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
            {
                ImGui_ImplAllegro5_InvalidateDeviceObjects();
                al_acknowledge_resize(this->display);
                ImGui_ImplAllegro5_CreateDeviceObjects();
            }

            //This code runs once every frame
            else if (ev.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(this->queue))
            {
                this->Update();
                this->LateUpdate();
                this->Render();

                bool show_demo = true;
                ImGui_ImplAllegro5_NewFrame();
                ImGui::NewFrame();
                ImGui::ShowDemoWindow(&show_demo);
                ImGui::Render();

                ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());

                al_flip_display();
            }
        }
    }

    #pragma region Python
    //Call pythons Enter function
    void Engine::Enter()
    {

        for (int i = 0; i < this->python_scripts.size(); i++)
        {
            try
            {
                lang::Python().DefEnter(this->python_scripts.at(i).c_str());
            }
            catch (const char *e)
            {
                Log().error("A fatal exception occured in `lang::Python().DefEnter(%s)` -> %s", this->python_scripts.at(i).c_str(), e);
            }
            catch (std::exception e)
            {
                Log().error("An unknown exception occured in `lang::Python().DefEnter(%s)` -> %s", this->python_scripts.at(i).c_str(), e.what());
            }
        }
        al_start_timer(this->fps);
    }

    void Engine::Update()
    {
        /* Execute the update function in each python script registered */
        for (int i = 0; i < this->python_scripts.size(); i++)
        {
            try
            {
                lang::Python().DefUpdate(this->python_scripts.at(i).c_str());
            }
            catch (const char *e)
            {
                Log().error("A fatal exception occured in `lang::Python().DefUpdate(%s)` -> %s", this->python_scripts.at(i).c_str(), e);
            }
            catch (std::exception e)
            {
                Log().error("An unknown exception occured in `lang::Python().DefUpdate(%s)` -> %s", this->python_scripts.at(i).c_str(), e.what());
            }
        }
    }

    void Engine::LateUpdate()
    {
        /* Execute the update function in each python script registered */
        for (int i = 0; i < this->python_scripts.size(); i++)
        {
            try
            {
                lang::Python().DefLateUpdate(this->python_scripts.at(i).c_str());
            }
            catch (const char *e)
            {
                Log().error("A fatal exception occured in `lang::Python().DefLateUpdate(%s)` -> %s", this->python_scripts.at(i).c_str(), e);
            }
            catch (std::exception e)
            {
                Log().error("An unknown exception occured in `lang::Python().DefLateUpdate(%s)` -> %s", this->python_scripts.at(i).c_str(), e.what());
            }
        }
    }

    void Engine::registerNewScript(std::string name)
    {
        this->python_scripts.push_back(name);
    }

    void Engine::UnregisterScript(std::string name)
    {
        std::vector<std::string>::iterator result = std::find(this->python_scripts.begin(), this->python_scripts.end(), name);
        if (result != this->python_scripts.end())
        {
            this->python_scripts.erase(result);
        }
        else
        {
            Log().warn("Could not unregister script :: The script %s was not found", name.c_str());
        }
    }
    #pragma endregion
    
    void Engine::read_config_file(const char *file)
    {
        // Log().info("Loading ini file");
        // config::Handler handler;
        // handler.Load(file, {"scripts"});

        // config::Item *setting;
        // setting = handler.Get("scripts.path");   
    }

    void Engine::Render()
    {
        /* Execute the renderCycle function in each python script registered */
        for (int i = 0; i < this->python_scripts.size(); i++)
        {
            try
            {
                lang::Python().DefRenderCycle(this->python_scripts.at(i).c_str());
            }
            catch (const char *e)
            {
                Log().error("A fatal exception occured in `lang::Python().DefRenderCycle(%s)` -> %s", this->python_scripts.at(i).c_str(), e);
            }
            catch (std::exception e)
            {
                Log().error("An unknown exception occured in `lang::Python().DefRenderCycle(%s)` -> %s", this->python_scripts.at(i).c_str(), e.what());
            }
        }
    }

    void Engine::shutdown()
    {
        ImGui_ImplAllegro5_Shutdown();
        al_destroy_display(this->display);
        al_destroy_timer(this->fps);
        al_uninstall_keyboard();
        al_uninstall_mouse();
        Py_Finalize();
    }
}
