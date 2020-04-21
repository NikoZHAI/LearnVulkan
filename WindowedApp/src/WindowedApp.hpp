#pragma once
#ifndef DC_WINDOWED_APP_INCLUDED
#define DC_WINDOWED_APP_INCLUDED


#include "Window.hpp"


namespace decor
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


} // namespace decor


#endif
