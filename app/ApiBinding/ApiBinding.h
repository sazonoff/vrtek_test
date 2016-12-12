#pragma once


#include "Utils/Singleton/Singleton.h"


namespace evil
{
    class EvilApi;
}

namespace app
{
    
    class ApiBinding
        : public utils::Singleton<ApiBinding>
    {
        friend class utils::Singleton<ApiBinding>;

    public:
        using Callback = std::function<void( const std::vector<char>& )>;
        struct Context
        {
            evil::EvilApi *api = nullptr;
        };

    private:
        ApiBinding() = default;
        ~ApiBinding();

    public:
        void setContext( const Context& context );
        void subscribe( Callback callback );
        void unsubscribeAll();

        void start();
        void stop();

    private:
        void loop();

    private:
        std::atomic_bool _isRunning = false;
        std::vector<Callback> _callbacks;
        std::shared_mutex _locker;
        Context _context;
        std::thread _workerThread;

    public:
        static void onRawRare( const char *data, size_t size );
    };

}
