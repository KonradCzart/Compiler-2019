#include "Expression.hpp"
#include <iostream>

Expression::Expression() {}

Expression::Expression(Expression::Type type, VariablePointer leftVariable, VariablePointer rightVariable) {
    this->type = type;
    this->leftVariable = leftVariable;
    this->rightVariable = rightVariable;
}

VariablePointer Expression::getLeftVariable() {
    return leftVariable;
}

VariablePointer Expression::getRightVariable() {
    return rightVariable;
}

Expression::Type Expression::getType() {
    return type;
}

void Expression::print(){
    std::string symbolType = " ";
    switch (type) {
        case ADDITION:
            symbolType =  "ADD ";
            break;
        case MULTIPLICATION:
            symbolType =  "MUL ";
            break;
        case SUBTRACTION:
            symbolType =  "SUB ";
            break;
        case DIVISION:
            symbolType =  "DIV ";
            break;
        case MODULO:
            symbolType =  "MOD ";
            break;
        case EMPTY:
            symbolType =  "";
            break;
    }

    symbolType = symbolType + leftVariable -> print() + " " + rightVariable -> print();
    std::cout << symbolType << std::endl;
}