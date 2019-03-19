#include <sstream>
#include "AssemblerMenager.hpp"
#include <string.h>
#include <map>

AssemblerMenager::AssemblerMenager(CommandBlock block){
    blockToCompile = block;
}

void AssemblerMenager::setCommandBlock(CommandBlock block){
  blockToCompile = block;
}

void AssemblerMenager::compileAll(){
    auto commandsToCompile = blockToCompile.getCommands();
    for(auto command : commandsToCompile){
      command.compile(this);
    }
    convertLabelToNumber();
}

std::ostream& AssemblerMenager::printCompiledCode(std::ostream &stream){
    for(auto com : commands){
        stream << com << std::endl;
    }
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
    if(free -> getType() != RegisterType::X){
        return free;
    }
    free = variable->loadVariable(this);
    free -> setVariable(variable);
    return free;
}

RegisterPointer AssemblerMenager::getRegisterForVariableWithoutLoad(VariablePointer variable){
    RegisterPointer free = registerMenager.variableInRegister(variable);
    if(free -> getType() != RegisterType::X){
        return free;
    }
    free = getFreeRegister();
    free -> setVariable(variable);
    return free;
}

RegisterPointer AssemblerMenager::getDifferentRegisterForVariable(VariablePointer variable, RegisterPointer diffrentRegister){
    RegisterPointer free = registerMenager.variableInRegister(variable);
    if(free->getType() == diffrentRegister->getType() && free -> getType() != RegisterType::X){
        RegisterPointer newFreeRegister = getFreeRegister();
        commands.push_back(AssemblerCommand(AssemblerInstruction::Copy, newFreeRegister->getType(), free->getType()));
        newFreeRegister->setVariable(variable);
        return newFreeRegister;
    }
    if(free -> getType() != RegisterType::X){
        return free;
    }
    free = variable->loadVariable(this);
    free -> setVariable(variable);
    return free;
}

RegisterPointer AssemblerMenager::getDifferentRegisterForVariableWithoutLoad(VariablePointer variable, RegisterPointer firstRegister, RegisterPointer secondRegister){
    RegisterPointer free = registerMenager.variableInRegister(variable);
    RegisterType freeType = free->getType();
    if(freeType != RegisterType::X && freeType != firstRegister->getType() && freeType != secondRegister->getType()){
        return free;
    }
    free = getFreeRegister();
    free->setVariable(variable);
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

void AssemblerMenager::saveValueRegister(RegisterPointer saveRegister){
  saveValueRegisterWithoutClear(saveRegister);
  saveRegister->clearRegister();
}
void AssemblerMenager::saveValueRegisterWithoutClear(RegisterPointer saveRegister){
  if(saveRegister->isStore()){
    VariablePointer variable = saveRegister->getVariable();
    variable->storeVariable(this, saveRegister);
  }
}

AddressRegisterPointer AssemblerMenager::getAddressRegister(){
  return registerMenager.getAddressRegister();
}

void AssemblerMenager::startNewBlock(){
    for(auto currentRegister : registerMenager.getRegisterVector()){
        if(currentRegister->isUsed()) {
          saveValueRegister(currentRegister);
        }
    }
    AddressRegisterPointer addressRegister = getAddressRegister();
    addressRegister->setValue(addressRegister -> UNKNOW_VALUE);
}

void AssemblerMenager::insertAssemblerCommand(std::vector<AssemblerCommand>& assemblerCommands){
    commands.insert(commands.end(), assemblerCommands.begin(), assemblerCommands.end());
}

void AssemblerMenager::insertAssemblerCommand(AssemblerCommand command){
    commands.push_back(command);
}
void AssemblerMenager::checkSpecyficVariableInRegister(RegisterPointer checkRegister){
  VariablePointer variable = checkRegister->getVariable();
  if(variable->isMustBeStoreNow()){
    saveValueRegister(checkRegister);
  }
}


std::vector<AssemblerCommand> AssemblerMenager::generateMultiplicationCommand(RegisterType result, RegisterType left, RegisterType right){
  std::vector<AssemblerCommand> mulCommands;
  std::string startLabel = labelMenager.getNextLabel("MUL");
  std::string endLabel = labelMenager.getLabel(startLabel, "END");
  std::string isOddLabel = labelMenager.getLabel(startLabel, "ISODD");
  std::string notOddLabel = labelMenager.getLabel(startLabel, "NODD");

  mulCommands.push_back(AssemblerCommand(AssemblerInstruction::Sub, result, result));
  mulCommands.push_back(AssemblerCommand(AssemblerInstruction::Jzero, left, endLabel));
  mulCommands.push_back(AssemblerCommand(AssemblerInstruction::Label, startLabel));
  mulCommands.push_back(AssemblerCommand(AssemblerInstruction::Jzero, right, endLabel));
  mulCommands.push_back(AssemblerCommand(AssemblerInstruction::Jodd, right, isOddLabel));
  mulCommands.push_back(AssemblerCommand(AssemblerInstruction::Jump, notOddLabel));
  mulCommands.push_back(AssemblerCommand(AssemblerInstruction::Label, isOddLabel));
  mulCommands.push_back(AssemblerCommand(AssemblerInstruction::Add, result, left));
  mulCommands.push_back(AssemblerCommand(AssemblerInstruction::Label, notOddLabel));
  mulCommands.push_back(AssemblerCommand(AssemblerInstruction::Half, right));
  mulCommands.push_back(AssemblerCommand(AssemblerInstruction::Add, left, left));
  mulCommands.push_back(AssemblerCommand(AssemblerInstruction::Jump, startLabel));
  mulCommands.push_back(AssemblerCommand(AssemblerInstruction::Label, endLabel));

  return mulCommands;
}

std::vector<AssemblerCommand> AssemblerMenager::generateDivisionCommand(RegisterType result, RegisterType left, RegisterType right, RegisterType help1, RegisterType help2, bool mod){
  std::vector<AssemblerCommand> divCommands;
  std::string startLabel = labelMenager.getNextLabel("DIV");
  std::string endLabel = labelMenager.getLabel(startLabel, "END");
  std::string endLabel2 = labelMenager.getLabel(startLabel, "END2");
  std::string div2Label = labelMenager.getLabel(startLabel, "2");
  std::string div3Label = labelMenager.getLabel(startLabel, "3");
  std::string div4Label = labelMenager.getLabel(startLabel, "4");
  std::string div5Label = labelMenager.getLabel(startLabel, "5");

  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Sub, result, result));
  if(mod){
    divCommands.push_back(AssemblerCommand(AssemblerInstruction::Jzero, right, endLabel2));
  }
  else{
    divCommands.push_back(AssemblerCommand(AssemblerInstruction::Jzero, right, endLabel));
  }
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Sub, help1, help1));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Label, startLabel));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Copy, help2, left));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Inc, help2));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Sub, help2, right));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Jzero, help2, div2Label));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Inc, help1));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Add, right, right));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Jump, startLabel));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Label, div2Label));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Half, right));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Label, div5Label));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Jzero, help1, endLabel));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Copy, help2, left));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Inc, help2));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Sub, help2, right));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Jzero, help2, div3Label));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Sub, left, right));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Add, result, result));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Inc, result));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Jump, div4Label));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Label, div3Label));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Add, result, result));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Label, div4Label));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Half, right));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Dec, help1));
  divCommands.push_back(AssemblerCommand(AssemblerInstruction::Jump, div5Label));
  if(mod){
    divCommands.push_back(AssemblerCommand(AssemblerInstruction::Label, endLabel));
    divCommands.push_back(AssemblerCommand(AssemblerInstruction::Copy, result, left));
    divCommands.push_back(AssemblerCommand(AssemblerInstruction::Label, endLabel2));
  }
  else{
    divCommands.push_back(AssemblerCommand(AssemblerInstruction::Label, endLabel));
  }

  return divCommands;
}


void AssemblerMenager::convertLabelToNumber(){
    std::map<std::string, long long> labelMap;
    std::vector<AssemblerCommand> newCommands;
    long long i = 0;
    for(auto command : commands){
      if(command.getInstruction() == AssemblerInstruction::Label){
        labelMap[command.getLabel()] = i;
      }
      else{
        newCommands.push_back(command);
        i++;
      }
    }
    int k = 0;
    for(auto command : newCommands){
      if(command.getInstruction() == AssemblerInstruction::Jump || command.getInstruction() == AssemblerInstruction::Jzero || command.getInstruction() == AssemblerInstruction::Jodd){
        newCommands[k].setJumpNumber(labelMap[command.getLabel()]);
      }
      k++;
    }

    commands = newCommands;
}