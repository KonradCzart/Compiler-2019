#ifndef __COMMANDSTRATEGY_HH__
#define __COMMANDSTRATEGY_HH__

#include "Variable.hpp"

class CommandStrategy {
public:
    virtual void generate() = 0;
};

using CommandStrategyPointer = shared_ptr<CommandStrategy>;

class AssignCommandStrategy : public CommandStrategy {
public:
    AssignCommandStrategy(VariablePointer resultVariable, VariablePointer assignVariable);

    static CommandStrategyPointer create(VariablePointer resultVariable, VariablePointer assignVariable);
    void generate();

private:
    VariablePointer resultVariable;
    VariablePointer assignVariable;
};

class IOCommandStrategy : public CommandStrategy {
public:
    enum Type {
        READ,
        WRITE
    };

    IOCommandStrategy(Type type, VariablePointer resultVariable);

    static CommandStrategyPointer create(Type type, VariablePointer resultVariable);
    void generate();

private:
    Type type;
    VariablePointer resultVariable;
};

class JumpCommandStrategy : public CommandStrategy {
public:
    JumpCommandStrategy(std::string label);

    static CommandStrategyPointer create(std::string label);
    void generate();

private:
    std::string label;
};

class JumpConditionCommandStrategy : public CommandStrategy {
public:
    enum Type {
        JODD,
        JZERO
    };
    JumpConditionCommandStrategy(Type type, std::string label, VariablePointer conditionVariable);

    static CommandStrategyPointer create(Type type, std::string label, VariablePointer conditionVariable);
    void generate();

private:
    Type type;
    std::string label;
    VariablePointer conditionVariable;
}; 

class IncDecCommandStrategy : public CommandStrategy {
public:
    enum Type {
        INC,
        DEC
    };
    IncDecCommandStrategy(Type type, VariablePointer resultVariable);

    static CommandStrategyPointer create(Type type, VariablePointer resultVariable);
    void generate();

private:
    Type type;
    VariablePointer resultVariable;
};

class SimpleCommandStrategy : public CommandStrategy {
public:
    enum Type {
        LABEL,
        HALT,
        NEW_BLOCK
    };
    SimpleCommandStrategy(Type type, std::string label);

    static CommandStrategyPointer create(Type type, std::string label);
    void generate();

private:
    Type type;
    std::string label;
};


#endif 