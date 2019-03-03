#ifndef __ASSEMBLERMENAGER_HH__
#define __ASSEMBLERMENAGER_HH__


#include "Command.hpp"
#include "AssemblerCommand.hpp"
#include "RegisterMenager.hpp"

class AssemblerMenager{
public:
    AssemblerMenager() = default;
    AssemblerMenager(CommandBlock block);

    void compileAll();
    std::ostream& printCompiledCode(std::ostream &stream);

    std::vector<AssemblerCommand> generateNumberInRegister(RegisterType registerType, long long n);
    std::vector<AssemblerCommand> generateAddress(long long address);

    RegisterPointer getRegisterForVariable(VariablePointer variable);
    RegisterPointer getRegisterForVariableWithoutLoad(VariablePointer variable);
    RegisterPointer getFreeRegister();
    void saveValueRegister(RegisterPointer register);

    void insertAssemblerCommand(std::vector<AssemblerCommand>& asmCommands);
    AddressRegisterPointer getAddressRegister();
    
    void startNewBlock();
    void clearRegister();
private:
    CommandBlock blockToCompile;
    std::vector<AssemblerCommand> commands;
    RegisterMenager registerMenager;
};
#endif