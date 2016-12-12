// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Trader.h"

#include "Wallet/Wallet.h"
#include "EvilApi/AbstractItem.h"
#include "EvilApi/RareItems.h"

#include "Utils/Log/Log.h"


namespace
{

    std::string dumpItem( const std::shared_ptr<evil::AbstractItem>& item )
    {
        assert( item != nullptr );
        const auto type = static_cast<evil::RareType>(item->type);

        std::stringstream ss;

        switch( type )
        {
        case evil::RareType::Jug:
            ss << "Jug";
            break;
        case evil::RareType::Helm:
            ss << "Helm";
            break;
        case evil::RareType::Coin:
            ss << "Coin";
            break;
        case evil::RareType::Sword:
            ss << "Sword";
            break;
        default:
            assert( false );
            break;
        }

        ss << " (" << item->cost << ")";
        const auto text = ss.str();
        return text;
    }

}


namespace app
{

    Trader::Trader( const Context& context )
        : _context( context )
    {
    }

    Trader::~Trader()
    {
    }

    // ReSharper disable once CppMemberFunctionMayBeConst
    bool Trader::purchase( const std::shared_ptr<evil::AbstractItem>& item )
    {
        assert( item != nullptr );

        const auto cost = item->cost;
        const auto money = _context.wallet->pop( cost );

        if ( money.empty() )
        {
            TRACE << "Not enough money for: " << dumpItem( item );
            return false;
        }

        TRACE << "Purchased: " << dumpItem( item );
        return true;
    }

}
