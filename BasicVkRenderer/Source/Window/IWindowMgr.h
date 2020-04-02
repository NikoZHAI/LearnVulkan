#pragma once
#ifndef IWINDOW_INCLUDED
#define IWINDOW_INCLUDED

enum E_WINDOW_SERVER_TYPE
{
    HEADLESS    =   0x00000000,
    GLFW        =   0x00000001,
};


class IWindow
{
public:


protected:
    E_WINDOW_SERVER_TYPE type = GLFW;
    
    void *
};


#endif
