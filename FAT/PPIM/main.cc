#include "PPim.h"
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
outFileData = new TFile("pNb_ppim_280.root","recreate");
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
p_pim_mass=new TH1F("p_pim_mass","Invariant mass #pi^{-} p",2000,500,2500);									       
p_pim1_mass=new TH1F("p_pim1_mass","Invariant mass #pi_{1}^{-} p",2000,500,2500);
p_pim2_mass=new TH1F("p_pim2_mass","Invariant mass #pi_{2}^{-} p",2000,500,2500);
pim_pip_mass=new TH1F("pim_pip_mass","Invariant mass #pi^{-} #pi^{+} ",2000,200,1500);
pim2_pip_mass=new TH1F("pim2_pip_mass","Invariant mass #pi_{2}^{-} #pi^{+} ",2000,200,1500);
pim1_pip_mass=new TH1F("pim1_pip_mass","Invariant mass #pi_{1}^{-} #pi^{+} ",2000,200,1500);
p_pim_pip_pim_mass=new TH1F("p_pim_pip_pim_mass","Invariant mass #pi^{-} #pi^{+} p #pi^{-}",2000,1000,2000);

  
Float_t xbins[] = {0, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1, 0.11, 0.12, 0.13, 0.14, 0.17, 0.2, 0.23, 0.26, 0.29, 0.32, 0.35, 0.38, 0.41, 0.44, 0.47, 0.5, 0.53, 0.56, 0.59, 0.62, 0.65, 0.68, 0.71, 0.74, 0.75, 0.76, 0.77, 0.78, 0.79, 0.8, 0.81, 0.84, 0.87, 0.9, 0.93, 0.96, 0.99, 1.02, 1.05, 1.08, 1.11, 1.14, 1.17, 1.2};
Int_t nbins = sizeof(xbins)/sizeof(Float_t);


   
Float_t xbinsang[] =  {-1.0, -0.9, -0.8, -0.7, -0.6, -0.4, -0.2, 0, 0.2, 0.4, 0.6, 0.7, 0.8, 0.9, 1.0};
Int_t nbinsang = sizeof(xbinsang)/sizeof(Float_t);

/**************************** M A I N   P A R T ****************************************/

PPim t;
PPimPipPim t2;
cout << "START PPIM!" << endl;
t.Loop();
cout << "STOP PPIM!" << endl;

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
p_pim_mass->Write();
p_pim1_mass->Write();
p_pim2_mass->Write();
pim_pip_mass->Write();
pim2_pip_mass->Write();
pim1_pip_mass->Write();
p_pim_pip_pim_mass->Write();


//p_mass->Write();
//pim_mass->Write();
 
//myfile.close();

outFileData->Close();
}

