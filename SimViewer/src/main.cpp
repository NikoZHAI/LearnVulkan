#include "App/App.hpp"


#include <Poco/Logger.h>
#include <Poco/AutoPtr.h>
#include <Poco/FileChannel.h>
#include <tera/Core/Logger.hpp>
#include <tera/Core/TeraSystem.hpp>


// alias tera::Logger
using tera::Logger;
using tera::TeraSystem;


/**
 * @brief SimViewer Driver
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
    sv::App app;
    {
        using Poco::AutoPtr;
        using Poco::FileChannel;
        using Poco::Logger;
        AutoPtr<FileChannel> pChannel(new FileChannel);
        pChannel->setProperty("path", "sv.log");
        pChannel->setProperty("rotation", "2 K");
        pChannel->setProperty("archive", "timestamp");
        Logger::root().setChannel(pChannel);

        Logger& logger = Logger::get("svInfo");
        tera::Logger::add("svInfo", logger);
    }
    
    // init tera system
    TeraSystem::init(argv[0], "SimViewer");
    
    Logger::info("------ TeraSystem init ------");

    Logger::info("------ svMain() init ------");

    return app.run(argc, argv);
}
