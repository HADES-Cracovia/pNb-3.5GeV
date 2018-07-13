//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jul  4 11:20:05 2018 by ROOT version 5.34/34
// from TTree PPim_ID/PPim_ID
// found on file: be08280234531_dst_gen1_sep08_1_hadron_out.root
//////////////////////////////////////////////////////////

#ifndef PPim_h
#define PPim_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class PPim {
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

  PPim(TTree *tree=0);

  virtual ~PPim();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
};
#endif
