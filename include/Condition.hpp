#ifndef __CONDITION_HH__
#define __CONDITION_HH__

#include "Variable.hpp"

class Condition {
public:
    enum Type {
        EQUAL,
        NOT_EQUAL,
        GREATER,
        LESSER,
        GREATER_EQUAL,
        LESSER_EQUAL
    };

    Condition();
    Condition(Type type, VariablePointer leftVariable, VariablePointer rightVariable);

    void print();
private:
    Type type;
    VariablePointer leftVariable;
    VariablePointer rightVariable;
};


#endif 