#include "RegisterMenager.hpp"

Register::Register (){
    tmpVariable = make_shared<TmpVariable>("EMPTY");
    type = RegisterType::A;
    used = false;
    variable = tmpVariable;
    usedTime = 0;
}

Register::Register (RegisterType type){
    Register();
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
    std::cout << type << "   " << usedTime << "   " << variable << std::endl;
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
    int i = 0;
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

void RegisterMenager::printRegisterAll(){
    addressRegister -> printRegister();
    for(auto elem : registerList){
        RegisterPointer r = elem;
        r -> printRegister();
    }
}