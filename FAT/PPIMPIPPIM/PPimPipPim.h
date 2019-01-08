//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jul 10 15:02:46 2018 by ROOT version 5.34/34
// from TTree PPimPipPim/PPimPipPim
// found on file: be08280235056_dst_gen1_sep08_hadron_out.root
//////////////////////////////////////////////////////////

#ifndef PPimPipPim_h
#define PPimPipPim_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class PPimPipPim {
public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

  // Declaration of leaf types
  Float_t         isBest;
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
  Float_t         pim1_beta;
  Float_t         pim1_beta_new;
  Float_t         pim1_btChargeRing;
  Float_t         pim1_btChargeSum;
  Float_t         pim1_btChi2;
  Float_t         pim1_btClusters;
  Float_t         pim1_btMaxima;
  Float_t         pim1_btMaximaCharge;
  Float_t         pim1_btMaximaChargeShared;
  Float_t         pim1_btMaximaChargeSharedFragment;
  Float_t         pim1_btMaximaShared;
  Float_t         pim1_btMaximaSharedFragment;
  Float_t         pim1_btMeanDist;
  Float_t         pim1_btNearbyMaxima;
  Float_t         pim1_btNearbyMaximaShared;
  Float_t         pim1_btPadsClus;
  Float_t         pim1_btPadsRing;
  Float_t         pim1_btRingMatrix;
  Float_t         pim1_dedx_mdc;
  Float_t         pim1_dedx_tof;
  Float_t         pim1_id;
  Float_t         pim1_isBT;
  Float_t         pim1_isOffVertexClust;
  Float_t         pim1_isPrimaryVertex;
  Float_t         pim1_isUsedVertex;
  Float_t         pim1_isring;
  Float_t         pim1_isringmdc;
  Float_t         pim1_isringnomatch;
  Float_t         pim1_isringtrack;
  Float_t         pim1_kIsLepton;
  Float_t         pim1_kIsUsed;
  Float_t         pim1_mdcinnerchi2;
  Float_t         pim1_mdcouterchi2;
  Float_t         pim1_oa_hadr;
  Float_t         pim1_oa_lept;
  Float_t         pim1_p;
  Float_t         pim1_p_corr_em;
  Float_t         pim1_p_corr_ep;
  Float_t         pim1_p_corr_p;
  Float_t         pim1_p_corr_pim;
  Float_t         pim1_p_corr_pip;
  Float_t         pim1_phi;
  Float_t         pim1_phi_rich;
  Float_t         pim1_pid;
  Float_t         pim1_q;
  Float_t         pim1_r;
  Float_t         pim1_resolution;
  Float_t         pim1_resoultion;
  Float_t         pim1_rich_amp;
  Float_t         pim1_rich_centr;
  Float_t         pim1_rich_houtra;
  Float_t         pim1_rich_padnum;
  Float_t         pim1_rich_patmat;
  Float_t         pim1_rkchi2;
  Float_t         pim1_sector;
  Float_t         pim1_shw_sum0;
  Float_t         pim1_shw_sum1;
  Float_t         pim1_shw_sum2;
  Float_t         pim1_system;
  Float_t         pim1_theta;
  Float_t         pim1_theta_rich;
  Float_t         pim1_tof_mom;
  Float_t         pim1_tof_new;
  Float_t         pim1_tof_rec;
  Float_t         pim1_track_length;
  Float_t         pim1_tracklength;
  Float_t         pim1_z;
  Float_t         pim2_beta;
  Float_t         pim2_beta_new;
  Float_t         pim2_btChargeRing;
  Float_t         pim2_btChargeSum;
  Float_t         pim2_btChi2;
  Float_t         pim2_btClusters;
  Float_t         pim2_btMaxima;
  Float_t         pim2_btMaximaCharge;
  Float_t         pim2_btMaximaChargeShared;
  Float_t         pim2_btMaximaChargeSharedFragment;
  Float_t         pim2_btMaximaShared;
  Float_t         pim2_btMaximaSharedFragment;
  Float_t         pim2_btMeanDist;
  Float_t         pim2_btNearbyMaxima;
  Float_t         pim2_btNearbyMaximaShared;
  Float_t         pim2_btPadsClus;
  Float_t         pim2_btPadsRing;
  Float_t         pim2_btRingMatrix;
  Float_t         pim2_dedx_mdc;
  Float_t         pim2_dedx_tof;
  Float_t         pim2_id;
  Float_t         pim2_isBT;
  Float_t         pim2_isOffVertexClust;
  Float_t         pim2_isPrimaryVertex;
  Float_t         pim2_isUsedVertex;
  Float_t         pim2_isring;
  Float_t         pim2_isringmdc;
  Float_t         pim2_isringnomatch;
  Float_t         pim2_isringtrack;
  Float_t         pim2_kIsLepton;
  Float_t         pim2_kIsUsed;
  Float_t         pim2_mdcinnerchi2;
  Float_t         pim2_mdcouterchi2;
  Float_t         pim2_oa_hadr;
  Float_t         pim2_oa_lept;
  Float_t         pim2_p;
  Float_t         pim2_p_corr_em;
  Float_t         pim2_p_corr_ep;
  Float_t         pim2_p_corr_p;
  Float_t         pim2_p_corr_pim;
  Float_t         pim2_p_corr_pip;
  Float_t         pim2_phi;
  Float_t         pim2_phi_rich;
  Float_t         pim2_pid;
  Float_t         pim2_q;
  Float_t         pim2_r;
  Float_t         pim2_resolution;
  Float_t         pim2_resoultion;
  Float_t         pim2_rich_amp;
  Float_t         pim2_rich_centr;
  Float_t         pim2_rich_houtra;
  Float_t         pim2_rich_padnum;
  Float_t         pim2_rich_patmat;
  Float_t         pim2_rkchi2;
  Float_t         pim2_sector;
  Float_t         pim2_shw_sum0;
  Float_t         pim2_shw_sum1;
  Float_t         pim2_shw_sum2;
  Float_t         pim2_system;
  Float_t         pim2_theta;
  Float_t         pim2_theta_rich;
  Float_t         pim2_tof_mom;
  Float_t         pim2_tof_new;
  Float_t         pim2_tof_rec;
  Float_t         pim2_track_length;
  Float_t         pim2_tracklength;
  Float_t         pim2_z;
  Float_t         pip_beta;
  Float_t         pip_beta_new;
  Float_t         pip_btChargeRing;
  Float_t         pip_btChargeSum;
  Float_t         pip_btChi2;
  Float_t         pip_btClusters;
  Float_t         pip_btMaxima;
  Float_t         pip_btMaximaCharge;
  Float_t         pip_btMaximaChargeShared;
  Float_t         pip_btMaximaChargeSharedFragment;
  Float_t         pip_btMaximaShared;
  Float_t         pip_btMaximaSharedFragment;
  Float_t         pip_btMeanDist;
  Float_t         pip_btNearbyMaxima;
  Float_t         pip_btNearbyMaximaShared;
  Float_t         pip_btPadsClus;
  Float_t         pip_btPadsRing;
  Float_t         pip_btRingMatrix;
  Float_t         pip_dedx_mdc;
  Float_t         pip_dedx_tof;
  Float_t         pip_id;
  Float_t         pip_isBT;
  Float_t         pip_isOffVertexClust;
  Float_t         pip_isPrimaryVertex;
  Float_t         pip_isUsedVertex;
  Float_t         pip_isring;
  Float_t         pip_isringmdc;
  Float_t         pip_isringnomatch;
  Float_t         pip_isringtrack;
  Float_t         pip_kIsLepton;
  Float_t         pip_kIsUsed;
  Float_t         pip_mdcinnerchi2;
  Float_t         pip_mdcouterchi2;
  Float_t         pip_oa_hadr;
  Float_t         pip_oa_lept;
  Float_t         pip_p;
  Float_t         pip_p_corr_em;
  Float_t         pip_p_corr_ep;
  Float_t         pip_p_corr_p;
  Float_t         pip_p_corr_pim;
  Float_t         pip_p_corr_pip;
  Float_t         pip_phi;
  Float_t         pip_phi_rich;
  Float_t         pip_pid;
  Float_t         pip_q;
  Float_t         pip_r;
  Float_t         pip_resolution;
  Float_t         pip_resoultion;
  Float_t         pip_rich_amp;
  Float_t         pip_rich_centr;
  Float_t         pip_rich_houtra;
  Float_t         pip_rich_padnum;
  Float_t         pip_rich_patmat;
  Float_t         pip_rkchi2;
  Float_t         pip_sector;
  Float_t         pip_shw_sum0;
  Float_t         pip_shw_sum1;
  Float_t         pip_shw_sum2;
  Float_t         pip_system;
  Float_t         pip_theta;
  Float_t         pip_theta_rich;
  Float_t         pip_tof_mom;
  Float_t         pip_tof_new;
  Float_t         pip_tof_rec;
  Float_t         pip_track_length;
  Float_t         pip_tracklength;
  Float_t         pip_z;
  Float_t         runnumber;
  Float_t         totalmult;
  Float_t         trigbit;
  Float_t         trigdec;
  Float_t         trigdownscale;
  Float_t         trigdownscaleflag;
  
  
  // List of branches
  TBranch        *b_isBest;   //!
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
  TBranch        *b_pim1_beta;   //!
  TBranch        *b_pim1_beta_new;   //!
  TBranch        *b_pim1_btChargeRing;   //!
  TBranch        *b_pim1_btChargeSum;   //!
  TBranch        *b_pim1_btChi2;   //!
  TBranch        *b_pim1_btClusters;   //!
  TBranch        *b_pim1_btMaxima;   //!
  TBranch        *b_pim1_btMaximaCharge;   //!
  TBranch        *b_pim1_btMaximaChargeShared;   //!
  TBranch        *b_pim1_btMaximaChargeSharedFragment;   //!
  TBranch        *b_pim1_btMaximaShared;   //!
  TBranch        *b_pim1_btMaximaSharedFragment;   //!
  TBranch        *b_pim1_btMeanDist;   //!
  TBranch        *b_pim1_btNearbyMaxima;   //!
  TBranch        *b_pim1_btNearbyMaximaShared;   //!
  TBranch        *b_pim1_btPadsClus;   //!
  TBranch        *b_pim1_btPadsRing;   //!
  TBranch        *b_pim1_btRingMatrix;   //!
  TBranch        *b_pim1_dedx_mdc;   //!
  TBranch        *b_pim1_dedx_tof;   //!
  TBranch        *b_pim1_id;   //!
  TBranch        *b_pim1_isBT;   //!
  TBranch        *b_pim1_isOffVertexClust;   //!
  TBranch        *b_pim1_isPrimaryVertex;   //!
  TBranch        *b_pim1_isUsedVertex;   //!
  TBranch        *b_pim1_isring;   //!
  TBranch        *b_pim1_isringmdc;   //!
  TBranch        *b_pim1_isringnomatch;   //!
  TBranch        *b_pim1_isringtrack;   //!
  TBranch        *b_pim1_kIsLepton;   //!
  TBranch        *b_pim1_kIsUsed;   //!
  TBranch        *b_pim1_mdcinnerchi2;   //!
  TBranch        *b_pim1_mdcouterchi2;   //!
  TBranch        *b_pim1_oa_hadr;   //!
  TBranch        *b_pim1_oa_lept;   //!
  TBranch        *b_pim1_p;   //!
  TBranch        *b_pim1_p_corr_em;   //!
  TBranch        *b_pim1_p_corr_ep;   //!
  TBranch        *b_pim1_p_corr_p;   //!
  TBranch        *b_pim1_p_corr_pim;   //!
  TBranch        *b_pim1_p_corr_pip;   //!
  TBranch        *b_pim1_phi;   //!
  TBranch        *b_pim1_phi_rich;   //!
  TBranch        *b_pim1_pid;   //!
  TBranch        *b_pim1_q;   //!
  TBranch        *b_pim1_r;   //!
  TBranch        *b_pim1_resolution;   //!
  TBranch        *b_pim1_resoultion;   //!
  TBranch        *b_pim1_rich_amp;   //!
  TBranch        *b_pim1_rich_centr;   //!
  TBranch        *b_pim1_rich_houtra;   //!
  TBranch        *b_pim1_rich_padnum;   //!
  TBranch        *b_pim1_rich_patmat;   //!
  TBranch        *b_pim1_rkchi2;   //!
  TBranch        *b_pim1_sector;   //!
  TBranch        *b_pim1_shw_sum0;   //!
  TBranch        *b_pim1_shw_sum1;   //!
  TBranch        *b_pim1_shw_sum2;   //!
  TBranch        *b_pim1_system;   //!
  TBranch        *b_pim1_theta;   //!
  TBranch        *b_pim1_theta_rich;   //!
  TBranch        *b_pim1_tof_mom;   //!
  TBranch        *b_pim1_tof_new;   //!
  TBranch        *b_pim1_tof_rec;   //!
  TBranch        *b_pim1_track_length;   //!
  TBranch        *b_pim1_tracklength;   //!
  TBranch        *b_pim1_z;   //!
  TBranch        *b_pim2_beta;   //!
  TBranch        *b_pim2_beta_new;   //!
  TBranch        *b_pim2_btChargeRing;   //!
  TBranch        *b_pim2_btChargeSum;   //!
  TBranch        *b_pim2_btChi2;   //!
  TBranch        *b_pim2_btClusters;   //!
  TBranch        *b_pim2_btMaxima;   //!
  TBranch        *b_pim2_btMaximaCharge;   //!
  TBranch        *b_pim2_btMaximaChargeShared;   //!
  TBranch        *b_pim2_btMaximaChargeSharedFragment;   //!
  TBranch        *b_pim2_btMaximaShared;   //!
  TBranch        *b_pim2_btMaximaSharedFragment;   //!
  TBranch        *b_pim2_btMeanDist;   //!
  TBranch        *b_pim2_btNearbyMaxima;   //!
  TBranch        *b_pim2_btNearbyMaximaShared;   //!
  TBranch        *b_pim2_btPadsClus;   //!
  TBranch        *b_pim2_btPadsRing;   //!
  TBranch        *b_pim2_btRingMatrix;   //!
  TBranch        *b_pim2_dedx_mdc;   //!
  TBranch        *b_pim2_dedx_tof;   //!
  TBranch        *b_pim2_id;   //!
  TBranch        *b_pim2_isBT;   //!
  TBranch        *b_pim2_isOffVertexClust;   //!
  TBranch        *b_pim2_isPrimaryVertex;   //!
  TBranch        *b_pim2_isUsedVertex;   //!
  TBranch        *b_pim2_isring;   //!
  TBranch        *b_pim2_isringmdc;   //!
  TBranch        *b_pim2_isringnomatch;   //!
  TBranch        *b_pim2_isringtrack;   //!
  TBranch        *b_pim2_kIsLepton;   //!
  TBranch        *b_pim2_kIsUsed;   //!
  TBranch        *b_pim2_mdcinnerchi2;   //!
  TBranch        *b_pim2_mdcouterchi2;   //!
  TBranch        *b_pim2_oa_hadr;   //!
  TBranch        *b_pim2_oa_lept;   //!
  TBranch        *b_pim2_p;   //!
  TBranch        *b_pim2_p_corr_em;   //!
  TBranch        *b_pim2_p_corr_ep;   //!
  TBranch        *b_pim2_p_corr_p;   //!
  TBranch        *b_pim2_p_corr_pim;   //!
  TBranch        *b_pim2_p_corr_pip;   //!
  TBranch        *b_pim2_phi;   //!
  TBranch        *b_pim2_phi_rich;   //!
  TBranch        *b_pim2_pid;   //!
  TBranch        *b_pim2_q;   //!
  TBranch        *b_pim2_r;   //!
  TBranch        *b_pim2_resolution;   //!
  TBranch        *b_pim2_resoultion;   //!
  TBranch        *b_pim2_rich_amp;   //!
  TBranch        *b_pim2_rich_centr;   //!
  TBranch        *b_pim2_rich_houtra;   //!
  TBranch        *b_pim2_rich_padnum;   //!
  TBranch        *b_pim2_rich_patmat;   //!
  TBranch        *b_pim2_rkchi2;   //!
  TBranch        *b_pim2_sector;   //!
  TBranch        *b_pim2_shw_sum0;   //!
  TBranch        *b_pim2_shw_sum1;   //!
  TBranch        *b_pim2_shw_sum2;   //!
  TBranch        *b_pim2_system;   //!
  TBranch        *b_pim2_theta;   //!
  TBranch        *b_pim2_theta_rich;   //!
  TBranch        *b_pim2_tof_mom;   //!
  TBranch        *b_pim2_tof_new;   //!
  TBranch        *b_pim2_tof_rec;   //!
  TBranch        *b_pim2_track_length;   //!
  TBranch        *b_pim2_tracklength;   //!
  TBranch        *b_pim2_z;   //!
  TBranch        *b_pip_beta;   //!
  TBranch        *b_pip_beta_new;   //!
  TBranch        *b_pip_btChargeRing;   //!
  TBranch        *b_pip_btChargeSum;   //!
  TBranch        *b_pip_btChi2;   //!
  TBranch        *b_pip_btClusters;   //!
  TBranch        *b_pip_btMaxima;   //!
  TBranch        *b_pip_btMaximaCharge;   //!
  TBranch        *b_pip_btMaximaChargeShared;   //!
  TBranch        *b_pip_btMaximaChargeSharedFragment;   //!
  TBranch        *b_pip_btMaximaShared;   //!
  TBranch        *b_pip_btMaximaSharedFragment;   //!
  TBranch        *b_pip_btMeanDist;   //!
  TBranch        *b_pip_btNearbyMaxima;   //!
  TBranch        *b_pip_btNearbyMaximaShared;   //!
  TBranch        *b_pip_btPadsClus;   //!
  TBranch        *b_pip_btPadsRing;   //!
  TBranch        *b_pip_btRingMatrix;   //!
  TBranch        *b_pip_dedx_mdc;   //!
  TBranch        *b_pip_dedx_tof;   //!
  TBranch        *b_pip_id;   //!
  TBranch        *b_pip_isBT;   //!
  TBranch        *b_pip_isOffVertexClust;   //!
  TBranch        *b_pip_isPrimaryVertex;   //!
  TBranch        *b_pip_isUsedVertex;   //!
  TBranch        *b_pip_isring;   //!
  TBranch        *b_pip_isringmdc;   //!
  TBranch        *b_pip_isringnomatch;   //!
  TBranch        *b_pip_isringtrack;   //!
  TBranch        *b_pip_kIsLepton;   //!
  TBranch        *b_pip_kIsUsed;   //!
  TBranch        *b_pip_mdcinnerchi2;   //!
  TBranch        *b_pip_mdcouterchi2;   //!
  TBranch        *b_pip_oa_hadr;   //!
  TBranch        *b_pip_oa_lept;   //!
  TBranch        *b_pip_p;   //!
  TBranch        *b_pip_p_corr_em;   //!
  TBranch        *b_pip_p_corr_ep;   //!
  TBranch        *b_pip_p_corr_p;   //!
  TBranch        *b_pip_p_corr_pim;   //!
  TBranch        *b_pip_p_corr_pip;   //!
  TBranch        *b_pip_phi;   //!
  TBranch        *b_pip_phi_rich;   //!
  TBranch        *b_pip_pid;   //!
  TBranch        *b_pip_q;   //!
  TBranch        *b_pip_r;   //!
  TBranch        *b_pip_resolution;   //!
  TBranch        *b_pip_resoultion;   //!
  TBranch        *b_pip_rich_amp;   //!
  TBranch        *b_pip_rich_centr;   //!
  TBranch        *b_pip_rich_houtra;   //!
  TBranch        *b_pip_rich_padnum;   //!
  TBranch        *b_pip_rich_patmat;   //!
  TBranch        *b_pip_rkchi2;   //!
  TBranch        *b_pip_sector;   //!
  TBranch        *b_pip_shw_sum0;   //!
  TBranch        *b_pip_shw_sum1;   //!
  TBranch        *b_pip_shw_sum2;   //!
  TBranch        *b_pip_system;   //!
  TBranch        *b_pip_theta;   //!
  TBranch        *b_pip_theta_rich;   //!
  TBranch        *b_pip_tof_mom;   //!
  TBranch        *b_pip_tof_new;   //!
  TBranch        *b_pip_tof_rec;   //!
  TBranch        *b_pip_track_length;   //!
  TBranch        *b_pip_tracklength;   //!
  TBranch        *b_pip_z;   //!
  TBranch        *b_runnumber;   //!
  TBranch        *b_totalmult;   //!
  TBranch        *b_trigbit;   //!
  TBranch        *b_trigdec;   //!
  TBranch        *b_trigdownscale;   //!
  TBranch        *b_trigdownscaleflag;   //!
  
  PPimPipPim(TTree *tree=0);
  virtual ~PPimPipPim();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
};

#endif

