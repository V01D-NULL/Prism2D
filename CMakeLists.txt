project (Prism2D)
cmake_minimum_required(VERSION 3.0)

# It is assumed that Prism2D is built inside of a build/ folder, hence the ../ prefix on the include paths
set(CMAKE_CXX_FLAGS "-fconcepts -I /usr/include/python3.9/ -I ../Engine/src/external/imgui -I /usr/include/SDL2/")
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

set(EXTERNAL_SRCS
    Engine/src/external/loguru/loguru.cpp
    Engine/src/external/imgui/backends/imgui_impl_sdl.cpp
    Engine/src/external/imgui/imgui_demo.cpp
    Engine/src/external/imgui/imgui_draw.cpp
    Engine/src/external/imgui/imgui_tables.cpp
    Engine/src/external/imgui/imgui_widgets.cpp
    Engine/src/external/imgui/imgui.cpp

    Engine/src/external/config-parser/config/parser.cc
    Engine/src/external/config-parser/config/item.cc
    Engine/src/external/config-parser/config/handler.cc
)

set(LD_LIBS
    -lSDL2
    -lpython3.9
    -lstdc++fs
    -lGL
    -lGLU
)

ADD_LIBRARY(PrismEngine
    SHARED
    Engine/SandboxApp/Sandbox.cc
    Engine/src/Engine.cc
    Engine/src/logging/log.cc
    Engine/src/renderer/primitives/shape.cc
    Engine/src/renderer/clear_color.cc
    Engine/src/renderer/textures/texture.cc
    Engine/src/UI/ui.cc
    Engine/src/threading/thread.cc
    Engine/src/language_bindings/python/python.cc
    Engine/src/misc/getter_setter.cc
    Engine/src/language_bindings/python/api/modules.cc
    Engine/src/OpenGL/ext/initGL.cc
    Engine/src/OS/os.cc
    ${EXTERNAL_SRCS}
)

target_link_libraries(PrismEngine ${LD_LIBS}) # PrismEngine holds the game engines core components  (audio, rendering, input, ui, etc)
ADD_EXECUTABLE(Prism2D main.cc) # This is the game engine executable itself which will just enter the library which in turns handles pretty much everything
target_link_libraries(Prism2D PrismEngine)