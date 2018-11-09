#ifndef HPARTICLECANDIDATE_H
#define HPARTICLECANDIDATE_H

#include "hcommondef.h"
#include "hparticlecand.h"
#include <string>

using namespace CommonDefinitions;

class HParticleCandidate {

public:

HParticleCandidate(HParticleCand* ptr);
virtual ~HParticleCandidate() {}

void setId(EParticle n) { dataPair["id"] = static_cast<float>(n); }
void set(const char* name, float val=0.) { dataPair[name] = val; }

int getId() { return static_cast<int>(get("id")); }
EParticle getEId() { return convertId( static_cast<int>(get("id")) ); }
bool isName(const char* name) { if (dataPair.find(name) != dataPair.end()) return true; return false; }
bool isLepton() { if (getId()==102||getId()==103||getId()==2||getId()==3) return true; return false; }
float get(const char* name) { if (dataPair.find(name) != dataPair.end()) return dataPair[name]; return -1.; }
float get(std::string name) { return get(name.c_str()); }
NtuplePairIter begin() { return dataPair.begin(); }
NtuplePairIter end() { return dataPair.end(); }

private:

   NtuplePair dataPair;
   NtuplePairIter dataIter;

ClassDef(HParticleCandidate, 0)  //
};

#endif
