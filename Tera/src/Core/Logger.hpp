#pragma once
#ifndef TERA_LOGGER_INCLUDED
#define TERA_LOGGER_INCLUDED


#include <string>
#include <vector>
#include <cstddef>
#include <functional>   // std::reference_wrapper


namespace Poco
{
    class Logger;
}


namespace tera
{

class Logger
{
public:
    enum Level : int
    {
        NONE,
        FATAL,
        CRITICAL,
        ERROR,
        WARNING,
        NOTICE,
        INFO,
        DEBUG,
        TRACE,

        LV_COUNT,
    };

public:
    static void             add(const std::string& loggerName, Poco::Logger& logger);
    static void             remove(const std::string& loggerName);
    
    static Level            level();
    static std::size_t      size();
    static std::string      getName(std::size_t i);
    static Poco::Logger&    getLogger(const std::string& loggerName);
    static Poco::Logger&    getLogger(std::size_t i);
    static void             setLevel(Level level);
    static void             clear();
    static void             turnOn();
    static void             turnOff();

    static void             fatal(const char* message);
    static void             fatal(const std::string& message);
    static void             critical(const char* message);
    static void             critical(const std::string& message);
    static void             error(const char* message);
    static void             error(const std::string& message);
    static void             warning(const char* message);
    static void             warning(const std::string& message);
    static void             info(const char* message);
    static void             info(const std::string& message);
    static void             debug(const char* message);
    static void             debug(const std::string& message);
    static void             trace(const char* message);
    static void             trace(const std::string& message);

protected:
    static Level                                                m_level;
    static std::vector<std::string>                             m_loggerNames;
    static std::vector<std::reference_wrapper<Poco::Logger> >   m_loggers;
};


}


#endif
