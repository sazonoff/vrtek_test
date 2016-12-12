#pragma once


#pragma warning( push )
#pragma warning( disable: 4305 )

#include "btc_miner.h"

#pragma warning( pop )

#include "Money/Money.h"


namespace app
{
    
    class Miner
        : public IBTCMiner
    {
    public:
        Miner() = default;
        ~Miner() = default;

        Coin calculate();
    };

}