#include "Window.hpp"


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

void Window::onDropCb(GLFWwindow *glfwwin, int count, const char **paths)
{
    Self* win = reinterpret_cast<Self*>( glfwGetWindowUserPointer(glfwwin) );
    if (win->isClosing()) return;
    win->onDragDrop(count, paths);
}


} // namespace tera
