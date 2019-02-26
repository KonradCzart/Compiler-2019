#include "Command.hpp"
#include <iostream>

Command::Command(){

}

Command::Command(CommandStrategyPointer generatorAsm){
    this->generatorAsm = generatorAsm;
}

void Command::generate(){
    generatorAsm->generate();
}

void Command::print(){
    std::cout << "Kommenda !!!!";
}