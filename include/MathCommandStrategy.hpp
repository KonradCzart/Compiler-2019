#ifndef __MATHCOMMANDSTRATEGY_HH__
#define __MATHCOMMANDSTRATEGY_HH__

#include "CommandStrategy.hpp"
#include "Variable.hpp"

class MathCommandStrategy : public CommandStrategy {
public:
    MathCommandStrategy(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable);

    virtual void generate() = 0;

protected:
    VariablePointer resultVariable;
    VariablePointer leftVariable;
    VariablePointer rightVariable;
};

class AdditionCommandStrategy : public MathCommandStrategy {
public:
    AdditionCommandStrategy(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable);

    static CommandStrategyPointer create(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable);
    void generate();
};

class SubtractionCommandStrategy : public MathCommandStrategy {
public:
    SubtractionCommandStrategy(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable);
    
    static CommandStrategyPointer create(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable);
    void generate();
};

class MultiplicationCommandStrategy : public MathCommandStrategy {
public:
    MultiplicationCommandStrategy(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable);

    static CommandStrategyPointer create(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable);
    void generate();
};

class DivisionCommandStrategy : public MathCommandStrategy {
public:
    DivisionCommandStrategy(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable);

    static CommandStrategyPointer create(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable);
    void generate();
};

class ModuloCommandStrategy : public MathCommandStrategy {
public:
    ModuloCommandStrategy(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable);

    static CommandStrategyPointer create(VariablePointer resultVariable, VariablePointer leftVariable, VariablePointer rightVariable);
    void generate();
};

#endif 