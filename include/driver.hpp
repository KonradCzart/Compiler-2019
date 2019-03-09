#ifndef __COMPILERDRIVER__
#define __COMPILERDRIVER__ 1

#include <string>
#include <cstddef>
#include <istream>

#include "scanner.hpp"
#include "parser.tab.hh"
#include "Variable.hpp"
#include "MemoryTable.hpp"
#include "CommandMenager.hpp"
#include "AssemblerMenager.hpp"

namespace Compiler{

class CompilerDriver{
public:
   CompilerDriver() = default;
   friend class Parser;
   friend class Scanner;
   bool compiled = false;
   virtual ~CompilerDriver();

   void parse( const char * const filename );
   void parse( std::istream &iss );
   std::ostream& print(std::ostream &stream);

   bool isFinishReadFile();
   void compaile();
   

private:
   void parse_helper( std::istream &stream );

   Compiler::Parser  *parser  = nullptr;
   Compiler::Scanner *scanner = nullptr;
   CommandMenager commandMenager;
   MemoryTable* memory = MemoryTable::getInstance();
   AssemblerMenager *assemblerMenager;
   bool finishReadFile = false;
};

}
#endif