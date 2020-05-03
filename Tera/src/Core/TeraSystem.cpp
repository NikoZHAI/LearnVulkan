#include "TeraSystem.hpp"

#include <algorithm>
#include <Poco/Path.h>


namespace tera {

bool            TeraSystem::m_sysInit           = false;
std::string     TeraSystem::m_exePath           = "";


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
    int result          = glfwInit();
    if (!result) {
        
    }
}


}
