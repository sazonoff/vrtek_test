// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Log.h"


namespace utils
{

    std::recursive_mutex& LogContext::locker()
    {
        return _locker;
    }

    Log::Log()
        : _lock( LogContext::instance().locker() )
    {
    }

    Log::~Log()
    {
        std::cout << std::endl;
    }

}
