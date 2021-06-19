/*
    PrismEngine entry point.
    Calls Sandbox/App.Start(), the rest is handled by the engine code
*/

#ifndef __GNUC__
    #error "Expected a GNU c++ compiler"
#endif

#include "Engine/SandboxApp/Sandbox.hpp"

int main(int argc, char **argv)
{
    loguru::init(argc, argv); //Catch segfaults, termination signals, etc
    SandboxApp().Start(argc, argv);
    
	return 0;
}