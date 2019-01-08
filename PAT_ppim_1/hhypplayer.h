#ifndef HHYPPLAYER_H
#define HHYPPLAYER_H

#include <string>
#include <list>
#include <vector>
#include <TMath.h>
#include "hreconstructor.h"
#include "hparticlecandidate.h"
#include "hhypcandidate.h"
#include "hcommondef.h"
#include "hhyppool.h"
#include "hpidpool.h"
#include "hcut.h"


using namespace CommonDefinitions;

class HHypPlayer : public HReconstructor
{
 public:

   HHypPlayer(HHypPool& refH, HPidPool& refP);
   virtual ~HHypPlayer();

   Bool_t          init();
   Bool_t          reinit() { return kTRUE; }
   Int_t           execute(); // does the loop over all HHypCandidatePaterns and stores in hypSet
   Bool_t          finalize() { return kTRUE; }

   HPidPool* getPool() { return &refPPool; }
   void add(HCut &cut) { vCut.push_back( &cut ); }

 protected:

   HHypPool& refHPool;
   HPidPool& refPPool;

   std::vector<HCut*> vCut;
   std::vector<HCut*>::iterator itCut;


ClassDef(HHypPlayer, 0)   // Fills the HypList with all possible particle combinations
};

#endif // HHYPPLAYER_H
