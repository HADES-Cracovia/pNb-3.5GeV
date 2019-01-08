#include "hparticleplayer.h"
#include <TMath.h>

using namespace std;

// ****************************************************************************
ClassImp(HParticlePlayer)

//-----------------------------------------------------------------------------
HParticlePlayer::HParticlePlayer(HParticlePool& refP, HHypPool& refH) : HReconstructor(const_cast<char*>("temp"),const_cast<char*>("temp")), 
	refPPool(refP), refHPool(refH)
{
}

//-----------------------------------------------------------------------------
HParticlePlayer::~HParticlePlayer() 
{
}


//-----------------------------------------------------------------------------
Bool_t HParticlePlayer::init() { 

   refHPool.set( refPPool.getEventPool() );

return kTRUE; 
}



//-----------------------------------------------------------------------------
int HParticlePlayer::execute()
{
   refHPool.reset();
   refHPool.loop(refPPool);

#ifdef DEBUG
   refHPool.dump();
#endif
   
   itCut = vCut.begin();
   while( itCut != vCut.end() )
   {
      (*itCut)->select(*this);
      ++itCut;
   }
   
   refHPool.fill();

return 0;
}
