#include "htaskset.h"
#include "hrootsource.h"
#include "hparticletrackcleaner.h"
#include "hparticletracksorter.h"
#include "hparasciifileio.h"
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
#include "hphysicsconstants.h"
#include <TF1.h>
//#include "hcommondef.h"


using namespace std;
//using namespace CommonDefinitions;

Bool_t myselectlepton(HParticleCand* pcand); // track cleaner methods
Bool_t myselecthadron(HParticleCand* pcand); // track cleaner methods

/*********************************************************************************/
/* Here set whether you run:                                                     */
/* experiment (simflag = 0)                                                      */ 
/* simulation (simflag = 1)                                                      */
/* embedded mode (simflag = 2)                                                   */
/*                                                                               */
/* here set whether you have also Forward Wall data (HWallHit or HWallHitSim)    */
/*********************************************************************************/

Int_t simflag = 0;
Int_t wallflag = 0;
Int_t startflag = 1;
Int_t piontrackerflag = 1;

#define LEPTONS 1
#define HADRONS 1

/*********************************************************************************/

int main(Int_t argc, Char_t **argv)
{
  TString outDir=""; // DO NOT CHANGE IT - HYDRA PARAM
  TString outFile=""; // DO NOT CHANGE IT - HYDRA PARAM

  //***----------------------------------------------------------
  // - - - - sim TString inputDir  ="/hera/hades/user/przygoda/PAT2/";
  //TString inputDir  ="/hera/hades/dst/jul14/online/195/root/"; // CARBON TAGET (DO NOT ADD TO PE TARGET !!!!)
  //TString inputDir  ="/hera/hades/dst/jul14/online/196/root/";
  //TString inputDir  ="/hera/hades/dst/jul14/online/197/root/";
  //TString inputDir  ="/hera/hades/dst/jul14/online/198/root/";
  //TString inputDir  ="/hera/hades/dst/aug14/online/233/root/";
//  TString inputDir  ="/hera/hades/dst/aug14/online/252/656/root/";
//  TString inputDir  ="/hera/hades/dst/aug14/online/235/root/";
  //TString inputDir  ="/hera/hades/dst/aug14/online/235/root/";
//  TString inputDir  ="/hera/hades/dst/aug14/online/236/root/";
 // TString inputDir  ="/hera/hades/dst/aug14/online/237/root/";
  //TString inputDir  ="/hera/hades/dst/aug14/online/238/root/";
  //TString inputDir  ="/hera/hades/dst/aug14/online/239/root/";
  //TString inputDir  ="/hera/hades/dst/aug14/online/240/root/";
  //TString inputDir  ="/hera/hades/dst/aug14/online/241/root/";
  TString inputDir  ="/hera/hades/dst/aug14/online/242/root/";
//  TString inputDir  ="/hera/hades/dst/aug14/online/245/root/";
   // TString inputDir  ="/hera/hades/dst/aug14/online/246/748/root/";
//    TString inputDir  ="/hera/hades/dst/aug14/online/248/656/root/";

  //TString inputDir  ="/hera/hades/user/jbiernat/pionsim/pion_generator_export/PE_july14_geo/";
  //TString inputDir  ="/tmp/";
  TString inputFile = argv[1];

  //TString output_Dir  ="/hera/hades/user/przygoda/PAT2/out/exp/195/";
  //TString output_Dir  ="/hera/hades/user/przygoda/PAT2/out/exp/196/";
  //TString output_Dir  ="/hera/hades/user/przygoda/PAT2/out/exp/197/";
  //TString output_Dir  ="/hera/hades/user/przygoda/PAT2/out/exp/198/";
//  TString output_Dir  ="/hera/hades/user/przygoda/PAT2/out/exp/233/";
 // TString output_Dir  ="/hera/hades/user/przygoda/PAT2/out/exp/233/";
 // TString output_Dir  ="/hera/hades/user/przygoda/PAT2/out/exp/235/";
 // TString output_Dir  ="/hera/hades/user/przygoda/PAT2/out/exp/235/";
//  TString output_Dir  ="/hera/hades/user/przygoda/PAT2/out/exp/236/";
  //TString output_Dir  ="/hera/hades/user/przygoda/PAT2/out/exp/237/";
//  TString output_Dir  ="/hera/hades/user/przygoda/PAT2/out/exp/238/";
  //TString output_Dir  ="/hera/hades/user/przygoda/PAT2/out/exp/239/";
  //TString output_Dir  ="/hera/hades/user/przygoda/PAT2/out/exp/240/";
  //TString output_Dir  ="/hera/hades/user/przygoda/PAT2/out/exp/241/";
  TString output_Dir  ="/hera/hades/user/przygoda/PAT2/out/exp/242_NEW/";
//  TString output_Dir  ="/hera/hades/user/przygoda/PAT2/out/exp/245/";
  //TString output_Dir  ="/hera/hades/user/przygoda/PAT2/out/exp/pt/";
//  TString output_Dir ="/hera/hades/user/${user}/PAT2/out/exp/Mom_748_1/";
//  TString output_Dir ="/hera/hades/user/${user}/PAT2/out/exp/Mom_656_2/";
  //TString output_Dir ="/hera/hades/user/${user}/PAT2/out/exp/C_Mom656_252/";

  //TString output_Dir   = "/tmp/";
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

        //HParticleTrackSorter sorter;
        //sorter.init();  
        HParticleTrackCleaner* cleaner = new HParticleTrackCleaner();
        // HParticleTrackSorter::setIgnoreRICH();
        // HParticleTrackSorter::setIgnoreInnerMDC();
        cleaner->setUserSelectionLeptons(myselectlepton);
        cleaner->setUserSelectionHadrons(myselecthadron);
        gHades->getTaskSet(context)->add(cleaner);


      //--------------------------CONFIGURATION---------------------------------------------------
    //At begin of the program (outside the event loop)
  //      HParticleTrackSorter sorter;
    //sorter.setDebug();                                            // for debug
    //sorter.setPrintLevel(3);                                      // max prints
    //sorter.setIgnoreInnerMDC();                                   // do not reject Double_t inner MDC hits
    //    sorter.setIgnoreOuterMDC();                                   // do not reject Double_t outer MDC hits
    //    sorter.setIgnoreMETA();                                       // do not reject Double_t META hits
    //sorter.setIgnorePreviousIndex();                              // do not reject indices from previous selctions
  //  sorter.init();                                                  // get catgegory pointers etc...

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

//  myParticles.sorter.init();


  HHypPool myHyps;
  //HHypPool myHyps( &outputFile );
  //HHypPool myHyps( &outputFile2 );
#ifdef LEPTONS
  myHyps.add("Lp",eLeptonPos);
  myHyps.add("Lm",eLeptonNeg);
  //***------------------------------------------------
  myHyps.add("LpLm",eLeptonPos,eLeptonNeg);
  myHyps.add("LpLp",eLeptonPos,eLeptonPos);
  myHyps.add("LmLm",eLeptonNeg,eLeptonNeg);
  myHyps.add("LpLmLpLm",eLeptonPos,eLeptonNeg,eLeptonPos,eLeptonNeg);
#endif 
  //***------- hadron stuff ---------------------------
#ifdef HADRONS
  //myHyps.add("Hp", eHadronPos);
  //myHyps.add("Hm", eHadronNeg);
  //myHyps.add("HpHp", eHadronPos,eHadronPos);
  myHyps.add("HpHm", eHadronPos,eHadronNeg);
  myHyps.add("HpHmHpHm", eHadronPos,eHadronNeg,eHadronPos,eHadronNeg);
  myHyps.add("HpHmLpLm", eHadronPos,eHadronNeg,eLeptonPos,eLeptonNeg);
#endif
  //*************************************************** 
#ifdef LEPTONS 
  //HPidPool myPids( &outputFile );
  HPidPool myPids;
#endif
#ifdef HADRONS
  //HPidPool myPids2( &outputFile2 );
  HPidPool myPids2;
#endif
  //***------------------------------------------------
#ifdef LEPTONS 
  //***------------------------------------------------
  myPids.add("LpLm", "EpEm",ePositron,eElectron);
  myPids.add("LpLp", "EpEp",ePositron,ePositron);
  myPids.add("LmLm", "EmEm",eElectron,eElectron);
  myPids.add("LpLmLpLm", "EpEmEpEm",ePositron,eElectron,ePositron,eElectron);
#endif 
  //***------- hadron stuff ---------------------------
#ifdef HADRONS
  //myPids2.add("HpHp", "PP",eProton,eProton);
  //myPids2.add("HpHp", "PPip",eProton,ePiPlus);
  myPids2.add("HpHm", "PipPim",ePiPlus,ePiMinus);
  myPids2.add("HpHm", "PPim",eProton,ePiMinus);
  myPids2.add("HpHmHpHm", "PPimPipPim",eProton,ePiMinus,ePiPlus,ePiMinus);
  myPids2.add("HpHmLpLm", "PipPimEpEm",ePiPlus,ePiMinus,ePositron,eElectron);
#endif
  //*************************************************** 
#ifdef LEPTONS 
  HPidPool myPids_A( &outputFile );
#endif
#ifdef HADRONS
  HPidPool myPids_A2( &outputFile2 );
  //HPidPool myPids_A2;
#endif
  //***------------------------------------------------
#ifdef LEPTONS 
  //***------------------------------------------------
  myPids_A.add("LpLm", "EpEm_ID",ePositron,eElectron);
  myPids_A.add("LpLp", "EpEp_ID",ePositron,ePositron);
  myPids_A.add("LmLm", "EmEm_ID",eElectron,eElectron);
  myPids_A.add("LpLmLpLm", "EpEmEpEm_ID",ePositron,eElectron,ePositron,eElectron);
#endif 
  //***------- hadron stuff ---------------------------
#ifdef HADRONS
  //myPids_A2.add("HpHp", "PP_ID",eProton,eProton);
  //myPids_A2.add("HpHp", "PPip_ID",eProton,ePiPlus);
  myPids_A2.add("HpHm", "PipPim_ID",ePiPlus,ePiMinus);
  myPids_A2.add("HpHm", "PPim_ID",eProton,ePiMinus);
  myPids_A2.add("HpHmHpHm", "PPimPipPim_ID",eProton,ePiMinus,ePiPlus,ePiMinus);
  myPids_A2.add("HpHmLpLm", "PipPimEpEm_ID",ePiPlus,ePiMinus,ePositron,eElectron);
#endif

  HTrackCut tCut("all");
  HTimeCut tCut2("all");
  HGraphCut tCut3("all","/hera/hades/user/przygoda/PAT2/PION_CUTS.root");
  //HGraphCut tCut3("all","/u/przygoda/PAT2/DP_PID_cuts.root");
  //HDedxCut tCut4("all","M3_DEDXCUTS_PAT.root");

  HTrackPlayer * hyp = new HTrackPlayer( myParticles );
  HParticlePlayer * hyp2 = new HParticlePlayer(myParticles, myHyps);
#ifdef LEPTONS 
  HHypPlayer * hyp3 = new HHypPlayer(myHyps, myPids);
  HHypPlayer * hyp3_A = new HHypPlayer(myHyps, myPids_A);
#endif
#ifdef HADRONS 
  HHypPlayer * hyp3H = new HHypPlayer(myHyps, myPids2);
  HHypPlayer * hyp3_AH = new HHypPlayer(myHyps, myPids_A2);
#endif

  //hyp->add( tCut );

#ifdef LEPTONS 
  hyp3->add( tCut2 );
#endif
#ifdef HADRONS 
  hyp3H->add( tCut2 );
#endif

#ifdef LEPTONS 
  hyp3_A->add( tCut2 );
  hyp3_A->add( tCut3 );
#endif
#ifdef HADRONS 
  hyp3_AH->add( tCut2 );
  hyp3_AH->add( tCut3 );
#endif

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



// util selection functions
//------------------------------------------------------------
// calculates velocity as a function of mass and momentum
Double_t fBeta(Double_t* x_val, Double_t* par)
{
    Double_t Momentum = TMath::Abs(x_val[0]);
    Double_t Mass     = par[0];
    Double_t Beta     = 0.0;
    Double_t poverm   = 0.0;

    if(Mass > 0.0) {
       poverm = Momentum/Mass;
       Beta   = poverm*1.0/(sqrt(poverm*poverm+1.0));
    }
    return Beta;
}

Bool_t isGoodRich(HParticleCand* cand){
    // return kTRUE if good rich
    //Float_t fRingPM  = cand->getRingPatternMatrix();
    //Float_t fRingNP  = cand->getRingNumPads();
    //Float_t fRingRC  = cand->getRingCentroid();
//    Float_t fRingAC = cand->getRingAmplitude()/cand->getRingNumPads();
//    if(fRingAC>45.){ return  kTRUE; } else return kFALSE;
    return kTRUE;
}




Bool_t myselecthadron(HParticleCand* pcand)
{

  // do your selection
  // must return kTRUE if selection criteria is fullfilled

  if(!pcand)                   return kFALSE;
  if (pcand->getSystem()<0)          return kFALSE;
  if (pcand->getMomentum()>5000) return kFALSE;
  if (pcand->getChi2()>10000.) return kFALSE;
  if (pcand->getBeta()<0.01)   return kFALSE;
  //if (pcand->getBeta(4)>2)   return kFALSE;
  if (pcand->getInnerSegmentChi2()==-1)   return kFALSE;
  // contemporary conditions:

    if (pcand->isFlagAND(4,
		       Particle::kIsAcceptedHitInnerMDC,
		       Particle::kIsAcceptedHitOuterMDC,
		       Particle::kIsAcceptedHitMETA,
		       Particle::kIsAcceptedRK)) return kTRUE;


  return kTRUE;
}

Bool_t myselectlepton(HParticleCand* pcand)
{

  // do your selection
  // must return kTRUE if selection criteria is fullfilled

  if(!pcand)                    return kFALSE;
  if (pcand->getSystem()<0)          return kFALSE;
  //if (pcand->nTofRecFlag[4]<1) return kFALSE;
  if (pcand->getMomentum()>5000) return kFALSE;
  if (pcand->getChi2()>10000.) return kFALSE;
  if (pcand->getBeta()<0.01)   return kFALSE;
  //if (pcand->getBeta(4)>2)   return kFALSE;
  if (pcand->getInnerSegmentChi2()==-1)   return kFALSE;
  // contemporary conditions:

  if (pcand->isFlagAND(5,
		       Particle::kIsAcceptedHitRICH,
		       Particle::kIsAcceptedHitInnerMDC,
		       Particle::kIsAcceptedHitOuterMDC,
		       Particle::kIsAcceptedHitMETA,
		       Particle::kIsAcceptedRK)) return kTRUE;

  return kTRUE;
}


