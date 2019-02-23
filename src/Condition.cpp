#include "Condition.hpp"
#include <iostream>


Condition::Condition() {}

Condition::Condition(Condition::Type type, VariablePointer leftVariable, VariablePointer rightVariable) {
    this->type = type;
    this->leftVariable = leftVariable;
    this->rightVariable = rightVariable;
}

void Condition::print(){
    std::string symbolType;
    switch (type) {
        case EQUAL:
            symbolType =  " == ";
            break;
        case NOT_EQUAL:
            symbolType =  " != ";
            break;
        case GREATER:
            symbolType =  " > ";
            break;
        case LESSER:
            symbolType =  " < ";
            break;
        case GREATER_EQUAL:
            symbolType =  " >= ";
            break;
        case LESSER_EQUAL:
            symbolType =  " <= ";
            break;
        default:
            symbolType = " ";
            break;
    }

    leftVariable -> print();
    std::cout << symbolType;
    rightVariable -> print();
    std::cout << std::endl;

}
