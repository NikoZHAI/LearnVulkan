#pragma once
#ifndef TERA_WINDOWED_APP_VK
#define TERA_WINDOWED_APP_VK


#include "WindowedApp.hpp"


namespace tera
{


/**
 * @brief class tera::WindowedAppVk
 * 
 * WindowedAppVk derives from tera::WindowedApp, and is essentially based on the 
 * 
 */
class WindowedAppVk : public WindowedApp
{
public:
    WindowedAppVk(bool doSwap = true)
    { m_doSwap = doSwap; }


public:
    bool            m_swapVsync;
    

};


} // namespace tera


#endif
