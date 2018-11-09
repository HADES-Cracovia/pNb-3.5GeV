//-----------------------------------------------------------------------------
#include "hdedxcut.h"
#include "hhypplayer.h"
#include "hcommondef.h"
#include <TError.h>
#include <TMath.h>
#include <string>


// ****************************************************************************
ClassImp(HDedxCut)

using namespace std;
using namespace CommonDefinitions;


//-----------------------------------------------------------------------------
Bool_t HDedxCut::select(HReconstructor& rec)
{
   HHypPlayer& dataRec = dynamic_cast<HHypPlayer&>(rec);
   HPidPool *pPool = dataRec.getPool();
   //cout << "PID POOL : " << pPool->size() << endl;
   HHypCandidate *pCand = 0;
   if ( getName() == string("all") )
   {
      int i = 0;
	  while (  ( pCand = pPool->getHyp( i ) ) != 0 )
	  {
	     graphCut( pCand );
	     ++i;
	  }
   }
   else
   {
      int i = 0;
	  while ( ( pCand = pPool->getHyp( getName(), i ) ) != 0 )
	  {
	     graphCut( pCand );
	     ++i;
	  }
   }

return kTRUE;
}


//-----------------------------------------------------------------------------
void HDedxCut::graphCut(HHypCandidate *pHyp)
{
   for (int i=0; i<pHyp->getSize(); ++i)
   {
      if ( graphCut( pHyp->getPart(i) ) == false )
	  {
	     pHyp->setActive( false );
	  }
   }
}


//-----------------------------------------------------------------------------
bool HDedxCut::graphCut(HParticle *pPart)
{
   id = pPart->getId();
   dedx_in = pPart->get("dedx_inn");
   dedx_out = pPart->get("dedx_out");
   beta = pPart->get("beta_new");
   switch ( id )
   {
       case 2: if (ep_dedx_cut) return ep_dedx_cut->IsInside( beta, dedx_in + dedx_out );
	           break;
       case 3: if (em_dedx_cut) return em_dedx_cut->IsInside( beta, dedx_in + dedx_out );
	           break;
       case 8: if (pip_dedx_cut) return pip_dedx_cut->IsInside( beta, dedx_in + dedx_out );
	           break;
       case 9: if (pim_dedx_cut) return pim_dedx_cut->IsInside( beta, dedx_in + dedx_out );
	           break;
       case 14: if (p_dedx_cut) return p_dedx_cut->IsInside( beta, dedx_in + dedx_out );
	            break;
       default: return true;
   }

return true;
}



