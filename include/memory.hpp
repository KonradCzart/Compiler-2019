#ifndef __MEMORYTABLE_HH__
#define __MEMORYTABLE_HH__

#include <map>
#include <vector>
#include <string.h>

struct SymbolVariable{
    std::string name;
    long long address;
    bool initialized;
};

struct SymbolArray{
    std::string name;
    long long startArray;
    long long endArray;
    long long address;
    bool initialized;
};

class MemoryTable{
public:
    const static long long FIRST_FREE_ADDRESS = 1;

private:
    MemoryTable();
    std::map<std::string, SymbolVariable> symbolMap;
    std::map<std::string, SymbolArray> symbolArrayMap;
    std::map<std::string, SymbolVariable> iteratorMap;
    std::vector<std::string> iteratorStack;
    long long lastFreeAddress;

};

#endif
