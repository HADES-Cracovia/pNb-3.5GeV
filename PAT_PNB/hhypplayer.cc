#include "hhypplayer.h"
#include <TMath.h>


// ****************************************************************************
ClassImp(HHypPlayer)

//-----------------------------------------------------------------------------
HHypPlayer::HHypPlayer(HHypPool& refH, HPidPool& refP) : HReconstructor(const_cast<char*>("temp"),const_cast<char*>("temp")), 
	refHPool(refH), refPPool(refP)
{
}

//-----------------------------------------------------------------------------
HHypPlayer::~HHypPlayer() 
{
}


//-----------------------------------------------------------------------------
Bool_t HHypPlayer::init()
{
   refPPool.set( refHPool.getEventPool() );

return kTRUE;
}


//-----------------------------------------------------------------------------
int HHypPlayer::execute()
{
   refPPool.reset();
   refPPool.loop(refHPool);

#ifdef DEBUG
   refPPool.dump();
#endif

   itCut = vCut.begin();
   while( itCut != vCut.end() )
   {
      (*itCut)->select(*this);
      ++itCut;
   }
   
   refPPool.fill();

return 0;
}
