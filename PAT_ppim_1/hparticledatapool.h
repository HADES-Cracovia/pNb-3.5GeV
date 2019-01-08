#ifndef HPARTICLEDATAPOOL_H
#define HPARTICLEDATAPOOL_H

#include <list>
#include "hcommondef.h"
#include "hiterator.h"
#include "hntuple.h"
#include "houtputfile.h"
#include "houtput.h"
#include "hparticlecandidate.h"
#include "hpattern.h"
#include "heventpool.h"

using namespace CommonDefinitions;


class HParticleDataPool {

public:

   HParticleDataPool();
   virtual ~HParticleDataPool() = 0;

   void addPartCand(EParticle eId, HParticleCand *ptrC);
   void addPartCand(EParticle eId, HParticleCandidate *pCand);
   HParticleCandidate* getParticle(EParticle eId, int n=0);
   HParticleCandidate* getParticle(int n);
   
   bool isPart(EParticle eId) { return (partNum.count(eId)>0); }
   int getNum(EParticle eId) { return partNum[eId]; }
   int getSize() const { return partCand.size(); }

   void removeParticle(HParticleCandidate* pCand);

   MultiParticleIterPair equal_range( EParticle n );
   MultiParticleIter lower_bound( EParticle n );
   MultiParticleIter upper_bound( EParticle n );

   void dump();

protected:

   MultiParticle partCand;
   ParticleNum partNum;


ClassDef(HParticleDataPool, 0) 
};

#endif // HPARTICLEDATAPOOL_H 
