// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Runtime.h"

#include <Windows.h>


namespace utils
{

    void Runtime::setCurrentDir()
    {
        WCHAR name[MAX_PATH];

        ::GetModuleFileNameW( ::GetModuleHandleW( nullptr ), name, sizeof( name ) );
        std::filesystem::path path = name;
        assert( path.has_filename() );
        path = path.remove_filename();
        SetCurrentDirectoryW( path.wstring().c_str() );
    }

}
