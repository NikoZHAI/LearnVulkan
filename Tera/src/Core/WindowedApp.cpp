#include "WindowedApp.hpp"
#include "Logger.hpp"
#include "TeraSystem.hpp"


#include <Poco/Format.h>
#include <cstdlib>
#include <cstring>


namespace tera
{


WindowedApp::WindowedApp()
    : Window()
{
}

WindowedApp::~WindowedApp()
{
}



/**
 * @brief set Window VSync mode
 * 
 * @param sync set true for VSync on, false for off
 */
void WindowedApp::setVsync(bool state)
{
    if (m_internal) {
        swapVsync(state);
        Logger::info( Poco::format("Vsync: %b", state) );
    }
    m_config.vsyncState                 = state;
    m_vsync                             = state;
}



/**
 * @brief function called in Window::onCursorPosCb()
 * 
 * @param x x coordinate of the current cursor position
 * @param y y coordinate of the current cursor position
 */
void WindowedApp::onMouseMotion(int x, int y)
{
    if (!m_windowState.m_mouseButtonFlags && mousePos(x, y)) {
        return;
    }

    m_windowState.m_mouseCurrent[0]     = x;
    m_windowState.m_mouseCurrent[1]     = y;
}



/**
 * @brief function called in Window::onMouseButtonCb()
 * 
 * @param button button enum
 * @param action action enum
 * @param mods modifier
 * @param x x coordinate of the current cursor position
 * @param y y coordinate of the current cursor position
 */
void WindowedApp::onMouseButton(MouseButton button, ButtonAction action, int mods, int x, int y)
{
    WindowedApp::WindowState&   window  = m_windowState;
    // m_profiler.reset()

    if (mouseButton(button, action)) {
        return;
    }

    if (action == BUTTON_PRESS)
    {
        switch (button)
        {
        case MOUSE_BUTTON_LEFT:
            window.m_mouseButtonFlags   |= ~MOUSE_BUTTONFLAG_LEFT;
            break;
        case MOUSE_BUTTON_MIDDLE:
            window.m_mouseButtonFlags   |= ~MOUSE_BUTTONFLAG_MIDDLE;
            break;
        case MOUSE_BUTTON_RIGHT:
            window.m_mouseButtonFlags   |= ~MOUSE_BUTTONFLAG_RIGHT;
            break;
        default:
            break;
        }
    }
    else if (action == BUTTON_RELEASE)
    {
        switch (button)
        {
        case MOUSE_BUTTON_LEFT:
            window.m_mouseButtonFlags   &= ~MOUSE_BUTTONFLAG_LEFT;
            break;
        case MOUSE_BUTTON_MIDDLE:
            window.m_mouseButtonFlags   &= ~MOUSE_BUTTONFLAG_MIDDLE;
            break;
        case MOUSE_BUTTON_RIGHT:
            window.m_mouseButtonFlags   &= ~MOUSE_BUTTONFLAG_RIGHT;
            break;
        default:
            break;
        }
    }
}



/**
 * @brief function called in Window::onScrollCb() 
 * 
 * @param y mouse wheel delta
 */
void WindowedApp::onMouseWheel(int y)
{
    // m_profiler.reset()
    if (mouseWheel(y)) {
        return;
    }

    m_windowState.m_mouseWheel += y;
}



/**
 * @brief function called in Window::onKeyCb() 
 * 
 * @param key keycode
 * @param action button action
 * @param mods key modifier
 * @param x x coordinate of the current cursor position
 * @param y y coordinate of the current cursor position
 */
void WindowedApp::onKeyboard(KeyCode key, ButtonAction action, int mods, int x, int y)
{
    WindowedApp::WindowState&   window = m_windowState;
    // m_profiler.reset()
    if (keyButton(key, action, mods))
        return;
    
    bool newState = (action != BUTTON_RELEASE);
    window.m_keyToggled[key] = window.m_keyPressed[key] != newState;
    window.m_keyPressed[key] = newState;
}



/**
 * @brief function called in Window::onCharCb() 
 * 
 * @param key keycode
 * @param mods key modifier
 * @param x x coordinate of the current cursor position
 * @param y y coordinate of the current cursor position
 */
void WindowedApp::onKeyboardChar(unsigned char key, int mods, int x, int y)
{
    // m_profiler.reset();
    if (keyChar(key)) {
        return;
    }
}



/**
 * @brief function called in Window::onWindowCloseCb() 
 * 
 */
void WindowedApp::onWindowClose()
{
    
}



/**
 * @brief function called in Window::onWindowSizeCb()
 * 
 * @param w new width of the window
 * @param h new height of the window
 */
void WindowedApp::onWindowResize(int w, int h)
{
    WindowedApp::WindowState& window = m_windowState;
    // m_profiler.reset();

    if (w == 0 || h == 0)
    {
        return;
    }

    window.m_viewSize[0] = w;
    window.m_viewSize[1] = h;
    if (m_active)
    {
        swapResize(w, h);
        resize(w, h);
    }
}



/**
 * @brief App leaving call
 * 
 */
void WindowedApp::leave()
{
    // stop rendering when leaving
    m_config.frameLimit = 1;
}



int WindowedApp::run()
{
    if ( !m_config.winsize[0] ) m_config.winsize[0] = 800;
    if ( !m_config.winsize[1] ) m_config.winsize[1] = 600;

    parseCmd(0, nullptr, ".");
    if (!validateCmd())
    {
        return EXIT_FAILURE;
    }

    // try opening Window
    if (!Window::open(m_config.winpos[0], m_config.winpos[1], m_config.winsize[0], m_config.winsize[1], "Test Window", false))
    {
        Logger::error("Could not create window...");
        return EXIT_FAILURE;
    }
    m_windowState.m_viewSize[0] = m_config.winsize[0];
    m_windowState.m_viewSize[1] = m_config.winsize[1];

    // init graphic API contexts
    postConfigPreContext();
    contextInit();

    // parameter callback here

    // print device info
    if (m_config.deviceCount)
    {
        for(uint32_t i = 0; i < m_config.deviceCount; ++i)
        {
            std::string deviceName(contextGetDeviceName());
            Logger::info(Poco::format("DEVICE: %s", deviceName));
        }
    }

    // init benchmark if profiling

    setVsync(m_config.vsyncState);

    bool run_   = !begin();   // TODO
    m_active    = true;

    bool quickExit = false;
    if (m_config.frameLimit)
    {
        quickExit = true;
    }


    double timeStart = getTime();
    double timeBegin = getTime();
    double frames    = 0;

    // buff Vsync state
    bool lastVsync = m_vsync;

    double lastProfilerPrintTime = 0;

    if (run_)
    {
        while (pollEvents())
        {
            bool wasClosed = false;
            while(!isOpen())
            {
                TeraSystem::waitEvents();
                wasClosed = true;
            }
            if (wasClosed)
            {
                continue;
            }

            // do vsync            
            // if(m_windowState.onPress(KEY_V))
            // {
            //     setVsync(!m_vsync);
            // }

            {
                // do benchmark
                if (m_doSwap)
                {
                    swapPrepare();
                }
                {
                    // render
                    think(getTime() - timeStart);
                }
                std::memset(m_windowState.m_keyToggled, 0 , sizeof(m_windowState.m_keyToggled));
                if (m_doSwap)
                {
                    swapBuffers();
                }
            }

            frames++;
            
            double timeCurrent = getTime();
            double timeDelta   = timeCurrent - timeBegin;
            if (timeDelta > double(m_config.intervalSeconds) || lastVsync != m_vsync || m_config.frameLimit == 1 )
            {
                if (lastVsync != m_vsync)
                {
                    timeDelta = 0;
                }

                if (m_timeInTitle)
                {

                }

                if (m_config.frameLimit == 1)
                {
                    Logger::info(Poco::format("frametime: %.2f ms", (timeDelta * 1000.0 / (frames))));
                }

                // reset
                frames      = 0;
                timeBegin   = timeCurrent;
                lastVsync   = m_vsync;
            }

            if (m_windowState.m_keyPressed[KEY_ESCAPE] || m_config.frameLimit == 1) {
                break;
            }
            
            if (m_config.frameLimit) {
                m_config.frameLimit--;
            }
        }
    }

    // exit screenshot

    if (quickExit)
    {
        // exit(0);
        return EXIT_SUCCESS;
    }

    end();
    m_active = false;
    contextDeinit();
    postEnd();

    return run_ ? EXIT_SUCCESS : EXIT_FAILURE;
}


} // namespace tera
