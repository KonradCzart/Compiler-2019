#include "AssemblerMenager.hpp"

AssemblerMenager::AssemblerMenager(CommandBlock block){
    blockToCompile = block;
}

void AssemblerMenager::compileAll(){

}

std::ostream& AssemblerMenager::printCompiledCode(std::ostream &stream){
    for(auto com : commands){
        stream << com << std::endl;
    }
    registerMenager.printRegisterAll();
    return(stream);
}

std::vector<AssemblerCommand> AssemblerMenager::generateNumberInRegister(RegisterType registerType, long long n){
    std::vector<AssemblerCommand> generateCommand;
    while(n != 0){
        if(n <= 5){
        generateCommand.insert(generateCommand.begin(), AssemblerCommand(AssemblerInstruction::Inc, registerType));
        n--;
        }
        else if(n%2 == 0){
        generateCommand.insert(generateCommand.begin(), AssemblerCommand(AssemblerInstruction::Add, registerType, registerType));
        n = n/2;
        }
        else{
        generateCommand.insert(generateCommand.begin(), AssemblerCommand(AssemblerInstruction::Inc, registerType));
        n--;
        }
    }
    generateCommand.insert(generateCommand.begin(), AssemblerCommand(AssemblerInstruction::Sub, registerType, registerType));
    return generateCommand;
}

std::vector<AssemblerCommand> AssemblerMenager::generateAddress(long long address){
    AddressRegisterPointer addressRegister = registerMenager.getAddressRegister();
    RegisterType assemblerRegister = addressRegister -> getType();
    std::vector<AssemblerCommand> generateCommand;

    if(addressRegister -> getValue() == addressRegister -> UNKNOW_VALUE){
      generateCommand = generateNumberInRegister(assemblerRegister, address);
    }
    else{
      long long difference = address - addressRegister -> getValue();
      if(difference > 0){
        if(difference <= addressRegister -> MAX_DIFFERENCE){
          for(int i=0; i < difference; i++){
            generateCommand.push_back(AssemblerCommand(AssemblerInstruction::Inc, assemblerRegister));
          }
        }
        else{
          generateCommand = generateNumberInRegister(assemblerRegister, address);
        }
      }
      else if(difference < 0){
        difference = (-1) * difference;
        if(difference <= addressRegister -> MAX_DIFFERENCE){
          for(int i=0; i < difference; i++){
            generateCommand.push_back(AssemblerCommand(AssemblerInstruction::Dec, assemblerRegister));
          }
        }
        else{
          generateCommand = generateNumberInRegister(assemblerRegister, address);
        }
      }
    }
    addressRegister -> setValue(address);
    return generateCommand;
}

RegisterPointer AssemblerMenager::getRegisterForVariable(VariablePointer variable){
    RegisterPointer free = registerMenager.variableInRegister(variable);
    //lastReadRegister = RegisterType::X;
    if(free -> getType() != RegisterType::X){
        //lastReadRegister = free;
        return free;
    }
    free = variable->loadVariable(this);
    return free;
}

RegisterPointer AssemblerMenager::getRegisterForVariableWithoutLoad(VariablePointer variable){
    RegisterPointer free = registerMenager.variableInRegister(variable);
    return free;
}

RegisterPointer AssemblerMenager::getFreeRegister(){
    RegisterPointer freeRegister = registerMenager.getFreeRegister();
    if(freeRegister -> getType() != RegisterType::X)
        return freeRegister;

    freeRegister = registerMenager.getLastUsedRegister();
    saveValueRegister(freeRegister);
    return freeRegister;
}

void AssemblerMenager::saveValueRegister(RegisterPointer register){

}

AddressRegisterPointer AssemblerMenager::getAddressRegister(){
  return registerMenager.getAddressRegister();
}

void AssemblerMenager::startNewBlock(){

}

void AssemblerMenager::clearRegister(){

}

void AssemblerMenager::insertAssemblerCommand(std::vector<AssemblerCommand>& asmCommands){
    commands.insert(commands.end(), asmCommands.begin(), asmCommands.end());
}