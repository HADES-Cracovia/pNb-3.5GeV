#ifndef FWSINGLEHIT_H
#define FWSINGLEHIT_H

#include "hwallhit.h"
#include "hwallhitsim.h"


class FWSingleHit 
{

   float fw_time, fw_charge, fw_cell, fw_theta, fw_phi, 
         fw_distance, fw_x_lab, fw_y_lab, fw_z_lab, fw_beta, fw_p, fw_gamma;
   float track1, track2; // default is -1
   bool  kIsUsed;


public:

   FWSingleHit(HWallHit* ptr);
   ~FWSingleHit() {}

   void setIsUsed( bool k = true ) { kIsUsed = k; }

   bool isActive() { return !kIsUsed; }

   float getTime() { return fw_time; }
   float getCharge() { return fw_charge; }
   float getCell() { return fw_cell; }
   float getTheta() { return fw_theta; }
   float getPhi() { return fw_phi; }
   float getDistance() { return fw_distance; }
   float getX() { return fw_x_lab; }
   float getY() { return fw_y_lab; }
   float getZ() { return fw_z_lab; }
   float getBeta() { return fw_beta; }
   float getGamma() { return fw_gamma; }
   float getMom() { return fw_p; }
   float getTrack(unsigned int id = 1) { return ( id == 1 ) ? track1 : track2; }

};


#endif // FWSINGLEHIT_H
