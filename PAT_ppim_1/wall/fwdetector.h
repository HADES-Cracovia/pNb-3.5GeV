#ifndef FWDETECTOR_H
#define FWDETECTOR_H

#include <vector>
#include "fwpad.h"


class FWDetector {

std::vector<FWPad*> pads;
std::vector<FWPad*>::iterator padsIt;
static const int neighbours[304][9];
static const int activepads[304];

public:

   FWDetector();
   ~FWDetector();
   bool isNext(int mainhit, int nexthit);
   bool isActive(unsigned int id) { return static_cast<bool>( activepads[ id ] ); }

};


#endif // FWDETECTOR_H
