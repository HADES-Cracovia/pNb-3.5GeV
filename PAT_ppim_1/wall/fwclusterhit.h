#ifndef FWCLUSTERHIT_H
#define FWCLUSTERHIT_H

#include <vector>
#include <algorithm>
#include "fwsinglehit.h"

extern int simflag;

class FWClusterHit 
{
      std::vector<FWSingleHit*> hits;
      std::vector<FWSingleHit*>::iterator hitsIt;
      std::vector<unsigned int> trackPool;
      float maxCharge, minCharge;

      float getChargeSum();
      float getSomething( float (FWSingleHit::*fun)() );

      // for pad-hit sorting according to charge
      struct chargesort {
         bool operator() ( FWSingleHit* l, FWSingleHit* r )
         {
            return l->getCharge() > r->getCharge();
         }
      };


   public:
      
      FWClusterHit() : maxCharge(135.), minCharge(25.) { if (simflag==1) { minCharge = 3.; maxCharge = 28.; } }
      FWClusterHit( FWSingleHit* ptr ) : maxCharge(135.), minCharge(25.) { if (simflag==1) { minCharge = 3.; maxCharge = 28.; } addHit( ptr ); }
      FWClusterHit& operator+=(FWSingleHit& src);
      void addHit(FWSingleHit *ptr);

      int getMult() const { return hits.size(); }

      void setMaxCharge(float mc) { maxCharge = mc; }
      void setMinCharge(float mc) { minCharge = mc; }
      float getMaxCharge() const { return maxCharge; }
      float getMinCharge() const { return minCharge; }

      void sort() 
      { 
         trackPool.clear();
         std::sort( hits.begin(), hits.end(), chargesort() ); 
	 for (hitsIt = hits.begin(); hitsIt != hits.end(); ++hitsIt)
	 {
            if ( (*hitsIt)->getTrack(1) > 0 ) trackPool.push_back( (unsigned int)(*hitsIt)->getTrack(1) );
            if ( (*hitsIt)->getTrack(2) > 0 ) trackPool.push_back( (unsigned int)(*hitsIt)->getTrack(2) );
	 }
      }
      bool isActive();

      float getTheta() { return getSomething( &FWSingleHit::getTheta ); }
      float getPhi() { return getSomething( &FWSingleHit::getPhi ); }
      float getDistance() { return getSomething( &FWSingleHit::getDistance ); }
      float getTime(const char* str = "mean");
      float getX() { return getSomething( &FWSingleHit::getX ); }
      float getY() { return getSomething( &FWSingleHit::getY ); }
      float getZ() { return getSomething( &FWSingleHit::getZ ); }
      float getCharge() { return (hits.size() > 0) ? getChargeSum() / hits.size() : 0.; }
      float getBeta(const char* str = "mean");
      float getGamma(const char* str = "mean");
      float getMom(const char* str = "mean");
      float getTrack(unsigned int id = 1); 

};


#endif // FWCLUSTERHIT_H
