#define make_input_from_sim_cxx
#include "make_input_from_sim.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
void make_input_from_sim::Loop()
{
  //   In a ROOT session, you can do:
  //      Root > .L make_input_from_sim.C
  //      Root > make_input_from_sim t
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
  if (fChain == 0) return;

  TFile* outputFile = new TFile("input_from_sim.root","recreate");
  if ( outputFile == 0 )
    {
      std::cout << "Error: file exampleEvents.root not found" << std::endl;
      return;
    }
  TTree* signal = new TTree("signal","signal reactions");
  TTree* background = new TTree("background","background reactions");
   
   
  // In an n-tuple, we assign each variable to its own branch.
  /*signal->Branch("p_p",&p_beta);
  signal->Branch("pip_p",&pip_p);
  signal->Branch("dist_p_pim", &dist_p_pim);
  signal->Branch("dist_pip_pim", &dist_pip_pim);
  signal->Branch("eVert_x", &eVert_x);
  signal->Branch("eVert_y", &eVert_y);
  signal->Branch("eVert_z", &eVert_z);
  signal->Branch("ver_pip_pim_x",&ver_pip_pim_x);
  signal->Branch("ver_pip_pim_y",&ver_pip_pim_y);
  signal->Branch("ver_pip_pim_z",&ver_pip_pim_z);
  signal->Branch("ver_p_pim_x",&ver_p_pim_x);
  signal->Branch("ver_p_pim_y",&ver_p_pim_y);
  signal->Branch("ver_p_pim_z",&ver_p_pim_z);
  signal->Branch("oa_lambda", &oa_lambda);
  signal->Branch("oa_pip_p",&oa_pip_p);
  //signal->Branch("lambda_mom_z",&lambda_mom_z);
  signal->Branch("dist_p_eVert",&dist_p_eVert);
  signal->Branch("dist_pim_eVert",&dist_pim_eVert);
  signal->Branch("dist_lambda_eVert",&dist_lambda_eVert);
  signal->Branch("dist_lambda_ver_pip_pim",&dist_lambda_ver_pip_pim);
  signal->Branch("pip_sim_vertex_x",&pip_sim_vertex_x);
  signal->Branch("pip_sim_vertex_y",&pip_sim_vertex_y);
  signal->Branch("pip_sim_vertex_z",&pip_sim_vertex_z);
  signal->Branch("p_sim_vertex_x",&p_sim_vertex_x);
  signal->Branch("p_sim_vertex_y",&p_sim_vertex_y);
  signal->Branch("p_sim_vertex_z",&p_sim_vertex_z);
  */
  //signal->Branch("p_p",&p_beta);
  //signal->Branch("pip_p",&pip_p);
  signal->Branch("dist_p_pim", &dist_p_pim);
  signal->Branch("dist_pip_pim", &dist_pip_pim);
  signal->Branch("eVert_x", &eVert_x);
  signal->Branch("eVert_y", &eVert_y);
  signal->Branch("eVert_z", &eVert_z);
  signal->Branch("ver_pip_pim_x",&ver_pip_pim_x);
  signal->Branch("ver_pip_pim_y",&ver_pip_pim_y);
  signal->Branch("ver_pip_pim_z",&ver_pip_pim_z);
  signal->Branch("ver_p_pim_x",&ver_p_pim_x);
  signal->Branch("ver_p_pim_y",&ver_p_pim_y);
  signal->Branch("ver_p_pim_z",&ver_p_pim_z);
  signal->Branch("oa_lambda", &oa_lambda);
  //signal->Branch("oa_pip_p",&oa_pip_p);
  //signal->Branch("lambda_mom_z",&lambda_mom_z);
  signal->Branch("dist_p_eVert",&dist_p_eVert);
  signal->Branch("dist_pim_eVert",&dist_pim_eVert);
  signal->Branch("dist_lambda_eVert",&dist_lambda_eVert);
  signal->Branch("dist_lambda_ver_pip_pim",&dist_lambda_ver_pip_pim);
  signal->Branch("dist_ver_to_ver",&dist_ver_to_ver);

  /*
  background->Branch("p_p",&p_beta);
  background->Branch("pip_p",&pip_p);
  background->Branch("dist_p_pim", &dist_p_pim);
  background->Branch("dist_pip_pim", &dist_pip_pim);
  background->Branch("eVert_x", &eVert_x);
  background->Branch("eVert_y", &eVert_y);
  background->Branch("eVert_z", &eVert_z);
  background->Branch("ver_pip_pim_x",&ver_pip_pim_x);
  background->Branch("ver_pip_pim_y",&ver_pip_pim_y);
  background->Branch("ver_pip_pim_z",&ver_pip_pim_z);
  background->Branch("ver_p_pim_x",&ver_p_pim_x);
  background->Branch("ver_p_pim_y",&ver_p_pim_y);
  background->Branch("ver_p_pim_z",&ver_p_pim_z);
  background->Branch("oa_lambda", &oa_lambda);
  background->Branch("oa_pip_p",&oa_pip_p);
  //background->Branch("lambda_mom_z",&lambda_mom_z);
  background->Branch("dist_p_eVert",&dist_p_eVert);
  background->Branch("dist_pim_eVert",&dist_pim_eVert);
  background->Branch("dist_lambda_eVert",&dist_lambda_eVert);
  background->Branch("dist_lambda_ver_pip_pim",&dist_lambda_ver_pip_pim);
  background->Branch("pip_sim_vertex_x",&pip_sim_vertex_x);
  background->Branch("pip_sim_vertex_y",&pip_sim_vertex_y);
  background->Branch("pip_sim_vertex_z",&pip_sim_vertex_z);
  background->Branch("p_sim_vertex_x",&p_sim_vertex_x);
  background->Branch("p_sim_vertex_y",&p_sim_vertex_y);
  background->Branch("p_sim_vertex_z",&p_sim_vertex_z);
  */
  //background->Branch("p_p",&p_beta);
  //background->Branch("pip_p",&pip_p);
  background->Branch("dist_p_pim", &dist_p_pim);
  background->Branch("dist_pip_pim", &dist_pip_pim);
  background->Branch("eVert_x", &eVert_x);
  background->Branch("eVert_y", &eVert_y);
  background->Branch("eVert_z", &eVert_z);
  background->Branch("ver_pip_pim_x",&ver_pip_pim_x);
  background->Branch("ver_pip_pim_y",&ver_pip_pim_y);
  background->Branch("ver_pip_pim_z",&ver_pip_pim_z);
  background->Branch("ver_p_pim_x",&ver_p_pim_x);
  background->Branch("ver_p_pim_y",&ver_p_pim_y);
  background->Branch("ver_p_pim_z",&ver_p_pim_z);
  background->Branch("oa_lambda", &oa_lambda);
  //background->Branch("oa_pip_p",&oa_pip_p);
  //background->Branch("lambda_mom_z",&lambda_mom_z);
  background->Branch("dist_p_eVert",&dist_p_eVert);
  background->Branch("dist_pim_eVert",&dist_pim_eVert);
  background->Branch("dist_lambda_eVert",&dist_lambda_eVert);
  background->Branch("dist_lambda_ver_pip_pim",&dist_lambda_ver_pip_pim);
  background->Branch("dist_ver_to_ver",&dist_ver_to_ver);
  
   
  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if (Cut(ientry))
      signal->Fill();
    else
      background->Fill();
  }
  signal->Print();
  signal->Write();
  background->Print();
  background->Write();
  outputFile->Close();

}
