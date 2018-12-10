#include "PPim.h"
//#include "PPimPipPim.h"
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
  //outFileData = new TFile("pNb_ppim_280.root","recreate");
  outFileData = new TFile("pNb_ppim_all_opt_dist_between_vertex.root","recreate");
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
  D_p_pim_mass=new TH1F("D_p_pim_mass","Invariant mass #pi^{-} p after distance cut",2000,500,2500);
  ZD_p_pim_mass=new TH1F("ZD_p_pim_mass","Invariant mass #pi^{-} p after geometric cuts",2000,500,2500);

  char hname[40];
  char htitle[40];
  char zname[40];
  char ztitle[40];
  char dzname[60];
  char dztitle[60]; 
  
  for(int jj=1; jj<=25;jj++)
    {
      sprintf(hname,"D_p_pim_mass_%d",(jj)*2);
      sprintf(htitle,"mass_after_distance_cut_%d",(jj)*2);
      sprintf(zname,"Z_p_pim_mass_%d",(jj)*2);
      sprintf(ztitle,"mass_after_Z-vertex_coordinate_cut_%d",(jj)*2);
      D_p_pim_mass_array[jj-1] = new TH1F(hname,htitle,2000,500,2500);
      Z_p_pim_mass_array[jj-1] = new TH1F(zname,ztitle,2000,500,2500);

      for(int kk=1; kk<=25;kk++)
	{
	  sprintf(dzname,"DZ_p_pim_mass_%d_%d",(jj)*2,kk*2);
	  sprintf(dztitle,"mass_after_distance_cut_%d_z_cut_%d",jj,(kk)*2);
	  DZ_p_pim_mass_array[jj-1][kk-1]=new TH1F(dzname,dztitle,2000,500,2500);
	} 
    }
  
  dist_p_pim=new TH1F("dist_p_pim","dist_p_pim",1000,0,300);
  vertex_z_r=new TH2F("vertex_z_r","Z vs. r coordinate for vertex, after distance cut",400,-100,100,200,0,100);  
  
  /**************************** M A I N   P A R T ****************************************/

  PPim t;
  //PPimPipPim t2;
  cout << "START PPIM!" << endl;
  t.Loop();
  cout << "STOP PPIM!" << endl;
  
  //cout << "START PPimPipPim!" << endl;
  //t2.Loop();
  //cout << "STOP PPimPipPim!!" << endl;
  
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
  
  dist_p_pim->Write();
  D_p_pim_mass->Write();
  ZD_p_pim_mass->Write();
  
  vertex_z_r->Write();
  
  TCanvas *c2=new TCanvas("c2","Cut on distance");
  c2->Divide(5,5);

  TCanvas *c3=new TCanvas("c3","Cut on Z axis");
  c3->Divide(5,5);

  for(int z=0;z<25;z++)
    {
      c2->cd(z+1);
      D_p_pim_mass_array[z]->Draw();
      D_p_pim_mass_array[z]->Write();

      c3->cd(z+1);
      Z_p_pim_mass_array[z]->Draw();
      Z_p_pim_mass_array[z]->Write();

      for(int x=0;x<25;x++)
	{
	  DZ_p_pim_mass_array[z][x]->Write();
	}  
    }
  c2->Write();
  c3->Write();
  
  outFileData->Close();
}

