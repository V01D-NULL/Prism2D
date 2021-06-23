#include "Engine.h"

namespace Prism
{
    Engine::Engine()    
    {
        /* Init */
        Log().info("Initializing SDL2");
        if (SDL_Init(SDL_INIT_VIDEO))
        {
            Log().error("Could not Initialize SDL2, Reason: %s\n", SDL_GetError());
            Log().fatal(""); //Quit
        }
        
        /* Setup a display */
        this->display_info = OS::Display().get_display_info(MAIN_MONITOR);
        Log().info("Display size (%d,%d)\n", this->display_info.width, this->display_info.height);

        /* Window */
        PrismGlobal::window_set
        (
            SDL_CreateWindow
            (
                "⧋ Prism2D ⧋",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                this->display_info.width,
                this->display_info.height,
                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
            )
        );
        
        if (PrismGlobal::window_get() == nullptr)
        {
            Log().error("Could not create a window, Reason: %s\n", SDL_GetError());
            Log().fatal(""); //Quit
        }

        /* Surface */
        PrismGlobal::window_surface_set
        (
            SDL_GetWindowSurface
            (
                PrismGlobal::window_get()
            )
        );

        if (PrismGlobal::window_surface_get() == nullptr)
        {
            Log().error("Could not get the window surface, Reason: %s\n", SDL_GetError());
            Log().fatal(""); //Quit
        }

        /* OpenGL context + glew */
        GL().init();
        
        PrismGlobal::glContext_set
        (
            SDL_GL_CreateContext
            (
                PrismGlobal::window_get()
            )
        );

        if (PrismGlobal::glContext_get() == nullptr)
        {
            Log().error("Could not create an OpenGL context, Reason: %s\n", SDL_GetError());
            Log().fatal(""); //Quit
        }
        
        SDL_GL_MakeCurrent(PrismGlobal::window_get(), PrismGlobal::glContext_get());
        SDL_GL_SetSwapInterval(PRISM_GL_VSYNC_UPDATE);
        GL().init_glew();
        Log().info("Initialized SDL2");

        /* Prepare ImGui UI */
        UI *_ui = new UI();
        this->ui = _ui;

        GLrenderer::GL_FBO *_prism_gl_fbo = new GLrenderer::GL_FBO();
        this->prism_gl_fbo = _prism_gl_fbo;

        Py_Initialize();
    }

    void Engine::SetFPS(int fps)
    {
        if (fps < 30 || fps > 80)
        {
            Log().warn("FPS should not be greater than 80 or less than 30. Tried to set FPS = %d", fps);
        }
        this->fps_val = fps;
        this->required_delta_time = 1000 / this->fps_val;
    }

    void Engine::PollEvents()
    {
        int elapsedTimeSinceLastFrame = SDL_GetTicks();
        while (SDL_PollEvent(&(this->event)))
        {
            switch (this->event.type)
            {
                case SDL_QUIT:
                    this->shutdown();
                    exit(0);
                    break;
                
                default:
                    break;
            }
        }
        
        /* Ensure the functions below are limited to a constant framerate */
        if ((this->delta = (SDL_GetTicks() - elapsedTimeSinceLastFrame)) < this->required_delta_time)
        {
            SDL_Delay(this->required_delta_time - this->delta);
        }
        
        this->ui->Update();
        
        /* Write data to custom FBO */
        this->prism_gl_fbo->bindFBO();
        glClearColor(.4f, .4f, .6f, 1.0f); //This still renders to the main framebuffer object?
        // this->Update();
        // this->LateUpdate();
        // this->Render();
        
        /* Render ImGui to default FBO (window) */
        this->prism_gl_fbo->unbindFBO();

        ImGui::Begin("Game Scene");
        {
            // Using a Child allow to fill all the space of the window.
            // It also allows customization
            ImGui::BeginChild("Game");
            // Get the size of the child (i.e. the whole draw size of the windows).
            ImVec2 wsize = ImGui::GetWindowSize();
            // Because I use the texture from OpenGL, I need to invert the V from the UV.
            ImGui::Image((ImTextureID)this->prism_gl_fbo->getTex(), wsize, ImVec2(0, 1), ImVec2(1, 0));
            ImGui::EndChild();
        }
        ImGui::End();
        
        this->ui->Render();

        glViewport(0, 0, this->display_info.width, this->display_info.height);
        
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        this->ui->ViewportRender();

        SDL_GL_SwapWindow(PrismGlobal::window_get());
        // SDL_UpdateWindowSurface(PrismGlobal::window_get());
        // SDL_GL_SwapWindow(this->window);
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
        // al_start_timer(this->fps);
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
        /* Check if there is a .py extension and remove if it that is the case */
        if (OS::FileSystem().python_script_has_extension(name.c_str()))
        {
            size_t found = name.find(".py");
            name.erase(found);
        }
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


#pragma endregion

    void Engine::read_config_file(const char *file)
    {
        // Log().info("Loading ini file");
        // config::Handler handler;
        // handler.Load(file, {"scripts"});

        // config::Item *setting;
        // setting = handler.Get("scripts.path");
    }

    void Engine::shutdown()
    {
        this->prism_gl_fbo->Destroy();
        this->ui->Destroy();
        SDL_GL_DeleteContext(PrismGlobal::glContext_get());
        SDL_DestroyWindow(PrismGlobal::window_get());
        SDL_Quit();
        Py_Finalize();
    }
}
