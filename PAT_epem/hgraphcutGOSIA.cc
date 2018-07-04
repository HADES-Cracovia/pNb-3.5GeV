//-----------------------------------------------------------------------------
#include "hgraphcut.h"
#include "hhypplayer.h"
#include "hcommondef.h"
#include <TError.h>
#include <TMath.h>
#include <string>


// ****************************************************************************
ClassImp(HGraphCut)

using namespace std;
using namespace CommonDefinitions;


//-----------------------------------------------------------------------------
Bool_t HGraphCut::select(HReconstructor& rec)
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
void HGraphCut::graphCut(HHypCandidate *pHyp)
{
   for (int i=0; i<pHyp->getSize(); ++i)
   {
      if ( graphCut( pHyp->getPart(i) ) == false )
	  {
	     pHyp->setActive( false );
	  }
   }
}

    Bool_t HGraphCut::isGoodShower(TF1* shwF, size_t system, double mom, double sum0, double sum1, double sum2)
    {
        // return kTRUE if good shower or no shower at all or momentum < 400
        if(system == 1)  return kTRUE;
        if(sum0 <= 0)  return kTRUE;
        if(mom < 400.) return kTRUE;

        return  sum1 + sum2 - sum0 > shwF->Eval(mom);
    }
//-----------------------------------------------------------------------------
//-------------- GOSIA'S SELECTION AuAu VERSION -------------------------------
bool HGraphCut::graphCut(HParticle *pPart)
{
   id = pPart->getId();
   double mass = mom*mom * (  1. / (beta*beta)  - 1. ) ; // mass squared !!!

   Float_t p = pPart->get("p");
   Float_t s = pPart->get("system");
   Float_t b = pPart->get("beta_new");
   Float_t c = pPart->get("q");
   Float_t shw_sum0 = pPart->get("shw_sum0");
   Float_t shw_sum1 = pPart->get("shw_sum1");
   Float_t shw_sum2 = pPart->get("shw_sum2");

   // GRAPH CUTS definitions

    // ********* SHOWER **************


    // Graph cuts
    Float_t xRich[]={0.,  500., 2000., 0., 0.};
    Float_t yRich[]={3.,  2.5,     0., 0., 3.};
    cutRICH = new TCutG("cutRICH",5,xRich,yRich);
    cutRICH->SetLineColor(2);
    //cout<<"RICHcut"<<endl;
    //cutRICH->Print();


   switch ( id )
   {

       case 2: return true; // return isGoodShower(showerF,s,p,shw_sum0,shw_sum1,shw_sum2);
               break;
       case 3: return true; // return isGoodShower(showerF,s,p,shw_sum0,shw_sum1,shw_sum2);
               break;
       case 8: if (pip_cut) return pip_cut->IsInside( mom, mass );
               // if (pip_cut) return pip_cut->IsInside( beta, mom );
               break;
       case 9: if (pim_cut) return pim_cut->IsInside( mom, mass );
               // if (pim_cut) return pim_cut->IsInside( beta, mom );
               break;
       case 14: return true; 
                if (p_cut) return p_cut->IsInside( mom, mass );
                // if (p_cut) return p_cut->IsInside( beta, mom );
                break;
       case 45: return true; 
                if (d_cut) return d_cut->IsInside( mom, mass );
                // if (d_cut) return d_cut->IsInside( beta, mom );
                break;
       default: return true;


   }

return true;
}



/*
//-----------------------------------------------------------------------------
bool HGraphCut::graphCut(HParticle *pPart)
{
   id = pPart->getId();
   mom = pPart->get("p");
   beta = pPart->get("beta_new");
   double mass = mom*mom * (  1. / (beta*beta)  - 1. ) ; // mass squared !!!

   switch ( id )
   {
       case 2: return true; 
               if (ep_cut) return ep_cut->IsInside( mom, mass );
               // if (ep_cut) return ep_cut->IsInside( beta, mom );
               break;
       case 3: return true; 
               if (em_cut) return em_cut->IsInside( mom, mass );
               // if (em_cut) return em_cut->IsInside( beta, mom );
               break;
       case 8: if (pip_cut) return pip_cut->IsInside( mom, mass );
               // if (pip_cut) return pip_cut->IsInside( beta, mom );
               break;
       case 9: if (pim_cut) return pim_cut->IsInside( mom, mass );
               // if (pim_cut) return pim_cut->IsInside( beta, mom );
               break;
       case 14: return true; 
                if (p_cut) return p_cut->IsInside( mom, mass );
                // if (p_cut) return p_cut->IsInside( beta, mom );
                break;
       case 45: return true; 
                if (d_cut) return d_cut->IsInside( mom, mass );
                // if (d_cut) return d_cut->IsInside( beta, mom );
                break;
       default: return true;
   }

return true;
}
*/


