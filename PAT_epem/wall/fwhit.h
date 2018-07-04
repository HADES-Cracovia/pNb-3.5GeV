#ifndef FWHIT_H
#define FWHIT_H

#include <vector>
#include "fwdetector.h"
#include "fwsinglehit.h"
#include "fwclusterhit.h"
#include "hwallhit.h"


class FWHit {

      FWDetector detector;

      std::vector<FWSingleHit*> hits; // all hits stored in one event
      std::vector<FWSingleHit*>::iterator hitsIt;
      std::vector<FWSingleHit*>::iterator hitsIt2;
      std::vector<FWClusterHit*> clusterhits; // cluster hits made in one event
      std::vector<FWClusterHit*>::iterator clusterhitsIt;

      // for cluster sorting  according to time
      struct timesort {
         bool operator() ( FWClusterHit* l, FWClusterHit* r )
         {
            return l->getTime("min") < r->getTime("min");
         }
      };

      void clearcluster();
      bool check_range(unsigned int i) { if (i > clusterhits.size()) return false; return true; }

   public:

      FWHit() {}
      ~FWHit() { clear(); }

      void clear();
      void addHit( HWallHit* p ) { if (detector.isActive( p->getCell() )) hits.push_back( new FWSingleHit( p ) ); }
      void makeClusters();
    
      unsigned int getClusterMult() { return clusterhits.size(); }
      int getMult() 
      { 
          unsigned int count = 0;
          for (unsigned int i=0; i<clusterhits.size(); ++i) 
	     if ( isActive(i) ) ++count;
          return count;
      }

      bool isActive(unsigned int i) 
      { 
         if (i < clusterhits.size()) 
            return clusterhits[i]->isActive(); 
         return false; 
      }

      float getTheta(unsigned int i) { if (check_range(i)) return clusterhits[i]->getTheta(); return -10000.; }
      float getPhi(unsigned int i) { if (check_range(i)) return clusterhits[i]->getPhi(); return -10000.; }
      float getDistance(unsigned int i) { if (check_range(i)) return clusterhits[i]->getDistance(); return -10000.; }
      float getTime(unsigned int i, const char* str = "mean") { if (check_range(i)) return clusterhits[i]->getTime(str); return -10000.; }
      float getSize(unsigned int i) { if (check_range(i)) return clusterhits[i]->getMult(); return -10000.; }
      float getX(unsigned int i) { if (check_range(i)) return clusterhits[i]->getX(); return -10000.; }
      float getY(unsigned int i) { if (check_range(i)) return clusterhits[i]->getY(); return -10000.; }
      float getZ(unsigned int i) { if (check_range(i)) return clusterhits[i]->getZ(); return -10000.; }
      float getCharge(unsigned int i) { if (check_range(i)) return clusterhits[i]->getCharge(); return -10000.; }
      float getBeta(unsigned int i, const char* str = "mean") { if (check_range(i)) return clusterhits[i]->getBeta(str); return -10000.; }
      float getGamma(unsigned int i, const char* str = "mean") { if (check_range(i)) return clusterhits[i]->getGamma(str); return -10000.; }
      float getMom(unsigned int i, const char* str = "mean") { if (check_range(i)) return clusterhits[i]->getMom(str); return -10000.; }
      float getTrack(unsigned int i, unsigned int track = 1) { if (check_range(i)) return clusterhits[i]->getTrack(track); return -10000.; }

     
};

#endif // FWHIT_H
