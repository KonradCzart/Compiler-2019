#include <iostream>
#include "Variable.hpp"
#include <sstream>
#include "RegisterMenager.hpp"
#include "AssemblerMenager.hpp"
#include "AssemblerCommand.hpp"
#include "MemoryTable.hpp"

bool Variable::compere(VariablePointer leftVariable, VariablePointer rightVariable){
    if(leftVariable->print() == rightVariable->print()){
        return true;
    }
    return false;
}

SimpleVariable::SimpleVariable(std::string identifier){
    this->identifier = identifier;
}

void SimpleVariable::loadVariable(){
    std::cout << "Zwykła zmienna: " << identifier << std::endl;
}

std::string SimpleVariable::print(){
    return identifier;
}

RegisterPointer SimpleVariable::loadVariable(AssemblerMenager* assemblerMenager){
    RegisterPointer loadRegister = assemblerMenager -> getFreeRegister();
    helpGenerateCommand(assemblerMenager, loadRegister, AssemblerInstruction::Load);

    return loadRegister;
}

void SimpleVariable::storeVariable(AssemblerMenager* assemblerMenager, RegisterPointer saveRegister){
    helpGenerateCommand(assemblerMenager, saveRegister, AssemblerInstruction::Store); 
}

void SimpleVariable::helpGenerateCommand(AssemblerMenager* assemblerMenager, RegisterPointer currentRegister, AssemblerInstruction instruction){
    std::vector<AssemblerCommand> commands;
    MemoryTable* memory = MemoryTable::getInstance();
    long long memoryAddress = memory -> getAddress(identifier);

    commands = assemblerMenager -> generateAddress(memoryAddress);
    commands.push_back(AssemblerCommand(instruction, currentRegister->getType()));
    assemblerMenager -> insertAssemblerCommand(commands);

    memory = nullptr;   
}

bool SimpleVariable::isMustBeStoreNow(){
    return false;
}

ConstVariable::ConstVariable(long long value){
    this->value = value;
}

void ConstVariable::loadVariable(){
    std::cout << "Stała: " << value << std::endl;
}

std::string ConstVariable::print(){
    std::stringstream tmp;
    tmp << value;
    return tmp.str();
}

RegisterPointer ConstVariable::loadVariable(AssemblerMenager* assemblerMenager){
    std::vector<AssemblerCommand> loadCommands;
    RegisterPointer loadRegister = assemblerMenager -> getFreeRegister();
    
    loadCommands = assemblerMenager -> generateNumberInRegister(loadRegister->getType(), value);
    assemblerMenager -> insertAssemblerCommand(loadCommands);

    return loadRegister;
}

void ConstVariable::storeVariable(AssemblerMenager* assemblerMenager, RegisterPointer saveRegister){
    //We don't want save constants variable
}

bool ConstVariable::isMustBeStoreNow(){
    return false;
}

ConstArrayVariable::ConstArrayVariable (std::string identifier, long long arrayIndex){
    this->identifier = identifier;
    this->arrayIndex = arrayIndex;
}

void ConstArrayVariable::loadVariable(){
    std::cout << "Tablica: " << identifier << " index " << arrayIndex << std::endl;
}

std::string ConstArrayVariable::print(){
    std::stringstream tmp;
    tmp << arrayIndex;
    return identifier + "[" + tmp.str() + "]";
}

RegisterPointer ConstArrayVariable::loadVariable(AssemblerMenager* assemblerMenager){
    RegisterPointer loadRegister = assemblerMenager -> getFreeRegister();
    helpGenerateCommand(assemblerMenager, loadRegister, AssemblerInstruction::Load);
        
    return loadRegister;
}

void ConstArrayVariable::storeVariable(AssemblerMenager* assemblerMenager, RegisterPointer saveRegister){
    helpGenerateCommand(assemblerMenager, saveRegister, AssemblerInstruction::Store);
}

bool ConstArrayVariable::isMustBeStoreNow(){
    return true;
}

void ConstArrayVariable::helpGenerateCommand(AssemblerMenager* assemblerMenager, RegisterPointer currentRegister, AssemblerInstruction instruction){
    std::vector<AssemblerCommand> commands;
    MemoryTable* memory = MemoryTable::getInstance();
    long long memoryAddress = memory -> getAddress(identifier);
    long long firstArrayIndex = memory -> getFirstArrayIndex(identifier);

    memoryAddress = memoryAddress + arrayIndex - firstArrayIndex;
    commands = assemblerMenager -> generateAddress(memoryAddress);
    commands.push_back(AssemblerCommand(instruction, currentRegister->getType()));
    assemblerMenager -> insertAssemblerCommand(commands);

    memory = nullptr;
}

IdentifierArrayVariable::IdentifierArrayVariable (std::string identifier, VariablePointer arrayVariableIndex){
    this->identifier = identifier;
    this->arrayVariableIndex = arrayVariableIndex;
}

void IdentifierArrayVariable::loadVariable(){
    std::cout << "Tablica: " << identifier << " index ";
    arrayVariableIndex->loadVariable();
}

std::string IdentifierArrayVariable::print(){
    return identifier + "[" + arrayVariableIndex->print() + "]";
}

RegisterPointer IdentifierArrayVariable::loadVariable(AssemblerMenager* assemblerMenager){
    RegisterPointer loadRegister = assemblerMenager -> getFreeRegister();    
    helpGenerateCommand(assemblerMenager, loadRegister, AssemblerInstruction::Load);
    return loadRegister;
}

void IdentifierArrayVariable::storeVariable(AssemblerMenager* assemblerMenager, RegisterPointer saveRegister){
    helpGenerateCommand(assemblerMenager, saveRegister, AssemblerInstruction::Store);
}

void IdentifierArrayVariable::helpGenerateCommand(AssemblerMenager* assemblerMenager, RegisterPointer currentRegister, AssemblerInstruction instruction){
    std::vector<AssemblerCommand> commands;
    MemoryTable* memory = MemoryTable::getInstance();
    long long memoryAddress = memory -> getAddress(identifier);
    long long firstArrayIndex = memory -> getFirstArrayIndex(identifier);
    
    RegisterPointer indexRegister = assemblerMenager -> getRegisterForVariable(arrayVariableIndex);
    RegisterPointer firstIndexRegister = assemblerMenager -> getRegisterForVariable(make_shared<ConstVariable>(firstArrayIndex));
    AddressRegisterPointer addressRegister = assemblerMenager -> getAddressRegister();

    commands = assemblerMenager -> generateAddress(memoryAddress);
    commands.push_back(AssemblerCommand(AssemblerInstruction::Add, addressRegister->getType(), indexRegister->getType()));
    commands.push_back(AssemblerCommand(AssemblerInstruction::Sub, addressRegister->getType(), firstIndexRegister->getType()));
    commands.push_back(AssemblerCommand(instruction, currentRegister->getType()));
    assemblerMenager -> insertAssemblerCommand(commands);

    addressRegister -> setValue(addressRegister -> UNKNOW_VALUE);
    memory = nullptr;    
}

bool IdentifierArrayVariable::isMustBeStoreNow(){
    return true;
}

void TmpVariable::loadVariable(){
    std::cout << "Tmp: załadowano";
}

std::string TmpVariable::print(){
    std::string tmp = "TMP";
    return tmp;
}

RegisterPointer TmpVariable::loadVariable(AssemblerMenager* assemblerMenager){
    std::vector<AssemblerCommand> loadCommands;
    RegisterPointer loadRegister = assemblerMenager -> getFreeRegister();

    loadCommands.push_back(AssemblerCommand(AssemblerInstruction::Sub, loadRegister->getType(), loadRegister->getType()));

    return loadRegister;
}

void TmpVariable::storeVariable(AssemblerMenager* assemblerMenager, RegisterPointer saveRegister){
    //We don't want save tmp variable
}

bool TmpVariable::isMustBeStoreNow(){
    return false;
}