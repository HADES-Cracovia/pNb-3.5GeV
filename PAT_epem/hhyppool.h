#ifndef HHYPPOOL_H
#define HHYPPOOL_H

#define COMB_REPETITION 1

#include <list>
#include <string>
#include <memory>
#include "hcommondef.h"
#include "hntuple.h"
#include "houtputfile.h"
#include "hparticlecandidate.h"
#include "hhypcandidate.h"
#include "hpool.h"
#include "hhypdatapool.h"
#include "hparticleplayerhandle.h"


using namespace CommonDefinitions;


struct DelHypCand {
  void operator()(MultiHypPair obj) {
     delete obj.second;
  }
};


class HHypPool : public HPool, public HHypDataPool {

public:

   HHypPool(HOutputFile *ptr = 0);
   virtual ~HHypPool();

   void reset();
   void loop(HParticlePool& ref);
   void fill();

private:

   int count(HPattern *ptrC, HParticlePool& refPPool);
   void combine(HPattern *ptrC, HParticlePool& refPPool);
 
   std::vector<HHypCandidate*> hypSet;
   std::vector<HHypCandidate*>::iterator hypIt;
   
   std::auto_ptr<HParticlePlayerHandle> ptrFH;

ClassDef(HHypPool, 0) 
};

#endif // HHYPPOOL_H
