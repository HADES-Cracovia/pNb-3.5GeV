#include "headers.h"
#include "hparasciifileio.h"
#include "hpidparcont.h"
#include "hpidtofrec.h"
#include <getopt.h>
#include <iostream>
#include "hntuple.h"
#include "htrackplayer.h"
#include "htrackcut.h"
#include "htimecut.h"
#include "hgraphcut.h"
#include "hdedxcut.h"
#include "hparticleplayer.h"
#include "hhypplayer.h"
#include "hparticlepool.h"
#include "hhyppool.h"
#include "hpidpool.h"
#include "houtputfile.h"
#include "houtput.h"
#include "heditor.h"
//#include "hcommondef.h"


using namespace std;
//using namespace CommonDefinitions;

Bool_t myselect(HPidTrackCand* pcand); // track cleaner methods
Bool_t myselecthadron(HPidTrackCand* pcand); // track cleaner methods

/*********************************************************************************/
/* Here set whether you run:                                                     */
/* experiment (simflag = 0)                                                      */ 
/* simulation (simflag = 1)                                                      */
/* embedded mode (simflag = 2)                                                   */
/*                                                                               */
/* here set whether you have also Forward Wall data (HWallHit or HWallHitSim)    */
/*********************************************************************************/

Int_t simflag = 2;
Int_t wallflag = 0;

//#define LEPTONS 1
#define HADRONS 1

/*********************************************************************************/

int main(Int_t argc, Char_t **argv)
{
  TString outDir=""; // DO NOT CHANGE IT - HYDRA PARAM
  TString outFile=""; // DO NOT CHANGE IT - HYDRA PARAM

  //***----------------------------------------------------------
  //TString inputDir  ="/net/disk131/beatam/pluto_sim/phasespace_ppee/";
  //TString inputDir  ="/home/hubert/workdir/PAT/indir/";
  //TString inputDir  ="/lustre/hades/user/trebacz/dstExp_dp/";
  //TString inputDir  ="/lustre/hades/user/trebacz/out_sim_dst07_2/";
  //TString inputDir  ="/home/przygoda/FILES/DP/EXP/";
  //TString inputDir  ="/lustre/hades/user/beatam/dst_simFiz/files/pi_ee/";
  //TString inputDir  ="/lustre/hades/user/beatam/dst_simFiz/files/pi_N1440/";
  //TString inputDir  ="/lustre/hades/user/beatam/dst_simFiz/files/delta1000_STANDARD/";
  //TString inputDir  ="/lustre/hades/user/przygoda/apr06/dst/";
  //TString inputDir  ="/lustre/hades/user/sudol/np125/dst_gen2/";
  TString inputDir  ="/lustre/hades/user/beatam/dst_simFiz/files/npip075/";
  //TString inputDir  ="/tmp/";
  TString inputFile = argv[1];

  //TString output_Dir  ="/lustre/hades/user/przygoda/apr07/pat/";
  TString output_Dir  ="/lustre/hades/user/przygoda/apr06/pat_hadron/npip075/";
  //TString output_Dir  ="/lustre/hades/user/przygoda/apr06/pat_hadron/";
  //TString output_Dir  ="/lustre/hades/user/przygoda/FILES/PP/SIM/pi_N1440/";
  //TString output_Dir   = "/tmp/";
  //TString output_Dir   = "/lustre/hades/user/przygoda/FILES/PP/SIM/delta1000_STANDARD/";
  TString output_File  = inputFile;
  TString output_File2  = inputFile;
          output_File.ReplaceAll(".root", "_out.root");
          output_File2.ReplaceAll(".root", "_hadron_out.root");


  TStopwatch timer;
  Int_t evN=0;
  // simflag is now a global variable, please look above the int main() 
  Int_t /*simflag=1,*/ nRunId=0, nEvents=0, startEvt=0;

  // set gHades
  if(gHades == NULL) new Hades;
  gHades->setTreeBufferSize(8000);

  const char *context;
  if (simflag==1) context="simulation";
  else context="real";

  ErrorMsg(INFO, "main", 2, "Context is ",context);

        HPidTrackCleaner* cleaner = new HPidTrackCleaner();
        HPidTrackSorter::setIgnoreRICH();
        HPidTrackSorter::setIgnoreInnerMDC();
        cleaner->setUserSelectionLeptons(myselect);
        cleaner->setUserSelectionHadrons(myselecthadron);
        gHades->getTaskSet(context)->add(cleaner);

  //*** PostDST Analysis Tool - PAT ***

#ifdef LEPTONS
  HOutputFile outputFile( (output_Dir+output_File).Data(), "recreate" );
#endif
#ifdef HADRONS
  HOutputFile outputFile2( (output_Dir+output_File2).Data(), "recreate" );
#endif

  HParticlePool myParticles;
  //HParticlePool myParticles( &outputFile );
  myParticles.add("all",eHadronPos,eHadronNeg,eLeptonPos,eLeptonNeg);

  HHypPool myHyps;
  //HHypPool myHyps( &outputFile );
#ifdef LEPTONS
  myHyps.add("HLpLm",eHadronPos,eLeptonPos,eLeptonNeg);
  myHyps.add("HLpLp",eHadronPos,eLeptonPos,eLeptonPos);
  myHyps.add("HLmLm",eHadronPos,eLeptonNeg,eLeptonNeg);
  //***------------------------------------------------
  myHyps.add("LpLm",eLeptonPos,eLeptonNeg);
  myHyps.add("LpLp",eLeptonPos,eLeptonPos);
  myHyps.add("LmLm",eLeptonNeg,eLeptonNeg);
  //***------------------------------------------------
  myHyps.add("HHLpLm",eHadronPos,eHadronPos,eLeptonPos,eLeptonNeg);
  myHyps.add("HHLpLp",eHadronPos,eHadronPos,eLeptonPos,eLeptonPos);
  myHyps.add("HHLmLm",eHadronPos,eHadronPos,eLeptonNeg,eLeptonNeg);
#endif 
  //***------- hadron stuff ---------------------------
#ifdef HADRONS
  myHyps.add("HpHp", eHadronPos,eHadronPos);
  myHyps.add("HpHm", eHadronPos,eHadronNeg);
  //myHyps.add("HpHpHm", eHadronPos,eHadronPos,eHadronNeg);
  //myHyps.add("HpHpHp", eHadronPos,eHadronPos,eHadronPos);
  //myHyps.add("HpHpHpHm", eHadronPos,eHadronPos,eHadronPos,eHadronNeg);
#endif
  //*************************************************** 
  //HPidPool myPids( &outputFile );
  //HPidPool myPids2( &outputFile2 );
  HPidPool myPids;
  HPidPool myPids2;
  //***------------------------------------------------
#ifdef LEPTONS 
  myPids.add("HLpLm", "DEpEm",eDeuteron,ePositron,eElectron);
  myPids.add("HLpLp", "DEpEp",eDeuteron,ePositron,ePositron);
  myPids.add("HLmLm", "DEmEm",eDeuteron,eElectron,eElectron);
  //***------------------------------------------------
  myPids.add("HLpLm", "PEpEm",eProton,ePositron,eElectron);
  myPids.add("HLpLp", "PEpEp",eProton,ePositron,ePositron);
  myPids.add("HLmLm", "PEmEm",eProton,eElectron,eElectron);
  //***------------------------------------------------
  myPids.add("LpLm", "EpEm",ePositron,eElectron);
  myPids.add("LpLp", "EpEp",ePositron,ePositron);
  myPids.add("LmLm", "EmEm",eElectron,eElectron);
  //***------------------------------------------------
  myPids.add("HHLpLm", "PPEpEm",eProton,eProton,ePositron,eElectron);
  myPids.add("HHLpLp", "PPEpEp",eProton,eProton,ePositron,ePositron);
  myPids.add("HHLmLm", "PPEmEm",eProton,eProton,eElectron,eElectron);
#endif 
  //***------- hadron stuff ---------------------------
#ifdef HADRONS
  myPids2.add("HpHp", "PP",eProton,eProton);
  myPids2.add("HpHp", "PPip",eProton,ePiPlus);
  //myPids2.add("HpHm", "PipPim",ePiPlus,ePiMinus);
  //myPids2.add("HpHpHm", "PPipPim",eProton,ePiPlus,ePiMinus);
  //myPids2.add("HpHpHm", "PPPim",eProton,eProton,ePiMinus);
  //myPids2.add("HpHpHp", "PPPip",eProton,eProton,ePiPlus);
  //myPids2.add("HpHpHpHm", "PPPipPim",eProton,eProton,ePiPlus,ePiMinus);
#endif
  //*************************************************** 
#ifdef LEPTONS 
  HPidPool myPids_A( &outputFile );
#endif
#ifdef HADRONS
  HPidPool myPids_A2( &outputFile2 );
#endif
  //***------------------------------------------------
#ifdef LEPTONS 
  myPids_A.add("HLpLm", "DEpEm_ID",eDeuteron,ePositron,eElectron);
  myPids_A.add("HLpLp", "DEpEp_ID",eDeuteron,ePositron,ePositron);
  myPids_A.add("HLmLm", "DEmEm_ID",eDeuteron,eElectron,eElectron);
  //***------------------------------------------------
  myPids_A.add("HLpLm", "PEpEm_ID",eProton,ePositron,eElectron);
  myPids_A.add("HLpLp", "PEpEp_ID",eProton,ePositron,ePositron);
  myPids_A.add("HLmLm", "PEmEm_ID",eProton,eElectron,eElectron);
  //***------------------------------------------------
  myPids_A.add("LpLm", "EpEm_ID",ePositron,eElectron);
  myPids_A.add("LpLp", "EpEp_ID",ePositron,ePositron);
  myPids_A.add("LmLm", "EmEm_ID",eElectron,eElectron);
  //***------------------------------------------------
  myPids_A.add("HHLpLm", "PPEpEm_ID",eProton,eProton,ePositron,eElectron);
  myPids_A.add("HHLpLp", "PPEpEp_ID",eProton,eProton,ePositron,ePositron);
  myPids_A.add("HHLmLm", "PPEmEm_ID",eProton,eProton,eElectron,eElectron);
#endif 
  //***------- hadron stuff ---------------------------
#ifdef HADRONS
  myPids_A2.add("HpHp", "PP_ID",eProton,eProton);
  myPids_A2.add("HpHp", "PPip_ID",eProton,ePiPlus);
  //myPids_A2.add("HpHm", "PipPim_ID",ePiPlus,ePiMinus);
  //myPids_A2.add("HpHpHm", "PPipPim_ID",eProton,ePiPlus,ePiMinus);
  //myPids_A2.add("HpHpHm", "PPPim_ID",eProton,eProton,ePiMinus);
  //myPids_A2.add("HpHpHp", "PPPip_ID",eProton,eProton,ePiPlus);
  //myPids_A2.add("HpHpHpHm", "PPPipPim_ID",eProton,eProton,ePiPlus,ePiMinus);
#endif
  //*************************************************** 
  //HPidPool myPids_B( &outputFile );
  //myPids_B.add("HLpLm", "PEpEm_DEDX",eProton,ePositron,eElectron);
  //myPids_B.add("HLpLp", "PEpEp_DEDX",eProton,ePositron,ePositron);
  //myPids_B.add("HLmLm", "PEmEm_DEDX",eProton,eElectron,eElectron);
  //***------------------------------------------------
  //myPids_B.add("HHLpLm", "PPEpEm_DEDX",eProton,eProton,ePositron,eElectron);
  //myPids_B.add("HHLpLp", "PPEpEp_DEDX",eProton,eProton,ePositron,ePositron);
  //myPids_B.add("HHLmLm", "PPEmEm_DEDX",eProton,eProton,eElectron,eElectron);

  //*************************************************** 
  //HPidPool myPids_C( &outputFile );
  //myPids_C.add("HLpLm", "PEpEm_ID_DEDX",eProton,ePositron,eElectron);
  //myPids_C.add("HLpLp", "PEpEp_ID_DEDX",eProton,ePositron,ePositron);
  //myPids_C.add("HLmLm", "PEmEm_ID_DEDX",eProton,eElectron,eElectron);
  //***------------------------------------------------
  //myPids_C.add("HHLpLm", "PPEpEm_ID_DEDX",eProton,eProton,ePositron,eElectron);
  //myPids_C.add("HHLpLp", "PPEpEp_ID_DEDX",eProton,eProton,ePositron,ePositron);
  //myPids_C.add("HHLmLm", "PPEmEm_ID_DEDX",eProton,eProton,eElectron,eElectron);
  //*************************************************** 

//  myPids.add("HH", "PP",eProton,eProton);
//  myPids.add("HH", "PPip",eProton,ePiPlus);

  HTrackCut tCut("all");
  HTimeCut tCut2("all");
  HGraphCut tCut3("all","/u/przygoda/PAT/PP125_PID_NEW_CUTS.root");
  //HGraphCut tCut3("all","/u/przygoda/PAT/DP_PID_cuts.root");
  //HDedxCut tCut4("all","M3_DEDXCUTS_PAT.root");

  HTrackPlayer * hyp = new HTrackPlayer( myParticles );
  HParticlePlayer * hyp2 = new HParticlePlayer(myParticles, myHyps);
  HHypPlayer * hyp3 = new HHypPlayer(myHyps, myPids);
  HHypPlayer * hyp3H = new HHypPlayer(myHyps, myPids2);
#ifdef LEPTONS 
  HHypPlayer * hyp3_A = new HHypPlayer(myHyps, myPids_A);
#endif
  HHypPlayer * hyp3_AH = new HHypPlayer(myHyps, myPids_A2);
  //HHypPlayer * hyp3_B = new HHypPlayer(myHyps, myPids_B);
  //HHypPlayer * hyp3_C = new HHypPlayer(myHyps, myPids_C);

  hyp->add( tCut );

  hyp3->add( tCut2 );
  hyp3H->add( tCut2 );

#ifdef LEPTONS 
  hyp3_A->add( tCut2 );
  hyp3_A->add( tCut3 );
#endif
  hyp3_AH->add( tCut2 );
  hyp3_AH->add( tCut3 );

  //hyp3_B->add( tCut2 );
  //hyp3_B->add( tCut4 );

  //hyp3_C->add( tCut2 );
  //hyp3_C->add( tCut3 );
  //hyp3_C->add( tCut4 );



  //Set batch (needed for TCanvas's)

  gROOT->SetBatch();

  //Add input files
  HRootSource *source=new HRootSource;
  source->setDirectory((Text_t*)inputDir.Data());
  source->addFile((Text_t*)inputFile.Data());

  gHades->setDataSource(source);
  if (nRunId) {
    source->setGlobalRefId(nRunId);
    // source->setRefId(nRunId,nRunId);// This might be better
  }

  
  //HRuntimeDb* rtdb=gHades->getRuntimeDb();

  gHades->getTaskSet(context)->add(hyp);
  gHades->getTaskSet(context)->add(hyp2);
#ifdef LEPTONS
  gHades->getTaskSet(context)->add(hyp3);
  gHades->getTaskSet(context)->add(hyp3_A);
#endif
#ifdef HADRONS
  gHades->getTaskSet(context)->add(hyp3H);
  gHades->getTaskSet(context)->add(hyp3_AH);
#endif
  //gHades->getTaskSet(context)->add(hyp3_B);
  //gHades->getTaskSet(context)->add(hyp3_C);


  gHades->getTaskSet(context)->print();

  //------------------------ Initialization ----------------------------
  cout<<"gHades->init()\n";

  gHades->makeCounter(1000);
  if(!gHades->init())
    cerr<<"Error gHades->init() returns false\n";


  //Set output

  if (! (outDir.EndsWith("null") || outDir.EndsWith("none") || outDir=="")) {
    gHades->setOutputFile((Text_t*)outFile.Data(),"RECREATE",const_cast<Text_t*>("Test"),2);
    gHades->makeTree();
  }

  //--------------------------------------------------------------------
        // gHades->printDefinedTaskSets();
        // gHades->setQuietMode(0);
  cout<<"Processing events...\n";
  timer.Reset();
  timer.Start();
  if ((nEvents<1) && (startEvt == 0) ) {
    evN=gHades->eventLoop();
  } else {
    evN=gHades->eventLoop(nEvents,startEvt);
  }

  gHades->getTaskSet(context)->printTimer();

  printf("rtdb deleted\n");
  delete gHades;

  timer.Stop();

  cout<<"------------------------------------------------------\n";
  cout<<"Events processed: "<<evN<<endl;
  cout<<"Real time: "<<timer.RealTime()<<endl;;
  cout<<"Cpu time: "<<timer.CpuTime()<<endl;
  if (evN) cout<<"Performance: "<<timer.CpuTime()/evN<<endl;;

  return 0;
}// END Int_t fill(TString, Int_t , Int_t)





Bool_t myselect(HPidTrackCand* pcand)
{

  HPidTrackData* pTrack  = pcand  -> getTrackData();
  HPidHitData*    pHit   = pcand  -> getHitData();

  // do your selection
  // must return kTRUE if selection criteria is fullfilled

  if(!pHit)                     return kFALSE;
  if(!pTrack)                   return kFALSE;
  if (!pTrack->bIsAccepted[2])  return kFALSE;
  if (!pTrack->bIsAccepted[4])  return kFALSE;
  if (pHit->iSystem<0)          return kFALSE;
  //if (pTrack->nTofRecFlag[4]<1) return kFALSE;
  if (pTrack->fMomenta[4]>3000) return kFALSE;
  if (pTrack->fRKChiSquare>10000.) return kFALSE;
  //if (pTrack->getBeta(4)<0.1)   return kFALSE;
  //if (pTrack->getBeta(4)>2)   return kFALSE;
  if (pHit->fInnerMdcChiSquare==-1)   return kFALSE;
  return kTRUE;
}

Bool_t myselecthadron(HPidTrackCand* pcand)
{

  HPidTrackData* pTrack  = pcand  -> getTrackData();
  HPidHitData*    pHit   = pcand  -> getHitData();

  // do your selection
  // must return kTRUE if selection criteria is fullfilled

  if(!pHit)                     return kFALSE;
  if(!pTrack)                   return kFALSE;
  if (!pTrack->bIsAccepted[2])  return kFALSE;
  if (!pTrack->bIsAccepted[4])  return kFALSE;
  if (pHit->iSystem<0)          return kFALSE;
  if (pTrack->fMomenta[4]>3000) return kFALSE;
  if (pTrack->fRKChiSquare>10000.) return kFALSE;
  //if (pTrack->getBeta(4)<0.1)   return kFALSE;
  //if (pTrack->getBeta(4)>2)   return kFALSE;
  if (pHit->fInnerMdcChiSquare==-1)   return kFALSE;
  return kTRUE;
}


