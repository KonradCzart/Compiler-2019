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
   VariablePointer result = std::make_shared<SimpleVariable>("abc"); 

   VariablePointer varG = var;

   if(varG == var){
      std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAaa";
   }
   if(Variable::compere(var, result)){
      std::cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
   }

}