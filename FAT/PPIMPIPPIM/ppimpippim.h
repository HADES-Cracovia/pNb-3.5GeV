//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Dec  6 09:49:22 2018 by ROOT version 6.13/02
// from TTree ppimpippim/ppimpippim
// found on file: pNb_ppimpippim_full_chi2_LM_pippimM_tlo.root
//////////////////////////////////////////////////////////

#ifndef ppimpippim_h
#define ppimpippim_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
 
// Header file for the classes stored in the TTree if any.

class ppimpippim
{
public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

  // Fixed size dimensions of array or collections stored in the TTree if any.

  // Declaration of leaf types
  Float_t         dist_lambda1_pim2;
  Float_t         dist_lambda1_pip;
  Float_t         dist_lambda2_pim1;
  Float_t         dist_lambda2_pip;
  Float_t         dist_p_pim1;
  Float_t         dist_p_pim2;
  Float_t         dist_pip_pim1;
  Float_t         dist_pip_pim2;
  Float_t         m_inv_p_pim1;
  Float_t         m_inv_p_pim2;
  Float_t         m_inv_p_pim_pip_pim;
  Float_t         m_inv_pip_pim1;
  Float_t         m_inv_pip_pim2;
  Float_t         miss_mass_kp;
  Float_t         p_beta;
  Float_t         p_m;
  Float_t         p_p;
  Float_t         p_phi;
  Float_t         p_phi_rich;
  Float_t         p_theta;
  Float_t         p_theta_rich;
  Float_t         pim1_beta;
  Float_t         pim1_m;
  Float_t         pim1_p;
  Float_t         pim1_phi;
  Float_t         pim1_phi_rich;
  Float_t         pim1_theta;
  Float_t         pim1_theta_rich;
  Float_t         pim2_beta;
  Float_t         pim2_m;
  Float_t         pim2_p;
  Float_t         pim2_phi;
  Float_t         pim2_phi_rich;
  Float_t         pim2_theta;
  Float_t         pim2_theta_rich;
  Float_t         pip_beta;
  Float_t         pip_m;
  Float_t         pip_p;
  Float_t         pip_phi;
  Float_t         pip_phi_rich;
  Float_t         pip_theta;
  Float_t         pip_theta_rich;
  Float_t         sum_dist2_1;
  Float_t         sum_dist2_2;
  Float_t         sum_dist_1;
  Float_t         sum_dist_2;
  Float_t         ver_p_pim1_x;
  Float_t         ver_p_pim1_y;
  Float_t         ver_p_pim1_z;
  Float_t         ver_p_pim2_x;
  Float_t         ver_p_pim2_y;
  Float_t         ver_p_pim2_z;
  Float_t         ver_pip_pim1_x;
  Float_t         ver_pip_pim1_y;
  Float_t         ver_pip_pim1_z;
  Float_t         ver_pip_pim2_x;
  Float_t         ver_pip_pim2_y;
  Float_t         ver_pip_pim2_z;

  // List of branches
  TBranch        *b_dist_lambda1_pim2;   //!
  TBranch        *b_dist_lambda1_pip;   //!
  TBranch        *b_dist_lambda2_pim1;   //!
  TBranch        *b_dist_lambda2_pip;   //!
  TBranch        *b_dist_p_pim1;   //!
  TBranch        *b_dist_p_pim2;   //!
  TBranch        *b_dist_pip_pim1;   //!
  TBranch        *b_dist_pip_pim2;   //!
  TBranch        *b_m_inv_p_pim1;   //!
  TBranch        *b_m_inv_p_pim2;   //!
  TBranch        *b_m_inv_p_pim_pip_pim;   //!
  TBranch        *b_m_inv_pip_pim1;   //!
  TBranch        *b_m_inv_pip_pim2;   //!
  TBranch        *b_miss_mass_kp;   //!
  TBranch        *b_p_beta;   //!
  TBranch        *b_p_m;   //!
  TBranch        *b_p_p;   //!
  TBranch        *b_p_phi;   //!
  TBranch        *b_p_phi_rich;   //!
  TBranch        *b_p_theta;   //!
  TBranch        *b_p_theta_rich;   //!
  TBranch        *b_pim1_beta;   //!
  TBranch        *b_pim1_m;   //!
  TBranch        *b_pim1_p;   //!
  TBranch        *b_pim1_phi;   //!
  TBranch        *b_pim1_phi_rich;   //!
  TBranch        *b_pim1_theta;   //!
  TBranch        *b_pim1_theta_rich;   //!
  TBranch        *b_pim2_beta;   //!
  TBranch        *b_pim2_m;   //!
  TBranch        *b_pim2_p;   //!
  TBranch        *b_pim2_phi;   //!
  TBranch        *b_pim2_phi_rich;   //!
  TBranch        *b_pim2_theta;   //!
  TBranch        *b_pim2_theta_rich;   //!
  TBranch        *b_pip_beta;   //!
  TBranch        *b_pip_m;   //!
  TBranch        *b_pip_p;   //!
  TBranch        *b_pip_phi;   //!
  TBranch        *b_pip_phi_rich;   //!
  TBranch        *b_pip_theta;   //!
  TBranch        *b_pip_theta_rich;   //!
  TBranch        *b_sum_dist2_1;   //!
  TBranch        *b_sum_dist2_2;   //!
  TBranch        *b_sum_dist_1;   //!
  TBranch        *b_sum_dist_2;   //!
  TBranch        *b_ver_p_pim1_x;   //!
  TBranch        *b_ver_p_pim1_y;   //!
  TBranch        *b_ver_p_pim1_z;   //!
  TBranch        *b_ver_p_pim2_x;   //!
  TBranch        *b_ver_p_pim2_y;   //!
  TBranch        *b_ver_p_pim2_z;   //!
  TBranch        *b_ver_pip_pim1_x;   //!
  TBranch        *b_ver_pip_pim1_y;   //!
  TBranch        *b_ver_pip_pim1_z;   //!
  TBranch        *b_ver_pip_pim2_x;   //!
  TBranch        *b_ver_pip_pim2_y;   //!
  TBranch        *b_ver_pip_pim2_z;   //!

  ppimpippim(TTree *tree=0);
  virtual ~ppimpippim();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  virtual void     FitK0(TH1F*hist, TF1 *sig, TF1* bg, TF1* sig_bg);
  virtual void     FitL1115(TH1F*hist, TF1 *sig, TF1* bg, TF1* sig_bg);
};

#endif

#ifdef ppimpippim_cxx
ppimpippim::ppimpippim(TTree *tree) : fChain(0) 
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  if (tree == 0)
    {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("pNb_ppimpippim_full_chi2_LM_pippimM_tlo.root");
      if (!f || !f->IsOpen())
	{
	  f = new TFile("pNb_ppimpippim_full_chi2_LM_pippimM_tlo.root");
	}
      f->GetObject("ppimpippim",tree);

    }
  Init(tree);
}

ppimpippim::~ppimpippim()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t ppimpippim::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t ppimpippim::LoadTree(Long64_t entry)
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

void ppimpippim::Init(TTree *tree)
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

  fChain->SetBranchAddress("dist_lambda1_pim2", &dist_lambda1_pim2, &b_dist_lambda1_pim2);
  fChain->SetBranchAddress("dist_lambda1_pip", &dist_lambda1_pip, &b_dist_lambda1_pip);
  fChain->SetBranchAddress("dist_lambda2_pim1", &dist_lambda2_pim1, &b_dist_lambda2_pim1);
  fChain->SetBranchAddress("dist_lambda2_pip", &dist_lambda2_pip, &b_dist_lambda2_pip);
  fChain->SetBranchAddress("dist_p_pim1", &dist_p_pim1, &b_dist_p_pim1);
  fChain->SetBranchAddress("dist_p_pim2", &dist_p_pim2, &b_dist_p_pim2);
  fChain->SetBranchAddress("dist_pip_pim1", &dist_pip_pim1, &b_dist_pip_pim1);
  fChain->SetBranchAddress("dist_pip_pim2", &dist_pip_pim2, &b_dist_pip_pim2);
  fChain->SetBranchAddress("m_inv_p_pim1", &m_inv_p_pim1, &b_m_inv_p_pim1);
  fChain->SetBranchAddress("m_inv_p_pim2", &m_inv_p_pim2, &b_m_inv_p_pim2);
  fChain->SetBranchAddress("m_inv_p_pim_pip_pim", &m_inv_p_pim_pip_pim, &b_m_inv_p_pim_pip_pim);
  fChain->SetBranchAddress("m_inv_pip_pim1", &m_inv_pip_pim1, &b_m_inv_pip_pim1);
  fChain->SetBranchAddress("m_inv_pip_pim2", &m_inv_pip_pim2, &b_m_inv_pip_pim2);
  fChain->SetBranchAddress("miss_mass_kp", &miss_mass_kp, &b_miss_mass_kp);
  fChain->SetBranchAddress("p_beta", &p_beta, &b_p_beta);
  fChain->SetBranchAddress("p_m", &p_m, &b_p_m);
  fChain->SetBranchAddress("p_p", &p_p, &b_p_p);
  fChain->SetBranchAddress("p_phi", &p_phi, &b_p_phi);
  fChain->SetBranchAddress("p_phi_rich", &p_phi_rich, &b_p_phi_rich);
  fChain->SetBranchAddress("p_theta", &p_theta, &b_p_theta);
  fChain->SetBranchAddress("p_theta_rich", &p_theta_rich, &b_p_theta_rich);
  fChain->SetBranchAddress("pim1_beta", &pim1_beta, &b_pim1_beta);
  fChain->SetBranchAddress("pim1_m", &pim1_m, &b_pim1_m);
  fChain->SetBranchAddress("pim1_p", &pim1_p, &b_pim1_p);
  fChain->SetBranchAddress("pim1_phi", &pim1_phi, &b_pim1_phi);
  fChain->SetBranchAddress("pim1_phi_rich", &pim1_phi_rich, &b_pim1_phi_rich);
  fChain->SetBranchAddress("pim1_theta", &pim1_theta, &b_pim1_theta);
  fChain->SetBranchAddress("pim1_theta_rich", &pim1_theta_rich, &b_pim1_theta_rich);
  fChain->SetBranchAddress("pim2_beta", &pim2_beta, &b_pim2_beta);
  fChain->SetBranchAddress("pim2_m", &pim2_m, &b_pim2_m);
  fChain->SetBranchAddress("pim2_p", &pim2_p, &b_pim2_p);
  fChain->SetBranchAddress("pim2_phi", &pim2_phi, &b_pim2_phi);
  fChain->SetBranchAddress("pim2_phi_rich", &pim2_phi_rich, &b_pim2_phi_rich);
  fChain->SetBranchAddress("pim2_theta", &pim2_theta, &b_pim2_theta);
  fChain->SetBranchAddress("pim2_theta_rich", &pim2_theta_rich, &b_pim2_theta_rich);
  fChain->SetBranchAddress("pip_beta", &pip_beta, &b_pip_beta);
  fChain->SetBranchAddress("pip_m", &pip_m, &b_pip_m);
  fChain->SetBranchAddress("pip_p", &pip_p, &b_pip_p);
  fChain->SetBranchAddress("pip_phi", &pip_phi, &b_pip_phi);
  fChain->SetBranchAddress("pip_phi_rich", &pip_phi_rich, &b_pip_phi_rich);
  fChain->SetBranchAddress("pip_theta", &pip_theta, &b_pip_theta);
  fChain->SetBranchAddress("pip_theta_rich", &pip_theta_rich, &b_pip_theta_rich);
  fChain->SetBranchAddress("sum_dist2_1", &sum_dist2_1, &b_sum_dist2_1);
  fChain->SetBranchAddress("sum_dist2_2", &sum_dist2_2, &b_sum_dist2_2);
  fChain->SetBranchAddress("sum_dist_1", &sum_dist_1, &b_sum_dist_1);
  fChain->SetBranchAddress("sum_dist_2", &sum_dist_2, &b_sum_dist_2);
  fChain->SetBranchAddress("ver_p_pim1_x", &ver_p_pim1_x, &b_ver_p_pim1_x);
  fChain->SetBranchAddress("ver_p_pim1_y", &ver_p_pim1_y, &b_ver_p_pim1_y);
  fChain->SetBranchAddress("ver_p_pim1_z", &ver_p_pim1_z, &b_ver_p_pim1_z);
  fChain->SetBranchAddress("ver_p_pim2_x", &ver_p_pim2_x, &b_ver_p_pim2_x);
  fChain->SetBranchAddress("ver_p_pim2_y", &ver_p_pim2_y, &b_ver_p_pim2_y);
  fChain->SetBranchAddress("ver_p_pim2_z", &ver_p_pim2_z, &b_ver_p_pim2_z);
  fChain->SetBranchAddress("ver_pip_pim1_x", &ver_pip_pim1_x, &b_ver_pip_pim1_x);
  fChain->SetBranchAddress("ver_pip_pim1_y", &ver_pip_pim1_y, &b_ver_pip_pim1_y);
  fChain->SetBranchAddress("ver_pip_pim1_z", &ver_pip_pim1_z, &b_ver_pip_pim1_z);
  fChain->SetBranchAddress("ver_pip_pim2_x", &ver_pip_pim2_x, &b_ver_pip_pim2_x);
  fChain->SetBranchAddress("ver_pip_pim2_y", &ver_pip_pim2_y, &b_ver_pip_pim2_y);
  fChain->SetBranchAddress("ver_pip_pim2_z", &ver_pip_pim2_z, &b_ver_pip_pim2_z);
  Notify();
}

Bool_t ppimpippim::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void ppimpippim::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}

Int_t ppimpippim::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}

void ppimpippim::FitK0(TH1F*hist, TF1 *sig, TF1* bg, TF1* sig_bg)
{
  cout<<endl<<"Fititing K0!!!"<<endl;
  double pedestal=0.5*(hist->GetBinContent(hist->FindBin(480))+hist->GetBinContent(hist->FindBin(500)));
  //cout<<"pedestal: "<<pedestal<<endl;

  sig->SetLineColor(kGreen);
  bg->SetLineColor(kBlue);
  sig_bg->SetLineColor(kRed);
  
  sig->SetRange(480,510);
  bg->SetRange(400,800);
  sig_bg->SetRange(350,800);

  sig->SetNpx(200);
  sig_bg->SetNpx(200);
  bg->SetNpx(200);
  
  hist->Fit(bg,"R");
  
  sig->SetParameter(0,hist->GetBinContent(hist->FindBin(495))-pedestal);
  sig->SetParameter(1,495);
  sig->SetParameter(2,10);
  sig->SetParameter(3,bg->GetParameter(0));
  sig->SetParameter(4,bg->GetParameter(1));
  //sig->SetParameter(2,5);
  
  hist->Fit(sig,"R");
  
  
  sig_bg->SetParameter(0,sig->GetParameter(0));
  sig_bg->SetParameter(1,sig->GetParameter(1));
  sig_bg->SetParameter(2,sig->GetParameter(2));
  sig_bg->SetParameter(3,bg->GetParameter(0));
  sig_bg->SetParameter(4,bg->GetParameter(1));
  sig_bg->SetParameter(5,bg->GetParameter(2));
  sig_bg->SetParameter(6,bg->GetParameter(3));
  sig_bg->SetParameter(7,bg->GetParameter(4));
  
  
  hist->Fit(sig_bg,"R");

  sig->SetParameter(0,sig_bg->GetParameter(0));
  sig->SetParameter(1,sig_bg->GetParameter(1));
  sig->SetParameter(2,sig_bg->GetParameter(2));

  bg->SetParameter(0,sig_bg->GetParameter(3));
  bg->SetParameter(1,sig_bg->GetParameter(4));
  bg->SetParameter(2,sig_bg->GetParameter(5));
  bg->SetParameter(3,sig_bg->GetParameter(6));
  bg->SetParameter(4,sig_bg->GetParameter(7));

  
  //hist->Draw();
  //sig_bg->Draw("cSAME");
  //sig->Draw("cSAME");
  //bg->Draw("cSAME");

  //sig_bg->Write();
  //sig->Write();
  //bg->Write();
  cout<<"End of fitting!"<<endl;
}

void ppimpippim::FitL1115(TH1F*hist, TF1 *sig, TF1* bg, TF1* sig_bg)
{
  cout<<endl<<"Fitting L1115"<<endl;
  double y1110=(hist->GetBinContent(hist->FindBin(1110)));
  double y1120=(hist->GetBinContent(hist->FindBin(1120)));
  double pedestal=0.5*(y1110+y1120);
  cout<<"pedestal: "<<pedestal<<endl;
  //hist->Draw();
  sig->SetLineColor(kGreen);
  bg->SetLineColor(kBlue);
  sig_bg->SetLineColor(kRed);

  sig->SetRange(118,1122);
  bg->SetRange(1080,1110);
  sig_bg->SetRange(1080,1120);

  sig->SetNpx(200);
  sig_bg->SetNpx(200);
  bg->SetNpx(200);

  hist->Fit(bg,"R");
  
  //sig->SetParameter(3,pedestal);
  sig->SetParameter(0,hist->GetBinContent(hist->FindBin(1115))-pedestal);
  sig->SetParameter(2,2);
  sig->SetParameter(1,1115);
  sig->SetParameter(3,y1110-1110*(y1120-y1110)/10);
  sig->SetParameter(4,(y1120-y1110)/10);
  //sig->SetParameter(4,bg->GetParameter(1));

  hist->Fit(sig,"R");
  
  sig_bg->SetParameter(0,sig->GetParameter(0));
  sig_bg->SetParameter(1,sig->GetParameter(1));
  sig_bg->SetParameter(2,sig->GetParameter(2));
  sig_bg->SetParameter(3,bg->GetParameter(0));
  sig_bg->SetParameter(4,bg->GetParameter(1));
  sig_bg->SetParameter(5,bg->GetParameter(2));
  sig_bg->SetParameter(6,bg->GetParameter(3));
  sig_bg->SetParameter(7,bg->GetParameter(4));
  sig_bg->SetParameter(8,bg->GetParameter(5));

  hist->Fit(sig_bg,"R");
  
  sig_bg->SetRange(1080,1160);
  hist->Fit(sig_bg,"R");

  sig->SetParameter(0,sig_bg->GetParameter(0));
  sig->SetParameter(1,sig_bg->GetParameter(1));
  sig->SetParameter(2,sig_bg->GetParameter(2));

  bg->SetParameter(0,sig_bg->GetParameter(3));
  bg->SetParameter(1,sig_bg->GetParameter(4));
  bg->SetParameter(2,sig_bg->GetParameter(5));
  bg->SetParameter(3,sig_bg->GetParameter(6));
  bg->SetParameter(4,sig_bg->GetParameter(7));
  bg->SetParameter(5,sig_bg->GetParameter(8));

  //hist->Draw();
  //sig_bg->Draw("cSAME");
  //sig->Draw("cSAME");
  //bg->Draw("cSAME");

  //sig_bg->Write();
  //sig->Write();
  //bg->Write();
}



#endif // #ifdef ppimpippim_cxx
