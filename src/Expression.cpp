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
            symbolType =  " add ";
            break;
        case MULTIPLICATION:
            symbolType =  " mul ";
            break;
        case SUBTRACTION:
            symbolType =  " sub ";
            break;
        case DIVISION:
            symbolType =  " div ";
            break;
        case MODULO:
            symbolType =  " mod ";
            break;
        case EMPTY:
            symbolType =  " mod ";
            break;
    }

    leftVariable -> print();
    std::cout << symbolType;
    rightVariable -> print();
    std::cout << std::endl;
}