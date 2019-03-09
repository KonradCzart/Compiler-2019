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


void test(){ 
   MemoryTable* memory = MemoryTable::getInstance();
   memory -> declare("abc");
   memory -> declareArray("tab", 5, 10);
   VariablePointer var = std::make_shared<SimpleVariable>("abc");
   VariablePointer var2 = std::make_shared<ConstVariable>(50); 
   VariablePointer result = std::make_shared<SimpleVariable>("abc"); 

   VariablePointer varTab = std::make_shared<ConstArrayVariable>("tab", 8);

   AssemblerCommand abc (AssemblerInstruction::Add, RegisterType::B, RegisterType::C);
   std::cout << abc;

   AssemblerMenager menagerAsm;
   menagerAsm.startNewBlock();
   auto reg2 = var2 -> loadVariable(&menagerAsm);
   reg2->setVariable(var2);
   auto reg = var -> loadVariable(&menagerAsm);
   reg->setVariable(var);
   auto reg4 = varTab -> loadVariable(&menagerAsm);
   reg4->setVariable(varTab);

   std::ofstream fout("wynik");
   menagerAsm.printCompiledCode(fout);

}

void test2(){
   MemoryTable* memory = MemoryTable::getInstance();
   memory -> declare("a");
   memory -> declare("b");
   memory -> declare("c");
   CommandBlock block;
   VariablePointer varA = std::make_shared<SimpleVariable>("a");
   VariablePointer varB = std::make_shared<SimpleVariable>("b");
   VariablePointer varC = std::make_shared<SimpleVariable>("c");
   block.addCommandToEnd(Command(SubtractionCommandStrategy::create(varA, varB, varA)));

   AssemblerMenager menagerAsm (block);
   menagerAsm.compileAll();
   std::ofstream fout("wynik");
   menagerAsm.printCompiledCode(fout);

}