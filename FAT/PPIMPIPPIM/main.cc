//#include "PPim.h"
#include "PPimPipPim.h"
//#include "EpEp.h"
//#include "EmEm.h"
#include "data.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include "HFilter.h"
#include <fstream>
#include <TLine.h>

using namespace std;
using namespace PATData;

int main()
{
  //******************************************* B E A M   P A R A M E T E R S *****************************/
  /*
  //proj = new TLorentzVector(0,0,1700,1705.71972227); // PION BEAM 1.7 GeV/c momentum
  //targ = new TLorentzVector(0,0,0,938.27231); // PROTON
  beam = new TLorentzVector(0,0,0,0);
  proj = new TLorentzVector(0,0,700,713.7785); // PION BEAM 0.7 GeV/c momentum 
  targ = new TLorentzVector(0,0,0,938.27231); // PROTON
  *beam = *proj + *targ;
  */

  //PION BEAM SCANNER
  //   double pion_momentum = 612.0;

  //   double pion_momentum = 656.0;
  double pion_momentum = 690.0; 
  //   double pion_momentum = 748.0;
  //   double pion_momentum = 800.0;

  // ORIGIN: https://hades-wiki.gsi.de/foswiki/bin/view/PionBeam/WebHome

  double pion_energy = sqrt( pion_momentum*pion_momentum + 139.56995*139.56995 );

  proj = new TLorentzVector(0,0, pion_momentum, pion_energy); // PION BEAM momentum as above

  targ = new TLorentzVector(0,0,0,938.27231); // PROTON
  /*******************************************************************************************************/
  beam = new TLorentzVector(0,0,0,0);
  *beam = *proj + *targ;



  //*******************************************************************************************************/


  //filter = new HFilter;

  // *********************** FILES WITH CUTS ****************************
  insideEmS0 = -1;
  insideEmS1 = -1;
  insideEpS0 = -1;
  insideEpS1 = -1;

  insideEm1S0 = -1;
  insideEm1S1 = -1;
  insideEm2S0 = -1;
  insideEm2S1 = -1;

  insideEp1S0 = -1;
  insideEp1S1 = -1;
  insideEp2S0 = -1;
  insideEp2S1 = -1;

  p = new TLorentzVector(0,0,0,0);
  pim1 = new TLorentzVector(0,0,0,0);
  pim2 = new TLorentzVector(0,0,0,0);
  pip = new TLorentzVector(0,0,0,0);
  pi = new TLorentzVector(0,0,0,0);
  gammappi = new TLorentzVector(0,0,0,0);
  gammappim1 = new TLorentzVector(0,0,0,0);
  gammappim2 = new TLorentzVector(0,0,0,0);
  gammapim1pip = new TLorentzVector(0,0,0,0);
  gammapim2pip = new TLorentzVector(0,0,0,0);
  gammappim1pippim2 = new TLorentzVector(0,0,0,0);

  ppi = new TLorentzVector(0,0,0,0);
  p_delta = new TLorentzVector(0,0,0,0);
  pi_delta = new TLorentzVector(0,0,0,0);
  ppi_miss = new TLorentzVector(0,0,0,0);

  /************************************** O U T P U T   F I L E ******************************************/
  outFileData = new TFile("pNb_ppimpippim_temp.root","recreate");
  //ofstream myfile;
  //myfile.open ("raport.txt",ios::trunc);
  //outFileData = new TFile("ntuple_epem_656_C_gen1.root","recreate");
  //outFileData = new TFile("ntuple_epem_690_C_gen1.root","recreate");
  //outFileData = new TFile("ntuple_epem_690_PE_gen1_helicity.root","recreate");
  //outFileData = new TFile("ntuple_epem_690_C_gen1_helicity.root","recreate");
  //outFileData = new TFile("ntuple_epem_748_C_gen1.root","recreate");
  //outFileData = new TFile("ntuple_epem_800_C_gen1.root","recreate");
  /*******************************************************************************************************/

  /************************** control ntuple ***************************/
  tlo = new HNtuple("ppim","ppim");
  tlo->setFile( outFileData );
  /*********************************************************************/

  int beta_min=0;
  int beta_max=1.2;
  int beta_n=240;
  int p_min=0;
  int p_max=3000;
  int p_n=3000;
  
  p_p_beta=new TH2F("p_p_beta","Momentum vs. beta for protons",p_n,p_min,p_max,beta_n,beta_min,beta_max);
  pim_p_beta=new TH2F("pim_p_beta","Momentum vs. beta for #pi^{-}",p_n,p_min,p_max,beta_n,beta_min,beta_max);
  pip_p_beta=new TH2F("pip_p_beta","Momentum vs. beta for #pi^{+}",p_n,p_min,p_max,beta_n,beta_min,beta_max);

  p_pim_mass=new TH1F("p_pim_mass","Invariant mass #pi^{-} p",2000,500,2500);									       
  p_pim1_mass=new TH1F("p_pim1_mass","Invariant mass #pi_{1}^{-} p",2000,500,2500);
  p_pim2_mass=new TH1F("p_pim2_mass","Invariant mass #pi_{2}^{-} p",2000,500,2500);
  pim_pip_mass=new TH1F("pim_pip_mass","Invariant mass #pi^{-} #pi^{+} ",2000,200,1500);
  pim2_pip_mass=new TH1F("pim2_pip_mass","Invariant mass #pi_{2}^{-} #pi^{+} ",2000,200,1500);
  pim1_pip_mass=new TH1F("pim1_pip_mass","Invariant mass #pi_{1}^{-} #pi^{+} ",2000,200,1500);
  p_pim_pip_pim_mass=new TH1F("p_pim_pip_pim_mass","Invariant mass #pi^{-} #pi^{+} p #pi^{-}",2000,1000,2000);

  dist_p_pim_pim_pip=new TH2F("dist_p_pim_pim_pip","dist_p_pim_pim_pip",300,0,300,300,0,300);
  dist_p_pim=new TH1F("dist_p_pim","dist_p_pim",1000,0,300);
  dist_pim_pip=new TH1F("dist_pip_pim","dist_pip_pim",1000,0,300);

  
  DL_p_pim_mass=new TH1F("DL_p_pim_mass","Invariant mass #pi^{-} p",2000,500,2500);						       
  DL_p_pim1_mass=new TH1F("DL_p_pim1_mass","DL_Invariant mass #pi_{1}^{-} p",2000,500,2500);
  DL_p_pim2_mass=new TH1F("DL_p_pim2_mass","DL_Invariant mass #pi_{2}^{-} p",2000,500,2500);
  DL_pim_pip_mass=new TH1F("DL_pim_pip_mass","DL_Invariant mass #pi^{-} #pi^{+} ",2000,200,1500);
  DL_pim2_pip_mass=new TH1F("DL_pim2_pip_mass","DL_Invariant mass #pi_{2}^{-} #pi^{+} ",2000,200,1500);
  DL_pim1_pip_mass=new TH1F("DL_pim1_pip_mass","DL_Invariant mass #pi_{1}^{-} #pi^{+} ",2000,200,1500);
  DL_p_pim_pip_pim_mass=new TH1F("DL_p_pim_pip_pim_mass","DL_Invariant mass #pi^{-} #pi^{+} p #pi^{-}",2000,1000,2000);
  DL_in_target=new TH1F("DL_in_target","DL_Invariant mass #pi^{-} #pi^{+} p #pi^{-} for events from target",2000,1000,2000);
  
  DL_dist_p_pim_pim_pip=new TH2F("DL_dist_p_pim_pim_pip","DL_dist_p_pim_pim_pip",300,0,300,300,0,300);
  DL_dist_p_pim=new TH1F("DL_dist_p_pim","DL_dist_p_pim",1000,0,300);
  DL_dist_pim_pip=new TH1F("DL_dist_pip_pim","DL_dist_pip_pim",1000,0,300);

  DL_target_z=new TH1F("DL_target_z","Z position of target",150,-100,50);
  DL_target_z_diff=new TH1F("DL_target_z_diff","Diffference between z of vertex for #pi^{-} and #pi^{+}",100,1,-1);
  DL_pim_pip_z=new TH1F("DL_pim_pip_z","Poinf of closest approach between #pi^{-} & #pi^{+}",150,-100,50);
  DL_pip_z=new TH1F("DL_pip_z","Z position of target according to #pi^{+}",150,-100,50);

  ver_pip_lambda=new TH2F("ver_pip_lambda","Point of the closest approach between #pi^{+} and #Lambda",200,1,-1,100,1,-1);
  
  DML_p_pim_mass=new TH1F("DML_p_pim_mass","Invariant mass #pi^{-} p",2000,500,2500);						       
  DML_p_pim1_mass=new TH1F("DML_p_pim1_mass","DML_Invariant mass #pi_{1}^{-} p",2000,500,2500);
  DML_p_pim2_mass=new TH1F("DML_p_pim2_mass","DML_Invariant mass #pi_{2}^{-} p",2000,500,2500);
  DML_pim_pip_mass=new TH1F("DML_pim_pip_mass","DML_Invariant mass #pi^{-} #pi^{+} ",2000,200,1500);
  DML_pim2_pip_mass=new TH1F("DML_pim2_pip_mass","DML_Invariant mass #pi_{2}^{-} #pi^{+} ",2000,200,1500);
  DML_pim1_pip_mass=new TH1F("DML_pim1_pip_mass","DML_Invariant mass #pi_{1}^{-} #pi^{+} ",2000,200,1500);
  DML_p_pim_pip_pim_mass=new TH1F("DML_p_pim_pip_pim_mass","DML_Invariant mass #pi^{-} #pi^{+} p #pi^{-}",2000,1000,2000);

  DML_dist_p_pim_pim_pip=new TH2F("DML_dist_p_pim_pim_pip","DML_dist_p_pim_pim_pip",300,0,300,300,0,300);
  DML_dist_p_pim=new TH1F("DML_dist_p_pim","DML_dist_p_pim",1000,0,300);
  DML_dist_pim_pip=new TH1F("DML_dist_pip_pim","DML_dist_pip_pim",1000,0,300);
  vertex_lambda=new TH2F("vertex_lambda","#Lambda (1116) decay vertex for all #pi^{-} p pairs;Z_{vertex} [mm] ;R_{vertex} [mm]",500,-100,400,400,0,400); 
  vertex_target=new TH2F("vertex_target","#Lambda (1520) decay vertex for all #pi^{-} #pi^{+} pairs;Z_{vertex} [mm] ;R_{vertex} [mm]",500,-100,400,400,0,400);
  DL_vertex_lambda=new TH2F("DL_vertex_lambda","#Lambda (1116) decay vertex for #pi^{-} p pairs closer then dist_{min};Z_{vertex} [mm] ;R_{vertex} [mm]",500,-100,400,400,0,400);
  DL_vertex_target=new TH2F("DL_vertex_target","#Lambda (1520) decay vertex for #pi^{-} #pi^{+} pairs closer then dist_{min};Z_{vertex} [mm] ;R_{vertex} [mm]",500,-100,400,400,0,400);
  DLM_vertex_lambda=new TH2F("DLM_vertex_lambda","#Lambda (1116) decay vertex for #pi^{-} p pairs from #Lambda (distance and mass cut);Z_{vertex} [mm] ;R_{vertex} [mm]",500,-100,400,400,0,400);
  DLM_vertex_target=new TH2F("DLM_vertex_target","#Lambda (1520) decay vertex for #pi^{-} #pi^{+} pairs pairs from;Z_{vertex} [mm] ;R_{vertex} [mm]",500,-100,400,400,0,400);

  sum_dist_1=new TH1F("sum_dist_1","Sum of all distances in hyp1",500,0,500);
  sum_dist_2=new TH1F("sum_dist_2","Sum of all distances in hyp2",500,0,500);
  sum_dist_diff=new TH1F("sum_dist_diff","Difference between hypothesis 1 and 2",400,0,400);

  chi_p_pim_mass=new TH1F("chi_p_pim_mass","p #pi^{-} mass after chi cut; M_{#pi^{-} p}[MeV]",600,1000,1600);
  chi_pip_pim_mass=new TH1F("chi_pip_pim_mass","#pi^{+} #pi^{-} mass after chi cut; M_{#pi^{-} #pi^{+}}[MeV]",900,200,1100);
  chi_lambda_vertex=new TH2F("chi_lambda_vertex","Reconstructed vertex of a #Lambda (1116);Z_{vertex}[mm];R_{vertex}[mm]",600,-100,200,400,0,200);
  chi_final_mass=new TH1F("chi_final_mass","#pi^{+} #pi^{-} P #Pi^{-} mass after chi cut; M_{#pi^{-} #pi^{+}  p #pi^{-}}[MeV]",1000,1300,2300);

  
  LM_chi_p_pim_mass=new TH1F("LM_chi_p_pim_mass","p #pi^{-} mass after chi cut and #Lambda mass; M_{#pi^{-} p}[MeV]",600,1000,1600);
  LM_chi_pip_pim_mass=new TH1F("LM_chi_pip_pim_mass","#pi^{+} #pi^{-} mass after chi cut and #Lambda mass; M_{#pi^{-} #pi^{+}}[MeV]",900,200,1100);
  LM_chi_lambda_vertex=new TH2F("LM_chi_lambda_vertex","Reconstructed vertex of a #Lambda (1116),after chi and #Lambda mass cut;Z_{vertex}[mm];R_{vertex}[mm]",600,-100,200,400,0,200);
  LM_chi_final_mass=new TH1F("LM_chi_final_mass","#pi^{+} #pi^{-} P #Pi^{-} mass after chi and mass cut; M_{#pi^{-} #pi^{+}  p #pi^{-}}[MeV]",1000,1300,2300);
  /**************************** M A I N   P A R T ****************************************/

  //PPim t;
  PPimPipPim t2;
  //cout << "START PPIM!" << endl;
  //t.Loop();
  //cout << "STOP PPIM!" << endl;

  cout << "START PPimPipPim!" << endl;
  t2.Loop();
  cout << "STOP PPimPipPim!!" << endl;
  
  /*EpEp t_back1;
    t_back1.Loop();
    cout << "START EPEP!" << endl;
    EmEm t_back2;
    t_back2.Loop();   
    cout << "START EMEM!" << endl;*/
  cout << "FINALIZING!" << endl;


  /***************************** F I N A L     C A L C U L A T I O N S ********************/


  /****************************************************************************************/

  outFileData->cd();

  //tlo->Write();
  
  p_p_beta->Write();
  pim_p_beta->Write();
  pip_p_beta->Write();

  p_pim_mass->Write();
  p_pim1_mass->Write();
  p_pim2_mass->Write();
  pim_pip_mass->Write();
  pim2_pip_mass->Write();
  pim1_pip_mass->Write();
  p_pim_pip_pim_mass->Write();

  dist_p_pim_pim_pip->Write();
  dist_pim_pip->Write();
  dist_p_pim->Write();
  
  DL_p_pim_mass->Write();
  DL_p_pim1_mass->Write();
  DL_p_pim2_mass->Write();
  DL_pim_pip_mass->Write();
  DL_pim2_pip_mass->Write();
  DL_pim1_pip_mass->Write();
  DL_p_pim_pip_pim_mass->Write();
  DL_in_target->Write();
  
  DL_dist_p_pim_pim_pip->Write();
  DL_dist_pim_pip->Write();
  DL_dist_p_pim->Write();

  DL_target_z_diff->Write();
  DL_target_z->Write();
  DL_pim_pip_z->Write();
  DL_pip_z->Write();

  ver_pip_lambda->Write();
  
  DML_p_pim_mass->Write();
  DML_p_pim1_mass->Write();
  DML_p_pim2_mass->Write();
  DML_pim_pip_mass->Write();
  DML_pim2_pip_mass->Write();
  DML_pim1_pip_mass->Write();
  DML_p_pim_pip_pim_mass->Write();

  DML_dist_p_pim_pim_pip->Write();
  DML_dist_pim_pip->Write();
  DML_dist_p_pim->Write();
  //p_mass->Write();
  //pim_mass->Write();

  sum_dist_diff->Write();
  sum_dist_2->Write();
  sum_dist_1->Write();

  chi_pip_pim_mass->Write();
  chi_p_pim_mass->Write();
  chi_lambda_vertex->Write();
  chi_final_mass->Write();
  
  LM_chi_pip_pim_mass->Write();
  LM_chi_p_pim_mass->Write();
  LM_chi_lambda_vertex->Write();
  LM_chi_final_mass->Write();
  //myfile.close();

  outFileData->Close();
}

