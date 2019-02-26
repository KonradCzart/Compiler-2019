#include <iostream>
#include "Variable.hpp"
#include <sstream>


SimpleVariable::SimpleVariable(std::string identifier){
    this->identifier = identifier;
}

void SimpleVariable::loadVariable(){
    std::cout << "Zwykła zmienna: " << identifier << std::endl;
}

std::string SimpleVariable::print(){
    return identifier;
}

ConstVariable::ConstVariable(long long value){
    this->value = value;
}

void ConstVariable::loadVariable(){
    std::cout << "Stała: " << value << std::endl;
}

std::string ConstVariable::print(){
    std::stringstream tmp;
    tmp << value;
    return tmp.str();
}


ConstArrayVariable::ConstArrayVariable (std::string identifier, long long arrayIndex){
    this->identifier = identifier;
    this->arrayIndex = arrayIndex;
}

void ConstArrayVariable::loadVariable(){
    std::cout << "Tablica: " << identifier << " index " << arrayIndex << std::endl;
}

std::string ConstArrayVariable::print(){
    std::stringstream tmp;
    tmp << arrayIndex;
    return identifier + "[" + tmp.str() + "]";
}

IdentifierArrayVariable::IdentifierArrayVariable (std::string identifier, VariablePointer arrayVariableIndex){
    this->identifier = identifier;
    this->arrayVariableIndex = arrayVariableIndex;
}

void IdentifierArrayVariable::loadVariable(){
    std::cout << "Tablica: " << identifier << " index ";
    arrayVariableIndex->loadVariable();
}

std::string IdentifierArrayVariable::print(){
    return identifier + "[" + arrayVariableIndex->print() + "]";
}


