#include "fwpad.h"

// ----------------------------------------------------------------------------
bool FWPad::isNext(int i) 
{
   padsIt = pads.begin();
   while ( padsIt != pads.end() ) 
   { 
      if ( (*padsIt)->getId() == i) return true;
      ++padsIt;
   }
    return false;
}
// ============================================================================

