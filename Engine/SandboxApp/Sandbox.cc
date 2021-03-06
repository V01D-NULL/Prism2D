#include "Sandbox.hpp"
#include <string>

void SandboxApp::Start(int argc, char **argv)
{
    Log().info("Prism version: %s", VERSION);
    
    //Save the executable path
    OS::FileSystem fs;
    fs.registerExecutablePath(argv[0]);
    
    //Init core
    Prism::Engine engine;
    // engine.read_config_file(argv[1]);
    for (int i = 1; i < argc; i++) //Register scripts
    {
        Log().info(argv[i]);
        engine.registerNewScript(argv[i]);
    }

    engine.Enter();
    while (should_run)
    {
        engine.PollEvents();
    }

    //Init UI

    //Init graphics (texture loading, etc)

    //Init input
}