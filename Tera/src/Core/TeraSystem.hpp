#pragma once
#ifndef TERA_SYSTEM_INCLUDED
#define TERA_SYSTEM_INCLUDED


#include "GLFW/glfw3.h"

#include <cstdlib>
#include <string>


namespace tera
{

/**
 * @brief This is basically NVPSystem renamed
 */
class TeraSystem
{
    using Self              = TeraSystem;
public:
    // simple helper class, put it into your main function
    TeraSystem(const char* exeFileNameWPath, const char* projectName)
    { init(exeFileNameWPath, projectName); }
    
    ~TeraSystem()
    { deinit(); }

    // exeFileName is typically argv[0]
    static void             init(const char* exeFileNameWPath, const char* projectName);
    static void             deinit();
    static void             pollEvents();
    static void             waitEvents();
    static void             sleep(double seconds);
    static void             postTiming(float ms, int fps, const char* details = NULL);
    static bool             isInited();
    static double           getTime();  // in seconds
    static std::string      exePath();

    // uses operating system specific code for sake of debugging/automated testing
    static void             windowScreenshot(GLFWwindow* glfwin, const char* filename);
    static void             windowClear(GLFWwindow* glfwin, uint32_t r, uint32_t g, uint32_t b);
    static std::string      windowOpenFileDialog(GLFWwindow* glfwin, const char* title, const char* exts);

private:
    static void             platformInit();
    static void             platformDeinit();

private:
    static bool             m_sysInit;
    static std::string      m_exePath;
};

}

#endif
