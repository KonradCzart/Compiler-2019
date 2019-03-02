#ifndef __VARIABLE_HH__
#define __VARIABLE_HH__

#include <memory>
#include <vector>


using  namespace std;

class Variable {
public:
    Variable() {}
    virtual ~Variable(){}

    virtual void loadVariable() = 0;
    virtual std::string print() = 0;

    static bool compere(shared_ptr<Variable> leftVariable, shared_ptr<Variable> rightVariable);
};

using VariablePointer = shared_ptr<Variable>;

class SimpleVariable : public Variable{
public:
    SimpleVariable(std::string identifier);
    ~SimpleVariable() = default;

    void loadVariable();
    std::string print();

private:
    std::string identifier;
};

class ConstVariable : public Variable{
public:
    ConstVariable(long long value);
    ~ConstVariable() = default;

    void loadVariable();
    std::string print();

private:
    long long value;
};

class ConstArrayVariable : public Variable{
public:
    ConstArrayVariable (std::string identifier, long long arrayIndex);
    ~ConstArrayVariable () = default;

    void loadVariable();
    std::string print();

private:
    std::string identifier;
    long long arrayIndex;
};

class IdentifierArrayVariable : public Variable{
public:
    IdentifierArrayVariable (std::string identifier, VariablePointer arrayVariableIndex);
    ~IdentifierArrayVariable () = default;

    void loadVariable();
    std::string print();

private:
    std::string identifier;
    VariablePointer arrayVariableIndex;
};

class TmpVariable : public Variable{
public:
    TmpVariable () = default;
    ~TmpVariable () = default;

    void loadVariable();
    std::string print();
};

#endif 