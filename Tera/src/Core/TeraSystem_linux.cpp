#include "../Common/platform.h"

#ifdef TERA_PLATFORM_LINUX

#include "TeraSystem.hpp"

#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>

#include <vector>
#include <algorithm>
#include <unistd.h>
#include <stdio.h>
#include <string>

// from https://docs.microsoft.com/en-us/windows/desktop/gdi/capturing-an-image

namespace tera
{

    void TeraSystem::windowScreenshot(GLFWwindow *glfwin, const char *filename)
    {
    }

    void TeraSystem::windowClear(GLFWwindow *glfwin, uint32_t r, uint32_t g, uint32_t b)
    {
        Window hwnd = glfwGetX11Window(glfwin);
    }

    std::string TeraSystem::windowOpenFileDialog(GLFWwindow *glfwin, const char *title, const char *exts)
    {
        Window hwnd = glfwGetX11Window(glfwin);

        return std::string();
    }

    void TeraSystem::sleep(double seconds)
    {
        ::sleep(seconds);
    }

    void TeraSystem::platformInit()
    {
    }

    void TeraSystem::platformDeinit()
    {
    }

} // namespace tera

#endif
