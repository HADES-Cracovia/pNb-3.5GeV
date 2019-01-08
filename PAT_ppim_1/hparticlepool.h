#ifndef HPARTICLEPOOL_H
#define HPARTICLEPOOL_H

#include <list>
#include <map>
#include "hcommondef.h"
#include "hiterator.h"
#include "hntuple.h"
#include "houtputfile.h"
#include "houtput.h"
#include "hparticlecandidate.h"
#include "hpattern.h"
#include "heventpool.h"
#include "hpool.h"
#include "hparticledatapool.h"
#include "hstarthit.h"
#include "wall/fwhit.h"
#include "hparticletracksorter.h"
#include "hparticlebtring.h"

using namespace CommonDefinitions;

class HWallHit;

struct DelParticleCand {
  void operator()(MultiPair obj) {
     delete obj.second;
  }
};



class HParticlePool : public HPool, public HParticleDataPool {

// this data only for FW investigation here
   FWHit fw_hits;

public:

   HParticlePool(HOutputFile *ptr = 0);
   virtual ~HParticlePool();

   void reset();
   void loop(HIterator *dataIt);
   void fill(HIterator *dataIt = 0, HIterator *geantIt = 0, HIterator *startIt = 0, HIterator *pionIt = 0);

ClassDef(HParticlePool, 0) 
};

#endif
