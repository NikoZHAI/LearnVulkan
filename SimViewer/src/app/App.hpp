#ifndef SV_APP
#define SV_APP

namespace sv
{


class App
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
