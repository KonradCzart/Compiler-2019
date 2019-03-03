#include "RegisterMenager.hpp"
#include <iostream>

Register::Register (){
    tmpVariable = make_shared<TmpVariable>();
    type = RegisterType::A;
    used = false;
    usedTime = 0;
    variable = tmpVariable;
}

Register::Register (RegisterType type){
    tmpVariable = make_shared<TmpVariable>();
    used = false;
    usedTime = 0;
    variable = tmpVariable;
    this->type = type;
}

RegisterType Register::getType(){
    return type;
}

VariablePointer Register::getVariable(){
    return variable;
}

void Register::setVariable(VariablePointer variable){
    this->variable = variable;
    usedTime = 0;
    used = true;
    store = false;
}

bool Register::isUsed(){
    return used;
}

void Register::setUsed(bool used){
    this->used = used;
}

bool Register::isStore(){
    return store;
}

void Register::setStore(bool store){
    this->store = store;
}

long long Register::getUsedTime(){
    return usedTime;
}

void Register::clearUsedTime(){
    usedTime = 0;
}
    
void Register::incrementUsedTime(){
    usedTime++;
}

void Register::printRegister(){

    std::cout << type << "   " << usedTime << "   " << variable->print() << std::endl;
}

AddressRegister::AddressRegister (){
    type = RegisterType::A;
    value = UNKNOW_VALUE;
}

AddressRegister::AddressRegister (RegisterType type){
    this->type = type;
    value = UNKNOW_VALUE;
}

RegisterType AddressRegister::getType(){
    return type;
}

void AddressRegister::setValue(long long value){
    this->value = value;
}

long long AddressRegister::getValue(){
    return value;
}

void AddressRegister::printRegister(){
    std::cout << type << "   " << value  << std::endl;
}

RegisterMenager::RegisterMenager (){
    addressRegister = make_shared<AddressRegister>(RegisterType::A);
    registerList.push_back(make_shared<Register>(RegisterType::B));
    registerList.push_back(make_shared<Register>(RegisterType::C));
    registerList.push_back(make_shared<Register>(RegisterType::D));
    registerList.push_back(make_shared<Register>(RegisterType::E));
    registerList.push_back(make_shared<Register>(RegisterType::F));
    registerList.push_back(make_shared<Register>(RegisterType::G));
    registerList.push_back(make_shared<Register>(RegisterType::H));
    xTypeRegister = make_shared<Register>(RegisterType::X);
}

void RegisterMenager::stepUseTime(){
    for(auto currentRegister : registerList){
        currentRegister -> incrementUsedTime();
    }
}

RegisterPointer RegisterMenager::variableInRegister(VariablePointer variable){
    for(auto currentRegister : registerList){
        if(Variable::compere(variable, currentRegister -> getVariable())){
        currentRegister -> clearUsedTime();
        return currentRegister;
    }
  }
  return xTypeRegister;
}

RegisterPointer RegisterMenager::getFreeRegister(){
    stepUseTime();
    for(auto currentRegister : registerList){
        if(!currentRegister -> isUsed()){
            return currentRegister;
        }
    }
    return xTypeRegister;
}

RegisterPointer RegisterMenager::getLastUsedRegister(){
    long long lastUsedTime = -1;
    RegisterPointer tmp = xTypeRegister;

    for(auto currentRegister : registerList){
        if(currentRegister -> getUsedTime() > lastUsedTime){
            lastUsedTime = currentRegister -> getUsedTime();
            tmp = currentRegister;
        }
    }
    return tmp;
}

AddressRegisterPointer RegisterMenager::getAddressRegister(){
    return addressRegister;
}

void RegisterMenager::printRegisterAll(){
    addressRegister -> printRegister();
    for(auto elem : registerList){
        RegisterPointer r = elem;
        r -> printRegister();
    }
    xTypeRegister -> printRegister();
}