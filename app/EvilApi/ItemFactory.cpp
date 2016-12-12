// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


#include "ItemFactory.h"

#include "RareItems.h"

#include "Utils/Log/Log.h"


namespace evil
{

    void ItemFactory::registerTypes()
    {
        registerTypeAndValidator<Jug>( RareType::Jug );
        registerTypeAndValidator<Helm>( RareType::Helm );
        registerTypeAndValidator<Coin>( RareType::Coin );
        registerTypeAndValidator<Sword>( RareType::Sword );
    }

    ItemFactory::ItemPtr ItemFactory::createFromRaw( const std::vector<char>& data ) const
    {
        if ( data.empty() )
            return {};

        const auto type = static_cast<AbstractItem::Key>(data[0]);
        const auto item = create( type );
        if ( item == nullptr )
            return {};

        const auto itValidator = _validSizes.find( type );
        assert( itValidator != _validSizes.end() );

        //const auto extraSize = offsetof( AbstractItem, Cost );
        constexpr auto extraSize = sizeof( AbstractItem::Cost );    // Hack, because offsetof is not working as expected in msvc14
        const auto dataSize = data.size() - sizeof( type );
        const auto expectedSize = itValidator->second - extraSize;

        if ( dataSize != expectedSize )
        {
            TRACE << "Invalid size of buffer for type: " << static_cast<int>( type );
            return {};
        }

        item->type = type;
        std::memcpy( &item->cost, &data[1], data.size() - sizeof( evil::AbstractItem::Key ) );
        return item;
    }

}
