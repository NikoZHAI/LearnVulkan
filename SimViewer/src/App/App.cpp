#include "App.hpp"


namespace sv
{
    

App::App(/* args */)
    : WindowedApp()
{}


App::~App()
{}


int App::run(int argc, char const *argv[])
{
    return WindowedApp::run();
}


} // namespace sv
