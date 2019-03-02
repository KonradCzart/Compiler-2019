#ifndef __REGISTERMENAGER_HH__
#define __REGISTERMENAGER_HH__

#include <vector>
#include <string.h>
#include <iostream>
#include "Variable.hpp"

enum class RegisterType: char{
  A = 'A',
  B = 'B',
  C = 'C',
  D = 'D',
  E = 'E',
  F = 'F',
  G = 'G',
  H = 'H',
  X = 'X',
};

inline std::ostream& operator<<(std::ostream& os, RegisterType r){
    return os << static_cast<char>(r);
}

class Register{
public:
    Register();
    Register (RegisterType type);
  
    RegisterType getType();
    VariablePointer getVariable();
    void setVariable(VariablePointer variable);
    bool isStore();
    void setStore(bool s);
    bool isUsed();
    void setUsed(bool used);
    long long getUsedTime();
    void clearUsedTime();
    void incrementUsedTime();
    void printRegister();
private:
    RegisterType type;
    VariablePointer variable;
    bool store;
    bool used;
    long long usedTime;
    VariablePointer tmpVariable;
};

using RegisterPointer = shared_ptr<Register>;

class AddressRegister{
public:
    const long long UNKNOW_VALUE = -1;
    const long long MAX_DIFFERENCE = 10;

    AddressRegister();
    AddressRegister (RegisterType type);

    RegisterType getType();
    void setValue(long long value);
    long long getValue();

    void printRegister();
private:
    long long value;
    RegisterType type;
};

using AddressRegisterPointer = shared_ptr<AddressRegister>;

class RegisterMenager{
public:
    RegisterMenager();

    RegisterPointer variableInRegister(VariablePointer variable);
    RegisterPointer getFreeRegister();
    RegisterPointer getLastUsedRegister();

    //debug
    void printRegisterAll();

private:
    std::vector<RegisterPointer> registerList;
    AddressRegisterPointer addressRegister;
    RegisterPointer xTypeRegister;
    void stepUseTime();
};


#endif
