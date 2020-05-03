#pragma once
#ifndef TERA_WINDOWED_APP_INCLUDED
#define TERA_WINDOWED_APP_INCLUDED


#include "Window.hpp"


namespace tera
{


class WindowedApp : public Window
{
protected:
    /* data */
public:
    WindowedApp(/* args */);
    ~WindowedApp();

    int run();
};


} // namespace tera


#endif
