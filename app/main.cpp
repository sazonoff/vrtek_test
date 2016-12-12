// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


#include "Application/Application.h"

#include "Utils/Runtime/Runtime.h"


int main( int argc, char *argv[] )
{
    (void)(argc, argv);

    utils::Runtime::setCurrentDir();

    app::Application app;

    if ( app.init() )
    {
        app.run();
    }

    std::cout << std::endl << "Press any key to exit app..." << std::endl;
    system( "pause >nul" );
    return 0;
}
