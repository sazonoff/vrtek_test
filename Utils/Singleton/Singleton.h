#pragma once


namespace utils
{
    
    template < typename T >
    class Singleton
    {
    public:
        static T& instance()
        {
            static T inst;
            return inst;
        }

    protected:
        Singleton() {}
        virtual ~Singleton() {}

    private:
        Singleton( const Singleton& ) = delete;
        Singleton& operator=( const Singleton& ) = delete;
    };



    template < typename T, typename R = T >
    class LazySingleton
    {
        static_assert(std::is_base_of_v<R, T>, "R should be a base type of T");

    public:
        static R& instance()
        {
            assert( _inst != nullptr );
            return *_inst;
        }

        template<typename ...Args>
        static void createSingleton( Args &&...args )
        {
            std::lock_guard<std::mutex> lock( _locker );

            auto object = std::make_shared<T>( std::forward<Args>( args )... );
            _inst = std::static_pointer_cast<R>(object);
        }

        static void releaseSingleton()
        {
            std::lock_guard<std::mutex> lock( _locker );
            _inst.reset();
        }

    protected:
        LazySingleton() = default;
        virtual ~LazySingleton() = default;

    private:
        LazySingleton( const LazySingleton& ) = delete;
        LazySingleton& operator=( const LazySingleton& ) = delete;

        static std::shared_ptr< R > _inst;
        static std::mutex _locker;
    };

    template <typename T, typename R>
    std::shared_ptr<R> LazySingleton<T, R>::_inst;

    template <typename T, typename R>
    std::mutex LazySingleton<T, R>::_locker;

}
