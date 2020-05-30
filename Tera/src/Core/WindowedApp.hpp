#pragma once
#ifndef TERA_WINDOWED_APP_INCLUDED
#define TERA_WINDOWED_APP_INCLUDED


#include "Window.hpp"


namespace tera
{


class WindowedApp : public Window
{
public:

    class WindowState
    {
    public:
        int                 m_viewSize[2]           = {};
        int                 m_mouseCurrent[2]       = {};
        int                 m_mouseButtonFlags      = 0;
        int                 m_mouseWheel            = 0;

        bool                m_keyPressed[KEY_COUNT] = {};
        bool                m_keyToggled[KEY_COUNT] = {};

        bool onPress(int key) {
            return m_keyPressed[key] && m_keyToggled[key];
        }
    };

    //////////////////////////////////////////////////////////////////////////


    WindowState             m_windowState;
    // [TODO] profiler
    bool                    m_timeInTitle           = false;
    bool                    m_doSwap                = false;

    // ctor
    WindowedApp();
    // dtor
    ~WindowedApp();


    // [TODO] parameter list

    // WindowedApp driver method
    int run();
    // leave WindowedApp
    void leave();
    // void        parseConfigFile(const char* filename);
    // std::string specialStrings(const char* original);
    void setVsync(bool sync);
    bool getVsync() const { return m_vsync; };


    //////////////////////////////////////////////////////////////////////////
    // Scene Related
    //
    // Use when the derived app has scene-based, interaction-responsive features
    // 

    // setup scene (this is executed after window/context creation)
    virtual bool begin() { return false; }
    // tear down the scene (triggered by ESC/window close)
    virtual void end() {}
    // primary logic<-->draw loop here
    virtual void think(double time) {}
    // react on window resizes here
    virtual void resize(int width, int height) {}
    
    // return true if desired to prevent m_windowState updates
    virtual bool mousePos (int x, int y)                            { return false; }
    virtual bool mouseButton (int button, int action)               { return false; }
    virtual bool mouseWheel (int delta)                             { return false; }
    virtual bool keyButton (int button, int action, int modifier)   { return false; }
    virtual bool keyChar (int button)                               { return false; }
    virtual bool validateCmd()                                      { return true;  }
    virtual void parseCmd(int argc, const char** argv, const std::string& path) { }

    // additional special-purpose callbacks
    virtual void postProfiling() {}
    virtual void postEnd() {}
    virtual void postBenchmarkAdvance() {}
    virtual void postConfigPreContext() {}


    //////////////////////////////////////////////////////////////////////////
    // Context Window Related
    //
    // Used when deriving from this class for the purpose of providing graphic API contexts
    // 

    virtual void contextInit() {}
    virtual void contextDeinit() {}
    virtual const char* contextGetDeviceName() { return nullptr; }
    virtual std::size_t contextGetDeviceCount() { return 0; }

    virtual void swapResize(int width, int height) {}
    virtual void swapPrepare() {}
    virtual void swapBuffers() {}
    virtual void swapVsync(bool state) {}


    //////////////////////////////////////////////////////////////////////////
    // Override tera::Window callbacks
    //
    // Used when the derived app needs to handle window events
    // 

    void onWindowClose() override;
    void onWindowResize(int w, int h) override;
    void onWindowRefresh() override {}; // leave empty for the moment
    void onMouseMotion(int x, int y) override;
    void onMouseWheel(int delta) override;
    void onMouseButton(MouseButton button, ButtonAction action, int mods, int x, int y) override;
    void onKeyboard(KeyCode key, ButtonAction action, int mods, int x, int y) override;
    void onKeyboardChar(unsigned char key, int mods, int x, int y) override;

protected:

    // struct Benchmark {
    //   std::string                   filename;
    //   std::string                   content;
    //   nvh::ParameterSequence        sequence;
    //   uint32_t                      frameLength = 256;
    //   uint32_t                      frame = 0;
    // };

    struct Config
    {
        int32_t             winpos[2]               = {50, 50};
        int32_t             winsize[2]              = {};
        bool                vsyncState              = true;
        uint32_t            intervalSeconds         = 2;
        uint32_t            frameLimit              = 0;
        uint32_t            timerLimit              = 0;
        uint32_t            clearColor[3]           = {127,0,0};
        uint32_t            deviceCount             = 0;
        std::string         dumpatexitFilename;
        std::string         screenshotFilename;
        std::string         logFilename;
        std::string         configFilename;
    };


    bool                    m_active                = false;
    bool                    m_hadScreenshot         = false;
    bool                    m_vsync                 = false;
    Config                  m_config;
//  Benchmark               m_benchmark;

    uint32_t                m_paramWinsize          = 0;
    uint32_t                m_paramVsync            = 0;
    uint32_t                m_paramScreenshot       = 0;
    uint32_t                m_paramLog              = 0;
    uint32_t                m_paramCfg              = 0;
    uint32_t                m_paramBat              = 0;
    uint32_t                m_paramClear            = 0;


    // void parameterCallback(uint32_t param);
    // void setupParameters();
    // void exitScreenshot();
    // void initBenchmark();
    // void advanceBenchmark();
};


} // namespace tera


#endif
