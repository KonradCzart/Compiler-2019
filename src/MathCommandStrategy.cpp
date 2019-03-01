#include "MathCommandStrategy.hpp"
#include <iostream>
#include <memory>

MathCommandStrategy::MathCommandStrategy(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable){
    this->resultVariable = resultVariable;
    this->leftVariable = leftVariable;
    this->rightVariable = rightVariable;
}

AdditionCommandStrategy::AdditionCommandStrategy(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable)
    :MathCommandStrategy(resultVariable, leftVariable, rightVariable){ }

CommandStrategyPointer AdditionCommandStrategy::create(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable){
    return make_shared<AdditionCommandStrategy>(resultVariable, leftVariable, rightVariable);
}

void AdditionCommandStrategy::generate(){
    std::cout << "ADD: " + resultVariable->print() + " " + leftVariable->print() + " " + rightVariable->print() << std::endl;
}

SubtractionCommandStrategy::SubtractionCommandStrategy(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable)
    :MathCommandStrategy(resultVariable, leftVariable, rightVariable){ }

CommandStrategyPointer SubtractionCommandStrategy::create(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable){
    return make_shared<SubtractionCommandStrategy>(resultVariable, leftVariable, rightVariable);
}

void SubtractionCommandStrategy::generate(){
    std::cout << "SUB: " + resultVariable->print() + " " + leftVariable->print() + " " + rightVariable->print() << std::endl;
}

MultiplicationCommandStrategy::MultiplicationCommandStrategy(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable)
    :MathCommandStrategy(resultVariable, leftVariable, rightVariable){ }

CommandStrategyPointer MultiplicationCommandStrategy::create(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable){
    return make_shared<MultiplicationCommandStrategy>(resultVariable, leftVariable, rightVariable);
}

void MultiplicationCommandStrategy::generate(){
    std::cout << "MUL: " + resultVariable->print() + " " + leftVariable->print() + " " + rightVariable->print() << std::endl;
}

DivisionCommandStrategy::DivisionCommandStrategy(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable)
    :MathCommandStrategy(resultVariable, leftVariable, rightVariable){ }

CommandStrategyPointer DivisionCommandStrategy::create(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable){
    return make_shared<DivisionCommandStrategy>(resultVariable, leftVariable, rightVariable);
}

void DivisionCommandStrategy::generate(){
    std::cout << "DIV: " + resultVariable->print() + " " + leftVariable->print() + " " + rightVariable->print() << std::endl;
}

ModuloCommandStrategy::ModuloCommandStrategy(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable)
    :MathCommandStrategy(resultVariable, leftVariable, rightVariable){ }

CommandStrategyPointer ModuloCommandStrategy::create(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable){
    return make_shared<ModuloCommandStrategy>(resultVariable, leftVariable, rightVariable);
}

void ModuloCommandStrategy::generate(){
    std::cout << "MOD: " + resultVariable->print() + " " + leftVariable->print() + " " + rightVariable->print() << std::endl;
}