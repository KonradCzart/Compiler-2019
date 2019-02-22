#include <iostream>
#include <cstdlib>
#include <cstring>

#include "driver.hpp"

int
main( const int argc, const char **argv )
{
   Compiler::CompilerDriver driver;
   driver.parse( argv[1] );
   driver.print( std::cout ) << "\n";

   return( EXIT_SUCCESS );
}
