#pragma once
#ifndef PLATFORM_INCLUDED
#define PLATFORM_INCLUDED 1


/**
 * @brief define platform macros
 */
#if defined(_WIN32)
    #define     S_ON_PLATFORM_WINDOWS   1
#elif defined(__linux__) && not defined(__ANDROID__)
    #define     S_ON_PLATFORM_LINUX     1
#elif defined(__APPLE__)
    #define     S_ON_PLATFORM_DARWIN    1
#elif defined(__ANDROID__)
    #define     S_ON_PLATFORM_ANDROID   1
#else
    #error "Unsupported Platform!"
#endif


#endif
