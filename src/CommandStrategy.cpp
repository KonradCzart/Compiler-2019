#include "CommandStrategy.hpp"
#include <iostream>

AssignCommandStrategy::AssignCommandStrategy(VariablePointer resultVariable, VariablePointer assignVariable){
    this->resultVariable = resultVariable;
    this->assignVariable = assignVariable;
}

void AssignCommandStrategy::generate(){
    std::cout << "ASSIGN: " + resultVariable->print() + " " + assignVariable->print() << std::endl;
}

MathCommandStrategy::MathCommandStrategy(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable){
    this->resultVariable = resultVariable;
    this->leftVariable = leftVariable;
    this->rightVariable = rightVariable;
}

AdditionCommandStrategy::AdditionCommandStrategy(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable)
    :MathCommandStrategy(resultVariable, leftVariable, rightVariable){ }

void AdditionCommandStrategy::generate(){
    std::cout << "ADD: " + resultVariable->print() + " " + leftVariable->print() + " " + rightVariable->print() << std::endl;
}

SubtractionCommandStrategy::SubtractionCommandStrategy(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable)
    :MathCommandStrategy(resultVariable, leftVariable, rightVariable){ }

void SubtractionCommandStrategy::generate(){
    std::cout << "SUB: " + resultVariable->print() + " " + leftVariable->print() + " " + rightVariable->print() << std::endl;
}

MultiplicationCommandStrategy::MultiplicationCommandStrategy(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable)
    :MathCommandStrategy(resultVariable, leftVariable, rightVariable){ }

void MultiplicationCommandStrategy::generate(){
    std::cout << "MUL: " + resultVariable->print() + " " + leftVariable->print() + " " + rightVariable->print() << std::endl;
}

ModuloCommandStrategy::ModuloCommandStrategy(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable)
    :MathCommandStrategy(resultVariable, leftVariable, rightVariable){ }

void ModuloCommandStrategy::generate(){
    std::cout << "MOD: " + resultVariable->print() + " " + leftVariable->print() + " " + rightVariable->print() << std::endl;
}

IOCommandStrategy::IOCommandStrategy(Type type, VariablePointer resultVariable){
    this->resultVariable = resultVariable;
    this->type = type;
}

void IOCommandStrategy::generate(){
    if(type == Type::READ){
        std::cout << "READ " + resultVariable -> print() << std::endl;
    }
    else if(type == Type::WRITE){
        std::cout << "WRITE " + resultVariable -> print() << std::endl;
    }
}

JumpCommandStrategy::JumpCommandStrategy(std::string label){
    this->label = label;
}

void JumpCommandStrategy::generate(){
    std::cout << "JUMP " + label << std::endl;
}

JumpConditionCommandStrategy::JumpConditionCommandStrategy(Type type, std::string label, VariablePointer conditionVariable){
    this->type = type;
    this->label = label;
    this->conditionVariable = conditionVariable;
}

void JumpConditionCommandStrategy::generate(){
    if(type == Type::JODD){
        std::cout << "JODD " + conditionVariable -> print() << std::endl;
    }
    else if(type == Type::JZERO){
        std::cout << "JZERO " + conditionVariable -> print() << std::endl;
    }
}

IncDecCommandStrategy::IncDecCommandStrategy(Type type, VariablePointer resultVariable){
    this->type = type;
    this->resultVariable = resultVariable;
}

void IncDecCommandStrategy::generate(){
    if(type == Type::INC){
        std::cout << "INC " + resultVariable -> print() << std::endl;
    }
    else if(type == Type::DEC){
        std::cout << "DEC " + resultVariable -> print() << std::endl;
    }
}

SimpleCommandStrategy::SimpleCommandStrategy(Type type, std::string label){
    this->type = type;
    this->label = label;
}

void SimpleCommandStrategy::generate(){
    if(type == Type::HALT){
        std::cout << "HALT " + label << std::endl;
    }
    else if(type == Type::NEW_BLOCK){
        std::cout << "NEW_BLOCK " + label << std::endl;
    }
    else if(type == Type::LABEL){
        std::cout << "LABEL " + label << std::endl;
    }
}

