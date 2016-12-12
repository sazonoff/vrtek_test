#pragma once


#include <Windows.h>


namespace utils
{
    
    class Loader
    {
    public:
        explicit Loader( const std::filesystem::path& path, bool forceUnload = false );
        ~Loader();

        bool load();
        bool isLoaded() const;
        template< typename T >
        T resolve( const std::string& symbol );

    private:
        const std::filesystem::path _path;
        const bool _forceUnload = false;
        HMODULE _handle = nullptr;
    };


    template <typename T>
    T Loader::resolve( const std::string& symbol )
    {
        assert( !symbol.empty() );

        if ( !isLoaded() )
            if ( !load() )
                return nullptr;

        auto proc = ::GetProcAddress( _handle, symbol.c_str() );
        if ( proc == nullptr )
            return nullptr;

        return reinterpret_cast<T>(proc);
    }

}
