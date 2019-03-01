#include <iostream>
#include <cstdlib>
#include <cstring>

#include "driver.hpp"
#include "Command.hpp"
#include "Variable.hpp"
#include "CommandStrategy.hpp"
#include "MathCommandStrategy.hpp"

#include <vector>
void test();



int
main( const int argc, const char **argv )
{
   std::vector<int> a;
   a.push_back(51);
   a.push_back(48);

   std::vector<int> b = a;
   a.push_back(10);
      for (int i=0; i<b.size(); i++) 
       cout << b[i] << " "; 


   Compiler::CompilerDriver driver;
   driver.parse( argv[1] );
   driver.print( std::cout ) << "\n";

   test();
   
   return( EXIT_SUCCESS );
}


void test(){
   VariablePointer var = std::make_shared<SimpleVariable>("abc");
   VariablePointer var2 = std::make_shared<ConstVariable>(50); 
   VariablePointer result = std::make_shared<SimpleVariable>("result"); 

   CommandStrategyPointer gen = std::make_shared<AdditionCommandStrategy>(result, var, var2);
   Command comm(gen);
   gen = std::make_shared<SimpleCommandStrategy>(SimpleCommandStrategy::Type::LABEL, "aaa");
   Command comm2(gen);
      gen = std::make_shared<SimpleCommandStrategy>(SimpleCommandStrategy::Type::HALT, "aadda");
   Command comm3(gen);
      gen = std::make_shared<SimpleCommandStrategy>(SimpleCommandStrategy::Type::NEW_BLOCK, "aadsa");
   Command comm4(AssignCommandStrategy::create(result, var));

   comm4.generate();
}