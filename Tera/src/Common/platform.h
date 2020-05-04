#pragma once
#ifndef TERA_PLATFORM_INCLUDED
#define TERA_PLATFORM_INCLUDED


#include <Poco/Platform.h>

#if POCO_OS == POCO_OS_LINUX
    #define TERA_PLATFORM_LINUX 1
#elif POCO_OS == POCO_OS_WINDOWS_NT
    #define TERA_PLATFORM_WIN32 1
#else
    #define TERA_PLATFORM_UNSUPPORTED
#endif


#endif
