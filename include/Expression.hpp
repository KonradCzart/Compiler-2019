#ifndef __EXPRESSION_HH__
#define __EXPRESSION_HH__

#include "Variable.hpp"
#include "Command.hpp"

class Expression {
public:
    enum Type {
        ADDITION,
        SUBTRACTION,
        MULTIPLICATION,
        DIVISION,
        MODULO,
        EMPTY
    };

    Expression();
    Expression(Type type, VariablePointer leftVariable, VariablePointer rightVariable);

    Command createCommand(VariablePointer resultVariable);
    VariablePointer getLeftVariable();
    VariablePointer getRightVariable();
    Type getType();

    void print();
private:
    Type type;
    VariablePointer leftVariable;
    VariablePointer rightVariable;
};

#endif 