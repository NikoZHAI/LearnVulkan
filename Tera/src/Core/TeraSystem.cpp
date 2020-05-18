#include "TeraSystem.hpp"
#include "Logger.hpp"
#include "../Common/errMsg.hpp"

#include <Poco/Path.h>
#include <Poco/Format.h>

#include <algorithm>


namespace tera {

bool            TeraSystem::m_sysInit           = false;
std::string     TeraSystem::m_exePath           = "";


// callback for glfw errors
static void onErrorGlfwCb(int code, const char* mess)
{ Logger::error( Poco::format("glfw(code = %d): %s", code, std::string(mess)) ); }


void TeraSystem::pollEvents()
{
    glfwPollEvents();
}


void TeraSystem::waitEvents()
{
    glfwWaitEvents();
}


void TeraSystem::postTiming(float ms, int fps, const char* details)
{
    // TODO
}


double TeraSystem::getTime()
{
  return glfwGetTime();
}


void TeraSystem::init(const char* exeFileNameWPath, const char* projectName)
{
    // get abs path to exe (argv[0])
    m_exePath           = Poco::Path(exeFileNameWPath).absolute().parent().toString();

    // init the glfw library
    glfwSetErrorCallback(onErrorGlfwCb);
    int result          = glfwInit();
    if (!result) {
        Logger::fatal("could not init glfw, exiting");
        errMsg( "GLFW initialization failed" );
    }


    m_sysInit = true;

    // init per platform
    platformInit();
}


void TeraSystem::deinit()
{
    platformDeinit();
    glfwTerminate();
}


std::string TeraSystem::exePath()
{ return m_exePath; }


bool TeraSystem::isInited()
{ return m_sysInit; }



}
