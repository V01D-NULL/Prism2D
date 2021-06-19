#pragma once

#include <python3.9/Python.h>

namespace lang
{
    class Python
    {
        public:
            Python();
            ~Python();

        public:
            //Execute a string of python code
            void ExecString(const char *code);

            //Core API functions that must be written in the python file (even if they just `pass`).
            //Functions are listed are in the order which they are called
            void DefEnter(const char *file);        //Before first frame
            void DefUpdate(const char *file);       //Runs once every frame (Update positions in here)
            void DefLateUpdate(const char *file);   //Runs once every frame (Move game objects that need to wait for other game objects to move first like a camera)
            void DefRenderCycle(const char *file);  //Runs once every frame (Render the updated sprites here)
    };
}