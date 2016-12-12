// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


#include "Application/Application.h"

#include "Utils/Runtime/Runtime.h"


int main( int argc, char *argv[] )
{
    (void)(argc, argv);

    utils::Runtime::setCurrentDir();
    std::cout << std::endl << "Press any key to exit..." << std::endl;

    app::Application app;

    if ( app.init() )
    {
        app.run();
    }

    system( "pause >nul" );
    return 0;
}
