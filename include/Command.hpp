#ifndef __COMMAND_HH__
#define __COMMAND_HH__

#include "CommandStrategy.hpp"
#include <vector>

class Command : public CommandStrategy{
public:
    Command();
    Command(CommandStrategyPointer generatorAsm);

    void compile(AssemblerMenager* assemblerMenager);
private:
    CommandStrategyPointer generatorAsm;
};

class CommandBlock {
public:
    CommandBlock();
    CommandBlock(Command command);
    CommandBlock(std::vector<Command>& commands);

    void addCommandToEnd(Command command);
    void addCommandToBegin(Command command);
    void addVectorCommands(std::vector<Command>& appendCommands);
    void append(CommandBlock& block);
    void appendToBegin(CommandBlock& block);
    std::vector<Command> getCommands();
private:
    std::vector<Command> commands;
};


#endif 