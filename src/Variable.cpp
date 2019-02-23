#include <iostream>
#include "Variable.hpp"

SimpleVariable::SimpleVariable(std::string identifier){
    this->identifier = identifier;
}

void SimpleVariable::loadVariable(){
    std::cout << "Zwykła zmienna: " << identifier << std::endl;
}

void SimpleVariable::print(){
    std::cout << identifier;
}

ConstVariable::ConstVariable(long long value){
    this->value = value;
}

void ConstVariable::loadVariable(){
    std::cout << "Stała: " << value << std::endl;
}

void ConstVariable::print(){
    std::cout << value;
}

ConstArrayVariable::ConstArrayVariable (std::string identifier, long long arrayIndex){
    this->identifier = identifier;
    this->arrayIndex = arrayIndex;
}

void ConstArrayVariable::loadVariable(){
    std::cout << "Tablica: " << identifier << " index " << arrayIndex << std::endl;
}

void ConstArrayVariable::print(){
    std::cout << identifier << "(" << arrayIndex << ")";
}

IdentifierArrayVariable::IdentifierArrayVariable (std::string identifier, VariablePointer arrayVariableIndex){
    this->identifier = identifier;
    this->arrayVariableIndex = arrayVariableIndex;
}

void IdentifierArrayVariable::loadVariable(){
    std::cout << "Tablica: " << identifier << " index ";
    arrayVariableIndex->loadVariable();
}

void IdentifierArrayVariable::print(){
    std::cout << identifier << "(";
    arrayVariableIndex->print();
    std::cout << ')';
}


