// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


#include "ApiBinding.h"

#include "EvilApi/EvilApi.h"

#include "Utils/Log/Log.h"


namespace app
{

    ApiBinding::~ApiBinding()
    {
        if ( _workerThread.joinable() )
            _workerThread.join();
    }

    void ApiBinding::setContext( const Context& context )
    {
        _context = context;
    }

    void ApiBinding::start()
    {
        assert( !_isRunning );
        _isRunning = true;

        _workerThread = std::thread( &ApiBinding::loop, this );
    }

    void ApiBinding::stop()
    {
        assert( _isRunning );
        _isRunning = false;
    }

    void ApiBinding::loop()
    {
        while ( _isRunning )
        {
            _context.api->get_raw_rare( &ApiBinding::onRawRare );
        }
    }

    void ApiBinding::subscribe( Callback callback )
    {
        std::unique_lock<std::shared_mutex> lock( _locker );

        _callbacks.push_back( callback );
    }

    void ApiBinding::unsubscribeAll()
    {
        std::unique_lock<std::shared_mutex> lock( _locker );
        _callbacks.clear();
    }

    void ApiBinding::onRawRare( const char* data, size_t size )
    {
        auto& inst = instance();
        const std::vector<char> buf( data, data + size );

        std::shared_lock<std::shared_mutex> lock( inst._locker );
        for ( const auto& callback : inst._callbacks )
            callback( buf );
    }

}
