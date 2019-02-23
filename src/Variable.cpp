#include <iostream>
#include "Variable.hpp"

SimpleVariable::SimpleVariable(std::string identifier){
    this->identifier = identifier;
}

void SimpleVariable::loadVariable(){
    std::cout << "Zwykła zmienna: " << identifier << std::endl;
}

ConstVariable::ConstVariable(long long value){
    this->value = value;
}

void ConstVariable::loadVariable(){
    std::cout << "Stała: " << value << std::endl;
}

ConstArrayVariable::ConstArrayVariable (std::string identifier, long long arrayIndex){
    this->identifier = identifier;
    this->arrayIndex = arrayIndex;
}

void ConstArrayVariable::loadVariable(){
    std::cout << "Tablica: " << identifier << " index " << arrayIndex << std::endl;
}

IdentifierArrayVariable::IdentifierArrayVariable (std::string identifier, VariablePointer arrayVariableIndex){
    this->identifier = identifier;
    this->arrayVariableIndex = arrayVariableIndex;
}

void IdentifierArrayVariable::loadVariable(){
    std::cout << "Tablica: " << identifier << " index ";
    arrayVariableIndex->loadVariable();
}
    

