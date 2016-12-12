#pragma once


#include "Money/Money.h"


namespace app
{
    
    class Wallet
    {
    public:
        Wallet() = default;
        ~Wallet() = default;

        void push( const std::initializer_list<Coin>& coins );
        Money pop( size_t count );

    private:
        std::mutex _locker;
        std::list<Coin> _coins;
    };

}
