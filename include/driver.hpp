#ifndef __COMPILERDRIVER__
#define __COMPILERDRIVER__ 1

#include <string>
#include <cstddef>
#include <istream>

#include "scanner.hpp"
#include "parser.tab.hh"
#include "Variable.hpp"
#include "MemoryTable.hpp"

namespace Compiler{

class CompilerDriver{
public:
   CompilerDriver() = default;

   virtual ~CompilerDriver();

   void parse( const char * const filename );
   void parse( std::istream &iss );
   std::ostream& print(std::ostream &stream);

private:
   void parse_helper( std::istream &stream );

   Compiler::Parser  *parser  = nullptr;
   Compiler::Scanner *scanner = nullptr;
};

}
#endif