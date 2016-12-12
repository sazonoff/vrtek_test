#pragma once


#include "AbstractItem.h"

#include "Utils/AbstractFactory/AbstractFactory.h"


namespace evil
{
    
    class ItemFactory
        : public utils::AbstractFactory<AbstractItem, AbstractItem::Key>
    {
    public:
        void registerTypes();

        ItemPtr createFromRaw( const std::vector<char>& data ) const;

    private:
        template< typename Type, typename KeyType >
        void registerTypeAndValidator( const KeyType& typeName );

    private:
        std::map< Key, size_t > _validSizes;
    };


    template <typename Type, typename KeyType>
    void ItemFactory::registerTypeAndValidator( const KeyType& typeName )
    {
        const auto type = static_cast<Key>(typeName);
        registerType<Type>( type );
        _validSizes[type] = sizeof( Type );
    }

}
