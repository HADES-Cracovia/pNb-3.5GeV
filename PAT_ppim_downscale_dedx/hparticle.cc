#include "hparticle.h"


// ****************************************************************************
ClassImp(HParticle)

//--------------------------------------------------------------
HParticle::HParticle(HParticleCandidate *pC) : pCand(pC)
{
      set("id", pCand->getEId() );
      set("track_length", -1. );
      set("tof_mom", -1. );
      set("tof_new", -1. );
      set("beta_new", -1. );
}

//--------------------------------------------------------------
HParticle::HParticle(HParticle *pC) 
{
      pCand = pC->getCandidate();
      dataIter = pC->begin();
      while ( dataIter != pC->end() )
      {
         set( dataIter->first, dataIter->second );
         ++dataIter;
      }
}


//--------------------------------------------------------------
float HParticle::get(const char* name) 
{ 
   if ( dataPair.find(name) != dataPair.end() ) 
   {
      return dataPair[name]; 
   }
   else 
   {
      return pCand->get(name);
   }

   return -1.; 
}
