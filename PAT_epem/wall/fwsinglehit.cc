#include <TMath.h>
#include "fwsinglehit.h"

using namespace TMath;

extern int simflag;

// ----------------------------------------------------------------------------
FWSingleHit::FWSingleHit(HWallHit* ptr) : kIsUsed(false)
{
   fw_time = ptr->getTime();
   fw_charge = ptr->getCharge();
   fw_cell = ptr->getCell();
   fw_theta = ptr->getTheta();
   fw_phi = ptr->getPhi();
   fw_distance = ptr->getDistance();
   float x_lab, y_lab, z_lab;
   ptr->getXYZLab( x_lab, y_lab, z_lab );
   fw_x_lab = x_lab;
   fw_y_lab = y_lab;
   fw_z_lab = z_lab;
   // momentum calculation
   fw_beta = ((ptr->getDistance()*cos(ptr->getTheta()*TMath::DegToRad()))/(3*ptr->getTime()*1e2));
   fw_gamma = sqrt(1 - (fw_beta*fw_beta));
   fw_p = (fw_beta*0.93827231)/fw_gamma; // we assume proton mass

   if ( simflag == 0 )
   {
      track1 = -1;
      track2 = -1;
   }
   else if ( simflag == 1 || simflag == 2 )
   {
      // this is not elegant. I know. But what can I do if "embedded" is in fact "real"
      track1 = static_cast< HWallHitSim* >( ptr )->getNTrack1();
      track2 = static_cast< HWallHitSim* >( ptr )->getNTrack2();
   }

}
// ============================================================================

