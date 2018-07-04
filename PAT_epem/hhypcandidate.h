#ifndef HHYPCANDIDATE_H
#define HHYPCANDIDATE_H

#include <TROOT.h>
#include <map>
#include <vector>
#include <utility>
#include <string>
#include "hparticlepool.h"
#include "hparticlecandidate.h"
#include "hparticle.h"
#include "hcommondef.h"


using namespace CommonDefinitions;

// ****************************************************************************
class HHypCandidate : public TObject
{
public:

   HHypCandidate(HPattern *pPat) : pPattern(pPat), isA(true)
   { 
      for (int i=0; i<pPat->getSize(); ++i) 
      {
         slot.push_back( std::pair<EParticle, int>(pPattern->get(i), 0) );
      }
      nPart.resize( pPat->getSize() );
   }
   virtual ~HHypCandidate() 
   {
      partIter = nPart.begin();
      while ( partIter != nPart.end() )
      {
         delete *partIter;
         ++partIter;
      }
   }

   HHypCandidate& operator+=(HParticleCandidate* part);
   HHypCandidate& operator+=(HParticle* part);

   EParticle getId(int n);
   EParticle get(int n) const { if (n>-1 && n<static_cast<int>(nPart.size())) return pPattern->get(n); else return eUnknown; }
   HParticle* getPart(int n=0);
   int getSize()   { return pPattern->getSize(); }
   int getNum(EParticle id) { return pPattern->getNum(id); }
   int getNum(int id) { return pPattern->getNum(id); }
   void setChi2(double chi) { chi2 = chi; }
   double getChi2() const { return chi2; }
   bool isActive() const { return isA; }
   void setActive(bool state) { isA = state; }

protected:

   ParticleCandSeq nPart; // changes each event
   ParticleCandSeqIter partIter;

   HPattern *pPattern;

private:

   int getSlot(EParticle p) 
   {
      int i = 0;
      slotIt = slot.begin();
      while(slotIt != slot.end())
      {
         if ( (*slotIt).first==p && (*slotIt).second==0 ) 
         {
            (*slotIt).second = 1;
            return i;
         }
         ++i;
         ++slotIt;
      }
      return -1;
   }

   std::vector< std::pair<EParticle, int> > slot;
   std::vector< std::pair<EParticle, int> >::iterator slotIt;
   double chi2; // for a given combination to decide which is the best   
   bool isA;

ClassDef(HHypCandidate, 0)  //
};
// ****************************************************************************

#endif // HHYPCANDIDATE_H
