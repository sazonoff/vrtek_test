#pragma once


#include "ElapsedTimer.h"
#include "../Base/Singleton.h"

namespace utils
{
    
    class PerformanceTracker
    {
    public:
        using Elapsed = std::chrono::nanoseconds;
        struct Info
        {
            std::map< std::string, Elapsed > timestamps;
            std::map< std::string, std::pair< Elapsed, Elapsed > > measurments;
        };

    public:
        explicit PerformanceTracker( size_t reserve = 1000 );
        ~PerformanceTracker() = default;

        void timestamp( const char * const text );
        void start( const char * const text );
        void end( const char * const text );

        Info collectInfo() const;

    public:
        static std::string dump( const Info& info );

    private:
        inline void pushTimestamp( std::vector< std::pair< size_t, const char * const > >& vec, const char * const text );

    private:
        ElapsedTimer< std::chrono::high_resolution_clock > _timer;
        std::vector< Elapsed > _timestamps;
        std::vector< std::pair< size_t, const char * const > > _labelMarks;
        std::vector< std::pair< size_t, const char * const > > _startMarks;
        std::vector< std::pair< size_t, const char * const > > _endMarks;

    private:
        inline static void validate( std::vector< std::pair< size_t, const char * const > >& vec, const char * const text );
    };

    class PerformanceTrackerSingelton : public Singleton<PerformanceTracker>
    {

    };

}
