#include "MathCommandStrategy.hpp"
#include <iostream>
#include <memory>
#include "AssemblerMenager.hpp"

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

void AdditionCommandStrategy::compile(AssemblerMenager* assemblerMenager){
    RegisterPointer registerLeft = assemblerMenager->getRegisterForVariable(leftVariable);
    RegisterPointer registerRight = assemblerMenager->getRegisterForVariable(rightVariable);
    RegisterPointer registerResult = assemblerMenager->getRegisterForVariableWithoutLoad(resultVariable);
    
    registerResult->setStore(true);
    std::vector<AssemblerCommand> addAssemblerCommands;

    if(Variable::compere(resultVariable, leftVariable)){
        addAssemblerCommands.push_back(AssemblerCommand(AssemblerInstruction::Add, registerResult->getType(), registerRight->getType()));
    }
    else if(Variable::compere(resultVariable, rightVariable)){
        addAssemblerCommands.push_back(AssemblerCommand(AssemblerInstruction::Add, registerResult->getType(), registerLeft->getType()));
    }
    else{
       addAssemblerCommands.push_back(AssemblerCommand(AssemblerInstruction::Copy, registerResult->getType(), registerLeft->getType()));
       addAssemblerCommands.push_back(AssemblerCommand(AssemblerInstruction::Add, registerResult->getType(), registerRight->getType())); 
    }
    assemblerMenager->insertAssemblerCommand(addAssemblerCommands);

    assemblerMenager->checkSpecyficVariableInRegister(registerResult);
    assemblerMenager->checkSpecyficVariableInRegister(registerLeft);
    assemblerMenager->checkSpecyficVariableInRegister(registerRight);
}

SubtractionCommandStrategy::SubtractionCommandStrategy(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable)
    :MathCommandStrategy(resultVariable, leftVariable, rightVariable){ }

CommandStrategyPointer SubtractionCommandStrategy::create(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable){
    return make_shared<SubtractionCommandStrategy>(resultVariable, leftVariable, rightVariable);
}

void SubtractionCommandStrategy::generate(){
    std::cout << "SUB: " + resultVariable->print() + " " + leftVariable->print() + " " + rightVariable->print() << std::endl;
}

void SubtractionCommandStrategy::compile(AssemblerMenager* assemblerMenager){
    RegisterPointer registerLeft = assemblerMenager->getRegisterForVariable(leftVariable);
    RegisterPointer registerRight = assemblerMenager->getRegisterForVariable(rightVariable);
    RegisterPointer registerResult = assemblerMenager->getRegisterForVariableWithoutLoad(resultVariable);

    registerResult->setStore(true);
    std::vector<AssemblerCommand> subAssemblerCommands;

    if(Variable::compere(resultVariable, leftVariable)){
        subAssemblerCommands.push_back(AssemblerCommand(AssemblerInstruction::Sub, registerResult->getType(), registerRight->getType()));
    }
    else if(Variable::compere(resultVariable, rightVariable)){
        assemblerMenager->saveValueRegister(registerLeft);
        subAssemblerCommands.push_back(AssemblerCommand(AssemblerInstruction::Sub, registerLeft->getType(), registerResult->getType()));
        subAssemblerCommands.push_back(AssemblerCommand(AssemblerInstruction::Copy, registerResult->getType(), registerLeft->getType()));
        registerLeft->clearRegister();
    }
    else{
        subAssemblerCommands.push_back(AssemblerCommand(AssemblerInstruction::Copy, registerResult->getType(), registerLeft->getType()));
        subAssemblerCommands.push_back(AssemblerCommand(AssemblerInstruction::Sub, registerResult->getType(), registerRight->getType()));
    }
    assemblerMenager->insertAssemblerCommand(subAssemblerCommands);

    assemblerMenager->checkSpecyficVariableInRegister(registerResult);
    assemblerMenager->checkSpecyficVariableInRegister(registerLeft);
    assemblerMenager->checkSpecyficVariableInRegister(registerRight);
}

MultiplicationCommandStrategy::MultiplicationCommandStrategy(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable)
    :MathCommandStrategy(resultVariable, leftVariable, rightVariable){ }

CommandStrategyPointer MultiplicationCommandStrategy::create(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable){
    return make_shared<MultiplicationCommandStrategy>(resultVariable, leftVariable, rightVariable);
}

void MultiplicationCommandStrategy::generate(){
    std::cout << "MUL: " + resultVariable->print() + " " + leftVariable->print() + " " + rightVariable->print() << std::endl;
}

void MultiplicationCommandStrategy::compile(AssemblerMenager* assemblerMenager){
    RegisterPointer registerLeft = assemblerMenager->getRegisterForVariable(leftVariable);
    RegisterPointer registerRight = assemblerMenager->getDifferentRegisterForVariable(rightVariable, registerLeft);
    RegisterPointer registerResult = assemblerMenager->getDifferentRegisterForVariableWithoutLoad(resultVariable, registerLeft, registerRight);   

    registerResult->setStore(true);
    assemblerMenager->saveValueRegisterWithoutClear(registerLeft);
    assemblerMenager->saveValueRegisterWithoutClear(registerRight);

    std::vector<AssemblerCommand> mulAssemblerCommands = assemblerMenager->generateMultiplicationCommand(registerResult->getType(), registerLeft->getType(), registerRight->getType());
    assemblerMenager->insertAssemblerCommand(mulAssemblerCommands);
    registerLeft->clearRegister();
    registerRight->clearRegister();
}

DivisionCommandStrategy::DivisionCommandStrategy(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable)
    :MathCommandStrategy(resultVariable, leftVariable, rightVariable){ }

CommandStrategyPointer DivisionCommandStrategy::create(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable){
    return make_shared<DivisionCommandStrategy>(resultVariable, leftVariable, rightVariable);
}

void DivisionCommandStrategy::generate(){
    std::cout << "DIV: " + resultVariable->print() + " " + leftVariable->print() + " " + rightVariable->print() << std::endl;
}

void DivisionCommandStrategy::compile(AssemblerMenager* assemblerMenager){ 
    std::vector<AssemblerCommand> divAssemblerCommands;
    RegisterPointer registerResult;
    
    if(Variable::compere(leftVariable, rightVariable)){
        registerResult = assemblerMenager->getRegisterForVariableWithoutLoad(resultVariable);
        divAssemblerCommands = assemblerMenager->generateNumberInRegister(registerResult->getType(), 1);    
    }
    else{ 
        RegisterPointer registerLeft = assemblerMenager->getRegisterForVariable(leftVariable);
        RegisterPointer registerRight = assemblerMenager->getDifferentRegisterForVariable(rightVariable, registerLeft);
        registerResult = assemblerMenager->getDifferentRegisterForVariableWithoutLoad(resultVariable, registerLeft, registerRight);  
        
        assemblerMenager->saveValueRegisterWithoutClear(registerLeft);
        assemblerMenager->saveValueRegisterWithoutClear(registerRight);

        RegisterPointer firstHelpRegister = assemblerMenager->getFreeRegister();
        firstHelpRegister->setUsed(true);
        RegisterPointer secondHelpRegister = assemblerMenager->getFreeRegister();
        secondHelpRegister->setUsed(true);

        RegisterType resultType = registerResult->getType();
        RegisterType leftType = registerLeft->getType();
        RegisterType rightType = registerRight->getType();
        RegisterType firstHelpType = firstHelpRegister->getType();
        RegisterType secondHelpType = secondHelpRegister->getType();
        divAssemblerCommands = assemblerMenager->generateDivisionCommand(resultType, leftType, rightType, firstHelpType, secondHelpType, false);
    
        firstHelpRegister->clearRegister();
        secondHelpRegister->clearRegister();
        registerLeft->clearRegister();
        registerRight->clearRegister();
    }
    registerResult->setStore(true);
    
    assemblerMenager->insertAssemblerCommand(divAssemblerCommands);
    assemblerMenager->checkSpecyficVariableInRegister(registerResult);
}

ModuloCommandStrategy::ModuloCommandStrategy(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable)
    :MathCommandStrategy(resultVariable, leftVariable, rightVariable){ }

CommandStrategyPointer ModuloCommandStrategy::create(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable){
    return make_shared<ModuloCommandStrategy>(resultVariable, leftVariable, rightVariable);
}

void ModuloCommandStrategy::generate(){
    std::cout << "MOD: " + resultVariable->print() + " " + leftVariable->print() + " " + rightVariable->print() << std::endl;
}

void ModuloCommandStrategy::compile(AssemblerMenager* assemblerMenager){
    std::vector<AssemblerCommand> divAssemblerCommands;
    RegisterPointer registerResult;
    
    if(Variable::compere(leftVariable, rightVariable)){
        registerResult = assemblerMenager->getRegisterForVariableWithoutLoad(resultVariable);
        divAssemblerCommands = assemblerMenager->generateNumberInRegister(registerResult->getType(), 0);    
    }
    else{ 
        RegisterPointer registerLeft = assemblerMenager->getRegisterForVariable(leftVariable);
        RegisterPointer registerRight = assemblerMenager->getDifferentRegisterForVariable(rightVariable, registerLeft);
        registerResult = assemblerMenager->getDifferentRegisterForVariableWithoutLoad(resultVariable, registerLeft, registerRight);  
        
        assemblerMenager->saveValueRegisterWithoutClear(registerLeft);
        assemblerMenager->saveValueRegisterWithoutClear(registerRight);

        RegisterPointer firstHelpRegister = assemblerMenager->getFreeRegister();
        firstHelpRegister->setUsed(true);
        RegisterPointer secondHelpRegister = assemblerMenager->getFreeRegister();
        secondHelpRegister->setUsed(true);


        RegisterType resultType = registerResult->getType();
        RegisterType leftType = registerLeft->getType();
        RegisterType rightType = registerRight->getType();
        RegisterType firstHelpType = firstHelpRegister->getType();
        RegisterType secondHelpType = secondHelpRegister->getType();
        divAssemblerCommands = assemblerMenager->generateDivisionCommand(resultType, leftType, rightType, firstHelpType, secondHelpType, true);
    
        firstHelpRegister->clearRegister();
        secondHelpRegister->clearRegister();
        registerLeft->clearRegister();
        registerRight->clearRegister();
    }
    registerResult->setStore(true);
    
    assemblerMenager->insertAssemblerCommand(divAssemblerCommands);
    assemblerMenager->checkSpecyficVariableInRegister(registerResult);    
}