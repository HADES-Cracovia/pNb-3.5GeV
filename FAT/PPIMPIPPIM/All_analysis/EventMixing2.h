
//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun  2 15:47:25 2020 by ROOT version 5.34/34
// from TTree TMVAeval/TMVAeval_after TMVA
// found on file: TMVA_output_experiement.root
//////////////////////////////////////////////////////////

#ifndef EventMixing2_h
#define EventMixing2_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class EventMixing2 {
public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

  // Declaration of leaf types
  Float_t         dist_lambda1_eVert;
  Float_t         dist_lambda1_pim2;
  Float_t         dist_lambda1_pip;
  Float_t         dist_lambda1_ver_pip_pim;
  Float_t         dist_lambda2_eVert;
  Float_t         dist_lambda2_pim1;
  Float_t         dist_lambda2_pip;
  Float_t         dist_lambda2_ver_pip_pim;
  Float_t         dist_lambda_eVert;
  Float_t         dist_lambda_ver_pip_pim;
  Float_t         dist_p1_eVert;
  Float_t         dist_p2_eVert;
  Float_t         dist_p_eVert;
  Float_t         dist_p_pim;
  Float_t         dist_p_pim1;
  Float_t         dist_p_pim2;
  Float_t         dist_pim1_eVert;
  Float_t         dist_pim2_eVert;
  Float_t         dist_pim_eVert;
  Float_t         dist_pip_pim;
  Float_t         dist_pip_pim1;
  Float_t         dist_pip_pim2;
  Float_t         dist_ver_to_ver;
  Float_t         dist_ver_to_ver_1;
  Float_t         dist_ver_to_ver_2;
  Float_t         eVert_x;
  Float_t         eVert_y;
  Float_t         eVert_z;
  Float_t         event;
  Float_t         event_mult;
  Float_t         hneg_mult;
  Float_t         hpos_mult;
  Float_t         hypothesis;
  Float_t         hypothesis_quality;
  Float_t         isBest;
  Float_t         isBest_new;
  Float_t         k0_p;
  Float_t         k0_pt;
  Float_t         k0_theta;
  Float_t         k0_w;
  Float_t         lambda_mom_z;
  Float_t         lambda_p;
  Float_t         lambda_pt;
  Float_t         lambda_theta;
  Float_t         lambda_w;
  Float_t         m_inv_p_pim;
  Float_t         m_inv_p_pim1;
  Float_t         m_inv_p_pim2;
  Float_t         m_inv_p_pim_pim;
  Float_t         m_inv_p_pim_pip;
  Float_t         m_inv_p_pim_pip_pim;
  Float_t         m_inv_p_pip;
  Float_t         m_inv_pip_pim;
  Float_t         m_inv_pip_pim1;
  Float_t         m_inv_pip_pim2;
  Float_t         miss_mass_kp;
  Float_t         mlp_output;
  Float_t         mlp_response;
  Float_t         oa_lambda;
  Float_t         oa_lambda_1;
  Float_t         oa_lambda_2;
  Float_t         oa_pim1_p;
  Float_t         oa_pim1_pim2;
  Float_t         oa_pim1_pip;
  Float_t         oa_pim2_p;
  Float_t         oa_pim2_pip;
  Float_t         oa_pim_p;
  Float_t         oa_pip_p;
  Float_t         p_beta;
  Float_t         p_dedx;
  Float_t         p_m;
  Float_t         p_p;
  Float_t         p_phi;
  Float_t         p_q;
  Float_t         p_theta;
  Float_t         pim1_beta;
  Float_t         pim1_dedx;
  Float_t         pim1_m;
  Float_t         pim1_p;
  Float_t         pim1_phi;
  Float_t         pim1_q;
  Float_t         pim1_theta;
  Float_t         pim2_beta;
  Float_t         pim2_dedx;
  Float_t         pim2_m;
  Float_t         pim2_p;
  Float_t         pim2_phi;
  Float_t         pim2_q;
  Float_t         pim2_theta;
  Float_t         pip_beta;
  Float_t         pip_dedx;
  Float_t         pip_m;
  Float_t         pip_p;
  Float_t         pip_phi;
  Float_t         pip_q;
  Float_t         pip_theta;
  Float_t         simon_cuts;
  Float_t         totalmult;
  Float_t         trigdownscale;
  Float_t         trigdownscaleflag;
  Float_t         ver_p_pim1_x;
  Float_t         ver_p_pim1_y;
  Float_t         ver_p_pim1_z;
  Float_t         ver_p_pim2_x;
  Float_t         ver_p_pim2_y;
  Float_t         ver_p_pim2_z;
  Float_t         ver_p_pim_x;
  Float_t         ver_p_pim_y;
  Float_t         ver_p_pim_z;
  Float_t         ver_pip_pim1_x;
  Float_t         ver_pip_pim1_y;
  Float_t         ver_pip_pim1_z;
  Float_t         ver_pip_pim2_x;
  Float_t         ver_pip_pim2_y;
  Float_t         ver_pip_pim2_z;
  Float_t         ver_pip_pim_x;
  Float_t         ver_pip_pim_y;
  Float_t         ver_pip_pim_z;

  // List of branches
  TBranch        *b_dist_lambda1_eVert;   //!
  TBranch        *b_dist_lambda1_pim2;   //!
  TBranch        *b_dist_lambda1_pip;   //!
  TBranch        *b_dist_lambda1_ver_pip_pim;   //!
  TBranch        *b_dist_lambda2_eVert;   //!
  TBranch        *b_dist_lambda2_pim1;   //!
  TBranch        *b_dist_lambda2_pip;   //!
  TBranch        *b_dist_lambda2_ver_pip_pim;   //!
  TBranch        *b_dist_lambda_eVert;   //!
  TBranch        *b_dist_lambda_ver_pip_pim;   //!
  TBranch        *b_dist_p1_eVert;   //!
  TBranch        *b_dist_p2_eVert;   //!
  TBranch        *b_dist_p_eVert;   //!
  TBranch        *b_dist_p_pim;   //!
  TBranch        *b_dist_p_pim1;   //!
  TBranch        *b_dist_p_pim2;   //!
  TBranch        *b_dist_pim1_eVert;   //!
  TBranch        *b_dist_pim2_eVert;   //!
  TBranch        *b_dist_pim_eVert;   //!
  TBranch        *b_dist_pip_pim;   //!
  TBranch        *b_dist_pip_pim1;   //!
  TBranch        *b_dist_pip_pim2;   //!
  TBranch        *b_dist_ver_to_ver;   //!
  TBranch        *b_dist_ver_to_ver_1;   //!
  TBranch        *b_dist_ver_to_ver_2;   //!
  TBranch        *b_eVert_x;   //!
  TBranch        *b_eVert_y;   //!
  TBranch        *b_eVert_z;   //!
  TBranch        *b_event;   //!
  TBranch        *b_event_mult;   //!
  TBranch        *b_hneg_mult;   //!
  TBranch        *b_hpos_mult;   //!
  TBranch        *b_hypothesis;   //!
  TBranch        *b_hypothesis_quality;   //!
  TBranch        *b_isBest;   //!
  TBranch        *b_isBest_new;   //!
  TBranch        *b_k0_p;   //!
  TBranch        *b_k0_pt;   //!
  TBranch        *b_k0_theta;   //!
  TBranch        *b_k0_w;   //!
  TBranch        *b_lambda_mom_z;   //!
  TBranch        *b_lambda_p;   //!
  TBranch        *b_lambda_pt;   //!
  TBranch        *b_lambda_theta;   //!
  TBranch        *b_lambda_w;   //!
  TBranch        *b_m_inv_p_pim;   //!
  TBranch        *b_m_inv_p_pim1;   //!
  TBranch        *b_m_inv_p_pim2;   //!
  TBranch        *b_m_inv_p_pim_pim;   //!
  TBranch        *b_m_inv_p_pim_pip;   //!
  TBranch        *b_m_inv_p_pim_pip_pim;   //!
  TBranch        *b_m_inv_p_pip;   //!
  TBranch        *b_m_inv_pip_pim;   //!
  TBranch        *b_m_inv_pip_pim1;   //!
  TBranch        *b_m_inv_pip_pim2;   //!
  TBranch        *b_miss_mass_kp;   //!
  TBranch        *b_mlp_output;   //!
  TBranch        *b_mlp_response;   //!
  TBranch        *b_oa_lambda;   //!
  TBranch        *b_oa_lambda_1;   //!
  TBranch        *b_oa_lambda_2;   //!
  TBranch        *b_oa_pim1_p;   //!
  TBranch        *b_oa_pim1_pim2;   //!
  TBranch        *b_oa_pim1_pip;   //!
  TBranch        *b_oa_pim2_p;   //!
  TBranch        *b_oa_pim2_pip;   //!
  TBranch        *b_oa_pim_p;   //!
  TBranch        *b_oa_pip_p;   //!
  TBranch        *b_p_beta;   //!
  TBranch        *b_p_dedx;   //!
  TBranch        *b_p_m;   //!
  TBranch        *b_p_p;   //!
  TBranch        *b_p_phi;   //!
  TBranch        *b_p_q;   //!
  TBranch        *b_p_theta;   //!
  TBranch        *b_pim1_beta;   //!
  TBranch        *b_pim1_dedx;   //!
  TBranch        *b_pim1_m;   //!
  TBranch        *b_pim1_p;   //!
  TBranch        *b_pim1_phi;   //!
  TBranch        *b_pim1_q;   //!
  TBranch        *b_pim1_theta;   //!
  TBranch        *b_pim2_beta;   //!
  TBranch        *b_pim2_dedx;   //!
  TBranch        *b_pim2_m;   //!
  TBranch        *b_pim2_p;   //!
  TBranch        *b_pim2_phi;   //!
  TBranch        *b_pim2_q;   //!
  TBranch        *b_pim2_theta;   //!
  TBranch        *b_pip_beta;   //!
  TBranch        *b_pip_dedx;   //!
  TBranch        *b_pip_m;   //!
  TBranch        *b_pip_p;   //!
  TBranch        *b_pip_phi;   //!
  TBranch        *b_pip_q;   //!
  TBranch        *b_pip_theta;   //!
  TBranch        *b_simon_cuts;   //!
  TBranch        *b_totalmult;   //!
  TBranch        *b_trigdownscale;   //!
  TBranch        *b_trigdownscaleflag;   //!
  TBranch        *b_ver_p_pim1_x;   //!
  TBranch        *b_ver_p_pim1_y;   //!
  TBranch        *b_ver_p_pim1_z;   //!
  TBranch        *b_ver_p_pim2_x;   //!
  TBranch        *b_ver_p_pim2_y;   //!
  TBranch        *b_ver_p_pim2_z;   //!
  TBranch        *b_ver_p_pim_x;   //!
  TBranch        *b_ver_p_pim_y;   //!
  TBranch        *b_ver_p_pim_z;   //!
  TBranch        *b_ver_pip_pim1_x;   //!
  TBranch        *b_ver_pip_pim1_y;   //!
  TBranch        *b_ver_pip_pim1_z;   //!
  TBranch        *b_ver_pip_pim2_x;   //!
  TBranch        *b_ver_pip_pim2_y;   //!
  TBranch        *b_ver_pip_pim2_z;   //!
  TBranch        *b_ver_pip_pim_x;   //!
  TBranch        *b_ver_pip_pim_y;   //!
  TBranch        *b_ver_pip_pim_z;   //!

  EventMixing2(TTree *tree=0);
  virtual ~EventMixing2();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    CutLK0(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop(char*  output);
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef EventMixing2_cxx
EventMixing2::EventMixing2(TTree *tree) : fChain(0) 
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  if (tree == 0)
    {
      //TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("TMVA_output_experiement.root");
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("TMVA_output_sim_L1520pippim.root");
      if (!f || !f->IsOpen())
	{
	  //f = new TFile("TMVA_output_experiement.root");
	  f = new TFile("TMVA_output_sim_L1520pippim.root");
	}
      
      f->GetObject("TMVAeval",tree);

  }
  Init(tree);
}

EventMixing2::~EventMixing2()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t EventMixing2::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t EventMixing2::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void EventMixing2::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("dist_lambda1_eVert", &dist_lambda1_eVert, &b_dist_lambda1_eVert);
  fChain->SetBranchAddress("dist_lambda1_pim2", &dist_lambda1_pim2, &b_dist_lambda1_pim2);
  fChain->SetBranchAddress("dist_lambda1_pip", &dist_lambda1_pip, &b_dist_lambda1_pip);
  fChain->SetBranchAddress("dist_lambda1_ver_pip_pim", &dist_lambda1_ver_pip_pim, &b_dist_lambda1_ver_pip_pim);
  fChain->SetBranchAddress("dist_lambda2_eVert", &dist_lambda2_eVert, &b_dist_lambda2_eVert);
  fChain->SetBranchAddress("dist_lambda2_pim1", &dist_lambda2_pim1, &b_dist_lambda2_pim1);
  fChain->SetBranchAddress("dist_lambda2_pip", &dist_lambda2_pip, &b_dist_lambda2_pip);
  fChain->SetBranchAddress("dist_lambda2_ver_pip_pim", &dist_lambda2_ver_pip_pim, &b_dist_lambda2_ver_pip_pim);
  fChain->SetBranchAddress("dist_lambda_eVert", &dist_lambda_eVert, &b_dist_lambda_eVert);
  fChain->SetBranchAddress("dist_lambda_ver_pip_pim", &dist_lambda_ver_pip_pim, &b_dist_lambda_ver_pip_pim);
  fChain->SetBranchAddress("dist_p1_eVert", &dist_p1_eVert, &b_dist_p1_eVert);
  fChain->SetBranchAddress("dist_p2_eVert", &dist_p2_eVert, &b_dist_p2_eVert);
  fChain->SetBranchAddress("dist_p_eVert", &dist_p_eVert, &b_dist_p_eVert);
  fChain->SetBranchAddress("dist_p_pim", &dist_p_pim, &b_dist_p_pim);
  fChain->SetBranchAddress("dist_p_pim1", &dist_p_pim1, &b_dist_p_pim1);
  fChain->SetBranchAddress("dist_p_pim2", &dist_p_pim2, &b_dist_p_pim2);
  fChain->SetBranchAddress("dist_pim1_eVert", &dist_pim1_eVert, &b_dist_pim1_eVert);
  fChain->SetBranchAddress("dist_pim2_eVert", &dist_pim2_eVert, &b_dist_pim2_eVert);
  fChain->SetBranchAddress("dist_pim_eVert", &dist_pim_eVert, &b_dist_pim_eVert);
  fChain->SetBranchAddress("dist_pip_pim", &dist_pip_pim, &b_dist_pip_pim);
  fChain->SetBranchAddress("dist_pip_pim1", &dist_pip_pim1, &b_dist_pip_pim1);
  fChain->SetBranchAddress("dist_pip_pim2", &dist_pip_pim2, &b_dist_pip_pim2);
  fChain->SetBranchAddress("dist_ver_to_ver", &dist_ver_to_ver, &b_dist_ver_to_ver);
  fChain->SetBranchAddress("dist_ver_to_ver_1", &dist_ver_to_ver_1, &b_dist_ver_to_ver_1);
  fChain->SetBranchAddress("dist_ver_to_ver_2", &dist_ver_to_ver_2, &b_dist_ver_to_ver_2);
  fChain->SetBranchAddress("eVert_x", &eVert_x, &b_eVert_x);
  fChain->SetBranchAddress("eVert_y", &eVert_y, &b_eVert_y);
  fChain->SetBranchAddress("eVert_z", &eVert_z, &b_eVert_z);
  fChain->SetBranchAddress("event", &event, &b_event);
  fChain->SetBranchAddress("event_mult", &event_mult, &b_event_mult);
  fChain->SetBranchAddress("hneg_mult", &hneg_mult, &b_hneg_mult);
  fChain->SetBranchAddress("hpos_mult", &hpos_mult, &b_hpos_mult);
  fChain->SetBranchAddress("hypothesis", &hypothesis, &b_hypothesis);
  fChain->SetBranchAddress("hypothesis_quality", &hypothesis_quality, &b_hypothesis_quality);
  fChain->SetBranchAddress("isBest", &isBest, &b_isBest);
  fChain->SetBranchAddress("isBest_new", &isBest_new, &b_isBest_new);
  fChain->SetBranchAddress("k0_p", &k0_p, &b_k0_p);
  fChain->SetBranchAddress("k0_pt", &k0_pt, &b_k0_pt);
  fChain->SetBranchAddress("k0_theta", &k0_theta, &b_k0_theta);
  fChain->SetBranchAddress("k0_w", &k0_w, &b_k0_w);
  fChain->SetBranchAddress("lambda_mom_z", &lambda_mom_z, &b_lambda_mom_z);
  fChain->SetBranchAddress("lambda_p", &lambda_p, &b_lambda_p);
  fChain->SetBranchAddress("lambda_pt", &lambda_pt, &b_lambda_pt);
  fChain->SetBranchAddress("lambda_theta", &lambda_theta, &b_lambda_theta);
  fChain->SetBranchAddress("lambda_w", &lambda_w, &b_lambda_w);
  fChain->SetBranchAddress("m_inv_p_pim", &m_inv_p_pim, &b_m_inv_p_pim);
  fChain->SetBranchAddress("m_inv_p_pim1", &m_inv_p_pim1, &b_m_inv_p_pim1);
  fChain->SetBranchAddress("m_inv_p_pim2", &m_inv_p_pim2, &b_m_inv_p_pim2);
  fChain->SetBranchAddress("m_inv_p_pim_pim", &m_inv_p_pim_pim, &b_m_inv_p_pim_pim);
  fChain->SetBranchAddress("m_inv_p_pim_pip", &m_inv_p_pim_pip, &b_m_inv_p_pim_pip);
  fChain->SetBranchAddress("m_inv_p_pim_pip_pim", &m_inv_p_pim_pip_pim, &b_m_inv_p_pim_pip_pim);
  fChain->SetBranchAddress("m_inv_p_pip", &m_inv_p_pip, &b_m_inv_p_pip);
  fChain->SetBranchAddress("m_inv_pip_pim", &m_inv_pip_pim, &b_m_inv_pip_pim);
  fChain->SetBranchAddress("m_inv_pip_pim1", &m_inv_pip_pim1, &b_m_inv_pip_pim1);
  fChain->SetBranchAddress("m_inv_pip_pim2", &m_inv_pip_pim2, &b_m_inv_pip_pim2);
  fChain->SetBranchAddress("miss_mass_kp", &miss_mass_kp, &b_miss_mass_kp);
  fChain->SetBranchAddress("mlp_output", &mlp_output, &b_mlp_output);
  fChain->SetBranchAddress("mlp_response", &mlp_response, &b_mlp_response);
  fChain->SetBranchAddress("oa_lambda", &oa_lambda, &b_oa_lambda);
  fChain->SetBranchAddress("oa_lambda_1", &oa_lambda_1, &b_oa_lambda_1);
  fChain->SetBranchAddress("oa_lambda_2", &oa_lambda_2, &b_oa_lambda_2);
  fChain->SetBranchAddress("oa_pim1_p", &oa_pim1_p, &b_oa_pim1_p);
  fChain->SetBranchAddress("oa_pim1_pim2", &oa_pim1_pim2, &b_oa_pim1_pim2);
  fChain->SetBranchAddress("oa_pim1_pip", &oa_pim1_pip, &b_oa_pim1_pip);
  fChain->SetBranchAddress("oa_pim2_p", &oa_pim2_p, &b_oa_pim2_p);
  fChain->SetBranchAddress("oa_pim2_pip", &oa_pim2_pip, &b_oa_pim2_pip);
  fChain->SetBranchAddress("oa_pim_p", &oa_pim_p, &b_oa_pim_p);
  fChain->SetBranchAddress("oa_pip_p", &oa_pip_p, &b_oa_pip_p);
  fChain->SetBranchAddress("p_beta", &p_beta, &b_p_beta);
  fChain->SetBranchAddress("p_dedx", &p_dedx, &b_p_dedx);
  fChain->SetBranchAddress("p_m", &p_m, &b_p_m);
  fChain->SetBranchAddress("p_p", &p_p, &b_p_p);
  fChain->SetBranchAddress("p_phi", &p_phi, &b_p_phi);
  fChain->SetBranchAddress("p_q", &p_q, &b_p_q);
  fChain->SetBranchAddress("p_theta", &p_theta, &b_p_theta);
  fChain->SetBranchAddress("pim1_beta", &pim1_beta, &b_pim1_beta);
  fChain->SetBranchAddress("pim1_dedx", &pim1_dedx, &b_pim1_dedx);
  fChain->SetBranchAddress("pim1_m", &pim1_m, &b_pim1_m);
  fChain->SetBranchAddress("pim1_p", &pim1_p, &b_pim1_p);
  fChain->SetBranchAddress("pim1_phi", &pim1_phi, &b_pim1_phi);
  fChain->SetBranchAddress("pim1_q", &pim1_q, &b_pim1_q);
  fChain->SetBranchAddress("pim1_theta", &pim1_theta, &b_pim1_theta);
  fChain->SetBranchAddress("pim2_beta", &pim2_beta, &b_pim2_beta);
  fChain->SetBranchAddress("pim2_dedx", &pim2_dedx, &b_pim2_dedx);
  fChain->SetBranchAddress("pim2_m", &pim2_m, &b_pim2_m);
  fChain->SetBranchAddress("pim2_p", &pim2_p, &b_pim2_p);
  fChain->SetBranchAddress("pim2_phi", &pim2_phi, &b_pim2_phi);
  fChain->SetBranchAddress("pim2_q", &pim2_q, &b_pim2_q);
  fChain->SetBranchAddress("pim2_theta", &pim2_theta, &b_pim2_theta);
  fChain->SetBranchAddress("pip_beta", &pip_beta, &b_pip_beta);
  fChain->SetBranchAddress("pip_dedx", &pip_dedx, &b_pip_dedx);
  fChain->SetBranchAddress("pip_m", &pip_m, &b_pip_m);
  fChain->SetBranchAddress("pip_p", &pip_p, &b_pip_p);
  fChain->SetBranchAddress("pip_phi", &pip_phi, &b_pip_phi);
  fChain->SetBranchAddress("pip_q", &pip_q, &b_pip_q);
  fChain->SetBranchAddress("pip_theta", &pip_theta, &b_pip_theta);
  fChain->SetBranchAddress("simon_cuts", &simon_cuts, &b_simon_cuts);
  fChain->SetBranchAddress("totalmult", &totalmult, &b_totalmult);
  fChain->SetBranchAddress("trigdownscale", &trigdownscale, &b_trigdownscale);
  fChain->SetBranchAddress("trigdownscaleflag", &trigdownscaleflag, &b_trigdownscaleflag);
  fChain->SetBranchAddress("ver_p_pim1_x", &ver_p_pim1_x, &b_ver_p_pim1_x);
  fChain->SetBranchAddress("ver_p_pim1_y", &ver_p_pim1_y, &b_ver_p_pim1_y);
  fChain->SetBranchAddress("ver_p_pim1_z", &ver_p_pim1_z, &b_ver_p_pim1_z);
  fChain->SetBranchAddress("ver_p_pim2_x", &ver_p_pim2_x, &b_ver_p_pim2_x);
  fChain->SetBranchAddress("ver_p_pim2_y", &ver_p_pim2_y, &b_ver_p_pim2_y);
  fChain->SetBranchAddress("ver_p_pim2_z", &ver_p_pim2_z, &b_ver_p_pim2_z);
  fChain->SetBranchAddress("ver_p_pim_x", &ver_p_pim_x, &b_ver_p_pim_x);
  fChain->SetBranchAddress("ver_p_pim_y", &ver_p_pim_y, &b_ver_p_pim_y);
  fChain->SetBranchAddress("ver_p_pim_z", &ver_p_pim_z, &b_ver_p_pim_z);
  fChain->SetBranchAddress("ver_pip_pim1_x", &ver_pip_pim1_x, &b_ver_pip_pim1_x);
  fChain->SetBranchAddress("ver_pip_pim1_y", &ver_pip_pim1_y, &b_ver_pip_pim1_y);
  fChain->SetBranchAddress("ver_pip_pim1_z", &ver_pip_pim1_z, &b_ver_pip_pim1_z);
  fChain->SetBranchAddress("ver_pip_pim2_x", &ver_pip_pim2_x, &b_ver_pip_pim2_x);
  fChain->SetBranchAddress("ver_pip_pim2_y", &ver_pip_pim2_y, &b_ver_pip_pim2_y);
  fChain->SetBranchAddress("ver_pip_pim2_z", &ver_pip_pim2_z, &b_ver_pip_pim2_z);
  fChain->SetBranchAddress("ver_pip_pim_x", &ver_pip_pim_x, &b_ver_pip_pim_x);
  fChain->SetBranchAddress("ver_pip_pim_y", &ver_pip_pim_y, &b_ver_pip_pim_y);
  fChain->SetBranchAddress("ver_pip_pim_z", &ver_pip_pim_z, &b_ver_pip_pim_z);
  Notify();
}

Bool_t EventMixing2::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void EventMixing2::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t EventMixing2::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  double mlp_cut=0.57;
  if(isBest_new!=1
     ||mlp_output<mlp_cut
     //||miss_mass_kp<1200 //replaced by graphical cut
     ||m_inv_pip_pim>410 //replaced by graphical cut
     ||dist_ver_to_ver<50
     ||(oa_lambda>10)
     )
    return 0;
  else
    return 1;
}

Int_t EventMixing2::CutLK0(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  double mlp_cut=0.57;
  if(isBest_new!=1
     ||mlp_output<mlp_cut
     //||miss_mass_kp<1200 //replaced by graphical cut
     ||m_inv_pip_pim>410 //replaced by graphical cut
     ||dist_ver_to_ver<50
     ||(oa_lambda>10)
     )
    return 0;
  else
    return 1;
}
#endif // #ifdef EventMixing_cxx
