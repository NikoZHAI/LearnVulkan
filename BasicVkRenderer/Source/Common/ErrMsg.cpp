#include "ErrMsg.h"


#include <string>
#include <stdexcept>


#ifdef _DEBUG

    #include <sstream>
    #if defined(__GNUCC__)
        #define FUNC_NAME __PRETTY_FUNCTION__
    #elif defined(_MSC_VER)
        #define FUNC_NAME __FUNCSIG__
    #else
        #define FUNC_NAME ""
    #endif

    inline void
    ErrMsgDebug ( const std::string &msg, const char *file, int line, const char *func )
    {
        if ( msg.empty() ) return;
		std::stringstream buff;
		buff << msg << "\n>>> " << file << "(" << line << "): " << func;
		throw std::runtime_error( buff.str() );
    }

    void ErrMsg( const std::string &msg )
    {
        ErrMsgDebug( msg, __FILE__, __LINE__, FUNC_NAME );
    }

#else

    void ErrMsg( const std::string &msg )
    {
        if ( msg.empty() ) return;
        throw std::runtime_error( msg );
    }

#endif
