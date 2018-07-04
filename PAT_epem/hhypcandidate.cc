
#include "hparticlecandidate.h"
#include "hparticle.h"
#include "hhypcandidate.h"
#include <TMath.h>

using namespace std;

// ****************************************************************************
ClassImp(HHypCandidate)

//--------------------------------------------------------------
HHypCandidate& HHypCandidate::operator+=(HParticleCandidate* part)
{
   //int i = getSlot(part->getEId());
   //nPart[ i ] =  new HParticle( part );
   nPart[ getSlot(part->getEId()) ] =  new HParticle( part );

 return *this;
}

//--------------------------------------------------------------
HHypCandidate& HHypCandidate::operator+=(HParticle* part)
{
   //int i = getSlot(part->getEId());
   //nPart[ i ] =  new HParticle( part );
   nPart[ getSlot(part->getEId()) ] =  new HParticle( part );

 return *this;
}


//--------------------------------------------------------------
EParticle HHypCandidate::getId(int n)
{
   int count = n;
   partIter = nPart.begin();
   while(count > 0)
   {
      ++partIter;
      --count;
      if (partIter == nPart.end()) return eUnknown;
   }

return (*partIter)->getEId();
}

//--------------------------------------------------------------
HParticle* HHypCandidate::getPart(int n)
{
   int count = n;
   partIter = nPart.begin();
   while(count > 0)
   {
      ++partIter;
      --count;
      if (partIter == nPart.end()) return 0;
   }

return *partIter;
}


