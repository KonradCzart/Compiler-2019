#ifndef __COMMANDMENAGER_HH__
#define __COMMANDMENAGER_HH__

#include <string>
#include <ostream>
#include "Variable.hpp"
#include "Command.hpp"
#include "Condition.hpp"
#include <vector>
#include "LabelMenager.hpp"

class CommandMenager{
public:
   CommandMenager() = default;
   ~CommandMenager() = default;

   CommandBlock getCommandIf(Condition condition, CommandBlock& ifBlock);
   CommandBlock getCommandIfElse(Condition condition, CommandBlock& trueBlock, CommandBlock& falseBlock);
   CommandBlock getCommandWhileDo(Condition condition, CommandBlock& whileBlock);
   CommandBlock getCommandDoWhile(Condition condition, CommandBlock& whileBlock);
   CommandBlock getCommandFor(VariablePointer iterator, VariablePointer counter,  VariablePointer fromVariablePointer, VariablePointer endVariablePointer, CommandBlock forBlock);
   CommandBlock getCommandForDown(VariablePointer iterator, VariablePointer counter, VariablePointer fromVariablePointer, VariablePointer endVariablePointer, CommandBlock forBlock);

private:
   LabelMenager labelMenager;
};

#endif