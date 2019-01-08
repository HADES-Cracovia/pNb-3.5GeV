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
//#include "hcommondef.h"


using namespace std;
//using namespace CommonDefinitions;

Bool_t myselect(HPidTrackCand* pcand);
Bool_t myselecthadron(HPidTrackCand* pcand);


int main(Int_t argc, Char_t **argv)
{
  TString outDir=""; // DO NOT CHANGE IT - HYDRA PARAM
  TString outFile=""; // DO NOT CHANGE IT - HYDRA PARAM

  //***----------------------------------------------------------
  //TString inputDir  ="/net/disk131/beatam/pluto_sim/phasespace_ppee/";
  //TString inputDir  ="/home/hubert/workdir/PAT/indir/";
  TString inputDir  ="/lustre/hades/user/trebacz/dstExp_dp/";
  //TString inputDir  ="/media/FreeAgent Drive/PLUTO/DST/OLD/";
  TString inputFile = argv[1];

  TString output_Dir   = "/lustre/hades/user/przygoda/DPtest/";
  TString output_File  = inputFile;
          output_File.ReplaceAll(".root", "_out.root");


  TStopwatch timer;
  Int_t evN=0;
  Int_t simflag=0, nRunId=0, nEvents=0, startEvt=0;

  // set gHades
  if(gHades == NULL) new Hades;
  gHades->setTreeBufferSize(8000);

  Char_t *context;
  if (simflag)
    context=const_cast<Char_t*>("simulation");
  else
    context=const_cast<Char_t*>("real");

  cout << "Context is " << context << endl;


  //HSpectrometer* spec = gHades->getSetup();

        HPidTrackCleaner* cleaner = new HPidTrackCleaner();
        HPidTrackSorter::setIgnoreRICH();
        HPidTrackSorter::setIgnoreInnerMDC();
        cleaner->setUserSelectionLeptons(myselect);
        cleaner->setUserSelectionHadrons(myselecthadron);
        gHades->getTaskSet(context)->add(cleaner);

  //*** PostDST Analysis Tool - PAT ***

  HOutputFile outputFile( (output_Dir+output_File).Data(), "recreate" );

  HParticlePool myParticles;
  //HParticlePool myParticles( &outputFile );
  myParticles.add("all",eHadronPos,eHadronNeg,eLeptonPos,eLeptonNeg);

  HHypPool myHyps;
  //HHypPool myHyps( &outputFile );
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
  //***------- hadron stuff ---------------------------
  myHyps.add("HpHpHm", eHadronPos,eHadronPos,eHadronNeg);
  //*************************************************** 
  HPidPool myPids( &outputFile );
  //***------------------------------------------------
  myPids.add("HLpLm", "DEpEm",eDeuteron,ePositron,eElectron);
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
  //***------- hadron stuff ---------------------------
  myPids.add("HpHpHm", "PPipPim",eProton,ePiPlus,ePiMinus);
  myPids.add("HpHpHm", "PPPim",eProton,eProton,ePiMinus);
  myPids.add("HpHpHm", "DPipPim",eDeuteron,ePiPlus,ePiMinus);
  //*************************************************** 
  HPidPool myPids_A( &outputFile );
  //***------------------------------------------------
  myPids_A.add("HLpLm", "DEpEm_ID",eDeuteron,ePositron,eElectron);
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
  //***------- hadron stuff ---------------------------
  myPids_A.add("HpHpHm", "PPipPim_ID",eProton,ePiPlus,ePiMinus);
  myPids_A.add("HpHpHm", "PPPim_ID",eProton,eProton,ePiMinus);
  myPids_A.add("HpHpHm", "DPipPim_ID",eDeuteron,ePiPlus,ePiMinus);
  //*************************************************** 
  HPidPool myPids_B( &outputFile );
  //myPids_B.add("HLpLm", "PEpEm_DEDX",eProton,ePositron,eElectron);
  //myPids_B.add("HLpLp", "PEpEp_DEDX",eProton,ePositron,ePositron);
  //myPids_B.add("HLmLm", "PEmEm_DEDX",eProton,eElectron,eElectron);
  //***------------------------------------------------
  //myPids_B.add("HHLpLm", "PPEpEm_DEDX",eProton,eProton,ePositron,eElectron);
  //myPids_B.add("HHLpLp", "PPEpEp_DEDX",eProton,eProton,ePositron,ePositron);
  //myPids_B.add("HHLmLm", "PPEmEm_DEDX",eProton,eProton,eElectron,eElectron);

  //*************************************************** 
  HPidPool myPids_C( &outputFile );
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
  HGraphCut tCut3("all","cuts_ID_dp.root");
  //HDedxCut tCut4("all","M3_DEDXCUTS_PAT.root");

  HTrackPlayer * hyp = new HTrackPlayer( myParticles );
  HParticlePlayer * hyp2 = new HParticlePlayer(myParticles, myHyps);
  HHypPlayer * hyp3 = new HHypPlayer(myHyps, myPids);
  HHypPlayer * hyp3_A = new HHypPlayer(myHyps, myPids_A);
  //HHypPlayer * hyp3_B = new HHypPlayer(myHyps, myPids_B);
  //HHypPlayer * hyp3_C = new HHypPlayer(myHyps, myPids_C);

  hyp->add( tCut );

  hyp3->add( tCut2 );

  hyp3_A->add( tCut2 );
  hyp3_A->add( tCut3 );

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
  gHades->getTaskSet(context)->add(hyp3);
  gHades->getTaskSet(context)->add(hyp3_A);
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


