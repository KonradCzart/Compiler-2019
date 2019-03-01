#include "Condition.hpp"
#include <iostream>


Condition::Condition() {}

Condition::Condition(Condition::Type type, VariablePointer leftVariable, VariablePointer rightVariable) {
    this->type = type;
    this->leftVariable = leftVariable;
    this->rightVariable = rightVariable;
}

CommandBlock Condition::createCommandBlock(std::string labelJump){
    CommandBlock block;

    switch (type){
        case EQUAL:

            break;
        case NOT_EQUAL:

            break;
        case GREATER:

            break;
        case LESSER:

            break;
        case GREATER_EQUAL:

            break;
        case LESSER_EQUAL:

            break;
        default:

            break;
    }

    return block;    
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

    symbolType = leftVariable -> print() + symbolType + rightVariable -> print();
    std::cout << symbolType << std::endl;

}
