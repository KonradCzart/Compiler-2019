#include <iostream>
#include <cstdlib>
#include <cstring>

#include "MemoryTable.hpp"
#include "Variable.hpp"

int
main( const int argc, const char **argv ){
   MemoryTable* table = MemoryTable::getInstance();
   table->declare("a");
   table->declare("b");
   table->declareArray("tab", 5, 10);
   table->declare("c");

   table->printAllMemory();

   MemoryTable* table2 = MemoryTable::getInstance();
   table2->declare("g");
   table2->printAllMemory();

   VariablePointer var1 = std::make_shared<SimpleVariable>("a");
   VariablePointer var2 = std::make_shared<ConstVariable>(50);

   var1->loadVariable();
   var2->loadVariable();
}
