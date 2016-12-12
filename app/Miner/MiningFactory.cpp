// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "MiningFactory.h"

#include "Wallet/Wallet.h"
#include "Miner.h"

#include "Utils/Log/Log.h"
#include "Utils/Timers/ElapsedTimer.h"


namespace app
{

    MiningFactory::MiningFactory( const Context& context )
        : _context( context )
    {
        assert( _context.wallet != nullptr );
    }

    MiningFactory::~MiningFactory()
    {
        stop();
    }

    void MiningFactory::start( size_t nThreads )
    {
        assert( !_isRunning );

        _isRunning = true;

        if ( nThreads == 0 )
            nThreads = std::max( std::thread::hardware_concurrency(), 1u );

        _threadPool.clear();
        _threadPool.reserve( nThreads );

        for ( size_t i = 0; i < nThreads; i++ )
        {
            _threadPool.emplace_back( &MiningFactory::doMining, this, i + 1 );
        }
    }

    void MiningFactory::stop()
    {
        if ( !_isRunning )
            return;

        _isRunning = false;
        for ( auto& thread : _threadPool )
            if ( thread.joinable() )
                thread.join();

        _threadPool.clear();
    }

    void MiningFactory::doMining( size_t threadId )
    {
        Miner miner;
        const auto wallet = _context.wallet;
        utils::ElapsedTimer<> timer;

        while ( _isRunning )
        {
            //TRACE << "Start mining in thread " << threadId;
            timer.start();

            auto coin = miner.calculate();
            wallet->push( { coin } );

            const auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(timer.elapsed());
            //TRACE << "Mining completed in thread " << threadId << "; " << elapsedMs.count() << "ms";
        }
    }

}
