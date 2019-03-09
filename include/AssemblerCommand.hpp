#ifndef __ASSEMBLERCOMMAND_HH__
#define __ASSEMBLERCOMMAND_HH__

#include "RegisterMenager.hpp"

enum class AssemblerInstruction{
    Get,
    Put,
    Load,
    Store,
    Copy,
    Add,
    Sub,
    Half,
    Inc,
    Dec,
    Jump,
    Jzero,
    Jodd,
    Halt,
    Label,
    Com
};

class AssemblerCommand{
public:
    AssemblerCommand(AssemblerInstruction instruction, RegisterType firstRegister, RegisterType secondRegister);
    AssemblerCommand(AssemblerInstruction instruction, RegisterType firstRegister, std::string label);
    AssemblerCommand(AssemblerInstruction instruction, RegisterType firstRegister, long long jumpNumber);
    AssemblerCommand(AssemblerInstruction instruction, std::string label);
    AssemblerCommand(AssemblerInstruction instruction, long long jumpNumber);
    AssemblerCommand(AssemblerInstruction instruction, RegisterType firstRegister);

    friend ostream& operator <<(std::ostream &strm, const AssemblerCommand &command);
    
    std::string getLabel();
    void setJumpNumber(long long jumpNumber);
    AssemblerInstruction getInstruction();
    
private:
    AssemblerInstruction instruction;
    RegisterType firstRegister;
    RegisterType secondRegister;
    std::string label;
    long long jumpNumber;
};

#endif