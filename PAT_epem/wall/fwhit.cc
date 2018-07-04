#include <algorithm>
#include <TMath.h>
#include "fwhit.h"

using namespace TMath;

// ----------------------------------------------------------------------------
void FWHit::makeClusters()
{
    if (clusterhits.size() > 0) clearcluster();
    // loop over all hits (fired pads) from FW
    hitsIt = hits.begin();
    while (hitsIt != hits.end())
    {
       if ( (*hitsIt)->isActive() )
       {
          // create new cluster hit and go recursively over all its neighbours
          clusterhits.push_back( new FWClusterHit( *hitsIt ) );
          hitsIt2 = hits.begin();
          while (hitsIt2 != hits.end())
          {
           if ( hitsIt != hitsIt2 && (*hitsIt2)->isActive() && detector.isNext( (int)(*hitsIt)->getCell(), (int)(*hitsIt2)->getCell() ) )
           {
              // there must here be a criterion of time hit separation 
              // 5 ns time difference between hit components
              if ( TMath::Abs( (*hitsIt)->getTime() - (*hitsIt2)->getTime()) < 5. )
              {
                 clusterhits.back()->addHit(*hitsIt2) ;
              }
           }
           ++hitsIt2;
          }
       } 
     ++hitsIt;
    }

    for (clusterhitsIt = clusterhits.begin(); clusterhitsIt != clusterhits.end(); ++clusterhitsIt)
    {
       (*clusterhitsIt)->sort();
    }

    std::sort( clusterhits.begin(), clusterhits.end(), timesort() );
}
// ============================================================================

// ----------------------------------------------------------------------------
void FWHit::clearcluster() 
{ 
   for (clusterhitsIt= clusterhits.begin(); clusterhitsIt!=clusterhits.end(); ++clusterhitsIt) 
   {
      delete *clusterhitsIt; 
   }
   clusterhits.clear(); 
}
// ============================================================================

// ----------------------------------------------------------------------------
void FWHit::clear() 
{ 
   for (hitsIt= hits.begin(); hitsIt!=hits.end(); ++hitsIt) 
   {
      delete *hitsIt; 
   }
   hits.clear(); 
   clearcluster();
}
// ============================================================================
    

