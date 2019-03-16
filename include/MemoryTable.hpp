#ifndef __MEMORYTABLE_HH__
#define __MEMORYTABLE_HH__

#include <unordered_map>
#include <vector>
#include <string.h>

struct MemorySymbol{
    std::string identifier;
    long long memoryAddress;
    bool isArray;
    long long size;
    long long firstArrayIndex;
    bool initialized;
};

class MemoryTable{
public:
    const static long long FIRST_FREE_ADDRESS = 1;
    static MemoryTable* getInstance();

    bool declare(std::string identifier);
    bool declareArray(std::string identifier, long long firstArrayIndex, long long lastArrayIndex);
    bool isAlreadyDeclared(std::string identifier);
    bool isArraySymbol(std::string identifier);
    
    void initialize(std::string identifier);
    bool isInitialized(std::string identifier);

    bool pushIterator(std::string identifier);
    std::string popIterator();
    bool iteratorOnStack(std::string identifier);

    long long getAddress(std::string identifier);
    long long getFirstArrayIndex(std::string identifier);

    void printAllMemory();

protected:
    MemoryTable();

private:
    static MemoryTable* instance;
    std::unordered_map<std::string, MemorySymbol> declaredSymbols;
    std::vector<std::string> iteratorStack;
    long long lastFreeAddress;

};

#endif
