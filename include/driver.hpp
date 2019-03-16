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
   CompilerDriver();
   friend class Parser;
   friend class Scanner;
   virtual ~CompilerDriver();

   void parse( const char * const filename );
   void parse( std::istream &iss );
   std::ostream& print(std::ostream &stream);

   bool isFinishReadFile();
   void compaile();
   
   void declare(std::string identifier);
   void declareArray(std::string identifier, long long firstIndex, long long lastIndex);

   VariablePointer getDeclaredVariable(std::string identifier);
   VariablePointer getDeclaredArray(std::string identifier, long long index);
   VariablePointer getDeclaredArray(std::string identifier, VariablePointer variableIndex); 
   VariablePointer getIterator(std::string identifier);
   VariablePointer getCounter(std::string identifier);

   void initialize(VariablePointer variable);
   void checkInitialized(VariablePointer variable);
   void checkModificationIterator(VariablePointer iterator);
   void validateAndPushIterator(std::string identifier);

private:
   void parse_helper( std::istream &stream );

   Compiler::Parser  *parser  = nullptr;
   Compiler::Scanner *scanner = nullptr;
   CommandMenager commandMenager;
   MemoryTable* memory = MemoryTable::getInstance();
   AssemblerMenager *assemblerMenager;
   bool finishReadFile = false;

   bool isCorrectDeclaredArray(std::string identifier);
};

}
#endif