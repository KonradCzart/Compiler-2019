#ifndef __COMMANDMENAGER_HH__
#define __COMMANDMENAGER_HH__

#include <string>
#include <ostream>
#include "Variable.hpp"
#include "Command.hpp"
#include "Condition.hpp"
#include <vector>


class LabelMenager{
private:
   long long labelIndex;

public:
   LabelMenager();
   ~LabelMenager();
   std::string getNextLabel(std::string infix);
   std::string getLabel(std::string label, std::string suffix);

};


class CommandMenager{
private:
   LabelMenager labelMenager;
   std::vector<Command> getConditionCommand(Condition condition, std::string labelJump, std::string labelHelp1, std::string labelHelp2);
public:
   std::vector<Command> getCommandIf(Condition condition, std::vector<Command> commands);
   std::vector<Command> getCommandIfElse(Condition condition, std::vector<Command> commandsTrue, std::vector<Command> commandsFalse);
   std::vector<Command> getCommandWhileDo(Condition condition, std::vector<Command> commands);
   std::vector<Command> getCommandDoWhile(Condition condition, std::vector<Command> commands);
   std::vector<Command> getCommandFor(Variable iterator, Variable fromVariable, Variable endVariable, std::vector<Command> commands);
   std::vector<Command> getCommandForDown(Variable iterator, Variable fromVariable, Variable endVariable, std::vector<Command> commands);
};

#endif