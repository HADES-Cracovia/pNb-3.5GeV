#ifndef HEVENTPOOL_H
#define HEVENTPOOL_H

#include "hcommondef.h"
#include <string>

using namespace CommonDefinitions;

class HEventPool {

public:

HEventPool() : pEvent(0), prefix(), suffix() {}
virtual ~HEventPool() {}

void set(HEventPool* previous) { pEvent = previous; }

void set(std::string name, float val=0.) { keyword = prefix + name + suffix; dataPair[keyword.c_str()] = val; }
float get(const char* name) { if (dataPair.find(name) != dataPair.end()) return dataPair[name]; return -1.; }
float get(std::string name) { return get(name.c_str()); }

bool isName(const char* name) { if (dataPair.find(name) != dataPair.end()) return true; return false; }

unsigned int getNum() { return dataPair.size(); }

void setSuffix(const char* suf = 0) { suffix = (suf != 0) ? suf : ""; }
void setPrefix(const char* pre = 0) { prefix = (pre != 0) ? pre : ""; }

NtuplePairIter begin() { return dataPair.begin(); }
NtuplePairIter end() { return dataPair.end(); }

void reset();
virtual void update();

HEventPool* getPreviousEventPool() { return pEvent; }

private:

   NtuplePair dataPair;
   NtuplePairIter dataIter;

   HEventPool* pEvent;

   std::string prefix;
   std::string suffix;
   std::string keyword;

};

#endif // HEVENTPOOL_H
