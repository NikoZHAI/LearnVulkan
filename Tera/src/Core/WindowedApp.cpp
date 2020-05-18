#include "WindowedApp.hpp"
#include "Logger.hpp"
#include "TeraSystem.hpp"


#include <cstdlib>


namespace tera
{


WindowedApp::WindowedApp(/* args */)
    : Window()
{
}

WindowedApp::~WindowedApp()
{
}


int WindowedApp::run()
{
    int winpos[2]{50, 50};
    int winsize[2]{800, 600};

    if (!Window::open(winpos[0], winpos[1], winsize[0], winsize[1], "Test Window", false))
    {
        Logger::error("Could not create window...");
        return EXIT_FAILURE;
    }

    bool run_ = true;

    if (run_)
    {
        bool wasClosed = false;
        while (pollEvents())
        {
            while(!isOpen())
            {
                TeraSystem::waitEvents();
                wasClosed = true;
            }
            if (wasClosed)
            {
                continue;
            }
            /* code */
        }
    }

    return EXIT_SUCCESS;
}


} // namespace tera
