// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


#include "Wallet.h"


namespace app
{

    void Wallet::push( const std::initializer_list<Coin>& coins )
    {
        std::lock_guard<std::mutex> lock( _locker );
        _coins.insert( _coins.end(), coins );
    }

    Money Wallet::pop( size_t count )
    {
        std::list<Coin> coins;

        {
            std::lock_guard<std::mutex> lock( _locker );

            if ( _coins.size() < count )
                return{};

            const auto begin = _coins.begin();
            const auto end = std::next( begin, count );

            coins.splice( coins.begin(), _coins, begin, end );
        }

        Money money{ std::make_move_iterator( coins.begin() ), std::make_move_iterator( coins.end() ) };

        return money;
    }

}
