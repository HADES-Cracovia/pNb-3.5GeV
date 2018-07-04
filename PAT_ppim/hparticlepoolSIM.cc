#include "hades.h"
#include "hevent.h"
#include "heventheader.h"
#include "hparticlecandsim.h"
#include "hparticledef.h"
#include "hparticlepool.h"
#include "hwallhit.h"
#include "hgeantkine.h"
#include "hgeantstart.h"
#include <algorithm>
#include <iostream>

using namespace std;

extern int simflag;
extern int startflag;


// ****************************************************************************
ClassImp(HParticlePool)



//-----------------------------------------------------------------------------
HParticlePool::HParticlePool(HOutputFile *ptr) : HPool(ptr), HParticleDataPool() 
{
   reset();
}


//-----------------------------------------------------------------------------
HParticlePool::~HParticlePool() 
{ 
   reset(); 
}


//-----------------------------------------------------------------------------
void HParticlePool::reset()
{
   partNum[ePositron] = 0;
   partNum[eElectron] = 0;
   partNum[ePiPlus] = 0;
   partNum[ePiMinus] = 0;
   partNum[eProton] = 0;
   partNum[eDeuteron] = 0;
   partNum[eLeptonPos] = 0;
   partNum[eLeptonNeg] = 0;
   partNum[eHadronPos] = 0;
   partNum[eHadronNeg] = 0;

   std::for_each( partCand.begin(), partCand.end(), DelParticleCand() ); 
   partCand.clear();
}

//-----------------------------------------------------------------------------
void HParticlePool::loop(HIterator* dataIt)
{
   HParticleCand *ParticleCand    = 0;

   Bool_t isPositive = kFALSE;
   Bool_t isRing = kFALSE;
   UInt_t hposnum = 0, hnegnum = 0, lposnum = 0, lnegnum = 0;

   dataIt->Reset();
   while (((ParticleCand = (HParticleCand *) dataIt->Next()) != 0))
   {
      if ( ParticleCand->isFlagBit(Particle::kIsUsed) == 1 ) {

      if ( ParticleCand->getCharge()>0 ) isPositive = kTRUE;
      else if ( ParticleCand->getCharge()<0 ) isPositive = kFALSE;
      isRing = ParticleCand->getRingCorr();
      if (  isPositive && !isRing ) ++hposnum;
      if (  isPositive &&  isRing ) ++lposnum;
      if ( !isPositive && !isRing ) ++hnegnum;
      if ( !isPositive &&  isRing ) ++lnegnum;

      }
   }
   Bool_t isContinue = kTRUE;
   const unsigned limit = 1000;
   if ( hposnum>limit || hnegnum>limit || lposnum>limit || lnegnum>limit )
   {
         cerr << "Event with more than " << limit << " tracks: ";
         if ( hposnum>limit ) cerr << hposnum << " positive hadrons |"; 
         if ( hnegnum>limit ) cerr << hnegnum << " negarive hadrons |"; 
         if ( lposnum>limit ) cerr << lposnum << " positive leptons |"; 
         if ( lnegnum>limit ) cerr << lnegnum << " negative leptons |"; 
         cerr << " event rejected!" << endl;
         isContinue = kFALSE;
   }

   dataIt->Reset();
   if ( isContinue )
   while (((ParticleCand = (HParticleCand *) dataIt->Next()) != 0))
   {
      if ( ParticleCand->getCharge()>0 ) isPositive = kTRUE;
      else if ( ParticleCand->getCharge()<0 ) isPositive = kFALSE;
      isRing = ParticleCand->getRingCorr();
      //std::cout << " positive - ring " << isPositive << ", " << isRing << std::endl;

      EParticle myEId = eUnknown;
      if (isPositive && isRing) myEId = eLeptonPos;
      else if (isPositive && !isRing) myEId = eHadronPos;
      else if (!isPositive && isRing) myEId = eLeptonNeg;
      else if (!isPositive && !isRing) myEId = eHadronNeg;

         HParticleCandSim *p = 0;
         if ( simflag > 0 ) p = static_cast<HParticleCandSim*>( ParticleCand );
          if (ParticleCand->isFlagBit(Particle::kIsUsed) == 1)
          {
           if ( simflag > 0 )
           {
               if ( p && p->getGeantPID() > 0 )
               {
                  addPartCand(myEId, p);
               }
           } else addPartCand(myEId, ParticleCand);
          }
   }

}


//-----------------------------------------------------------------------------
void HParticlePool::fill(HIterator* dataIt, HIterator *geantIt, HIterator *geantStartIt) 
{
    HParticleCandidate *pc = 0;
    EParticle ePcTab[] = { eHadronPos, eHadronNeg, eLeptonPos, eLeptonNeg };
	unsigned pcTabSize = sizeof(ePcTab)/sizeof(EParticle);
    int count = 0;
    int totalcount = 0;
    int totalmult = 0;

	eventData.update();

    // header information
    HEventHeader *evHeader = gHades->getCurrentEvent()->getHeader();
		 
    eventData.set("trigdownscale", evHeader->getDownscaling() );
    eventData.set("trigdownscaleflag", evHeader->getDownscalingFlag() );
    eventData.set("trigdec", evHeader->getTriggerDecision() );
    eventData.set("trigbit", evHeader->getTBit() );
    eventData.set("event", evHeader->getEventSeqNumber() );
    eventData.set("runnumber", evHeader->getEventRunNumber() );

    for (unsigned i=0; i<pcTabSize; ++i)
	{
	   eventData.set( convertId( ePcTab[i] ) + "_mult" , getNum( ePcTab[i] ) );
	   totalmult += getNum( ePcTab[i] );
	}
	eventData.set("totalmult", totalmult);

	HVertex& vertex = gHades->getCurrentEvent()->getHeader()->getVertex();

	eventData.set("eVert_x", vertex.getX());
	eventData.set("eVert_y", vertex.getY());
	eventData.set("eVert_z", vertex.getZ());
	eventData.set("eVert_chi2", vertex.getChi2());

// ----------- variables for retrieving data from Geant branches
           float weight, geninfo, geninfo1, geninfo2;
           float seloss, sx, sy, stof, smom, slen;
// -------------------------------------------------------------

	   HGeantKine *pKine = 0;
       HGeantStart *GeantStartCand    = 0;
       unsigned scounter = 0, smult = 0;
       // =========================================================
    // ----------- geant start data ----------------------------------
    if ( startflag > 0 ) 
    {
       // re-setting start data
       eventData.set("start_eloss", -100. );
       eventData.set("start_x", -100. );
       eventData.set("start_y", -100. );
       eventData.set("start_tof", -100. );
       eventData.set("start_p", -100. );
       eventData.set("start_trklen", -100. );
       eventData.set("start_cell", -100. );
       eventData.set("start_mult", -100. );
       eventData.set("start_counter", -100. );

       if ( simflag > 0 )
       {
          eventData.set("start_sim_id", -100. );
          eventData.set("start_sim_parentid", -100. );
          eventData.set("start_sim_geninfo", -100. );
          eventData.set("start_sim_geninfo1", -100. );
          eventData.set("start_sim_geninfo2", -100. );
          eventData.set("start_sim_genweight", -100. );
          eventData.set("start_sim_p", -100. );
       }
    }


    if ( geantStartIt != 0 )
    {
       geantStartIt->Reset();
       while (((GeantStartCand = (HGeantStart *) geantStartIt->Next()) != 0))
       {
          ++smult;
          //cout << " smult " << smult << endl;
       }


       geantStartIt->Reset();
       while (((GeantStartCand = (HGeantStart *) geantStartIt->Next()) != 0))
       {
          GeantStartCand->getHit( seloss, sx, sy, stof, smom, slen );
          eventData.set("start_eloss", seloss );
          eventData.set("start_x", sx );
          eventData.set("start_y", sy );
          eventData.set("start_tof", stof );
          eventData.set("start_p", smom );
          eventData.set("start_trklen", slen );
          eventData.set("start_cell", GeantStartCand->getCell() );
          eventData.set("start_mult", smult );
          eventData.set("start_counter", scounter );
           ++scounter;

           // here we correlate with HGeantKine data
           if ( simflag > 0 )
           {
              pKine = 0;
              geantIt->Reset();
              while (((pKine = (HGeantKine *) geantIt->Next()) != 0))
              {
                 if ( GeantStartCand->getTrack() == pKine->getTrack() )
                 {
                    eventData.set("start_sim_id", pKine->getID() );
                    eventData.set("start_sim_parentid", pKine->getParentTrack() );
                    pKine->getGenerator(geninfo, geninfo1, geninfo2);
                    eventData.set("start_sim_geninfo", geninfo );
                    eventData.set("start_sim_geninfo1", geninfo1 );
                    eventData.set("start_sim_geninfo2", geninfo2 );
                    pKine->getGenerator(geninfo, weight);
                    eventData.set("start_sim_genweight", weight );
                    eventData.set("start_sim_p", pKine->getTotalMomentum() );
                    break;
                }
             }
           }

       }
       //  --- eof corr

    }

	// ----------- forward wall data ----------------------------------
	if ( dataIt != 0)
	{
	   // ------------- data reset --------------------------
             eventData.set("fw_mult", -100. );
             eventData.set("fw_cluster_mult", -100. );

             eventData.set("fw_time_1", -100. );
             eventData.set("fw_time_min_1", -100. );
             eventData.set("fw_charge_1", -100. );
             eventData.set("fw_theta_1", -100. );
             eventData.set("fw_phi_1", -100. );
             eventData.set("fw_distance_1", -100. );
             eventData.set("fw_x_lab_1", -100. );
             eventData.set("fw_y_lab_1", -100. );
             eventData.set("fw_z_lab_1", -100. );
             eventData.set("fw_beta_1", -100. );
             eventData.set("fw_p_1", -100. );
             eventData.set("fw_size_1", -100. );
             eventData.set("fw_spectator_1", -100. );
	     // -------------------------------------
             if ( simflag > 0 )
             {
                eventData.set("fw_sim_id_1", -100. );
                eventData.set("fw_sim_parentid_1", -100. );
                eventData.set("fw_sim_geninfo_1", -100. );
                eventData.set("fw_sim_geninfo1_1", -100. );
                eventData.set("fw_sim_geninfo2_1", -100. );
                eventData.set("fw_sim_genweight_1", -100. );
                eventData.set("fw_sim_p_1", -100. );
                eventData.set("fw_tracknr_1", -100. );
                eventData.set("fw_tracknr_12", -100. );
             }

             eventData.set("fw_time_2", -100. );
             eventData.set("fw_time_min_2", -100. );
             eventData.set("fw_charge_2", -100. );
             eventData.set("fw_theta_2", -100. );
             eventData.set("fw_phi_2", -100. );
             eventData.set("fw_distance_2", -100. );
             eventData.set("fw_x_lab_2", -100. );
             eventData.set("fw_y_lab_2", -100. );
             eventData.set("fw_z_lab_2", -100. );
             eventData.set("fw_beta_2", -100. );
             eventData.set("fw_p_2", -100. );
             eventData.set("fw_size_2", -100. );
             eventData.set("fw_spectator_2", -100. );
	     // -------------------------------------
             if ( simflag > 0 )
             {
                eventData.set("fw_sim_id_2", -100. );
                eventData.set("fw_sim_parentid_2", -100. );
                eventData.set("fw_sim_geninfo_2", -100. );
                eventData.set("fw_sim_geninfo1_2", -100. );
                eventData.set("fw_sim_geninfo2_2", -100. );
                eventData.set("fw_sim_genweight_2", -100. );
                eventData.set("fw_sim_p_2", -100. );
                eventData.set("fw_tracknr_2", -100. );
                eventData.set("fw_tracknr_22", -100. );
             }

             eventData.set("fw_time_3", -100. );
             eventData.set("fw_time_min_3", -100. );
             eventData.set("fw_charge_3", -100. );
             eventData.set("fw_theta_3", -100. );
             eventData.set("fw_phi_3", -100. );
             eventData.set("fw_distance_3", -100. );
             eventData.set("fw_x_lab_3", -100. );
             eventData.set("fw_y_lab_3", -100. );
             eventData.set("fw_z_lab_3", -100. );
             eventData.set("fw_beta_3", -100. );
             eventData.set("fw_p_3", -100. );
             eventData.set("fw_size_3", -100. );
             eventData.set("fw_spectator_3", -100. );
	     // -------------------------------------
             if ( simflag > 0 )
             {
                eventData.set("fw_sim_id_3", -100. );
                eventData.set("fw_sim_parentid_3", -100. );
                eventData.set("fw_sim_geninfo_3", -100. );
                eventData.set("fw_sim_geninfo1_3", -100. );
                eventData.set("fw_sim_geninfo2_3", -100. );
                eventData.set("fw_sim_genweight_3", -100. );
                eventData.set("fw_sim_p_3", -100. );
                eventData.set("fw_tracknr_3", -100. );
                eventData.set("fw_tracknr_32", -100. );
             }

       // ---------------------------------------------------
           HWallHit *WallHitCand    = 0;
	   int counter = 0;
	   // =========================================================
           // sorry for this hard-wired value, this is lower charge cut
	   // see charge digitised !!! it is completely different than measured !!!
           double CHARGE_CUT = simflag == 0 ? 25. : 3. ;

	   dataIt->Reset();
	   fw_hits.clear();

	   while (((WallHitCand = (HWallHit *) dataIt->Next()) != 0))
	   {
	      if ( WallHitCand->getCharge() > CHARGE_CUT )
	      {
                 fw_hits.addHit( WallHitCand );
	         ++counter;
	      }
	   }

	   fw_hits.makeClusters();

	   // ============================
	   eventData.set("fw_mult", counter);
	   eventData.set("fw_cluster_mult", fw_hits.getClusterMult() );
	   for (unsigned int i=0; i<fw_hits.getClusterMult(); ++i)
	   {
              if (fw_hits.isActive( i ))
	      {
                 if (fw_hits.getTime(i, "min") > 24.5 && fw_hits.getTime(i, "min") < 27.5)
		 {
		    switch (i) 
		    {
                       case 0: eventData.set("fw_spectator_1", 1);
		               break;
                       case 1: eventData.set("fw_spectator_2", 1);
		               break;
                       case 2: eventData.set("fw_spectator_3", 1);
		               break;
		    }
		 }
		 else 
		 {
		    switch (i)
		    {
		       case 0: eventData.set("fw_spectator_1", 0);
		               break;
		       case 1: eventData.set("fw_spectator_2", 0);
		               break;
		       case 2: eventData.set("fw_spectator_3", 0);
		               break;
		    }
		 }
		 // the rest of data
		 

		 switch (i)
		 {
		    case 0: 
                            eventData.set("fw_time_1", fw_hits.getTime(i) );
                            eventData.set("fw_time_min_1", fw_hits.getTime(i, "min") );
                            eventData.set("fw_charge_1", fw_hits.getCharge(i) );
                            eventData.set("fw_theta_1", fw_hits.getTheta(i) );
                            eventData.set("fw_phi_1", fw_hits.getPhi(i) );
                            eventData.set("fw_distance_1", fw_hits.getDistance(i) );
                            eventData.set("fw_x_lab_1", fw_hits.getX(i) );
                            eventData.set("fw_y_lab_1", fw_hits.getY(i) );
                            eventData.set("fw_z_lab_1", fw_hits.getZ(i) );
                            eventData.set("fw_beta_1", fw_hits.getBeta(i) );
                            eventData.set("fw_p_1", fw_hits.getMom(i) );
                            eventData.set("fw_size_1", fw_hits.getSize(i) );
	   // ----------------------------
	   // here we correlate with HGeantKine data
           if ( simflag > 0 )
           {
	      pKine = 0;
              geantIt->Reset();
	      while (((pKine = (HGeantKine *) geantIt->Next()) != 0))
	      {
                 if ( fw_hits.getTrack(i, 1) == pKine->getTrack()  || fw_hits.getTrack(i, 2) == pKine->getTrack() )
	         {
                    eventData.set("fw_sim_id_1", pKine->getID() );
                    eventData.set("fw_sim_parentid_1", pKine->getParentTrack() );
                    pKine->getGenerator(geninfo, geninfo1, geninfo2);
                    eventData.set("fw_sim_geninfo_1", geninfo );
                    eventData.set("fw_sim_geninfo1_1", geninfo1 );
                    eventData.set("fw_sim_geninfo2_1", geninfo2 );
                    pKine->getGenerator(geninfo, weight);
                    eventData.set("fw_sim_genweight_1", weight );
                    eventData.set("fw_sim_p_1", pKine->getTotalMomentum() );
                    break;
	         }
	      }
	                    eventData.set("fw_tracknr_1", fw_hits.getTrack(i, 1) );
	                    eventData.set("fw_tracknr_12", fw_hits.getTrack(i, 2) );
           }
	   // ----------------------------
			               
			    break;
		    case 1: 
                            eventData.set("fw_time_2", fw_hits.getTime(i) );
                            eventData.set("fw_time_min_2", fw_hits.getTime(i, "min") );
                            eventData.set("fw_charge_2", fw_hits.getCharge(i) );
                            eventData.set("fw_theta_2", fw_hits.getTheta(i) );
                            eventData.set("fw_phi_2", fw_hits.getPhi(i) );
                            eventData.set("fw_distance_2", fw_hits.getDistance(i) );
                            eventData.set("fw_x_lab_2", fw_hits.getX(i) );
                            eventData.set("fw_y_lab_2", fw_hits.getY(i) );
                            eventData.set("fw_z_lab_2", fw_hits.getZ(i) );
                            eventData.set("fw_beta_2", fw_hits.getBeta(i) );
                            eventData.set("fw_p_2", fw_hits.getMom(i) );
                            eventData.set("fw_size_2", fw_hits.getSize(i) );
	   // ----------------------------
	   // here we correlate with HGeantKine data
           if ( simflag > 0 )
           {
	      pKine = 0;
              geantIt->Reset();
	      while (((pKine = (HGeantKine *) geantIt->Next()) != 0))
	      {
                 if ( fw_hits.getTrack(i, 1) == pKine->getTrack()  || fw_hits.getTrack(i, 2) == pKine->getTrack() )
	         {
                    eventData.set("fw_sim_id_2", pKine->getID() );
                    eventData.set("fw_sim_parentid_2", pKine->getParentTrack() );
                    pKine->getGenerator(geninfo, geninfo1, geninfo2);
                    eventData.set("fw_sim_geninfo_2", geninfo );
                    eventData.set("fw_sim_geninfo1_2", geninfo1 );
                    eventData.set("fw_sim_geninfo2_2", geninfo2 );
                    pKine->getGenerator(geninfo, weight);
                    eventData.set("fw_sim_genweight_2", weight );
                    eventData.set("fw_sim_p_2", pKine->getTotalMomentum() );
                    break;
	         }
	      }
	                    eventData.set("fw_tracknr_2", fw_hits.getTrack(i, 1) );
	                    eventData.set("fw_tracknr_22", fw_hits.getTrack(i, 2) );
           }
	   // ----------------------------
			    break;
		    case 2: 
                            eventData.set("fw_time_3", fw_hits.getTime(i) );
                            eventData.set("fw_time_min_3", fw_hits.getTime(i, "min") );
                            eventData.set("fw_charge_3", fw_hits.getCharge(i) );
                            eventData.set("fw_theta_3", fw_hits.getTheta(i) );
                            eventData.set("fw_phi_3", fw_hits.getPhi(i) );
                            eventData.set("fw_distance_3", fw_hits.getDistance(i) );
                            eventData.set("fw_x_lab_3", fw_hits.getX(i) );
                            eventData.set("fw_y_lab_3", fw_hits.getY(i) );
                            eventData.set("fw_z_lab_3", fw_hits.getZ(i) );
                            eventData.set("fw_beta_3", fw_hits.getBeta(i) );
                            eventData.set("fw_p_3", fw_hits.getMom(i) );
                            eventData.set("fw_size_3", fw_hits.getSize(i) );
	   // ----------------------------
	   // here we correlate with HGeantKine data
           if ( simflag > 0 )
           {
	      pKine = 0;
              geantIt->Reset();
	      while (((pKine = (HGeantKine *) geantIt->Next()) != 0))
	      {
                 if ( fw_hits.getTrack(i, 1) == pKine->getTrack()  || fw_hits.getTrack(i, 2) == pKine->getTrack() )
	         {
                    eventData.set("fw_sim_id_3", pKine->getID() );
                    eventData.set("fw_sim_parentid_3", pKine->getParentTrack() );
                    pKine->getGenerator(geninfo, geninfo1, geninfo2);
                    eventData.set("fw_sim_geninfo_3", geninfo );
                    eventData.set("fw_sim_geninfo1_3", geninfo1 );
                    eventData.set("fw_sim_geninfo2_3", geninfo2 );
                    pKine->getGenerator(geninfo, weight);
                    eventData.set("fw_sim_genweight_3", weight );
                    eventData.set("fw_sim_p_3", pKine->getTotalMomentum() );
                    break;
	         }
	      }
	                    eventData.set("fw_tracknr_3", fw_hits.getTrack(i, 1) );
	                    eventData.set("fw_tracknr_32", fw_hits.getTrack(i, 2) );
           }
	   // ----------------------------
			    break;
		 }
		 
	      } // eof isActive hit
	   }

	}
	// ----------------------------------------------------------------
             
    if (ptrFile != 0) 
	{
	   totalcount = 0;
       for (unsigned i=0; i<pcTabSize; ++i)
       for (count = 0; count<getNum( ePcTab[i] ); ++count)
       {  
          // internal loop over all particle (set) patterns
          for (objIt = objectList.begin(); objIt != objectList.end(); ++objIt)
          {
       	     if ( (**objIt)[ ePcTab[i] ] > 0 )
       	     {
                (*objIt)->set("cid", count+1 );
                (*objIt)->set("mult", getNum(ePcTab[i]) );
   
                pc = getParticle( ePcTab[i], count );
                for (NtuplePairIter it = pc->begin(); it != pc->end(); ++it)
                {
                   (*objIt)->set( it->first, it->second );
                }
                
                for (NtuplePairIter it = eventData.begin(); it != eventData.end(); ++it)
                {
                   (*objIt)->set( it->first, it->second );
                }
                (*objIt)->set( "totalcid", ++totalcount );
                
                (*objIt)->fill();
       	     }
          }
          // end of internal loop
       }
	} // if ptrFile
}

