#pragma once
#ifndef TERA_ERR_MSG_INCLUDED
#define TERA_ERR_MSG_INCLUDED


#include <Poco/Exception.h>


namespace tera
{

#ifdef _DEBUG

	#include <sstream>
	#if defined(POCO_OS_FAMILY_WINDOWS)
		#define __FUNC__ __FUNCSIG__
	#elif defined(POCO_OS_FAMILY_UNIX)
		#define __FUNC__ __PRETTY_FUNCTION__
	#else
		#define __FUNC__ ""
	#endif

	inline void
	_errMsg(const std::string& msg, const char* file, int line, const char* func) {
		if (msg.size() == 0) return;
		std::stringstream buff;
		buff << msg << "\n>>> " << file << "(" << line << "): " << func;
		throw Poco::Exception(buff.str());
	}
	#define errMsg(msg) (_errMsg(msg, __FILE__, __LINE__, __FUNC__))
#else
	#include <string>

	inline void
	errMsg(const std::string& msg) {
		if (msg.size() == 0) return;
		throw Poco::Exception(msg);
	}

#endif

}



#endif
