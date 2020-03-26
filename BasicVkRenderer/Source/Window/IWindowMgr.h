#pragma once
#ifndef IWINDOW_INCLUDED
#define IWINDOW_INCLUDED



class IWindow
{
public:
    enum SERVER_TYPE
    {
        HEADLESS    =   0x00000000,
        GLFW        =   0x00000001,
    };

protected:
};


#endif
