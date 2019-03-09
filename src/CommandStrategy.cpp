#include "CommandStrategy.hpp"
#include <iostream>
#include <memory>
#include "AssemblerMenager.hpp"

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

void AssignCommandStrategy::compile(AssemblerMenager* assemblerMenager){
    if(!Variable::compere(resultVariable, assignVariable)){
        RegisterPointer registerAssign = assemblerMenager->getRegisterForVariable(assignVariable);
        RegisterPointer registerResult = assemblerMenager->getRegisterForVariableWithoutLoad(resultVariable);
        
        registerResult->setStore(true);
        std::vector<AssemblerCommand> assignCommands;
        assignCommands.push_back(AssemblerCommand(AssemblerInstruction::Copy, registerResult->getType(), registerAssign->getType()));

        assemblerMenager->insertAssemblerCommand(assignCommands);
        assemblerMenager->checkSpecyficVariableInRegister(registerResult);
        assemblerMenager->checkSpecyficVariableInRegister(registerAssign);
    }
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

void IOCommandStrategy::compile(AssemblerMenager* assemblerMenager){
    RegisterPointer registerResult;
    std::vector<AssemblerCommand> ioCommands;
    if(type == Type::READ){
        registerResult = assemblerMenager->getRegisterForVariableWithoutLoad(resultVariable);
        ioCommands.push_back(AssemblerCommand(AssemblerInstruction::Get, registerResult->getType()));
        registerResult->setStore(true);
    }
    else if(type == Type::WRITE){
        registerResult = assemblerMenager->getRegisterForVariable(resultVariable);
        ioCommands.push_back(AssemblerCommand(AssemblerInstruction::Put, registerResult->getType()));
    }
    assemblerMenager->insertAssemblerCommand(ioCommands);
    assemblerMenager->checkSpecyficVariableInRegister(registerResult);
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

void JumpCommandStrategy::compile(AssemblerMenager* assemblerMenager){
    assemblerMenager->insertAssemblerCommand(AssemblerCommand(AssemblerInstruction::Jump, label));
}

JumpConditionCommandStrategy::JumpConditionCommandStrategy(Type type, VariablePointer conditionVariable, std::string label){
    this->type = type;
    this->label = label;
    this->conditionVariable = conditionVariable;
}

CommandStrategyPointer JumpConditionCommandStrategy::create(Type type, VariablePointer conditionVariable, std::string label){
    return make_shared<JumpConditionCommandStrategy>(type, conditionVariable, label);
}

void JumpConditionCommandStrategy::generate(){
    if(type == Type::JODD){
        std::cout << "JODD " + conditionVariable -> print() + " " + label << std::endl;
    }
    else if(type == Type::JZERO){
        std::cout << "JZERO " + conditionVariable -> print() + " " + label << std::endl;
    }
}

void JumpConditionCommandStrategy::compile(AssemblerMenager* assemblerMenager){
    RegisterPointer registerCondition = assemblerMenager->getRegisterForVariable(conditionVariable);
    if(type == Type::JODD){
        assemblerMenager->insertAssemblerCommand(AssemblerCommand(AssemblerInstruction::Jodd, registerCondition->getType(), label));
    }
    else if(type == Type::JZERO){
        assemblerMenager->insertAssemblerCommand(AssemblerCommand(AssemblerInstruction::Jzero, registerCondition->getType(), label));
    }
    assemblerMenager->checkSpecyficVariableInRegister(registerCondition);
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

void IncDecCommandStrategy::compile(AssemblerMenager* assemblerMenager){ 
    RegisterPointer registerResult = assemblerMenager->getRegisterForVariable(resultVariable);
    registerResult->setStore(true);   
    if(type == Type::INC){
        assemblerMenager->insertAssemblerCommand(AssemblerCommand(AssemblerInstruction::Inc, registerResult->getType()));
    }
    else if(type == Type::DEC){
        assemblerMenager->insertAssemblerCommand(AssemblerCommand(AssemblerInstruction::Dec, registerResult->getType()));
    }
    assemblerMenager->checkSpecyficVariableInRegister(registerResult);
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

void CodeCommandStrategy::compile(AssemblerMenager* assemblerMenager){
    if(type == Type::HALT){
       assemblerMenager->insertAssemblerCommand(AssemblerCommand(AssemblerInstruction::Halt, label));
    }
    else if(type == Type::NEW_BLOCK){
       assemblerMenager->startNewBlock();
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

void LabelCommandStrategy::compile(AssemblerMenager* assemblerMenager){
    assemblerMenager->insertAssemblerCommand(AssemblerCommand(AssemblerInstruction::Label, label));
}