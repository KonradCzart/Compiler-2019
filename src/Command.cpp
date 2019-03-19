#include "Command.hpp"
#include <iostream>

Command::Command(){

}

Command::Command(CommandStrategyPointer generatorAsm){
    this->generatorAsm = generatorAsm;
}

void Command::compile(AssemblerMenager* assemblerMenager){
    generatorAsm->compile(assemblerMenager);
}

CommandBlock::CommandBlock(){}

CommandBlock::CommandBlock(Command com){
    commands.push_back(com);
}

CommandBlock::CommandBlock(std::vector<Command>& commands){
    this->commands = commands;
}

void CommandBlock::addCommandToEnd(Command command){
    commands.push_back(command);
}

void CommandBlock::addVectorCommands(std::vector<Command>& appendCommands){
    commands.insert(commands.end(), appendCommands.begin(), appendCommands.end());
}

void CommandBlock::addCommandToBegin(Command com){
    commands.insert(commands.begin(), com);
}

void CommandBlock::append(CommandBlock& block){
    auto innerCommands = block.getCommands();
    commands.insert(commands.end(), innerCommands.begin(), innerCommands.end());
}

void CommandBlock::appendToBegin(CommandBlock& block){
    auto innerCommands = block.getCommands();
    commands.insert(commands.begin(), innerCommands.begin(), innerCommands.end());
}

std::vector<Command> CommandBlock::getCommands(){
    return commands;
}