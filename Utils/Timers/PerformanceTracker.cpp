#include "Common.h"
#include "PerformanceTracker.h"


namespace utils
{

    PerformanceTracker::PerformanceTracker( size_t reserve )
    {
        _timestamps.reserve( reserve );
        _startMarks.reserve( reserve );
        _endMarks.reserve( reserve );
        _labelMarks.reserve( reserve );
    }

    void PerformanceTracker::pushTimestamp( std::vector< std::pair< size_t, const char * const > >& vec, const char * const text )
    {
        ASSERT( text != nullptr );
        validate( vec, text );
        if ( !_timer.isValid() )
            _timer.start();

        const auto elapsed = _timer.elapsed();
        _timestamps.emplace_back( elapsed );
        
        const auto index = _timestamps.size() - 1;
        vec.emplace_back( std::make_pair( index, text ) );
    }

    void PerformanceTracker::validate( std::vector<std::pair<size_t, const char* const>>& vec, const char* const text )
    {
        (void)vec;
        (void)text;
#ifdef _DEBUG
        const auto count = std::count_if( vec.begin(), vec.end(),
            [text]( const std::pair<size_t, const char* const>& condition )
            {
                return std::strcmp( text, condition.second ) == 0;
            });
        ASSERT( count == 0 );
#endif
    }

    void PerformanceTracker::timestamp( const char* const text )
    {
        pushTimestamp( _labelMarks, text );
    }

    void PerformanceTracker::start( const char* const text )
    {
        pushTimestamp( _startMarks, text );
    }

    void PerformanceTracker::end( const char* const text )
    {
        pushTimestamp( _endMarks, text );
    }

    PerformanceTracker::Info PerformanceTracker::collectInfo() const
    {
        Info info;

        for ( const auto& labelMark : _labelMarks )
        {
            const auto timestamp = _timestamps[labelMark.first];
            info.timestamps[labelMark.second] = timestamp;
        }
        for ( const auto& startMark : _startMarks )
        {
            const auto timestamp = _timestamps[startMark.first];
            info.measurments[startMark.second].first = timestamp;
        }
        for ( const auto& endMark : _endMarks )
        {
            const auto timestamp = _timestamps[endMark.first];
            info.measurments[endMark.second].second = timestamp;
        }

        return std::move( info );
    }

    std::string PerformanceTracker::dump( const Info& info )
    {
        std::stringstream ss;

        using Timestamp = std::pair< std::string, Elapsed >;
        auto minTimestamp = []( const Timestamp& first, const Timestamp& last )
        {
            const auto needSwap = first.second < last.second;
            return needSwap;
        };
        auto startToTimestamp = []( const std::pair<std::string, std::pair< Elapsed, Elapsed >>& item )
        {
            const auto text = "Start: " + item.first;
            return std::make_pair( text, item.second.first );
        };
        auto endToTimestamp = []( const std::pair<std::string, std::pair< Elapsed, Elapsed >>& item )
        {
            const auto text = "End:   " + item.first;
            return std::make_pair( text, item.second.second );
        };

        auto measurments = info.measurments;
        for ( auto it = measurments.begin(); it != measurments.end(); )
        {
            const auto isValid = it->second.second >= it->second.first;
            if ( !isValid )
                it = measurments.erase( it );
            else
                ++it;
        }

        std::vector< std::pair< std::string, Elapsed > > timestamps;
        timestamps.reserve( info.timestamps.size() + info.measurments.size() * 2 );

        std::copy( info.timestamps.begin(), info.timestamps.end(), std::back_inserter( timestamps ) );
        std::transform( measurments.begin(), measurments.end(), std::back_inserter( timestamps ), startToTimestamp );
        std::transform( measurments.begin(), measurments.end(), std::back_inserter( timestamps ), endToTimestamp );
        
        std::sort( timestamps.begin(), timestamps.end(), minTimestamp );

        ss << "------->8----->8--";
        if ( !timestamps.empty() )
        {
            ss << "\n*** Timestamps ***";
            for ( const auto& timestamp : timestamps )
            {
                const auto time = std::chrono::duration_cast<std::chrono::milliseconds>(timestamp.second).count();
                const auto text = timestamp.first;
                ss << "\n" << time << " ms;\t" <<  text;
            }
        }

        if ( !info.measurments.empty() )
        {
            ss << "\n*** Measurements ***";
            for ( const auto& measure : info.measurments )
            {
                const auto elapsed = measure.second.second - measure.second.first;
                const auto time = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
                const auto text = measure.first;
                const auto isValid = time >= 0;

                if ( !isValid )
                {
                    ss << "\nInvalid measure for: " << text << " // both \'start\' and \'end\' should be called";
                    continue;
                }

                ss << "\n" << time << " ms;\t" <<  text;
            }
        }

        ss << "\n---8<-----8<------";
        const auto str = ss.str();
        return str;
    }

}
