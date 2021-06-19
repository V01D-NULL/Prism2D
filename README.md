# Prism 2D

NOTE: 
I am just playing around with this for fun or when I get bored, it's nothing serious

Prism2D is a follow up on my first game engine attempt, called lovelyGameEngine.

That project was an absolute mess, now I have a decent plan of what I wish to use and how the engine is going to work

## Building
- Building the engine:
  
    1. `git submodule init && git submodule update`

    2. You need to open `Engine/src/external/imgui/backends/imgui_impl_allegro5.h/cpp` and change `#include "imgui.h"` to `#include "../imgui.h"`
```bash
mkdir build && cd build
cmake -G Ninja ../
ninja
cp ../api/prism2d . # Python api
cp ../api/example.py . # Python script to test the api
./Prism2D example
```

- Depends on (apt package manager names):
    - allegro5, cmake, ninja, pybind11-dev

- Depends on (submodule):
    - loguru (Logging)
    - imgui (GUI)
    - config-parser
    - pybind11 (API)# Prism2D
