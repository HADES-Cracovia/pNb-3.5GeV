#ifndef HPATTERN_H
#define HPATTERN_H

#include <string>
#include "hcommondef.h"
#include "houtput.h"

using namespace CommonDefinitions;


   class HPattern 
   {
      public:
         HPattern(HOutputFile *ptr = 0) : sId(""), prongNumber(0), ptrOut(0) { out(ptr); }
         HPattern(std::string name, EParticle p1, HOutputFile *ptr = 0) : 
                           sId(name), prongNumber(1), ptrOut(0) { add(p1); out(ptr, &name); }
         HPattern(std::string name, EParticle p1, EParticle p2, HOutputFile *ptr = 0) : 
                           sId(name), prongNumber(2), ptrOut(0) { add(p1); add(p2); out(ptr, &name); }
         HPattern(std::string name, EParticle p1, EParticle p2, EParticle p3, HOutputFile *ptr = 0) : 
                           sId(name), prongNumber(3), ptrOut(0) { add(p1); add(p2); add(p3); out(ptr, &name); }
         HPattern(std::string name, EParticle p1, EParticle p2, EParticle p3, EParticle p4, HOutputFile *ptr = 0) : 
                           sId(name), prongNumber(4), ptrOut(0) { add(p1); add(p2); add(p3); add(p4); out(ptr, &name); }
         ~HPattern() { if (ptrOut) delete ptrOut; }

         std::string getName() const { return sId; }
	 EParticle get(int n) const { if (n>-1 && n<prongNumber) return partSeq[n]; else return eUnknown; }
         int getNum(EParticle id) { if (partNum.find(id) != partNum.end()) { return partNum[id]; } return 0; }
         int getNum(int id) { EParticle tid = convertId(id); if ( partNum.find(tid) != partNum.end()) { return partNum[tid]; } return 0; }

         int getSize() const { return prongNumber; }
         int operator[](EParticle p) { if (partNum.find(p) != partNum.end()) return partNum[p]; return 0; } 
       
        
         void set(std::string name, float val) { ptrOut->set(name, val); }
         void fill() { if (ptrOut) ptrOut->fill(); } 
         void setSuffix(const char* suf = 0) { ptrOut->setSuffix(suf); }
         void setPrefix(const char* pre = 0) { ptrOut->setPrefix(pre); }
         void setSuffix(std::string suf) { ptrOut->setSuffix(suf); }
         void setPrefix(std::string pre) { ptrOut->setPrefix(pre); }

         ParticleSeq partSeq;
         ParticleNum partNum; // particle_eid and number of particles in a pattern
         ParticleNum partComb; // init at the beginning and calculated each event
         ParticleNumIter partNumIter;
         int number; // number of combinations in a given event

      protected:

         void add(EParticle p) { partSeq.push_back( p ); partNum[p]++; partComb[p] = 0; }
         void out(HOutputFile *p, std::string* n = 0) { if (p) { ptrOut = new HOutput ( p ); if (n) ptrOut->book(n->c_str(), n->c_str()); } }
      
         std::string sId;
         int prongNumber;
         
         HOutput *ptrOut;

   };
   
   struct DelPCObj {
      void operator()(HPattern* ptr) {
         delete ptr;
      }
   };


   struct IsPCName : std::binary_function<HPattern*, const char*, bool> {
      bool operator()(HPattern* ptrE, const char* name) const {
         return ( std::string(name) == ptrE->getName() );
      }
   };

#endif // HPATTERN_H
