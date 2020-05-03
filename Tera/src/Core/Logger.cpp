#include "Logger.hpp"
#include "Common/errMsg.hpp"


#include <Poco/Logger.h>
#include <Poco/Exception.h>
#include <Poco/Format.h>
#include <algorithm>


namespace tera
{

// init static variables
typename Logger::Level          Logger::m_level             = Logger::Level::INFO;
// std::string                     Logger::m_fnameDefault      = "log_tera_system.txt";
std::vector<std::string>        Logger::m_loggerNames;
std::vector<Poco::Logger&>      Logger::m_loggers;



void Logger::add(const std::string& loggerName, Poco::Logger& logger)
{
    if ( !m_loggers.empty() )
    {
        auto it = std::find( m_loggerNames.begin(), m_loggerNames.end(), loggerName );
        if ( it != m_loggerNames.end() ) {
            errMsg( Poco::format(
                "Internal: cannot add logger('%s') since it already exists", loggerName)
            );
        }
    }

    m_loggers.emplace_back(logger);
    m_loggerNames.emplace_back(loggerName);
}


void Logger::remove( const std::string &loggerName )
{
    auto it = std::find( m_loggerNames.begin(), m_loggerNames.end(), loggerName );
    if ( it == m_loggerNames.end() ) {
        errMsg( Poco::format(
            "Internal: cannot remove logger('%s') since it does not exist", loggerName)
        );
    }
    m_loggers.erase(m_loggers.begin() + std::distance(m_loggerNames.begin(), it));
    m_loggerNames.erase(it);
}


typename Logger::Level Logger::level()
{ return m_level; }


std::size_t Logger::size()
{ return m_loggers.size(); }


std::string Logger::getName( std::size_t i )
{
    if ( i >= size() ) {
        errMsg( Poco::format("Internal: loggerName(%d) does not exist", i) );
    }
    return m_loggerNames[i];
}


Poco::Logger& Logger::getLogger(const std::string& loggerName)
{
    auto it = std::find( m_loggerNames.begin(), m_loggerNames.end(), loggerName );
    if ( it == m_loggerNames.end() ) {
        errMsg( Poco::format(
            "Internal: cannot remove logger('%s') since it does not exist", loggerName)
        );
    }
    return m_loggers[ std::distance( m_loggerNames.begin(), it ) ];
}


Poco::Logger& Logger::getLogger(std::size_t i)
{
    if ( i >= size() ) {
        errMsg( Poco::format("Internal: logger(%d) does not exist", i) );
    }
    return m_loggers[i];
}


void Logger::setLevel( Level level )
{
    if ( level < LV_COUNT ) {
        m_level = level;
    } else {
        errMsg( Poco::format("Internal: Unkown logger level(%d)", level) );
    }
}


void Logger::turnOn()
{ m_level = INFO; }


void Logger::turnOff()
{ m_level = NONE; }


void Logger::fatal(const char* message)
{
    if ( level() < FATAL ){
        return;
    }

    for ( auto &&logger : m_loggers ) {
        poco_fatal(logger, message);
    }
}


void Logger::fatal(const std::string& message)
{
    if ( level() < FATAL ){
        return;
    }

    for ( auto &&logger : m_loggers ) {
        poco_fatal(logger, message);
    }
}


void Logger::critical(const char* message)
{
    if ( level() < CRITICAL ){
        return;
    }

    for ( auto &&logger : m_loggers ) {
        poco_critical(logger, message);
    }
}


void Logger::critical(const std::string& message)
{
    if ( level() < CRITICAL ){
        return;
    }

    for ( auto &&logger : m_loggers ) {
        poco_critical(logger, message);
    }
}


void Logger::error(const char* message)
{
    if ( level() < ERROR ){
        return;
    }

    for ( auto &&logger : m_loggers ) {
        poco_error(logger, message);
    }
}


void Logger::error(const std::string& message)
{
    if ( level() < ERROR ){
        return;
    }

    for ( auto &&logger : m_loggers ) {
        poco_error(logger, message);
    }
}



void Logger::warning(const char* message)
{
    if ( level() < WARNING ){
        return;
    }

    for ( auto &&logger : m_loggers ) {
        poco_warning(logger, message);
    }
}


void Logger::warning(const std::string& message)
{
    if ( level() < WARNING ){
        return;
    }

    for ( auto &&logger : m_loggers ) {
        poco_warning(logger, message);
    }
}


void Logger::info(const char* message)
{
    if ( level() < INFO ){
        return;
    }

    for ( auto &&logger : m_loggers ) {
        poco_information(logger, message);
    }
}


void Logger::info(const std::string& message)
{
    if ( level() < INFO ){
        return;
    }

    for ( auto &&logger : m_loggers ) {
        poco_information(logger, message);
    }
}


void Logger::debug(const char* message)
{
    if ( level() < DEBUG ){
        return;
    }

    for ( auto &&logger : m_loggers ) {
        poco_debug(logger, message);
    }
}


void Logger::debug(const std::string& message)
{
    if ( level() < DEBUG ){
        return;
    }

    for ( auto &&logger : m_loggers ) {
        poco_debug(logger, message);
    }
}


void Logger::trace(const char* message)
{
    if ( level() < TRACE ){
        return;
    }

    for ( auto &&logger : m_loggers ) {
        poco_trace(logger, message);
    }
}


void Logger::trace(const std::string& message)
{
    if ( level() < TRACE ){
        return;
    }

    for ( auto &&logger : m_loggers ) {
        poco_trace(logger, message);
    }
}


}
