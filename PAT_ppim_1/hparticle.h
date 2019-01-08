#ifndef HPARTICLE_H
#define HPARTICLE_H

#include "hcommondef.h"
#include "hparticlecandidate.h"
#include <string>

using namespace CommonDefinitions;

class HParticle {
// this is a wrapper to HParticleCandidate pointer. Since HParticleCandidate object cannot be changed 
// because it is used many times in combinatorics, it will contain all additional and to be changed variables

public:

HParticle(HParticleCandidate *pC);
HParticle(HParticle *pC);
virtual ~HParticle() {}

void setId(EParticle n) { dataPair["id"] = static_cast<float>(n); }
void set(std::string name, float val=0.) { dataPair[name] = val; }

int getId() { return static_cast<int>(get("id")); }
EParticle getEId() { return convertId( static_cast<int>(get("id")) ); }
bool isName(std::string name) { if (dataPair.find(name) != dataPair.end()) return true; return false; }
float get(const char* name);
float get(std::string name) { return get(name.c_str()); }
NtuplePairIter begin() { return dataPair.begin(); }
NtuplePairIter end() { return dataPair.end(); }
HParticleCandidate* getCandidate() { return pCand; }

private:

   HParticleCandidate* pCand;
   NtuplePair dataPair;
   NtuplePairIter dataIter;

ClassDef(HParticle, 0)  //
};

#endif
