#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>

#include "driver.hpp"
#include "Command.hpp"
#include "Variable.hpp"
#include "CommandStrategy.hpp"
#include "MathCommandStrategy.hpp"
#include "AssemblerCommand.hpp"
#include "AssemblerMenager.hpp"

#include <vector>
void test();
void test2();


int
main( const int argc, const char **argv ){
   Compiler::CompilerDriver driver;
   driver.parse( argv[1] );
   if(driver.isFinishReadFile()){
      driver.compaile();
      std::ofstream fout(argv[2]);
      driver.print( fout );
      fout.close();
   }
   return( EXIT_SUCCESS );
}
