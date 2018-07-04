#include "htaskset.h"
#include "hrootsource.h"
#include "hparticletrackcleaner.h"
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
//#include "hcommondef.h"


using namespace std;
//using namespace CommonDefinitions;

Bool_t myselect(HParticleCand* pcand); // track cleaner methods
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
Int_t wallflag = 1;

#define LEPTONS 1
#define HADRONS 1

/*********************************************************************************/

int main(Int_t argc, Char_t **argv)
{
  TString outDir=""; // DO NOT CHANGE IT - HYDRA PARAM
  TString outFile=""; // DO NOT CHANGE IT - HYDRA PARAM

  //***----------------------------------------------------------
  TString inputDir  ="/lustre/hades/dst/aug11gen0/229/root/";
  //TString inputDir  ="/tmp/";
  TString inputFile = argv[1];

  TString output_Dir  ="/lustre/hades/user/przygoda/aug11/";
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

        HParticleTrackCleaner* cleaner = new HParticleTrackCleaner();
        // HParticleTrackSorter::setIgnoreRICH();
        // HParticleTrackSorter::setIgnoreInnerMDC();
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
  myHyps.add("Lp",eLeptonPos);
  myHyps.add("Lm",eLeptonNeg);
  //***------------------------------------------------
  myHyps.add("LpLm",eLeptonPos,eLeptonNeg);
  myHyps.add("LpLp",eLeptonPos,eLeptonPos);
  myHyps.add("LmLm",eLeptonNeg,eLeptonNeg);
#endif 
  //***------- hadron stuff ---------------------------
#ifdef HADRONS
  myHyps.add("Hp", eHadronPos);
  myHyps.add("Hm", eHadronNeg);
  //myHyps.add("HpHp", eHadronPos,eHadronPos);
#endif
  //*************************************************** 
  //HPidPool myPids( &outputFile );
  HPidPool myPids;
  //HPidPool myPids2( &outputFile2 );
  HPidPool myPids2;
  //***------------------------------------------------
#ifdef LEPTONS 
  //***------------------------------------------------
  myPids.add("LpLm", "EpEm",ePositron,eElectron);
  myPids.add("LpLp", "EpEp",ePositron,ePositron);
  myPids.add("LmLm", "EmEm",eElectron,eElectron);
#endif 
  //***------- hadron stuff ---------------------------
#ifdef HADRONS
  //myPids2.add("HpHp", "PP",eProton,eProton);
  //myPids2.add("HpHp", "PPip",eProton,ePiPlus);
  //myPids2.add("HpHm", "PipPim",ePiPlus,ePiMinus);
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
#endif 
  //***------- hadron stuff ---------------------------
#ifdef HADRONS
  //myPids_A2.add("HpHp", "PP_ID",eProton,eProton);
  //myPids_A2.add("HpHp", "PPip_ID",eProton,ePiPlus);
  //myPids_A2.add("HpHm", "PipPim_ID",ePiPlus,ePiMinus);
#endif

  HTrackCut tCut("all");
  HTimeCut tCut2("all");
  HGraphCut tCut3("all","/u/przygoda/PAT2/PP125_PID_NEW_CUTS.root");
  //HGraphCut tCut3("all","/u/przygoda/PAT2/DP_PID_cuts.root");
  //HDedxCut tCut4("all","M3_DEDXCUTS_PAT.root");

  HTrackPlayer * hyp = new HTrackPlayer( myParticles );
  HParticlePlayer * hyp2 = new HParticlePlayer(myParticles, myHyps);
  HHypPlayer * hyp3 = new HHypPlayer(myHyps, myPids);
  HHypPlayer * hyp3H = new HHypPlayer(myHyps, myPids2);
#ifdef LEPTONS 
  HHypPlayer * hyp3_A = new HHypPlayer(myHyps, myPids_A);
#endif
#ifdef HADRONS 
  HHypPlayer * hyp3_AH = new HHypPlayer(myHyps, myPids_A2);
#endif

  //hyp->add( tCut );

  hyp3->add( tCut2 );
  hyp3H->add( tCut2 );

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





Bool_t myselect(HParticleCand* pcand)
{

  // do your selection
  // must return kTRUE if selection criteria is fullfilled

  if(!pcand)                    return kFALSE;
  if (pcand->getSystem()<0)          return kFALSE;
  //if (pcand->nTofRecFlag[4]<1) return kFALSE;
  if (pcand->getMomentum()>5000) return kFALSE;
  if (pcand->getChi2()>10000.) return kFALSE;
  //if (pcand->getBeta(4)<0.1)   return kFALSE;
  //if (pcand->getBeta(4)>2)   return kFALSE;
  if (pcand->getInnerSegmentChi2()==-1)   return kFALSE;
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
  //if (pcand->getBeta(4)<0.1)   return kFALSE;
  //if (pcand->getBeta(4)>2)   return kFALSE;
  if (pcand->getInnerSegmentChi2()==-1)   return kFALSE;
  return kTRUE;
}


