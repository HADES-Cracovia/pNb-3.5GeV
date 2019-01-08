#include "hparticlecandidate.h"
#include "hparticlecandsim.h"
#include "hreconstructor.h"
#include "hiterator.h"
#include "hevent.h"
#include "hcategory.h"
#include "hcategorymanager.h"
#include "hades.h"
#include "hparticlebtring.h"



ClassImp(HParticleCandidate)

    extern int simflag;

HParticleCandidate::HParticleCandidate(HParticleCand* ptr) 
{
   if (ptr)
   {

      set("id", 0. );
      set("pid", ptr->getPID() );
      set("sector", ptr->getSector() );
      set("system", ptr->getSystem() );
      set("p", ptr->getMomentum() );
      set("p_corr_ep", ptr->getCorrectedMomentumPID(2) );
      set("p_corr_em", ptr->getCorrectedMomentumPID(3) );
      set("p_corr_p", ptr->getCorrectedMomentumPID(14) );
      set("p_corr_pip", ptr->getCorrectedMomentumPID(8) );
      set("p_corr_pim", ptr->getCorrectedMomentumPID(9) );
      set("theta", ptr->getTheta() );
      set("phi", ptr->getPhi() );
      set("q", ptr->getCharge() );
      set("theta_rich", ptr->getRichTheta() );
      set("phi_rich", ptr->getRichPhi() );
      set("r", ptr->getR() );
      set("z", ptr->getZ() );
      set("rkchi2", ptr->getChi2() );
      set("mdcinnerchi2", ptr->getInnerSegmentChi2() );
      set("mdcouterchi2", ptr->getOuterSegmentChi2() );
      set("oa_hadr",0.);
      set("oa_lept",0.);
      set("resoultion",0.);
      if ( ptr->getAngleToNearbyFittedInner() < 0 )
          set("oa_hadr", -1*ptr->getAngleToNearbyFittedInner() );
      else if ( ptr->getAngleToNearbyUnfittedInner() < 0 )
          set("oa_hadr", ptr->getAngleToNearbyUnfittedInner() );
      if ( ptr->getAngleToNearbyFittedInner() > 0 )
          set("oa_lept", ptr->getAngleToNearbyFittedInner() );
      else if ( ptr->getAngleToNearbyUnfittedInner() > 0 )
          set("oa_lept", -1*ptr->getAngleToNearbyUnfittedInner() );
      set("isBT", ptr->getRichBTInd() );
      set("isring", ptr->getRingCorr() );


      if ( ptr->getRichBTInd() != -1 ) {
         HCategory* btCat = (HCategory*)HCategoryManager::getCategory(catParticleBtRing);
         HParticleBtRing*     btRing = 0;
         btRing = HCategoryManager::getObject(btRing,btCat,ptr->getRichBTInd());

         set("btChargeSum", btRing->getChargeClus());
         set("btChargeRing", btRing->getChargeRing());
         set("btChi2", btRing->getChi2());
         set("btClusters", btRing->getClusters());
         set("btMaxima", btRing->getMaxima());
         set("btMaximaCharge", btRing->getMaximaCharge());
         set("btMaximaChargeShared", btRing->getMaximaChargeShared());
         set("btMaximaChargeSharedFragment", btRing->getMaximaChargeSharedFragment());
   //getMaximaChargeSharedTrack(Int_t idx)
         set("btMaximaShared", btRing->getMaximaShared());
         set("btMaximaSharedFragment", btRing->getMaximaSharedFragment());
   //getMaximaSharedTrack(Int_t idx)
         set("btMeanDist", btRing->getMeanDist());
         set("btNearbyMaxima", btRing->getNearbyMaxima());
         set("btNearbyMaximaShared", btRing->getNearbyMaximaShared());
   //getNearbyMaximaSharedTrack(Int_t idx)
         set("btPadsClus", btRing->getPadsClus());
         set("btPadsRing", btRing->getPadsRing());
         set("btRingMatrix", btRing->getRingMatrix());
      } else {
         set("btChargeSum", -1 );
         set("btChargeRing", -1 );
         set("btChi2", -1 );
         set("btClusters", -1 );
         set("btMaxima", -1 );
         set("btMaximaCharge", -1 );
         set("btMaximaChargeShared", -1 );
         set("btMaximaChargeSharedFragment", -1 );
         set("btMaximaShared", -1 );
         set("btMaximaSharedFragment", -1 );
         set("btMeanDist", -1 );
         set("btNearbyMaxima", -1 );
         set("btNearbyMaximaShared", -1 );
         set("btPadsClus", -1 );
         set("btPadsRing", -1 );
         set("btRingMatrix", -1 );
      }


      set("isringnomatch", ptr->isRichMatch(kIsNoMatch) );
      set("isringmdc", ptr->isRichMatch(kIsRICHMDC) );
      set("isringtrack", ptr->isRichMatch(kIsRICHRK) );
      set("beta", ptr->getBeta() );
      set("dedx_mdc", ptr->getMdcdEdx() );
      set("dedx_tof", ptr->getTofdEdx() );
      set("shw_sum0", ptr->getShowerSum0() );
      set("shw_sum1", ptr->getShowerSum1() );
      set("shw_sum2", ptr->getShowerSum2() );
      set("rich_amp", ptr->getRingAmplitude() );
      set("rich_padnum", ptr->getRingNumPads() );
      set("rich_centr", ptr->getRingCentroid() );
      set("rich_patmat", ptr->getRingPatternMatrix() );
      set("rich_houtra", ptr->getRingHouTra() );
      set("tof_rec", ptr->getTofRec() );
      set("tracklength", ptr->getDistanceToMetaHit() );
      // ----------------------------- new addons
      set("isOffVertexClust", ptr->isOffVertexClust() );
      set("isUsedVertex", ptr->isUsedVertex() );
      set("isPrimaryVertex", ptr->isPrimaryVertex() );

      if (ptr->getSystem() == 0)
      {
         set("resolution", 250); 
      }
      else
      {
         set("resolution", 150); 
      }

/*
      set("kIsDoubleHitRICH", ptr->isFlagBit(HParticleCand::kIsDoubleHitRICH) );
      set("kIsDoubleHitInnerMDC", ptr->isFlagBit(HParticleCand::kIsDoubleHitInnerMDC) );
      set("kIsDoubleHitOuterMDC", ptr->isFlagBit(HParticleCand::kIsDoubleHitOuterMDC) );
      set("kIsDoubleHitMETA", ptr->isFlagBit(HParticleCand::kIsDoubleHitMETA) );
      set("kIsBestHitRICH", ptr->isFlagBit(HParticleCand::kIsBestHitRICH) );
      set("kIsBestHitInnerMDC", ptr->isFlagBit(HParticleCand::kIsBestHitInnerMDC) );
      set("kIsBestHitOuterMDC", ptr->isFlagBit(HParticleCand::kIsBestHitOuterMDC) );
      set("kIsBestHitMETA", ptr->isFlagBit(HParticleCand::kIsBestHitMETA) );
      set("kIsBestRKMETA", ptr->isFlagBit(HParticleCand::kIsBestRKMETA) );
      set("kIsBestRKRICH", ptr->isFlagBit(HParticleCand::kIsBestRKRICH) );
      set("kIsBestRK", ptr->isFlagBit(HParticleCand::kIsBestRK) );
      set("kIsBestSPLINE", ptr->isFlagBit(HParticleCand::kIsBestSPLINE) );
      set("kIsBestKICK", ptr->isFlagBit(HParticleCand::kIsBestKICK) );
      set("kIsBestRKRKMETA", ptr->isFlagBit(HParticleCand::kIsBestRKRKMETA) );
      set("kIsBestRKRKRICH", ptr->isFlagBit(HParticleCand::kIsBestRKRKRICH) );
      set("kIsBestRKMETAQA", ptr->isFlagBit(HParticleCand::kIsBestRKMETAQA) );
      set("kIsAcceptedHitRICH", ptr->isFlagBit(HParticleCand::kIsAcceptedHitRICH) );
      set("kIsAcceptedHitInnerMDC", ptr->isFlagBit(HParticleCand::kIsAcceptedHitInnerMDC) );
      set("kIsAcceptedHitOuterMDC", ptr->isFlagBit(HParticleCand::kIsAcceptedHitOuterMDC) );
      set("kIsAcceptedHitMETA", ptr->isFlagBit(HParticleCand::kIsAcceptedHitMETA) );
      set("kIsAcceptedRKMETA", ptr->isFlagBit(HParticleCand::kIsAcceptedRKMETA) );
      set("kIsAcceptedRKRICH", ptr->isFlagBit(HParticleCand::kIsAcceptedRKRICH) );
      set("kIsAcceptedRK", ptr->isFlagBit(HParticleCand::kIsAcceptedRK) );
      set("kIsAcceptedSPLINE", ptr->isFlagBit(HParticleCand::kIsAcceptedSPLINE) );
      set("kIsAcceptedKICK", ptr->isFlagBit(HParticleCand::kIsAcceptedKICK) );
      set("kIsAcceptedRKRKMETA", ptr->isFlagBit(HParticleCand::kIsAcceptedRKRKMETA) );
      set("kIsAcceptedRKRKRICH", ptr->isFlagBit(HParticleCand::kIsAcceptedRKRKRICH) );
      set("kIsAcceptedRKMETAQA", ptr->isFlagBit(HParticleCand::kIsAcceptedRKMETAQA) );
*/
      set("kIsLepton", ptr->isFlagBit(kIsLepton) );
      set("kIsUsed", ptr->isFlagBit(kIsUsed) );
//     set("kIsRejected", ptr->isFlagBit(HParticleCand::kIsRejected) );
//     set("isCorrelated", 0 );

      // *********************** below part of data from simulation ******************
      HParticleCandSim *ptrSim = 0;
      if ( simflag == 2 ) 
      {
          ptrSim = static_cast<HParticleCandSim*>( ptr );
      }
      if ( simflag < 2 ) 
      {
          ptrSim = dynamic_cast<HParticleCandSim*>( ptr );
      }
      if ( ptrSim != 0 )
      {
		 set("sim_iscommon", ptrSim->getNDetector() );
		 set("sim_id", ptrSim->getGeantPID() );
		 set("sim_parentid", ptrSim->getGeantParentPID() );
		 set("sim_grandparentid", ptrSim->getGeantGrandParentPID() );
		 set("sim_geninfo", ptrSim->getGeantGeninfo() );
		 set("sim_geninfo1", ptrSim->getGeantGeninfo1() );
		 set("sim_geninfo2", ptrSim->getGeantGeninfo2() );
		 set("sim_genweight", ptrSim->getGeantGenweight() );
		 set("sim_vertexx", ptrSim->getGeantxVertex() );
		 set("sim_vertexy", ptrSim->getGeantyVertex() );
		 set("sim_vertexz", ptrSim->getGeantzVertex() );
		 set("sim_mediumid", ptrSim->getGeantMediumNumber() );
		 set("sim_processid", ptrSim->getGeantCreationMechanism() );
		 set("sim_px", ptrSim->getGeantxMom() );
		 set("sim_py", ptrSim->getGeantyMom() );
		 set("sim_pz", ptrSim->getGeantzMom() );
		 set("sim_p", TMath::Sqrt(ptrSim->getGeantxMom()*ptrSim->getGeantxMom()+ptrSim->getGeantyMom()*ptrSim->getGeantyMom()+ptrSim->getGeantzMom()*ptrSim->getGeantzMom()) );
		 set("sim_isghost", ptrSim->isGhostTrack() );
      }

   }

}
