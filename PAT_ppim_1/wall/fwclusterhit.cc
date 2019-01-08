#include <iostream>
#include <string>
#include <TMath.h>
#include "fwclusterhit.h"

using namespace TMath;

// ----------------------------------------------------------------------------
float FWClusterHit::getChargeSum()
{
   float res = 0.;
   for (hitsIt = hits.begin(); hitsIt != hits.end(); ++hitsIt) 
   {
      res += (*hitsIt)->getCharge();   
   }
   return res;
}
// ============================================================================

// ----------------------------------------------------------------------------
FWClusterHit& FWClusterHit::operator+=(FWSingleHit& src)
{
   hits.push_back( &src );
   src.setIsUsed();
   return *this;
}
// ============================================================================

// ----------------------------------------------------------------------------
void FWClusterHit::addHit(FWSingleHit *ptr)
{
   hits.push_back( ptr );
   ptr->setIsUsed();
}
// ============================================================================

// ----------------------------------------------------------------------------
bool FWClusterHit::isActive()
{
   for (hitsIt = hits.begin(); hitsIt != hits.end(); ++hitsIt)
   {
       if ( (*hitsIt)->getCharge() > maxCharge || (*hitsIt)->getCharge() < minCharge)
          return false;
   }
 return true;
}
// ============================================================================

// ----------------------------------------------------------------------------
// calculated as mean weight (charge is weight)
float FWClusterHit::getSomething( float (FWSingleHit::*fun)() ) 
{
   float res = 0.;
   for (hitsIt = hits.begin(); hitsIt != hits.end(); ++hitsIt)
   {
       res += ( (*hitsIt->*fun)() ) * ( (*hitsIt)->getCharge());
   }
   float charge = getChargeSum();
   if ( charge > 0. ) res /= charge; else res = 0.;
   return res;
}
// ============================================================================

// ----------------------------------------------------------------------------
float FWClusterHit::getTime(const char* str) 
{
   float res = -1.;
   if ( std::string("max") == str )
   {
      res = 0.;
      for (hitsIt = hits.begin(); hitsIt != hits.end(); ++hitsIt)
      {
          if ( (*hitsIt)->getTime() > res) res = (*hitsIt)->getTime();
      }
   }
   else if ( std::string("min") == str )
   {
      res = 1000000.;
      for (hitsIt = hits.begin(); hitsIt != hits.end(); ++hitsIt)
      {
          if ( (*hitsIt)->getTime() < res) res = (*hitsIt)->getTime();
      }
   }
   else // if ( std::string("mean") == str )
   {
      res = getSomething( &FWSingleHit::getTime );
   }
 return res;
}
// ============================================================================

// ----------------------------------------------------------------------------
float FWClusterHit::getBeta(const char* str) 
{
   // max beta means min time !!!
   float time = -1.;
   if (std::string("max") == str)
   {
      time = getTime("min");
   }
   else if (std::string("min") == str)
   {
      time = getTime("max");
   }
   else
   {
      time = getTime();
   }
 return ((getDistance()*cos(getTheta()*TMath::DegToRad()))/(3*time*1e2));
}
// ============================================================================

// ----------------------------------------------------------------------------
float FWClusterHit::getGamma(const char* str)
{
   float beta = -1.;
   if (std::string("max") == str)
   {
      beta = getBeta("max");
   }
   else if (std::string("min") == str)
   {
      beta = getBeta("min");
   } 
   else
   {
      beta = getBeta();
   }
 return sqrt(1 - (beta*beta));
}
// ============================================================================

// ----------------------------------------------------------------------------
float FWClusterHit::getMom(const char* str)
{
   float beta = -1.;
   float gamma = -1.;
   if (std::string("max") == str)
   {
      beta = getBeta("max");
      gamma = getGamma("max");
   }
   else if (std::string("min") == str)
   {
      beta = getBeta("min");
      gamma = getGamma("min");
   }
   else
   {
      beta = getBeta();
      gamma = getGamma();
   }
      
 return (beta*0.93827231)/gamma; // we assume proton mass
}
// ============================================================================

// ----------------------------------------------------------------------------
float FWClusterHit::getTrack(unsigned int id)
{
   if ( trackPool.size() < id ) return -1;

  return trackPool[ id-1 ];
}
// ============================================================================
