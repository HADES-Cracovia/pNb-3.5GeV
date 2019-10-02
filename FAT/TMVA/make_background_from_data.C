#define make_background_from_data_cxx
#include "make_background_from_data.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

using namespace std;

void make_background_from_data::Loop()
{
  //   In a ROOT session, you can do:
  //      Root > .L make_background_from_data.C
  //      Root > make_background_from_data t
  //      Root > t.GetEntry(12); // Fill t data members with entry number 12
  //      Root > t.Show();       // Show values of entry 12
  //      Root > t.Show(16);     // Read and show values of entry 16
  //      Root > t.Loop();       // Loop on all entries
  //

  //     This is the loop skeleton where:
  //    jentry is the global entry number in the chain
  //    ientry is the entry number in the current Tree
  //  Note that the argument to GetEntry must be:
  //    jentry for TChain::GetEntry
  //    ientry for TTree::GetEntry and TBranch::GetEntry
  //
  //       To read only selected branches, Insert statements like:
  // METHOD1:
  //    fChain->SetBranchStatus("*",0);  // disable all branches
  //    fChain->SetBranchStatus("branchname",1);  // activate branchname
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch
  
  if(fChain == 0)
    return;

  TFile* outputFile = new TFile("input_from_data_miss_mass_new_vertex.root","recreate");
  if( outputFile == 0 )
    {
      cout << "Error: file exampleEvents.root not found" << endl;
      return;
    }
 
  TTree* background_data = new TTree("background_data","background reactions from data file");
  TTree* signal_data = new TTree("signal_data","sigbal and background reactions from data file");
   
  //background_data->Branch("p_p",&p_beta);
  //background_data->Branch("pip_p",&pip_p);
  background_data->Branch("dist_p_pim", &dist_p_pim);
  background_data->Branch("dist_pip_pim", &dist_pip_pim);
  background_data->Branch("eVert_x", &eVert_x);
  background_data->Branch("eVert_y", &eVert_y);
  background_data->Branch("eVert_z", &eVert_z);
  background_data->Branch("ver_pip_pim_x",&ver_pip_pim_x);
  background_data->Branch("ver_pip_pim_y",&ver_pip_pim_y);
  background_data->Branch("ver_pip_pim_z",&ver_pip_pim_z);
  background_data->Branch("ver_p_pim_x",&ver_p_pim_x);
  background_data->Branch("ver_p_pim_y",&ver_p_pim_y);
  background_data->Branch("ver_p_pim_z",&ver_p_pim_z);
  background_data->Branch("oa_lambda", &oa_lambda);
  //background_data->Branch("oa_pip_p",&oa_pip_p);
  //background_data->Branch("lambda_mom_z",&lambda_mom_z);
  background_data->Branch("dist_p_eVert",&dist_p_eVert);
  background_data->Branch("dist_pim_eVert",&dist_pim_eVert);
  background_data->Branch("dist_lambda_eVert",&dist_lambda_eVert);
  background_data->Branch("dist_lambda_ver_pip_pim",&dist_lambda_ver_pip_pim);
  background_data->Branch("dist_ver_to_ver",&dist_ver_to_ver);


  //signal_data->Branch("p_p",&p_beta);
  //signal_data->Branch("pip_p",&pip_p);
  signal_data->Branch("dist_p_pim", &dist_p_pim);
  signal_data->Branch("dist_pip_pim", &dist_pip_pim);
  signal_data->Branch("eVert_x", &eVert_x);
  signal_data->Branch("eVert_y", &eVert_y);
  signal_data->Branch("eVert_z", &eVert_z);
  signal_data->Branch("ver_pip_pim_x",&ver_pip_pim_x);
  signal_data->Branch("ver_pip_pim_y",&ver_pip_pim_y);
  signal_data->Branch("ver_pip_pim_z",&ver_pip_pim_z);
  signal_data->Branch("ver_p_pim_x",&ver_p_pim_x);
  signal_data->Branch("ver_p_pim_y",&ver_p_pim_y);
  signal_data->Branch("ver_p_pim_z",&ver_p_pim_z);
  signal_data->Branch("oa_lambda", &oa_lambda);
  //signal_data->Branch("oa_pip_p",&oa_pip_p);
  //signal_data->Branch("lambda_mom_z",&lambda_mom_z);
  signal_data->Branch("dist_p_eVert",&dist_p_eVert);
  signal_data->Branch("dist_pim_eVert",&dist_pim_eVert);
  signal_data->Branch("dist_lambda_eVert",&dist_lambda_eVert);
  signal_data->Branch("dist_lambda_ver_pip_pim",&dist_lambda_ver_pip_pim);
  signal_data->Branch("dist_ver_to_ver",&dist_ver_to_ver);
  
   
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nentries_true = fChain->GetEntries();
  cout<<"nentries: "<<nentries<<endl;
  cout<<"nentries_true: "<<nentries_true<<endl;

  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if(jentry%100000==0)
      cout<<(double)jentry/((double)nentries_true/100)<<" %"<<endl;
    
    if ((m_inv_p_pim<1110 ||m_inv_p_pim>1120)
        && isBest_new==1
	//&& miss_mass_kp>1077
	)
      background_data->Fill();
    
    else
      {
	if(isBest_new==1
	   //&& miss_mass_kp>1077
	   &&m_inv_p_pim<1160
	   &&m_inv_p_pim>970
	   )
	  
	  signal_data->Fill();
      }
  }
  
  signal_data->Write();
  background_data->Write();
  outputFile->Close();

}
