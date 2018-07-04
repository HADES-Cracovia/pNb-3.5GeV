#ifndef HHYPDATAPOOL_H
#define HHYPDATAPOOL_H

#include <list>
#include <string>
#include <memory>
#include "hcommondef.h"
#include "hntuple.h"
#include "houtputfile.h"
#include "hparticlecandidate.h"
#include "hhypcandidate.h"
#include "hparticleplayerhandle.h"


using namespace CommonDefinitions;


class HHypDataPool {

public:

   HHypDataPool();
   virtual ~HHypDataPool() = 0;

   void addHypCand(std::string name, HHypCandidate* ptrC);
   HHypCandidate* getHyp(std::string name, int n=0);
   HHypCandidate* getHyp(unsigned int n=0);
   
   std::string getName(int n);
   int getSize()   { return hypNum.size(); }
   int size()   { return hypCand.size(); }
   int getNum(std::string name) { return hypNum[name]; }
   int getNum(int n) { return getNum( getName(n) ); }

   MultiHypIterPair equal_range( std::string name );
   MultiHypIter lower_bound( std::string name );
   MultiHypIter upper_bound( std::string name );

   void dump();


protected:

   MultiHyp hypCand;
   HypNum hypNum;
   MultiHypIter hypIter;

   ParticleNum numId;

   
ClassDef(HHypDataPool, 0) 
};


#endif // HHYPDATAPOOL_H
