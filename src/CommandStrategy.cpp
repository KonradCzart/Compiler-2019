#include "CommandStrategy.hpp"
#include <iostream>
#include <memory>

AssignCommandStrategy::AssignCommandStrategy(VariablePointer resultVariable, VariablePointer assignVariable){
    this->resultVariable = resultVariable;
    this->assignVariable = assignVariable;
}

CommandStrategyPointer AssignCommandStrategy::create(VariablePointer resultVariable, VariablePointer assignVariable){
    return make_shared<AssignCommandStrategy>(resultVariable, assignVariable);
}

void AssignCommandStrategy::generate(){
    std::cout << "ASSIGN: " + resultVariable->print() + " " + assignVariable->print() << std::endl;
}

IOCommandStrategy::IOCommandStrategy(Type type, VariablePointer resultVariable){
    this->resultVariable = resultVariable;
    this->type = type;
}

CommandStrategyPointer IOCommandStrategy::create(Type type, VariablePointer resultVariable){
    return make_shared<IOCommandStrategy>(type, resultVariable);
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

CommandStrategyPointer JumpCommandStrategy::create(std::string label){
    return make_shared<JumpCommandStrategy>(label);
}

void JumpCommandStrategy::generate(){
    std::cout << "JUMP " + label << std::endl;
}

JumpConditionCommandStrategy::JumpConditionCommandStrategy(Type type, VariablePointer conditionVariable, std::string label){
    this->type = type;
    this->label = label;
    this->conditionVariable = conditionVariable;
}

CommandStrategyPointer JumpConditionCommandStrategy::create(Type type, VariablePointer conditionVariable, std::string label){
    return make_shared<JumpConditionCommandStrategy>(type, label, conditionVariable);
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

CommandStrategyPointer IncDecCommandStrategy::create(Type type, VariablePointer resultVariable){
    return make_shared<IncDecCommandStrategy>(type, resultVariable);
}

void IncDecCommandStrategy::generate(){
    if(type == Type::INC){
        std::cout << "INC " + resultVariable -> print() << std::endl;
    }
    else if(type == Type::DEC){
        std::cout << "DEC " + resultVariable -> print() << std::endl;
    }
}

CodeCommandStrategy::CodeCommandStrategy(Type type, std::string label){
    this->type = type;
    this->label = label;
}

CommandStrategyPointer CodeCommandStrategy::create(Type type, std::string label){
    return make_shared<CodeCommandStrategy>(type, label);
}

void CodeCommandStrategy::generate(){
    if(type == Type::HALT){
        std::cout << "HALT " + label << std::endl;
    }
    else if(type == Type::NEW_BLOCK){
        std::cout << "NEW_BLOCK " + label << std::endl;
    }
}

LabelCommandStrategy::LabelCommandStrategy(std::string label){
    this->label = label;
}

CommandStrategyPointer LabelCommandStrategy::create(std::string label){
    return make_shared<LabelCommandStrategy>(label);
}

void LabelCommandStrategy::generate(){
    std::cout << "LABEL " + label << std::endl;
}