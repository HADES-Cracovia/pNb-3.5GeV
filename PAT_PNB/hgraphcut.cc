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
  //cout << OB"PID POOL : " << pPool->size() << endl;
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
  //cout << " - - - " << endl;
}


//-----------------------------------------------------------------------------
bool HGraphCut::graphCut(HParticle *pPart)
{
  id = pPart->getId();
  mom = pPart->get("p");
  beta = pPart->get("beta_new");
  // double mass = mom / ( beta * TMath::Sqrt( 1. / ( 1. - (beta*beta) ) ) );
  double mass = mom*mom * (  1. / (beta*beta)  - 1. ) ; // mass squared !!!
  /*
    cout<<endl;
    cout<<"particle id: "<<id<<endl;
    cout<<"particle p: "<<mom<<endl;
    cout<<"particle beta: "<<beta<<endl;
    cout<<"particle mass: "<<sqrt(mass);
  */
  switch ( id )
    {
    case 2: if ( beta > 0.8 )
	return true; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! always ok
      else return false;
      if (ep_cut) return ep_cut->IsInside( beta, mom );
      break;
      
    case 3: if ( beta > 0.8 )
	return true; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! always ok
      else return false;
      if (em_cut) return em_cut->IsInside( beta, mom );
      break;
      
    case 8: if ( sqrt(mass) < 240 && sqrt(mass)>40 )
	return true;
      else return false;
      return true;
      if (pip_cut) return pip_cut->IsInside( mom, mass );
      //cout << "8 masa: " << mass << "    ";
      //if ( mass > 5000. && mass < 30000. ) cout << " 8 OK "; else cout << "8 NO!!! ";
      //if ( mass > 5000. && mass < 30000. ) return true; else return false;
      break;
      
    case 9: if ( sqrt(mass) < 240 && sqrt(mass)>40 ) return true; else return false;
      //return true;
      //if (pip_cut) return ( mass > 4000. && pip_cut->IsInside( mom, mass ) ); // same for pi-
      //cout << "9 masa: " << mass << "    ";
      //if ( mass > 5000. && mass < 30000. ) cout << " 9 OK "; else cout << " 9 NO!!! ";
      //if ( mass > 5000. && mass < 30000. ) return true; else return false;
      //if (pim_cut) return pim_cut->IsInside( mom, mass ); 
      break;
      
    case 14: if ( sqrt(mass) > 750 && sqrt(mass) <1027 )
	{
	  //	  cout<<endl<<"true proton"<<endl;
	  return true;
	}
      else
	{
	  // cout<<endl<<"false proton"<<endl;
	  return false;
	}
      //return true; 
      //if (p_cut) return p_cut->IsInside( mom, mass );
      break;
      
    case 45: return true; // !!!! always ok
      //if (d_cut) return d_cut->IsInside( mom, mass );
      if (p_cut) return p_cut->IsInside( mom, mass );
      break;
    default: return true;
    }

  return true;
}



