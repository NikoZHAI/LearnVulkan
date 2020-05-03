#pragma once
#ifndef SV_APP
#define SV_APP


#include <tera/Core/WindowedApp.hpp>


namespace sv
{


class App : public tera::WindowedApp
{
protected:


public:
    App(/* args */);
    ~App();
    
    /**
     * @brief run app from cmd
     * 
     * @param argc arg count
     * @param argv arg values
     * @return int exit status
     */
    int run(int argc, char const *argv[]);
};


} // namespace sv


#endif
