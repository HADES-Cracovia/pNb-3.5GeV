//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jul  4 11:20:05 2018 by ROOT version 5.34/34
// from TTree PPim_ID/PPim_ID
// found on file: be08280234531_dst_gen1_sep08_1_hadron_out.root
//////////////////////////////////////////////////////////

#ifndef PPim_ID_h
#define PPim_ID_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class PPim_ID {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         eVertClust_chi2;
   Float_t         eVertClust_x;
   Float_t         eVertClust_y;
   Float_t         eVertClust_z;
   Float_t         eVertReco_chi2;
   Float_t         eVertReco_x;
   Float_t         eVertReco_y;
   Float_t         eVertReco_z;
   Float_t         eVert_chi2;
   Float_t         eVert_x;
   Float_t         eVert_y;
   Float_t         eVert_z;
   Float_t         event;
   Float_t         hneg_mult;
   Float_t         hpos_mult;
   Float_t         isBest;
   Float_t         lneg_mult;
   Float_t         lpos_mult;
   Float_t         p_beta;
   Float_t         p_beta_new;
   Float_t         p_btChargeRing;
   Float_t         p_btChargeSum;
   Float_t         p_btChi2;
   Float_t         p_btClusters;
   Float_t         p_btMaxima;
   Float_t         p_btMaximaCharge;
   Float_t         p_btMaximaChargeShared;
   Float_t         p_btMaximaChargeSharedFragment;
   Float_t         p_btMaximaShared;
   Float_t         p_btMaximaSharedFragment;
   Float_t         p_btMeanDist;
   Float_t         p_btNearbyMaxima;
   Float_t         p_btNearbyMaximaShared;
   Float_t         p_btPadsClus;
   Float_t         p_btPadsRing;
   Float_t         p_btRingMatrix;
   Float_t         p_dedx_mdc;
   Float_t         p_dedx_tof;
   Float_t         p_id;
   Float_t         p_isBT;
   Float_t         p_isOffVertexClust;
   Float_t         p_isPrimaryVertex;
   Float_t         p_isUsedVertex;
   Float_t         p_isring;
   Float_t         p_isringmdc;
   Float_t         p_isringnomatch;
   Float_t         p_isringtrack;
   Float_t         p_kIsLepton;
   Float_t         p_kIsUsed;
   Float_t         p_mdcinnerchi2;
   Float_t         p_mdcouterchi2;
   Float_t         p_oa_hadr;
   Float_t         p_oa_lept;
   Float_t         p_p;
   Float_t         p_p_corr_em;
   Float_t         p_p_corr_ep;
   Float_t         p_p_corr_p;
   Float_t         p_p_corr_pim;
   Float_t         p_p_corr_pip;
   Float_t         p_phi;
   Float_t         p_phi_rich;
   Float_t         p_pid;
   Float_t         p_q;
   Float_t         p_r;
   Float_t         p_resolution;
   Float_t         p_resoultion;
   Float_t         p_rich_amp;
   Float_t         p_rich_centr;
   Float_t         p_rich_houtra;
   Float_t         p_rich_padnum;
   Float_t         p_rich_patmat;
   Float_t         p_rkchi2;
   Float_t         p_sector;
   Float_t         p_shw_sum0;
   Float_t         p_shw_sum1;
   Float_t         p_shw_sum2;
   Float_t         p_system;
   Float_t         p_theta;
   Float_t         p_theta_rich;
   Float_t         p_tof_mom;
   Float_t         p_tof_new;
   Float_t         p_tof_rec;
   Float_t         p_track_length;
   Float_t         p_tracklength;
   Float_t         p_z;
   Float_t         pim_beta;
   Float_t         pim_beta_new;
   Float_t         pim_btChargeRing;
   Float_t         pim_btChargeSum;
   Float_t         pim_btChi2;
   Float_t         pim_btClusters;
   Float_t         pim_btMaxima;
   Float_t         pim_btMaximaCharge;
   Float_t         pim_btMaximaChargeShared;
   Float_t         pim_btMaximaChargeSharedFragment;
   Float_t         pim_btMaximaShared;
   Float_t         pim_btMaximaSharedFragment;
   Float_t         pim_btMeanDist;
   Float_t         pim_btNearbyMaxima;
   Float_t         pim_btNearbyMaximaShared;
   Float_t         pim_btPadsClus;
   Float_t         pim_btPadsRing;
   Float_t         pim_btRingMatrix;
   Float_t         pim_dedx_mdc;
   Float_t         pim_dedx_tof;
   Float_t         pim_id;
   Float_t         pim_isBT;
   Float_t         pim_isOffVertexClust;
   Float_t         pim_isPrimaryVertex;
   Float_t         pim_isUsedVertex;
   Float_t         pim_isring;
   Float_t         pim_isringmdc;
   Float_t         pim_isringnomatch;
   Float_t         pim_isringtrack;
   Float_t         pim_kIsLepton;
   Float_t         pim_kIsUsed;
   Float_t         pim_mdcinnerchi2;
   Float_t         pim_mdcouterchi2;
   Float_t         pim_oa_hadr;
   Float_t         pim_oa_lept;
   Float_t         pim_p;
   Float_t         pim_p_corr_em;
   Float_t         pim_p_corr_ep;
   Float_t         pim_p_corr_p;
   Float_t         pim_p_corr_pim;
   Float_t         pim_p_corr_pip;
   Float_t         pim_phi;
   Float_t         pim_phi_rich;
   Float_t         pim_pid;
   Float_t         pim_q;
   Float_t         pim_r;
   Float_t         pim_resolution;
   Float_t         pim_resoultion;
   Float_t         pim_rich_amp;
   Float_t         pim_rich_centr;
   Float_t         pim_rich_houtra;
   Float_t         pim_rich_padnum;
   Float_t         pim_rich_patmat;
   Float_t         pim_rkchi2;
   Float_t         pim_sector;
   Float_t         pim_shw_sum0;
   Float_t         pim_shw_sum1;
   Float_t         pim_shw_sum2;
   Float_t         pim_system;
   Float_t         pim_theta;
   Float_t         pim_theta_rich;
   Float_t         pim_tof_mom;
   Float_t         pim_tof_new;
   Float_t         pim_tof_rec;
   Float_t         pim_track_length;
   Float_t         pim_tracklength;
   Float_t         pim_z;
   Float_t         runnumber;
   Float_t         totalmult;
   Float_t         trigbit;
   Float_t         trigdec;
   Float_t         trigdownscale;
   Float_t         trigdownscaleflag;

   // List of branches
   TBranch        *b_eVertClust_chi2;   //!
   TBranch        *b_eVertClust_x;   //!
   TBranch        *b_eVertClust_y;   //!
   TBranch        *b_eVertClust_z;   //!
   TBranch        *b_eVertReco_chi2;   //!
   TBranch        *b_eVertReco_x;   //!
   TBranch        *b_eVertReco_y;   //!
   TBranch        *b_eVertReco_z;   //!
   TBranch        *b_eVert_chi2;   //!
   TBranch        *b_eVert_x;   //!
   TBranch        *b_eVert_y;   //!
   TBranch        *b_eVert_z;   //!
   TBranch        *b_event;   //!
   TBranch        *b_hneg_mult;   //!
   TBranch        *b_hpos_mult;   //!
   TBranch        *b_isBest;   //!
   TBranch        *b_lneg_mult;   //!
   TBranch        *b_lpos_mult;   //!
   TBranch        *b_p_beta;   //!
   TBranch        *b_p_beta_new;   //!
   TBranch        *b_p_btChargeRing;   //!
   TBranch        *b_p_btChargeSum;   //!
   TBranch        *b_p_btChi2;   //!
   TBranch        *b_p_btClusters;   //!
   TBranch        *b_p_btMaxima;   //!
   TBranch        *b_p_btMaximaCharge;   //!
   TBranch        *b_p_btMaximaChargeShared;   //!
   TBranch        *b_p_btMaximaChargeSharedFragment;   //!
   TBranch        *b_p_btMaximaShared;   //!
   TBranch        *b_p_btMaximaSharedFragment;   //!
   TBranch        *b_p_btMeanDist;   //!
   TBranch        *b_p_btNearbyMaxima;   //!
   TBranch        *b_p_btNearbyMaximaShared;   //!
   TBranch        *b_p_btPadsClus;   //!
   TBranch        *b_p_btPadsRing;   //!
   TBranch        *b_p_btRingMatrix;   //!
   TBranch        *b_p_dedx_mdc;   //!
   TBranch        *b_p_dedx_tof;   //!
   TBranch        *b_p_id;   //!
   TBranch        *b_p_isBT;   //!
   TBranch        *b_p_isOffVertexClust;   //!
   TBranch        *b_p_isPrimaryVertex;   //!
   TBranch        *b_p_isUsedVertex;   //!
   TBranch        *b_p_isring;   //!
   TBranch        *b_p_isringmdc;   //!
   TBranch        *b_p_isringnomatch;   //!
   TBranch        *b_p_isringtrack;   //!
   TBranch        *b_p_kIsLepton;   //!
   TBranch        *b_p_kIsUsed;   //!
   TBranch        *b_p_mdcinnerchi2;   //!
   TBranch        *b_p_mdcouterchi2;   //!
   TBranch        *b_p_oa_hadr;   //!
   TBranch        *b_p_oa_lept;   //!
   TBranch        *b_p_p;   //!
   TBranch        *b_p_p_corr_em;   //!
   TBranch        *b_p_p_corr_ep;   //!
   TBranch        *b_p_p_corr_p;   //!
   TBranch        *b_p_p_corr_pim;   //!
   TBranch        *b_p_p_corr_pip;   //!
   TBranch        *b_p_phi;   //!
   TBranch        *b_p_phi_rich;   //!
   TBranch        *b_p_pid;   //!
   TBranch        *b_p_q;   //!
   TBranch        *b_p_r;   //!
   TBranch        *b_p_resolution;   //!
   TBranch        *b_p_resoultion;   //!
   TBranch        *b_p_rich_amp;   //!
   TBranch        *b_p_rich_centr;   //!
   TBranch        *b_p_rich_houtra;   //!
   TBranch        *b_p_rich_padnum;   //!
   TBranch        *b_p_rich_patmat;   //!
   TBranch        *b_p_rkchi2;   //!
   TBranch        *b_p_sector;   //!
   TBranch        *b_p_shw_sum0;   //!
   TBranch        *b_p_shw_sum1;   //!
   TBranch        *b_p_shw_sum2;   //!
   TBranch        *b_p_system;   //!
   TBranch        *b_p_theta;   //!
   TBranch        *b_p_theta_rich;   //!
   TBranch        *b_p_tof_mom;   //!
   TBranch        *b_p_tof_new;   //!
   TBranch        *b_p_tof_rec;   //!
   TBranch        *b_p_track_length;   //!
   TBranch        *b_p_tracklength;   //!
   TBranch        *b_p_z;   //!
   TBranch        *b_pim_beta;   //!
   TBranch        *b_pim_beta_new;   //!
   TBranch        *b_pim_btChargeRing;   //!
   TBranch        *b_pim_btChargeSum;   //!
   TBranch        *b_pim_btChi2;   //!
   TBranch        *b_pim_btClusters;   //!
   TBranch        *b_pim_btMaxima;   //!
   TBranch        *b_pim_btMaximaCharge;   //!
   TBranch        *b_pim_btMaximaChargeShared;   //!
   TBranch        *b_pim_btMaximaChargeSharedFragment;   //!
   TBranch        *b_pim_btMaximaShared;   //!
   TBranch        *b_pim_btMaximaSharedFragment;   //!
   TBranch        *b_pim_btMeanDist;   //!
   TBranch        *b_pim_btNearbyMaxima;   //!
   TBranch        *b_pim_btNearbyMaximaShared;   //!
   TBranch        *b_pim_btPadsClus;   //!
   TBranch        *b_pim_btPadsRing;   //!
   TBranch        *b_pim_btRingMatrix;   //!
   TBranch        *b_pim_dedx_mdc;   //!
   TBranch        *b_pim_dedx_tof;   //!
   TBranch        *b_pim_id;   //!
   TBranch        *b_pim_isBT;   //!
   TBranch        *b_pim_isOffVertexClust;   //!
   TBranch        *b_pim_isPrimaryVertex;   //!
   TBranch        *b_pim_isUsedVertex;   //!
   TBranch        *b_pim_isring;   //!
   TBranch        *b_pim_isringmdc;   //!
   TBranch        *b_pim_isringnomatch;   //!
   TBranch        *b_pim_isringtrack;   //!
   TBranch        *b_pim_kIsLepton;   //!
   TBranch        *b_pim_kIsUsed;   //!
   TBranch        *b_pim_mdcinnerchi2;   //!
   TBranch        *b_pim_mdcouterchi2;   //!
   TBranch        *b_pim_oa_hadr;   //!
   TBranch        *b_pim_oa_lept;   //!
   TBranch        *b_pim_p;   //!
   TBranch        *b_pim_p_corr_em;   //!
   TBranch        *b_pim_p_corr_ep;   //!
   TBranch        *b_pim_p_corr_p;   //!
   TBranch        *b_pim_p_corr_pim;   //!
   TBranch        *b_pim_p_corr_pip;   //!
   TBranch        *b_pim_phi;   //!
   TBranch        *b_pim_phi_rich;   //!
   TBranch        *b_pim_pid;   //!
   TBranch        *b_pim_q;   //!
   TBranch        *b_pim_r;   //!
   TBranch        *b_pim_resolution;   //!
   TBranch        *b_pim_resoultion;   //!
   TBranch        *b_pim_rich_amp;   //!
   TBranch        *b_pim_rich_centr;   //!
   TBranch        *b_pim_rich_houtra;   //!
   TBranch        *b_pim_rich_padnum;   //!
   TBranch        *b_pim_rich_patmat;   //!
   TBranch        *b_pim_rkchi2;   //!
   TBranch        *b_pim_sector;   //!
   TBranch        *b_pim_shw_sum0;   //!
   TBranch        *b_pim_shw_sum1;   //!
   TBranch        *b_pim_shw_sum2;   //!
   TBranch        *b_pim_system;   //!
   TBranch        *b_pim_theta;   //!
   TBranch        *b_pim_theta_rich;   //!
   TBranch        *b_pim_tof_mom;   //!
   TBranch        *b_pim_tof_new;   //!
   TBranch        *b_pim_tof_rec;   //!
   TBranch        *b_pim_track_length;   //!
   TBranch        *b_pim_tracklength;   //!
   TBranch        *b_pim_z;   //!
   TBranch        *b_runnumber;   //!
   TBranch        *b_totalmult;   //!
   TBranch        *b_trigbit;   //!
   TBranch        *b_trigdec;   //!
   TBranch        *b_trigdownscale;   //!
   TBranch        *b_trigdownscaleflag;   //!

   PPim_ID(TTree *tree=0);
   virtual ~PPim_ID();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef PPim_ID_cxx
PPim_ID::PPim_ID(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("be08280234531_dst_gen1_sep08_1_hadron_out.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("be08280234531_dst_gen1_sep08_1_hadron_out.root");
      }
      f->GetObject("PPim_ID",tree);

   }
   Init(tree);
}

PPim_ID::~PPim_ID()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t PPim_ID::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t PPim_ID::LoadTree(Long64_t entry)
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

void PPim_ID::Init(TTree *tree)
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

   fChain->SetBranchAddress("eVertClust_chi2", &eVertClust_chi2, &b_eVertClust_chi2);
   fChain->SetBranchAddress("eVertClust_x", &eVertClust_x, &b_eVertClust_x);
   fChain->SetBranchAddress("eVertClust_y", &eVertClust_y, &b_eVertClust_y);
   fChain->SetBranchAddress("eVertClust_z", &eVertClust_z, &b_eVertClust_z);
   fChain->SetBranchAddress("eVertReco_chi2", &eVertReco_chi2, &b_eVertReco_chi2);
   fChain->SetBranchAddress("eVertReco_x", &eVertReco_x, &b_eVertReco_x);
   fChain->SetBranchAddress("eVertReco_y", &eVertReco_y, &b_eVertReco_y);
   fChain->SetBranchAddress("eVertReco_z", &eVertReco_z, &b_eVertReco_z);
   fChain->SetBranchAddress("eVert_chi2", &eVert_chi2, &b_eVert_chi2);
   fChain->SetBranchAddress("eVert_x", &eVert_x, &b_eVert_x);
   fChain->SetBranchAddress("eVert_y", &eVert_y, &b_eVert_y);
   fChain->SetBranchAddress("eVert_z", &eVert_z, &b_eVert_z);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("hneg_mult", &hneg_mult, &b_hneg_mult);
   fChain->SetBranchAddress("hpos_mult", &hpos_mult, &b_hpos_mult);
   fChain->SetBranchAddress("isBest", &isBest, &b_isBest);
   fChain->SetBranchAddress("lneg_mult", &lneg_mult, &b_lneg_mult);
   fChain->SetBranchAddress("lpos_mult", &lpos_mult, &b_lpos_mult);
   fChain->SetBranchAddress("p_beta", &p_beta, &b_p_beta);
   fChain->SetBranchAddress("p_beta_new", &p_beta_new, &b_p_beta_new);
   fChain->SetBranchAddress("p_btChargeRing", &p_btChargeRing, &b_p_btChargeRing);
   fChain->SetBranchAddress("p_btChargeSum", &p_btChargeSum, &b_p_btChargeSum);
   fChain->SetBranchAddress("p_btChi2", &p_btChi2, &b_p_btChi2);
   fChain->SetBranchAddress("p_btClusters", &p_btClusters, &b_p_btClusters);
   fChain->SetBranchAddress("p_btMaxima", &p_btMaxima, &b_p_btMaxima);
   fChain->SetBranchAddress("p_btMaximaCharge", &p_btMaximaCharge, &b_p_btMaximaCharge);
   fChain->SetBranchAddress("p_btMaximaChargeShared", &p_btMaximaChargeShared, &b_p_btMaximaChargeShared);
   fChain->SetBranchAddress("p_btMaximaChargeSharedFragment", &p_btMaximaChargeSharedFragment, &b_p_btMaximaChargeSharedFragment);
   fChain->SetBranchAddress("p_btMaximaShared", &p_btMaximaShared, &b_p_btMaximaShared);
   fChain->SetBranchAddress("p_btMaximaSharedFragment", &p_btMaximaSharedFragment, &b_p_btMaximaSharedFragment);
   fChain->SetBranchAddress("p_btMeanDist", &p_btMeanDist, &b_p_btMeanDist);
   fChain->SetBranchAddress("p_btNearbyMaxima", &p_btNearbyMaxima, &b_p_btNearbyMaxima);
   fChain->SetBranchAddress("p_btNearbyMaximaShared", &p_btNearbyMaximaShared, &b_p_btNearbyMaximaShared);
   fChain->SetBranchAddress("p_btPadsClus", &p_btPadsClus, &b_p_btPadsClus);
   fChain->SetBranchAddress("p_btPadsRing", &p_btPadsRing, &b_p_btPadsRing);
   fChain->SetBranchAddress("p_btRingMatrix", &p_btRingMatrix, &b_p_btRingMatrix);
   fChain->SetBranchAddress("p_dedx_mdc", &p_dedx_mdc, &b_p_dedx_mdc);
   fChain->SetBranchAddress("p_dedx_tof", &p_dedx_tof, &b_p_dedx_tof);
   fChain->SetBranchAddress("p_id", &p_id, &b_p_id);
   fChain->SetBranchAddress("p_isBT", &p_isBT, &b_p_isBT);
   fChain->SetBranchAddress("p_isOffVertexClust", &p_isOffVertexClust, &b_p_isOffVertexClust);
   fChain->SetBranchAddress("p_isPrimaryVertex", &p_isPrimaryVertex, &b_p_isPrimaryVertex);
   fChain->SetBranchAddress("p_isUsedVertex", &p_isUsedVertex, &b_p_isUsedVertex);
   fChain->SetBranchAddress("p_isring", &p_isring, &b_p_isring);
   fChain->SetBranchAddress("p_isringmdc", &p_isringmdc, &b_p_isringmdc);
   fChain->SetBranchAddress("p_isringnomatch", &p_isringnomatch, &b_p_isringnomatch);
   fChain->SetBranchAddress("p_isringtrack", &p_isringtrack, &b_p_isringtrack);
   fChain->SetBranchAddress("p_kIsLepton", &p_kIsLepton, &b_p_kIsLepton);
   fChain->SetBranchAddress("p_kIsUsed", &p_kIsUsed, &b_p_kIsUsed);
   fChain->SetBranchAddress("p_mdcinnerchi2", &p_mdcinnerchi2, &b_p_mdcinnerchi2);
   fChain->SetBranchAddress("p_mdcouterchi2", &p_mdcouterchi2, &b_p_mdcouterchi2);
   fChain->SetBranchAddress("p_oa_hadr", &p_oa_hadr, &b_p_oa_hadr);
   fChain->SetBranchAddress("p_oa_lept", &p_oa_lept, &b_p_oa_lept);
   fChain->SetBranchAddress("p_p", &p_p, &b_p_p);
   fChain->SetBranchAddress("p_p_corr_em", &p_p_corr_em, &b_p_p_corr_em);
   fChain->SetBranchAddress("p_p_corr_ep", &p_p_corr_ep, &b_p_p_corr_ep);
   fChain->SetBranchAddress("p_p_corr_p", &p_p_corr_p, &b_p_p_corr_p);
   fChain->SetBranchAddress("p_p_corr_pim", &p_p_corr_pim, &b_p_p_corr_pim);
   fChain->SetBranchAddress("p_p_corr_pip", &p_p_corr_pip, &b_p_p_corr_pip);
   fChain->SetBranchAddress("p_phi", &p_phi, &b_p_phi);
   fChain->SetBranchAddress("p_phi_rich", &p_phi_rich, &b_p_phi_rich);
   fChain->SetBranchAddress("p_pid", &p_pid, &b_p_pid);
   fChain->SetBranchAddress("p_q", &p_q, &b_p_q);
   fChain->SetBranchAddress("p_r", &p_r, &b_p_r);
   fChain->SetBranchAddress("p_resolution", &p_resolution, &b_p_resolution);
   fChain->SetBranchAddress("p_resoultion", &p_resoultion, &b_p_resoultion);
   fChain->SetBranchAddress("p_rich_amp", &p_rich_amp, &b_p_rich_amp);
   fChain->SetBranchAddress("p_rich_centr", &p_rich_centr, &b_p_rich_centr);
   fChain->SetBranchAddress("p_rich_houtra", &p_rich_houtra, &b_p_rich_houtra);
   fChain->SetBranchAddress("p_rich_padnum", &p_rich_padnum, &b_p_rich_padnum);
   fChain->SetBranchAddress("p_rich_patmat", &p_rich_patmat, &b_p_rich_patmat);
   fChain->SetBranchAddress("p_rkchi2", &p_rkchi2, &b_p_rkchi2);
   fChain->SetBranchAddress("p_sector", &p_sector, &b_p_sector);
   fChain->SetBranchAddress("p_shw_sum0", &p_shw_sum0, &b_p_shw_sum0);
   fChain->SetBranchAddress("p_shw_sum1", &p_shw_sum1, &b_p_shw_sum1);
   fChain->SetBranchAddress("p_shw_sum2", &p_shw_sum2, &b_p_shw_sum2);
   fChain->SetBranchAddress("p_system", &p_system, &b_p_system);
   fChain->SetBranchAddress("p_theta", &p_theta, &b_p_theta);
   fChain->SetBranchAddress("p_theta_rich", &p_theta_rich, &b_p_theta_rich);
   fChain->SetBranchAddress("p_tof_mom", &p_tof_mom, &b_p_tof_mom);
   fChain->SetBranchAddress("p_tof_new", &p_tof_new, &b_p_tof_new);
   fChain->SetBranchAddress("p_tof_rec", &p_tof_rec, &b_p_tof_rec);
   fChain->SetBranchAddress("p_track_length", &p_track_length, &b_p_track_length);
   fChain->SetBranchAddress("p_tracklength", &p_tracklength, &b_p_tracklength);
   fChain->SetBranchAddress("p_z", &p_z, &b_p_z);
   fChain->SetBranchAddress("pim_beta", &pim_beta, &b_pim_beta);
   fChain->SetBranchAddress("pim_beta_new", &pim_beta_new, &b_pim_beta_new);
   fChain->SetBranchAddress("pim_btChargeRing", &pim_btChargeRing, &b_pim_btChargeRing);
   fChain->SetBranchAddress("pim_btChargeSum", &pim_btChargeSum, &b_pim_btChargeSum);
   fChain->SetBranchAddress("pim_btChi2", &pim_btChi2, &b_pim_btChi2);
   fChain->SetBranchAddress("pim_btClusters", &pim_btClusters, &b_pim_btClusters);
   fChain->SetBranchAddress("pim_btMaxima", &pim_btMaxima, &b_pim_btMaxima);
   fChain->SetBranchAddress("pim_btMaximaCharge", &pim_btMaximaCharge, &b_pim_btMaximaCharge);
   fChain->SetBranchAddress("pim_btMaximaChargeShared", &pim_btMaximaChargeShared, &b_pim_btMaximaChargeShared);
   fChain->SetBranchAddress("pim_btMaximaChargeSharedFragment", &pim_btMaximaChargeSharedFragment, &b_pim_btMaximaChargeSharedFragment);
   fChain->SetBranchAddress("pim_btMaximaShared", &pim_btMaximaShared, &b_pim_btMaximaShared);
   fChain->SetBranchAddress("pim_btMaximaSharedFragment", &pim_btMaximaSharedFragment, &b_pim_btMaximaSharedFragment);
   fChain->SetBranchAddress("pim_btMeanDist", &pim_btMeanDist, &b_pim_btMeanDist);
   fChain->SetBranchAddress("pim_btNearbyMaxima", &pim_btNearbyMaxima, &b_pim_btNearbyMaxima);
   fChain->SetBranchAddress("pim_btNearbyMaximaShared", &pim_btNearbyMaximaShared, &b_pim_btNearbyMaximaShared);
   fChain->SetBranchAddress("pim_btPadsClus", &pim_btPadsClus, &b_pim_btPadsClus);
   fChain->SetBranchAddress("pim_btPadsRing", &pim_btPadsRing, &b_pim_btPadsRing);
   fChain->SetBranchAddress("pim_btRingMatrix", &pim_btRingMatrix, &b_pim_btRingMatrix);
   fChain->SetBranchAddress("pim_dedx_mdc", &pim_dedx_mdc, &b_pim_dedx_mdc);
   fChain->SetBranchAddress("pim_dedx_tof", &pim_dedx_tof, &b_pim_dedx_tof);
   fChain->SetBranchAddress("pim_id", &pim_id, &b_pim_id);
   fChain->SetBranchAddress("pim_isBT", &pim_isBT, &b_pim_isBT);
   fChain->SetBranchAddress("pim_isOffVertexClust", &pim_isOffVertexClust, &b_pim_isOffVertexClust);
   fChain->SetBranchAddress("pim_isPrimaryVertex", &pim_isPrimaryVertex, &b_pim_isPrimaryVertex);
   fChain->SetBranchAddress("pim_isUsedVertex", &pim_isUsedVertex, &b_pim_isUsedVertex);
   fChain->SetBranchAddress("pim_isring", &pim_isring, &b_pim_isring);
   fChain->SetBranchAddress("pim_isringmdc", &pim_isringmdc, &b_pim_isringmdc);
   fChain->SetBranchAddress("pim_isringnomatch", &pim_isringnomatch, &b_pim_isringnomatch);
   fChain->SetBranchAddress("pim_isringtrack", &pim_isringtrack, &b_pim_isringtrack);
   fChain->SetBranchAddress("pim_kIsLepton", &pim_kIsLepton, &b_pim_kIsLepton);
   fChain->SetBranchAddress("pim_kIsUsed", &pim_kIsUsed, &b_pim_kIsUsed);
   fChain->SetBranchAddress("pim_mdcinnerchi2", &pim_mdcinnerchi2, &b_pim_mdcinnerchi2);
   fChain->SetBranchAddress("pim_mdcouterchi2", &pim_mdcouterchi2, &b_pim_mdcouterchi2);
   fChain->SetBranchAddress("pim_oa_hadr", &pim_oa_hadr, &b_pim_oa_hadr);
   fChain->SetBranchAddress("pim_oa_lept", &pim_oa_lept, &b_pim_oa_lept);
   fChain->SetBranchAddress("pim_p", &pim_p, &b_pim_p);
   fChain->SetBranchAddress("pim_p_corr_em", &pim_p_corr_em, &b_pim_p_corr_em);
   fChain->SetBranchAddress("pim_p_corr_ep", &pim_p_corr_ep, &b_pim_p_corr_ep);
   fChain->SetBranchAddress("pim_p_corr_p", &pim_p_corr_p, &b_pim_p_corr_p);
   fChain->SetBranchAddress("pim_p_corr_pim", &pim_p_corr_pim, &b_pim_p_corr_pim);
   fChain->SetBranchAddress("pim_p_corr_pip", &pim_p_corr_pip, &b_pim_p_corr_pip);
   fChain->SetBranchAddress("pim_phi", &pim_phi, &b_pim_phi);
   fChain->SetBranchAddress("pim_phi_rich", &pim_phi_rich, &b_pim_phi_rich);
   fChain->SetBranchAddress("pim_pid", &pim_pid, &b_pim_pid);
   fChain->SetBranchAddress("pim_q", &pim_q, &b_pim_q);
   fChain->SetBranchAddress("pim_r", &pim_r, &b_pim_r);
   fChain->SetBranchAddress("pim_resolution", &pim_resolution, &b_pim_resolution);
   fChain->SetBranchAddress("pim_resoultion", &pim_resoultion, &b_pim_resoultion);
   fChain->SetBranchAddress("pim_rich_amp", &pim_rich_amp, &b_pim_rich_amp);
   fChain->SetBranchAddress("pim_rich_centr", &pim_rich_centr, &b_pim_rich_centr);
   fChain->SetBranchAddress("pim_rich_houtra", &pim_rich_houtra, &b_pim_rich_houtra);
   fChain->SetBranchAddress("pim_rich_padnum", &pim_rich_padnum, &b_pim_rich_padnum);
   fChain->SetBranchAddress("pim_rich_patmat", &pim_rich_patmat, &b_pim_rich_patmat);
   fChain->SetBranchAddress("pim_rkchi2", &pim_rkchi2, &b_pim_rkchi2);
   fChain->SetBranchAddress("pim_sector", &pim_sector, &b_pim_sector);
   fChain->SetBranchAddress("pim_shw_sum0", &pim_shw_sum0, &b_pim_shw_sum0);
   fChain->SetBranchAddress("pim_shw_sum1", &pim_shw_sum1, &b_pim_shw_sum1);
   fChain->SetBranchAddress("pim_shw_sum2", &pim_shw_sum2, &b_pim_shw_sum2);
   fChain->SetBranchAddress("pim_system", &pim_system, &b_pim_system);
   fChain->SetBranchAddress("pim_theta", &pim_theta, &b_pim_theta);
   fChain->SetBranchAddress("pim_theta_rich", &pim_theta_rich, &b_pim_theta_rich);
   fChain->SetBranchAddress("pim_tof_mom", &pim_tof_mom, &b_pim_tof_mom);
   fChain->SetBranchAddress("pim_tof_new", &pim_tof_new, &b_pim_tof_new);
   fChain->SetBranchAddress("pim_tof_rec", &pim_tof_rec, &b_pim_tof_rec);
   fChain->SetBranchAddress("pim_track_length", &pim_track_length, &b_pim_track_length);
   fChain->SetBranchAddress("pim_tracklength", &pim_tracklength, &b_pim_tracklength);
   fChain->SetBranchAddress("pim_z", &pim_z, &b_pim_z);
   fChain->SetBranchAddress("runnumber", &runnumber, &b_runnumber);
   fChain->SetBranchAddress("totalmult", &totalmult, &b_totalmult);
   fChain->SetBranchAddress("trigbit", &trigbit, &b_trigbit);
   fChain->SetBranchAddress("trigdec", &trigdec, &b_trigdec);
   fChain->SetBranchAddress("trigdownscale", &trigdownscale, &b_trigdownscale);
   fChain->SetBranchAddress("trigdownscaleflag", &trigdownscaleflag, &b_trigdownscaleflag);
   Notify();
}

Bool_t PPim_ID::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void PPim_ID::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t PPim_ID::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef PPim_ID_cxx
