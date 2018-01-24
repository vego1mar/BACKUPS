#pragma region Headers includes
#include "CNN.hpp"
#include "Logger.hpp"
#include "GNUCompilersPatches.hpp"
#include <chrono>
#pragma endregion

/*
 * Default project command arguments:
 * $(TargetPath) Data\\Test.txt 1> Logs\\stdout.txt 2> Logs\\stderr.txt
 *
 * For compiling under GNU MinGW or Cygwin:
 * (1) Use -std==c++11 or -std=c++0x compiler option feature to enable ISO C++ usage.
 * (2) Use -Wunknown-pragmas compiler option to decrease its verbosity in terms of #pragma region's.
 *
 */

int main( int argc, char * argv[] )
{
    auto timeOfStart = std::chrono::high_resolution_clock::now();

    if ( argc > 1 ) {
        pg::CNN::GetCNNSet( argv[argc - 1] );
    }
    else {
        pg::Logger::WriteLineToStdErr( "No file name argument found." );
    }

    auto timeOfEnd = std::chrono::high_resolution_clock::now();
    auto timeResultMilis = std::chrono::duration_cast<std::chrono::milliseconds>(timeOfEnd - timeOfStart).count();
    auto timeResultString = gnu::to_string( timeResultMilis );
    pg::Logger::WriteLineToStdOut( "Program finished after " + timeResultString + " ms." );
    return 0;
}
