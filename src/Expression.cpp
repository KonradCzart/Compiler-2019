#include "Expression.hpp"
#include <iostream>
#include "CommandStrategy.hpp"
#include "MathCommandStrategy.hpp"

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

Command Expression::createCommand(VariablePointer resultVariable){
    CommandStrategyPointer commandTypeStrategy;
    switch (type) {
        case EMPTY: 
                commandTypeStrategy = AssignCommandStrategy::create(resultVariable, leftVariable);
            break; 
        case ADDITION:
                commandTypeStrategy = AdditionCommandStrategy::create(resultVariable, leftVariable, rightVariable);
            break;
        case MULTIPLICATION:
                commandTypeStrategy = MultiplicationCommandStrategy::create(resultVariable, leftVariable, rightVariable);
            break;
        case SUBTRACTION:
                commandTypeStrategy = SubtractionCommandStrategy::create(resultVariable, leftVariable, rightVariable);
            break;
        case DIVISION:
                commandTypeStrategy = DivisionCommandStrategy::create(resultVariable, leftVariable, rightVariable);
            break;
        case MODULO:
                commandTypeStrategy = ModuloCommandStrategy::create(resultVariable, leftVariable, rightVariable);
            break;    
    }
    return Command(commandTypeStrategy);
}