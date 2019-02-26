#ifndef __COMMAND_HH__
#define __COMMAND_HH__

#include "CommandStrategy.hpp"

class Command : public CommandStrategy{
public:
    Command();
    Command(CommandStrategyPointer generatorAsm);

    void generate();

    void print();
private:
    CommandStrategyPointer generatorAsm;
};

#endif 