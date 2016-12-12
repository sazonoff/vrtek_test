#pragma once


#include "Utils/Singleton/Singleton.h"


namespace evil
{
    class EvilApi;
}


namespace app
{

    class Wallet;
    class MiningFactory;
    class Trader;

    
    class Application
    {
    public:
        Application();
        ~Application();

        bool init();
        void run();

    private:
        std::shared_ptr<Wallet> _wallet;
        evil::EvilApi *_api = nullptr;
        std::unique_ptr<MiningFactory> _miningFactory;
        std::shared_ptr<Trader> _trader;
    };

}
