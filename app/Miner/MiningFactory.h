#pragma once


namespace app
{

    class Wallet;
    
    class MiningFactory
    {
    public:
        struct Context
        {
            std::shared_ptr<Wallet> wallet;
        };

    public:
        explicit MiningFactory( const Context& context = {} );
        ~MiningFactory();

        void start( size_t nThreads = 0 );
        void stop();

    private:
        MiningFactory( const MiningFactory& ) = delete;
        MiningFactory& operator=( const MiningFactory& ) = delete;

        void doMining( size_t threadId );

    private:
        const Context _context;
        std::atomic_bool _isRunning = false;
        std::vector< std::thread > _threadPool;
    };

}
