#ifndef __COMMANDSTRATEGY_HH__
#define __COMMANDSTRATEGY_HH__

#include "Variable.hpp"

class CommandStrategy {
public:
    virtual void compile(AssemblerMenager* assemblerMenager) = 0;
};

using CommandStrategyPointer = shared_ptr<CommandStrategy>;

class AssignCommandStrategy : public CommandStrategy {
public:
    AssignCommandStrategy(VariablePointer resultVariable, VariablePointer assignVariable);

    static CommandStrategyPointer create(VariablePointer resultVariable, VariablePointer assignVariable);
    void compile(AssemblerMenager* assemblerMenager);

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
    void compile(AssemblerMenager* assemblerMenager);

private:
    Type type;
    VariablePointer resultVariable;
};

class JumpCommandStrategy : public CommandStrategy {
public:
    JumpCommandStrategy(std::string label);

    static CommandStrategyPointer create(std::string label);
    void compile(AssemblerMenager* assemblerMenager);

private:
    std::string label;
};

class JumpConditionCommandStrategy : public CommandStrategy {
public:
    enum Type {
        JODD,
        JZERO
    };
    JumpConditionCommandStrategy(Type type, VariablePointer conditionVariable, std::string label);

    static CommandStrategyPointer create(Type type, VariablePointer conditionVariable, std::string label);
    void compile(AssemblerMenager* assemblerMenager);

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
    void compile(AssemblerMenager* assemblerMenager);

private:
    Type type;
    VariablePointer resultVariable;
};

class CodeCommandStrategy : public CommandStrategy {
public:
    enum Type {
        HALT,
        NEW_BLOCK
    };
    CodeCommandStrategy(Type type, std::string label);

    static CommandStrategyPointer create(Type type, std::string label);
    void compile(AssemblerMenager* assemblerMenager);

private:
    Type type;
    std::string label;
};

class LabelCommandStrategy : public CommandStrategy {
public:
    LabelCommandStrategy(std::string label);

    static CommandStrategyPointer create(std::string label);
    void compile(AssemblerMenager* assemblerMenager);

private:
    std::string label;
};


#endif 