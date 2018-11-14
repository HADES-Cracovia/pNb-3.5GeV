#ifndef PPimEpEm_h
#define PPimEpEm_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

using namespace std;

/*********************************************************************************************/
class PPimEpEm {

public :

  float em_acc, em_acc_err, ep_acc, ep_acc_err;
  float em_eff, em_eff_err, ep_eff, ep_eff_err;

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
  Float_t         em_beta;
  Float_t         em_beta_new;
  Float_t         em_btChargeRing;
  Float_t         em_btChargeSum;
  Float_t         em_btChi2;
  Float_t         em_btClusters;
  Float_t         em_btMaxima;
  Float_t         em_btMaximaCharge;
  Float_t         em_btMaximaChargeShared;
  Float_t         em_btMaximaChargeSharedFragment;
  Float_t         em_btMaximaShared;
  Float_t         em_btMaximaSharedFragment;
  Float_t         em_btMeanDist;
  Float_t         em_btNearbyMaxima;
  Float_t         em_btNearbyMaximaShared;
  Float_t         em_btPadsClus;
  Float_t         em_btPadsRing;
  Float_t         em_btRingMatrix;
  Float_t         em_dedx_mdc;
  Float_t         em_dedx_tof;
  Float_t         em_id;
  Float_t         em_isBT;
  Float_t         em_isOffVertexClust;
  Float_t         em_isPrimaryVertex;
  Float_t         em_isUsedVertex;
  Float_t         em_isring;
  Float_t         em_isringmdc;
  Float_t         em_isringnomatch;
  Float_t         em_isringtrack;
  Float_t         em_kIsLepton;
  Float_t         em_kIsUsed;
  Float_t         em_mdcinnerchi2;
  Float_t         em_mdcouterchi2;
  Float_t         em_oa_hadr;
  Float_t         em_oa_lept;
  Float_t         em_p;
  Float_t         em_p_corr_em;
  Float_t         em_p_corr_ep;
  Float_t         em_p_corr_p;
  Float_t         em_p_corr_pim;
  Float_t         em_p_corr_pip;
  Float_t         em_phi;
  Float_t         em_phi_rich;
  Float_t         em_pid;
  Float_t         em_q;
  Float_t         em_r;
  Float_t         em_resolution;
  Float_t         em_resoultion;
  Float_t         em_rich_amp;
  Float_t         em_rich_centr;
  Float_t         em_rich_houtra;
  Float_t         em_rich_padnum;
  Float_t         em_rich_patmat;
  Float_t         em_rkchi2;
  Float_t         em_sector;
  Float_t         em_shw_sum0;
  Float_t         em_shw_sum1;
  Float_t         em_shw_sum2;
  Float_t         em_system;
  Float_t         em_theta;
  Float_t         em_theta_rich;
  Float_t         em_tof_mom;
  Float_t         em_tof_new;
  Float_t         em_tof_rec;
  Float_t         em_track_length;
  Float_t         em_tracklength;
  Float_t         em_z;
  Float_t         ep_beta;
  Float_t         ep_beta_new;
  Float_t         ep_btChargeRing;
  Float_t         ep_btChargeSum;
  Float_t         ep_btChi2;
  Float_t         ep_btClusters;
  Float_t         ep_btMaxima;
  Float_t         ep_btMaximaCharge;
  Float_t         ep_btMaximaChargeShared;
  Float_t         ep_btMaximaChargeSharedFragment;
  Float_t         ep_btMaximaShared;
  Float_t         ep_btMaximaSharedFragment;
  Float_t         ep_btMeanDist;
  Float_t         ep_btNearbyMaxima;
  Float_t         ep_btNearbyMaximaShared;
  Float_t         ep_btPadsClus;
  Float_t         ep_btPadsRing;
  Float_t         ep_btRingMatrix;
  Float_t         ep_dedx_mdc;
  Float_t         ep_dedx_tof;
  Float_t         ep_id;
  Float_t         ep_isBT;
  Float_t         ep_isOffVertexClust;
  Float_t         ep_isPrimaryVertex;
  Float_t         ep_isUsedVertex;
  Float_t         ep_isring;
  Float_t         ep_isringmdc;
  Float_t         ep_isringnomatch;
  Float_t         ep_isringtrack;
  Float_t         ep_kIsLepton;
  Float_t         ep_kIsUsed;
  Float_t         ep_mdcinnerchi2;
  Float_t         ep_mdcouterchi2;
  Float_t         ep_oa_hadr;
  Float_t         ep_oa_lept;
  Float_t         ep_p;
  Float_t         ep_p_corr_em;
  Float_t         ep_p_corr_ep;
  Float_t         ep_p_corr_p;
  Float_t         ep_p_corr_pim;
  Float_t         ep_p_corr_pip;
  Float_t         ep_phi;
  Float_t         ep_phi_rich;
  Float_t         ep_pid;
  Float_t         ep_q;
  Float_t         ep_r;
  Float_t         ep_resolution;
  Float_t         ep_resoultion;
  Float_t         ep_rich_amp;
  Float_t         ep_rich_centr;
  Float_t         ep_rich_houtra;
  Float_t         ep_rich_padnum;
  Float_t         ep_rich_patmat;
  Float_t         ep_rkchi2;
  Float_t         ep_sector;
  Float_t         ep_shw_sum0;
  Float_t         ep_shw_sum1;
  Float_t         ep_shw_sum2;
  Float_t         ep_system;
  Float_t         ep_theta;
  Float_t         ep_theta_rich;
  Float_t         ep_tof_mom;
  Float_t         ep_tof_new;
  Float_t         ep_tof_rec;
  Float_t         ep_track_length;
  Float_t         ep_tracklength;
  Float_t         ep_z;
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
  Float_t         event;
  Float_t         hneg_mult;
  Float_t         hpos_mult;
  Float_t         isBest;
  Float_t         lneg_mult;
  Float_t         lpos_mult;
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
  TBranch        *b_em_beta;   //!
  TBranch        *b_em_beta_new;   //!
  TBranch        *b_em_btChargeRing;   //!
  TBranch        *b_em_btChargeSum;   //!
  TBranch        *b_em_btChi2;   //!
  TBranch        *b_em_btClusters;   //!
  TBranch        *b_em_btMaxima;   //!
  TBranch        *b_em_btMaximaCharge;   //!
  TBranch        *b_em_btMaximaChargeShared;   //!
  TBranch        *b_em_btMaximaChargeSharedFragment;   //!
  TBranch        *b_em_btMaximaShared;   //!
  TBranch        *b_em_btMaximaSharedFragment;   //!
  TBranch        *b_em_btMeanDist;   //!
  TBranch        *b_em_btNearbyMaxima;   //!
  TBranch        *b_em_btNearbyMaximaShared;   //!
  TBranch        *b_em_btPadsClus;   //!
  TBranch        *b_em_btPadsRing;   //!
  TBranch        *b_em_btRingMatrix;   //!
  TBranch        *b_em_dedx_mdc;   //!
  TBranch        *b_em_dedx_tof;   //!
  TBranch        *b_em_id;   //!
  TBranch        *b_em_isBT;   //!
  TBranch        *b_em_isOffVertexClust;   //!
  TBranch        *b_em_isPrimaryVertex;   //!
  TBranch        *b_em_isUsedVertex;   //!
  TBranch        *b_em_isring;   //!
  TBranch        *b_em_isringmdc;   //!
  TBranch        *b_em_isringnomatch;   //!
  TBranch        *b_em_isringtrack;   //!
  TBranch        *b_em_kIsLepton;   //!
  TBranch        *b_em_kIsUsed;   //!
  TBranch        *b_em_mdcinnerchi2;   //!
  TBranch        *b_em_mdcouterchi2;   //!
  TBranch        *b_em_oa_hadr;   //!
  TBranch        *b_em_oa_lept;   //!
  TBranch        *b_em_p;   //!
  TBranch        *b_em_p_corr_em;   //!
  TBranch        *b_em_p_corr_ep;   //!
  TBranch        *b_em_p_corr_p;   //!
  TBranch        *b_em_p_corr_pim;   //!
  TBranch        *b_em_p_corr_pip;   //!
  TBranch        *b_em_phi;   //!
  TBranch        *b_em_phi_rich;   //!
  TBranch        *b_em_pid;   //!
  TBranch        *b_em_q;   //!
  TBranch        *b_em_r;   //!
  TBranch        *b_em_resolution;   //!
  TBranch        *b_em_resoultion;   //!
  TBranch        *b_em_rich_amp;   //!
  TBranch        *b_em_rich_centr;   //!
  TBranch        *b_em_rich_houtra;   //!
  TBranch        *b_em_rich_padnum;   //!
  TBranch        *b_em_rich_patmat;   //!
  TBranch        *b_em_rkchi2;   //!
  TBranch        *b_em_sector;   //!
  TBranch        *b_em_shw_sum0;   //!
  TBranch        *b_em_shw_sum1;   //!
  TBranch        *b_em_shw_sum2;   //!
  TBranch        *b_em_system;   //!
  TBranch        *b_em_theta;   //!
  TBranch        *b_em_theta_rich;   //!
  TBranch        *b_em_tof_mom;   //!
  TBranch        *b_em_tof_new;   //!
  TBranch        *b_em_tof_rec;   //!
  TBranch        *b_em_track_length;   //!
  TBranch        *b_em_tracklength;   //!
  TBranch        *b_em_z;   //!
  TBranch        *b_ep_beta;   //!
  TBranch        *b_ep_beta_new;   //!
  TBranch        *b_ep_btChargeRing;   //!
  TBranch        *b_ep_btChargeSum;   //!
  TBranch        *b_ep_btChi2;   //!
  TBranch        *b_ep_btClusters;   //!
  TBranch        *b_ep_btMaxima;   //!
  TBranch        *b_ep_btMaximaCharge;   //!
  TBranch        *b_ep_btMaximaChargeShared;   //!
  TBranch        *b_ep_btMaximaChargeSharedFragment;   //!
  TBranch        *b_ep_btMaximaShared;   //!
  TBranch        *b_ep_btMaximaSharedFragment;   //!
  TBranch        *b_ep_btMeanDist;   //!
  TBranch        *b_ep_btNearbyMaxima;   //!
  TBranch        *b_ep_btNearbyMaximaShared;   //!
  TBranch        *b_ep_btPadsClus;   //!
  TBranch        *b_ep_btPadsRing;   //!
  TBranch        *b_ep_btRingMatrix;   //!
  TBranch        *b_ep_dedx_mdc;   //!
  TBranch        *b_ep_dedx_tof;   //!
  TBranch        *b_ep_id;   //!
  TBranch        *b_ep_isBT;   //!
  TBranch        *b_ep_isOffVertexClust;   //!
  TBranch        *b_ep_isPrimaryVertex;   //!
  TBranch        *b_ep_isUsedVertex;   //!
  TBranch        *b_ep_isring;   //!
  TBranch        *b_ep_isringmdc;   //!
  TBranch        *b_ep_isringnomatch;   //!
  TBranch        *b_ep_isringtrack;   //!
  TBranch        *b_ep_kIsLepton;   //!
  TBranch        *b_ep_kIsUsed;   //!
  TBranch        *b_ep_mdcinnerchi2;   //!
  TBranch        *b_ep_mdcouterchi2;   //!
  TBranch        *b_ep_oa_hadr;   //!
  TBranch        *b_ep_oa_lept;   //!
  TBranch        *b_ep_p;   //!
  TBranch        *b_ep_p_corr_em;   //!
  TBranch        *b_ep_p_corr_ep;   //!
  TBranch        *b_ep_p_corr_p;   //!
  TBranch        *b_ep_p_corr_pim;   //!
  TBranch        *b_ep_p_corr_pip;   //!
  TBranch        *b_ep_phi;   //!
  TBranch        *b_ep_phi_rich;   //!
  TBranch        *b_ep_pid;   //!
  TBranch        *b_ep_q;   //!
  TBranch        *b_ep_r;   //!
  TBranch        *b_ep_resolution;   //!
  TBranch        *b_ep_resoultion;   //!
  TBranch        *b_ep_rich_amp;   //!
  TBranch        *b_ep_rich_centr;   //!
  TBranch        *b_ep_rich_houtra;   //!
  TBranch        *b_ep_rich_padnum;   //!
  TBranch        *b_ep_rich_patmat;   //!
  TBranch        *b_ep_rkchi2;   //!
  TBranch        *b_ep_sector;   //!
  TBranch        *b_ep_shw_sum0;   //!
  TBranch        *b_ep_shw_sum1;   //!
  TBranch        *b_ep_shw_sum2;   //!
  TBranch        *b_ep_system;   //!
  TBranch        *b_ep_theta;   //!
  TBranch        *b_ep_theta_rich;   //!
  TBranch        *b_ep_tof_mom;   //!
  TBranch        *b_ep_tof_new;   //!
  TBranch        *b_ep_tof_rec;   //!
  TBranch        *b_ep_track_length;   //!
  TBranch        *b_ep_tracklength;   //!
  TBranch        *b_ep_z;   //!
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
  TBranch        *b_event;   //!
  TBranch        *b_hneg_mult;   //!
  TBranch        *b_hpos_mult;   //!
  TBranch        *b_isBest;   //!
  TBranch        *b_lneg_mult;   //!
  TBranch        *b_lpos_mult;   //!
  TBranch        *b_runnumber;   //!
  TBranch        *b_totalmult;   //!
  TBranch        *b_trigbit;   //!
  TBranch        *b_trigdec;   //!
  TBranch        *b_trigdownscale;   //!
  TBranch        *b_trigdownscaleflag;   //!

  PPimEpEm(TTree *tree=0);
  virtual ~PPimEpEm();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
};

#endif

