#ifndef HPARTICLEPLAYER_H
#define HPARTICLEPLAYER_H

#include <string>
#include <vector>
#include <list>
#include <TMath.h>
#include "hreconstructor.h"
#include "hparticlecandidate.h"
#include "hhypcandidate.h"
#include "hcommondef.h"
#include "hparticlepool.h"
#include "hhyppool.h"
#include "hcut.h"


using namespace CommonDefinitions;

class HParticlePlayer : public HReconstructor
{
 public:

   HParticlePlayer(HParticlePool& refP, HHypPool& refH);
   virtual ~HParticlePlayer();

   Bool_t          init();
   Bool_t          reinit() { return kTRUE; }
   Int_t           execute(); // does the loop over all HHypCandidatePaterns and stores in hypSet
   Bool_t          finalize() { return kTRUE; }

   void add(HCut &cut) { vCut.push_back( &cut ); }

 protected:
 
   HParticlePool& refPPool;
   HHypPool& refHPool;

   std::vector<HCut*> vCut;
   std::vector<HCut*>::iterator itCut;


ClassDef(HParticlePlayer, 0)   // Fills the HypList with all possible particle combinations
};

#endif // HPARTICLEPLAYER_H
