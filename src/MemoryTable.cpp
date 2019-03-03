#include "MemoryTable.hpp"
#include <iostream>
#include <sstream>
#include  <algorithm>

MemoryTable* MemoryTable::instance = 0;

MemoryTable::MemoryTable(){
  lastFreeAddress = FIRST_FREE_ADDRESS;
}

MemoryTable* MemoryTable::getInstance(){
    if(instance == 0){
        instance = new MemoryTable;
    }
    return instance;
}

bool MemoryTable::declare(std::string identifier){
    if(!isAlreadyDeclared(identifier)){
        struct MemorySymbol symbol;
        symbol.identifier = identifier;
        symbol.memoryAddress = lastFreeAddress;
        symbol.initialized = false;
        symbol.isArray = false;
        symbol.firstArrayIndex = 1;
        symbol.size = 1;
        declaredSymbols[identifier] = symbol;
        lastFreeAddress++;
        return true;
    }
    return false;
}

bool MemoryTable::declareArray(std::string identifier, long long firstArrayIndex, long long lastArrayIndex){
    if(!isAlreadyDeclared(identifier)){
        struct MemorySymbol symbol;
        symbol.identifier = identifier;
        symbol.memoryAddress = lastFreeAddress;
        symbol.initialized = true;
        symbol.isArray = true;
        symbol.firstArrayIndex = firstArrayIndex;
        symbol.size = lastArrayIndex - firstArrayIndex + 1;
        declaredSymbols[identifier] = symbol;
        lastFreeAddress += symbol.size;
        return true;
    }
    return false;
}

bool MemoryTable::isAlreadyDeclared(std::string identifier){
    auto it = declaredSymbols.find(identifier);
    if(it != declaredSymbols.end()) {
        return true;
    }
    return false;
}

void MemoryTable::initialize(std::string identifier){
    declaredSymbols.at(identifier).initialized = true;
}

bool MemoryTable::isInitialized(std::string identifier){
    return declaredSymbols.at(identifier).initialized;
}

bool MemoryTable::pushIterator(std::string identifier){
  if(iteratorOnStack(identifier)){
    return false;
  }
  declare(identifier);
  iteratorStack.push_back(identifier);
  return true;
}

bool MemoryTable::iteratorOnStack(std::string identifier){
  if(std::find(iteratorStack.begin(), iteratorStack.end(), identifier) != iteratorStack.end()) {
    return true;
  }
  return false;
}

std::string MemoryTable::popIterator(){
  std::string identifier = iteratorStack.back();
  iteratorStack.pop_back();
  return identifier;
}

long long MemoryTable::getAddress(std::string identifier){
  if(isAlreadyDeclared(identifier)){
    return declaredSymbols[identifier].memoryAddress;
  }
  return 0;
}

long long MemoryTable::getFirstArrayIndex(std::string identifier){
   if(isAlreadyDeclared(identifier)){
    return declaredSymbols[identifier].firstArrayIndex;
  }
  return 0; 
}


void MemoryTable::printAllMemory(){
  for(auto elem : declaredSymbols){
    MemorySymbol symbol = elem.second;
    std::cout << symbol.identifier << " " << symbol.memoryAddress << " " << symbol.initialized << " Array: " << symbol.isArray << std::endl;
  }
}