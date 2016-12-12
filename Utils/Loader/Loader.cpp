// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


#include "Loader.h"


namespace utils
{
    
    Loader::Loader( const std::filesystem::path& path, bool forceUnload )
        : _path( path )
        , _forceUnload( forceUnload )
    {
    }

    Loader::~Loader()
    {
        if ( isLoaded() && _forceUnload )
        {
            ::FreeLibrary( _handle );
        }
    }

    bool Loader::isLoaded() const
    {
        return _handle != nullptr;
    }

    bool Loader::load()
    {
        if ( isLoaded() )
            return true;

        ::SetLastError( 0 );
        auto handle = ::LoadLibraryW( _path.wstring().c_str() );
        if ( handle == nullptr )
        {
            std::wcerr << "Could not load library: " << _path.wstring() << std::endl;
            return false;
        }

        _handle = handle;
        return true;
    }

}
