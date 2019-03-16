#ifndef __ASSEMBLERMENAGER_HH__
#define __ASSEMBLERMENAGER_HH__


#include "Command.hpp"
#include "AssemblerCommand.hpp"
#include "RegisterMenager.hpp"
#include "LabelMenager.hpp"

class AssemblerMenager{
public:
    AssemblerMenager() = default;
    AssemblerMenager(CommandBlock block);
    ~AssemblerMenager() = default;

    void setCommandBlock(CommandBlock block);

    void compileAll();
    std::ostream& printCompiledCode(std::ostream &stream);

    std::vector<AssemblerCommand> generateNumberInRegister(RegisterType registerType, long long n);
    std::vector<AssemblerCommand> generateAddress(long long address);

    RegisterPointer getRegisterForVariable(VariablePointer variable);
    RegisterPointer getRegisterForVariableWithoutLoad(VariablePointer variable);
    RegisterPointer getDifferentRegisterForVariableWithoutLoad(VariablePointer variable, RegisterPointer firstRegister, RegisterPointer secondRegister);
    RegisterPointer getDifferentRegisterForVariable(VariablePointer variable, RegisterPointer diffrentRegister);
    RegisterPointer getFreeRegister();
    void saveValueRegister(RegisterPointer saveRegister);
    void saveValueRegisterWithoutClear(RegisterPointer saveRegister);

    void insertAssemblerCommand(std::vector<AssemblerCommand>& asmCommands);
    void insertAssemblerCommand(AssemblerCommand command);
    AddressRegisterPointer getAddressRegister();
    void checkSpecyficVariableInRegister(RegisterPointer register);
    void startNewBlock();
    void clearRegister();

    std::vector<AssemblerCommand> generateDivisionCommand(RegisterType result, RegisterType left, RegisterType right, RegisterType help1, RegisterType help2, bool mod);
    std::vector<AssemblerCommand> generateMultiplicationCommand(RegisterType result, RegisterType left, RegisterType right);
private:
    CommandBlock blockToCompile;
    std::vector<AssemblerCommand> commands;
    RegisterMenager registerMenager;
    LabelMenager labelMenager;

    void convertLabelToNumber();
};
#endif