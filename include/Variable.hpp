#ifndef __VARIABLE_HH__
#define __VARIABLE_HH__

#include <memory>
#include <vector>


using  namespace std;
class AssemblerMenager;
class Register;
enum class AssemblerInstruction;
using RegisterPointer = shared_ptr<Register>;

class Variable {
public:
    Variable() {}
    virtual ~Variable(){}

    virtual std::string getIdentifier() = 0;
    virtual std::string toString() = 0;

    virtual RegisterPointer loadVariable(AssemblerMenager* assemblerMenager) = 0;
    virtual void storeVariable(AssemblerMenager* assemblerMenager, RegisterPointer saveRegister) = 0;
    virtual bool isMustBeStoreNow() = 0;

    static bool compere(std::shared_ptr<Variable> leftVariable, std::shared_ptr<Variable> rightVariable);
};

using VariablePointer = std::shared_ptr<Variable>;

class SimpleVariable : public Variable{
public:
    SimpleVariable(std::string identifier);
    ~SimpleVariable() = default;

    std::string getIdentifier();
    std::string toString();

    RegisterPointer loadVariable(AssemblerMenager* assemblerMenager);
    void storeVariable(AssemblerMenager* assemblerMenager, RegisterPointer saveRegister);
    bool isMustBeStoreNow();

private:
    std::string identifier;
    void helpGenerateCommand(AssemblerMenager* assemblerMenager, RegisterPointer currentRegister, AssemblerInstruction instruction);
};

class ConstVariable : public Variable{
public:
    ConstVariable(long long value);
    ~ConstVariable() = default;

    std::string getIdentifier();
    std::string toString();

    RegisterPointer loadVariable(AssemblerMenager* assemblerMenager);
    void storeVariable(AssemblerMenager* assemblerMenager, RegisterPointer saveRegister);
    bool isMustBeStoreNow();

private:
    long long value;
};

class ConstArrayVariable : public Variable{
public:
    ConstArrayVariable (std::string identifier, long long arrayIndex);
    ~ConstArrayVariable () = default;

    std::string getIdentifier();
    std::string toString();

    RegisterPointer loadVariable(AssemblerMenager* assemblerMenager);
    void storeVariable(AssemblerMenager* assemblerMenager, RegisterPointer saveRegister);
    bool isMustBeStoreNow();

private:
    std::string identifier;
    long long arrayIndex;
    void helpGenerateCommand(AssemblerMenager* assemblerMenager, RegisterPointer currentRegister, AssemblerInstruction instruction);
};

class IdentifierArrayVariable : public Variable{
public:
    IdentifierArrayVariable (std::string identifier, VariablePointer arrayVariableIndex);
    ~IdentifierArrayVariable () = default;

    std::string getIdentifier();
    std::string toString();

    RegisterPointer loadVariable(AssemblerMenager* assemblerMenager);
    void storeVariable(AssemblerMenager* assemblerMenager, RegisterPointer saveRegister);
    bool isMustBeStoreNow();

private:
    std::string identifier;
    VariablePointer arrayVariableIndex;
    void helpGenerateCommand(AssemblerMenager* assemblerMenager, RegisterPointer currentRegister, AssemblerInstruction instruction);
};

class TmpVariable : public Variable{
public:
    TmpVariable ();
    TmpVariable (std::string name);
    ~TmpVariable () = default;

    std::string getIdentifier();
    std::string toString();

    RegisterPointer loadVariable(AssemblerMenager* assemblerMenager);
    void storeVariable(AssemblerMenager* assemblerMenager, RegisterPointer saveRegister);
    bool isMustBeStoreNow();
private:
    std::string identifier;
};

#endif