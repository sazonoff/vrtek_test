#pragma once

#include "Utils/Singleton/Singleton.h"


namespace utils
{
    
    class LogContext
        : public Singleton<LogContext>
    {
        friend class Singleton<LogContext>;

    private:
        LogContext() = default;
        ~LogContext() = default;

    public:
        std::recursive_mutex& locker();

    private:
        std::recursive_mutex _locker;
    };


    class Log
    {
    public:
        Log();
        ~Log();

        template< typename T >
        Log& operator<<( T&& item );

    private:
        std::lock_guard<std::recursive_mutex> _lock;
    };

    template <typename T>
    Log& Log::operator<<( T&& item )
    {
        std::cout << std::forward<T>( item );
        return *this;
    }

}


#define TRACE utils::Log()