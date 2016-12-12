#pragma once


namespace utils
{
    
    template< typename Clock = std::chrono::steady_clock >
    class ElapsedTimer
    {
    public:
        using Time = typename Clock::duration;

    public:
        ElapsedTimer() = default;
        ~ElapsedTimer() = default;

        Time elapsed() const;
        bool isValid() const;
        template< typename T = Time >
        bool hasExpired( const T& timeout ) const;
        Time timeTo( const ElapsedTimer& other ) const;

        void invalidate();
        void start();
        Time restart();

    private:
        typename Clock::time_point _timePoint;
        bool _isValid = false;
    };

    template <typename Clock>
    typename ElapsedTimer<Clock>::Time ElapsedTimer<Clock>::elapsed() const
    {
        assert( _isValid );
        const auto interval = Clock::now() - _timePoint;

        return interval;
    }

    template <typename Clock>
    bool ElapsedTimer<Clock>::isValid() const
    {
        return _isValid;
    }

    template <typename Clock>
    template <typename T>
    bool ElapsedTimer<Clock>::hasExpired( const T& timeout ) const
    {
        assert( _isValid );
        const auto expired = elapsed() > timeout;

        return expired;
    }

    template <typename Clock>
    typename ElapsedTimer<Clock>::Time ElapsedTimer<Clock>::timeTo( const ElapsedTimer& other ) const
    {
        if ( !isValid() || other.isValid() )
            return{};

        const auto distance = _timePoint - other._timePoint;
        return distance;
    }

    template <typename Clock>
    void ElapsedTimer<Clock>::invalidate()
    {
        _timePoint = {};
        _isValid = false;
    }

    template <typename Clock>
    void ElapsedTimer<Clock>::start()
    {
        _timePoint = Clock::now();
        _isValid = true;
    }

    template <typename Clock>
    typename ElapsedTimer<Clock>::Time ElapsedTimer<Clock>::restart()
    {
        const auto timeout = elapsed();
        start();

        return timeout;
    }

}
