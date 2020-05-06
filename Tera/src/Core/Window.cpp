#include "Window.hpp"
#include "../Common/predefs.hpp"
#include "../Common/platform.h"


#include <cstdio>
#include <string>
#include <algorithm>


namespace tera
{


/// callbacks
// call back that handles window refresh events
void Window::onWindowRefreshCb(GLFWwindow* glfwwin)
{
    Self* win = reinterpret_cast<Self*>( glfwGetWindowUserPointer(glfwwin) );
    if (win->isClosing()) return;
    win->onWindowRefresh();
}

// call back that handles window size init and change events
void Window::onWindowSizeCb(GLFWwindow* glfwwin, int w, int h)
{
    Self* win = reinterpret_cast<Self*>( glfwGetWindowUserPointer(glfwwin) );
    if (win->isClosing()) return;
    win->m_windowSize[0] = w;
    win->m_windowSize[1] = h;
    win->onWindowResize(w, h);
}

// call back that handles window close event
void Window::onWindowCloseCb(GLFWwindow* glfwwin)
{
    Self* win = reinterpret_cast<Self*>( glfwGetWindowUserPointer(glfwwin) );
    win->m_isClosing = true;
    win->onWindowClose();
}

// call back that handles mouse button events
void Window::onMouseButtonCb(GLFWwindow* glfwwin, int button, int action, int mods)
{
    double x, y;
    glfwGetCursorPos(glfwwin, &x, &y);

    Self* win = reinterpret_cast<Self*>( glfwGetWindowUserPointer(glfwwin) );
    if (win->isClosing()) return;
    win->m_keyModifiers = mods;
    win->m_mouseX = int(x);
    win->m_mouseY = int(y);
    win->onMouseButton((MouseButton)button, (ButtonAction)action, mods, win->m_mouseX, win->m_mouseY);
}

// call back that handles cursor position function
void Window::onCursorPosCb(GLFWwindow* glfwwin, double x, double y)
{
    Self* win = reinterpret_cast<Self*>( glfwGetWindowUserPointer(glfwwin) );
    if (win->isClosing()) return;
    win->m_mouseX = int(x);
    win->m_mouseY = int(y);
    win->onMouseMotion(win->m_mouseX, win->m_mouseY);
}

// call back that handles device scrolling events
void Window::onScrollCb(GLFWwindow* glfwwin, double x, double y)
{
    Self* win = reinterpret_cast<Self*>( glfwGetWindowUserPointer(glfwwin) );
    if (win->isClosing()) return;
    int delta = int(y);
    win->m_mouseWheel += delta;
    win->onMouseWheel(int(y));
}

// call back for keyboard key press events
void Window::onKeyCb(GLFWwindow *glfwwin, int key, int scancode, int action, int mods)
{
    Self* win = reinterpret_cast<Self*>( glfwGetWindowUserPointer(glfwwin) );
    if (win->isClosing()) return;
    win->m_keyModifiers = mods;
    win->onKeyboard((KeyCode)key, (ButtonAction)action, mods, win->m_mouseX, win->m_mouseY);
}

// call back for character input events
void Window::onCharCb(GLFWwindow *glfwwin, unsigned int codepoint)
{
    Self* win = reinterpret_cast<Self*>( glfwGetWindowUserPointer(glfwwin) );
    if (win->isClosing()) return;
    win->onKeyboardChar(codepoint, win->m_keyModifiers, win->m_mouseX, win->m_mouseY);
}

// call back for drap-drop events
void Window::onDropCb(GLFWwindow *glfwwin, int count, const char **paths)
{
    Self* win = reinterpret_cast<Self*>( glfwGetWindowUserPointer(glfwwin) );
    if (win->isClosing()) return;
    win->onDragDrop(count, paths);
}

// open a Tera Window
bool Window::open(int posX, int posY, int width, int height, const char* title, bool requireGLContext)
{
    tera_assert(TeraSystem::isInited() && "TeraSystem::Init() not called before instantiating a tera::Window");
    
    m_windowSize[0]     = width;
    m_windowSize[1]     = height;
    m_windowName        = title ? title : "Unamed";

#ifdef TERA_PALTFORM_WIN32
    (void)requireGLContext;
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#else
    if (!requireGLContext)
    {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    }
    else
    {
        // hint yo use opengl4.6
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    }
#endif

    /// create window using hint
    m_internal = glfwCreateWindow(width, height, title, nullptr, nullptr);
    
    /// return false immediately if failed
    if (!m_internal) return false;

    /// set window position
    if (posX != 0 || posY != 0) glfwSetWindowPos(m_internal, posX, posY);
    
    /// bind `this` to GLFWwindow `m_internal`
    glfwSetWindowUserPointer(m_internal, this);

    /// bind window callbacks
    glfwSetWindowRefreshCallback(   m_internal, onWindowRefreshCb  );
    glfwSetWindowSizeCallback   (   m_internal, onWindowSizeCb     );
    glfwSetWindowCloseCallback  (   m_internal, onWindowCloseCb    );
    glfwSetMouseButtonCallback  (   m_internal, onMouseButtonCb    );
    glfwSetCursorPosCallback    (   m_internal, onCursorPosCb      );
    glfwSetScrollCallback       (   m_internal, onScrollCb         );
    glfwSetKeyCallback          (   m_internal, onKeyCb            );
    glfwSetCharCallback         (   m_internal, onCharCb           );
    glfwSetDropCallback         (   m_internal, onDropCb           );

    /// success
    return true;
}


} // namespace tera
