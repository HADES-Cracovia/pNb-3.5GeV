#include "hades.h"
#include "hevent.h"
#include "heventheader.h"
#include "hparticledatapool.h"
#include <algorithm>

// ****************************************************************************
ClassImp(HParticleDataPool)



//-----------------------------------------------------------------------------
HParticleDataPool::HParticleDataPool() 
{
}


//-----------------------------------------------------------------------------
HParticleDataPool::~HParticleDataPool() 
{ 
}


//-----------------------------------------------------------------------------
void HParticleDataPool::addPartCand(EParticle eId, HParticleCand *ptrC)
{
   HParticleCandidate *ptr = new HParticleCandidate(ptrC);
   ptr->setId(eId);
   partCand.insert(pair<EParticle, HParticleCandidate*>( eId, ptr ));
   partNum[eId]++;
}
   
//-----------------------------------------------------------------------------
void HParticleDataPool::addPartCand(EParticle eId, HParticleCandidate *pCand)
{
   pCand->setId(eId);
   partCand.insert(pair<EParticle, HParticleCandidate*>( eId, pCand ));
   partNum[eId]++;
}
   

//-----------------------------------------------------------------------------
MultiParticleIterPair HParticleDataPool::equal_range( EParticle eId )
{  
   return partCand.equal_range( eId );
}

//-----------------------------------------------------------------------------
MultiParticleIter HParticleDataPool::lower_bound( EParticle eId )
{
   return partCand.lower_bound( eId );
}  

//-----------------------------------------------------------------------------
MultiParticleIter HParticleDataPool::upper_bound( EParticle eId )
{
           return partCand.upper_bound( eId );
}



//-----------------------------------------------------------------------------
HParticleCandidate* HParticleDataPool::getParticle(EParticle eId, int n)
{
   if ( getNum(eId) == 0 || getNum(eId) < n ) return 0;
   MultiParticleIter iter = lower_bound( eId );
   int count = -1;
   while (++count < n) ++iter;
   return iter->second;
}


//-----------------------------------------------------------------------------
HParticleCandidate* HParticleDataPool::getParticle(int n)
{
   MultiParticleIter iter = partCand.begin();
   int count = -1;
   while (++count < n && iter!=partCand.end() ) ++iter;
   if (iter != partCand.end())
   {
      return iter->second;
   }
return 0;
}


//-----------------------------------------------------------------------------
void HParticleDataPool::removeParticle(HParticleCandidate* pCand)
{
   MultiParticleIter iter = partCand.lower_bound( pCand->getEId() );
   while ( iter!=partCand.upper_bound( pCand->getEId() ) ) 
   {
      if (pCand == iter->second)
      {
         partCand.erase( iter );
         partNum[pCand->getEId()]--;
         break;
      }
      ++iter;
   }
}

//-----------------------------------------------------------------------------
void HParticleDataPool::dump() {
   std::cout << "[DEBUG] HParticlePool size: " << partCand.size() << std::endl;
   std::cout << "[DEBUG] 2("<<partNum[ePositron]<<"), 3("<<partNum[eElectron]<<"), 8("<<partNum[ePiPlus]<<"), 9("<<partNum[ePiMinus]<<"), 14("<<partNum[eProton]<<"), 45("<<partNum[eDeuteron]<<"), 102("<<partNum[eLeptonPos]<<"), 103("<<partNum[eLeptonNeg]<<"), 104("<<partNum[eHadronPos]<<"), 105("<<partNum[eHadronNeg]<<")" << std::endl;
}
