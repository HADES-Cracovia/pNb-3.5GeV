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
#include "henergylosscorrpar.h"
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
Int_t startflag = 0;

//#define LEPTONS 1
#define HADRONS 1

/*********************************************************************************/
/*********************************************************************************/

int main(Int_t argc, Char_t **argv)
{
  HEnergyLossCorrPar enLossCorr;
  //enLossCorr.setDefaultPar("jul14_PE"); // "jul14_W" - Wolfram target, "jul14_C3" - Carbon 3 segments, "jul14_PE" & "aug14_PE" - PE target, "aug14_C7" - Carbon 7 segments
  //enLossCorr.setDefaultPar("jul14_C3"); // "jul14_W" - Wolfram target, "jul14_C3" - Carbon 3 segments, "jul14_PE" & "aug14_PE" - PE target, "aug14_C7" - Carbon 7 segments
  //enLossCorr.setDefaultPar("aug14_PE"); // "jul14_W" - Wolfram target, "jul14_C3" - Carbon 3 segments, "jul14_PE" & "aug14_PE" - PE target, "aug14_C7" - Carbon 7 segments
  //enLossCorr.setDefaultPar("aug14_C7"); // "jul14_W" - Wolfram target, "jul14_C3" - Carbon 3 segments, "jul14_PE" & "aug14_PE" - PE target, "aug14_C7" - Carbon 7 segments

  TString outDir=""; // DO NOT CHANGE IT - HYDRA PARAM
  TString outFile=""; // DO NOT CHANGE IT - HYDRA PARAM

  //***----------------------------------------------------------
  // - - - - sim TString inputDir  ="/hera/hades/user/przygoda/PAT2/";
  ////******************************************************
  //TString inputDir  ="/lustre/nyx/hades/user/przygoda/PION/DST/FILES/ELASTIC_GEN2_NEW/root/";
  ////******************************************************
  ////******************************************************
  TString inputDir;
  //TString inputDir  ="/lustre/nyx/hades/dst/sep08_BT/gen2/288/root/";
  //TString inputDir  ="/lustre/nyx/hades/user/kempter/dst/sep08_BT/gen1/288/root/";
  //TString inputDir  ="/lustre/nyx/hades/dst/aug14/gen2/237/690/root/";
  ////******************************************************
  ////******************************************************

  TString inputFile = argv[1];

  
  //get file name from path
  inputDir=inputFile;
  inputDir.Resize(inputFile.Last('/')+1);
  inputFile=inputFile(inputFile.Last('/')+1,inputFile.Length()-inputFile.Last('/')-1);

  //*******************************************
  //*******************************************
  TString output_Dir ="/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_1/";
  //TString output_Dir ="/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/day280/";
  //TString output_Dir ="/lustre/nyx/hades/user/knowakow/PION/FILES/288_time/";
  //*******************************************
  //*******************************************
  //*******************************************
  //*******************************************

  
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
  //HParticleTrackSorter& sorter = cleaner->getSorter();
  //sorter.resetFlags(kTRUE,kTRUE,kTRUE,kTRUE);
  //sorter.fill(HParticleTrackSorter::selectLeptons);
  //sorter.selectBest(HParticleTrackSorter::kIsBestRK,HParticleTrackSorter::kIsLepton);
  HParticleTrackSorter::setBetaLeptonCut(0.5);
  //sorter.fill(HParticleTrackSorter::selectHadrons);
  //sorter.selectBest(HParticleTrackSorter::kIsBestRK,HParticleTrackSorter::kIsHadron);
  //sorter.init();  
  // HParticleTrackSorter::setIgnoreRICH();
  // HParticleTrackSorter::setIgnoreInnerMDC();
  //cleaner->setUserSelectionLeptons(myselectlepton);
  //cleaner->setUserSelectionHadrons(myselecthadron);
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
    //myHyps.add("HLpLm",eHadronPos,eLeptonPos,eLeptonNeg);
    //myHyps.add("HLpLp",eHadronPos,eLeptonPos,eLeptonPos);
    //myHyps.add("HLmLm",eHadronPos,eLeptonNeg,eLeptonNeg);
    //***------------------------------------------------
    myHyps.add("LpLm",eLeptonPos,eLeptonNeg);
    myHyps.add("LpLp",eLeptonPos,eLeptonPos);
    myHyps.add("LmLm",eLeptonNeg,eLeptonNeg);
    //***------------------------------------------------
    myHyps.add("HLpLm",eHadronPos,eHadronPos,eLeptonPos,eLeptonNeg);
    myHyps.add("HLpLp",eHadronPos,eHadronPos,eLeptonPos,eLeptonPos);
    myHyps.add("HLmLm",eHadronPos,eHadronPos,eLeptonNeg,eLeptonNeg);
#endif
    //***------- hadron stuff ---------------------------
#ifdef HADRONS
    //myHyps.add("HpHp", eHadronPos,eHadronPos);
    //myHyps.add("HpHm", eHadronPos,eHadronNeg);
    myHyps.add("HpHm", eHadronPos,eHadronNeg);
    myHyps.add("HpHnHp", eHadronPos,eHadronPos,eHadronPos);
    myHyps.add("HpHmHpHm", eHadronPos,eHadronNeg,eHadronPos,eHadronNeg);
#endif
    //***************************************************
    //HPidPool myPids( &outputFile );
    HPidPool myPids;
    //HPidPool myPids2( &outputFile2 );
    HPidPool myPids2;
    //***------------------------------------------------
#ifdef LEPTONS
    //myPids.add("HLpLm", "DEpEm",eDeuteron,ePositron,eElectron);
    //myPids.add("HLpLp", "DEpEp",eDeuteron,ePositron,ePositron);
    //myPids.add("HLmLm", "DEmEm",eDeuteron,eElectron,eElectron);
    //***------------------------------------------------
    myPids.add("HLpLm", "PEpEm",eProton,ePositron,eElectron);
    myPids.add("HLpLp", "PEpEp",eProton,ePositron,ePositron);
    myPids.add("HLmLm", "PEmEm",eProton,eElectron,eElectron);
    //***------------------------------------------------
    myPids.add("LpLm", "EpEm",ePositron,eElectron);
    myPids.add("LpLp", "EpEp",ePositron,ePositron);
    myPids.add("LmLm", "EmEm",eElectron,eElectron);
    //***------------------------------------------------
    //myPids.add("HHLpLm", "PPEpEm",eProton,eProton,ePositron,eElectron);
    //myPids.add("HHLpLp", "PPEpEp",eProton,eProton,ePositron,ePositron);
    //myPids.add("HHLmLm", "PPEmEm",eProton,eProton,eElectron,eElectron);
#endif
    //***------- hadron stuff ---------------------------
#ifdef HADRONS
    //myPids2.add("HpHp", "PP",eProton,eProton);
    //myPids2.add("HpHp", "PPip",eProton,ePiPlus);
    //myPids2.add("HpHm", "PPim",eProton,ePiMinus);
    //myPids2.add("HpHm", "PipPim",ePiPlus,ePiMinus);
    myPids2.add("HpHm", "PPim",eProton,ePiMinus);
    //myPids2.add("HpHpHm", "PPPim",eProton,eProton,ePiMinus);
    myPids2.add("HpHnHp", "PPimPip",eProton,ePiMinus,ePiPlus);
    myPids2.add("HpHmHpHm", "PPPipPim",eProton,ePiMinus,ePiPlus,ePiMinus);
#endif
    //***************************************************
#ifdef LEPTONS
    HPidPool myPids_A( &outputFile );
    //HPidPool myPids_A;
#endif
#ifdef HADRONS
    HPidPool myPids_A2( &outputFile2 );
    //HPidPool myPids_A2;
#endif
    //***------------------------------------------------
#ifdef LEPTONS
    //myPids_A.add("HLpLm", "DEpEm_ID",eDeuteron,ePositron,eElectron);
    //myPids_A.add("HLpLp", "DEpEp_ID",eDeuteron,ePositron,ePositron);
    //myPids_A.add("HLmLm", "DEmEm_ID",eDeuteron,eElectron,eElectron);
    //***------------------------------------------------
    myPids_A.add("HLpLm", "PEpEm_ID",eProton,ePositron,eElectron);
    myPids_A.add("HLpLp", "PEpEp_ID",eProton,ePositron,ePositron);
    myPids_A.add("HLmLm", "PEmEm_ID",eProton,eElectron,eElectron);
    //***------------------------------------------------
    myPids_A.add("LpLm", "EpEm_ID",ePositron,eElectron);
    myPids_A.add("LpLp", "EpEp_ID",ePositron,ePositron);
    myPids_A.add("LmLm", "EmEm_ID",eElectron,eElectron);
    //***------------------------------------------------
    //myPids_A.add("HHLpLm", "PPEpEm_ID",eProton,eProton,ePositron,eElectron);
    //myPids_A.add("HHLpLp", "PPEpEp_ID",eProton,eProton,ePositron,ePositron);
    //myPids_A.add("HHLmLm", "PPEmEm_ID",eProton,eProton,eElectron,eElectron);
#endif
    //***------- hadron stuff ---------------------------
#ifdef HADRONS
    //myPids_A2.add("HpHp", "PP_ID",eProton,eProton);
    //myPids_A2.add("HpHp", "PPip_ID",eProton,ePiPlus);
    //myPids_A2.add("HpHm", "PipPim_ID",ePiPlus,ePiMinus);
    myPids_A2.add("HpHm", "PPim_ID",eProton,ePiMinus);
    //myPids_A2.add("HpHpHm", "PPPim_ID",eProton,eProton,ePiMinus);
    myPids_A2.add("HpHnHp", "PPimPip_ID",eProton,ePiMinus,ePiPlus);
    myPids_A2.add("HpHmHpHm", "PPimPipPim_ID",eProton,ePiMinus,ePiPlus,ePiMinus);
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

    //HTrackCut tCut("all");
    HTimeCut tCut2("all");
    //HGraphCut tCut3("all","/u/przygoda/PAT/PP125_PID_NEW_CUTS.root");
    // poprzedni staranny EXP HGraphCut tCut3("all","/u/przygoda/PAT/PP125_p_pip_CUT.root");
    //HGraphCut tCut3("all","/hera/hades/user/przygoda/PAT35/pp35_cuts.root"); // mass^2 versus mom
    HGraphCut tCut3("all","/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/de_dx_cut.root");
    //HGraphCut tCut3("all","/u/przygoda/PAT/PP125_p_p_CUT.root");
    //HGraphCut tCut3("all","/u/przygoda/PAT/PP_END_CUTS.root");
    // dla testow
    //HGraphCut tCut3("all","/u/przygoda/PAT/pp_fake_cuts.root");
    //HGraphCut tCut3("all","/u/przygoda/PAT/DP_PID_cuts.root");
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
    //HHypPlayer * hyp3_B = new HHypPlayer(myHyps, myPids_B);
    //HHypPlayer * hyp3_C = new HHypPlayer(myHyps, myPids_C);
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



// **************************** BELOW OBSOLETE FUNCTIONS *************************************
// **************************** BELOW OBSOLETE FUNCTIONS *************************************
// **************************** BELOW OBSOLETE FUNCTIONS *************************************
// **************************** BELOW OBSOLETE FUNCTIONS *************************************
// **************************** BELOW OBSOLETE FUNCTIONS *************************************
// **************************** BELOW OBSOLETE FUNCTIONS *************************************

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



Bool_t myselectlepton(HParticleCand* pcand)
{

  // do your selection
  // must return kTRUE if selection criteria is fullfilled

  if(!pcand)                    return kFALSE;
  if (pcand->getSystem()<0)          return kFALSE;
  if (pcand->getMomentum()>5000) return kFALSE;
  if (pcand->getChi2()>1000.) return kFALSE;
  if (pcand->getBeta()<0.01)   return kFALSE;
  if (pcand->getInnerSegmentChi2()==-1)   return kFALSE;
  // contemporary conditions:
  /*
    if (pcand->isFlagAND(5,
    Particle::kIsAcceptedHitRICH,
    Particle::kIsAcceptedHitInnerMDC,
    Particle::kIsAcceptedHitOuterMDC,
    Particle::kIsAcceptedHitMETA,
    Particle::kIsAcceptedRK)) return kTRUE;
  */
  return kTRUE;
}

Bool_t myselecthadron(HParticleCand* pcand)
{

  // do your selection
  // must return kTRUE if selection criteria is fullfilled

  if(!pcand)                   return kFALSE;
  if (pcand->getSystem()<0)          return kFALSE;
  if (pcand->getMomentum()>5000) return kFALSE;
  if (pcand->getChi2()>1000.) return kFALSE;
  if (pcand->getBeta()<0.01)   return kFALSE;
  //if (pcand->getBeta(4)>2)   return kFALSE;
  if (pcand->getInnerSegmentChi2()==-1)   return kFALSE;
  // contemporary conditions:
  /*
    if (pcand->isFlagAND(4,
    Particle::kIsAcceptedHitInnerMDC,
    Particle::kIsAcceptedHitOuterMDC,
    Particle::kIsAcceptedHitMETA,
    Particle::kIsAcceptedRK)) return kTRUE;

  */
  return kTRUE;
}


