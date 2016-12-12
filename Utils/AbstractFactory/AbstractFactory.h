#pragma once


namespace utils
{

    template< typename T, typename K = std::string >
    class AbstractFactory
    {
    public:
        using ItemType = T;
        using ItemPtr = std::shared_ptr<ItemType>;
        using ItemFactory = std::function< ItemPtr() >;
        using Key = K;

    public:
        AbstractFactory() = default;
        ~AbstractFactory() = default;

        template <typename Type, typename KeyType>
        void registerType( const KeyType& typeName );
        template <typename KeyType>
        bool isRegistered( const KeyType& typeName );

        template <typename KeyType, typename ...Args>
        ItemPtr create( const KeyType& typeName, Args&& ...args ) const;

        const std::vector< Key >& typeNames() const;

    private:
        template <typename Type, typename ...Args>
        static ItemFactory creator();

    private:
        std::map< Key, ItemFactory > _factory;
        std::vector< Key > _typeNames;
    };

    template <typename T, typename K>
    template <typename Type, typename KeyType>
    void AbstractFactory<T, K>::registerType( const KeyType& typeName )
    {
        const auto type = static_cast<Key>( typeName );

        assert( _factory.count( type ) == 0 );

        auto factory = creator<Type>();
        _factory.emplace( type, factory );
        _typeNames.push_back( type );
    }

    template <typename T, typename K>
    template <typename KeyType>
    bool AbstractFactory<T, K>::isRegistered( const KeyType& typeName )
    {
        const auto type = static_cast<Key>(typeName);
        return _factory.find( type ) != _factory.end();
    }

    template <typename T, typename K>
    template <typename KeyType, typename ... Args>
    typename AbstractFactory<T, K>::ItemPtr AbstractFactory<T, K>::create( const KeyType& typeName, Args&&... args ) const
    {
        const auto type = static_cast<Key>(typeName);
        const auto it = _factory.find( type );
        if ( it == _factory.end() )
            return {};

        const auto& factory = it->second;
        const auto& object = factory( std::forward<Args>( args )... );

        return object;
    }

    template <typename T, typename K>
    const std::vector<typename AbstractFactory<T, K>::Key>& AbstractFactory<T, K>::typeNames() const
    {
        return _typeNames;
    }

    template <typename T, typename K>
    template <typename Type, typename ... Args>
    typename AbstractFactory<T, K>::ItemFactory AbstractFactory<T, K>::creator()
    {
        auto fn = []( Args&& ...args ) -> ItemPtr
        {
            return std::make_shared<Type>( std::forward<Args>( args )... );
        };
        return fn;
    }

}
