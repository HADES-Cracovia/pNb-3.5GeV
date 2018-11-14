#ifndef PPimEmEm_h
#define PPimEmEm_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class PPimEmEm {

public :

  float em1_acc, em1_acc_err, em2_acc, em2_acc_err;
  float em1_eff, em1_eff_err, em2_eff, em2_eff_err;

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
  Float_t         em1_beta;
  Float_t         em1_beta_new;
  Float_t         em1_btChargeRing;
  Float_t         em1_btChargeSum;
  Float_t         em1_btChi2;
  Float_t         em1_btClusters;
  Float_t         em1_btMaxima;
  Float_t         em1_btMaximaCharge;
  Float_t         em1_btMaximaChargeShared;
  Float_t         em1_btMaximaChargeSharedFragment;
  Float_t         em1_btMaximaShared;
  Float_t         em1_btMaximaSharedFragment;
  Float_t         em1_btMeanDist;
  Float_t         em1_btNearbyMaxima;
  Float_t         em1_btNearbyMaximaShared;
  Float_t         em1_btPadsClus;
  Float_t         em1_btPadsRing;
  Float_t         em1_btRingMatrix;
  Float_t         em1_dedx_mdc;
  Float_t         em1_dedx_tof;
  Float_t         em1_id;
  Float_t         em1_isOffVertexClust;
  Float_t         em1_isPrimaryVertex;
  Float_t         em1_isUsedVertex;
  Float_t         em1_isring;
  Float_t         em1_isBT;
  Float_t         em1_isringmdc;
  Float_t         em1_isringnomatch;
  Float_t         em1_isringtrack;
  Float_t         em1_kIsLepton;
  Float_t         em1_kIsUsed;
  Float_t         em1_mdcinnerchi2;
  Float_t         em1_mdcouterchi2;
  Float_t         em1_oa_hadr;
  Float_t         em1_oa_lept;
  Float_t         em1_p;
  Float_t         em1_p_corr_em;
  Float_t         em1_p_corr_ep;
  Float_t         em1_p_corr_p;
  Float_t         em1_p_corr_pim;
  Float_t         em1_p_corr_pip;
  Float_t         em1_phi;
  Float_t         em1_phi_rich;
  Float_t         em1_pid;
  Float_t         em1_q;
  Float_t         em1_r;
  Float_t         em1_resolution;
  Float_t         em1_resoultion;
  Float_t         em1_rich_amp;
  Float_t         em1_rich_centr;
  Float_t         em1_rich_houtra;
  Float_t         em1_rich_padnum;
  Float_t         em1_rich_patmat;
  Float_t         em1_rkchi2;
  Float_t         em1_sector;
  Float_t         em1_shw_sum0;
  Float_t         em1_shw_sum1;
  Float_t         em1_shw_sum2;
  Float_t         em1_system;
  Float_t         em1_theta;
  Float_t         em1_theta_rich;
  Float_t         em1_tof_mom;
  Float_t         em1_tof_new;
  Float_t         em1_tof_rec;
  Float_t         em1_track_length;
  Float_t         em1_tracklength;
  Float_t         em1_z;
  Float_t         em2_beta;
  Float_t         em2_beta_new;
  Float_t         em2_btChargeRing;
  Float_t         em2_btChargeSum;
  Float_t         em2_btChi2;
  Float_t         em2_btClusters;
  Float_t         em2_btMaxima;
  Float_t         em2_btMaximaCharge;
  Float_t         em2_btMaximaChargeShared;
  Float_t         em2_btMaximaChargeSharedFragment;
  Float_t         em2_btMaximaShared;
  Float_t         em2_btMaximaSharedFragment;
  Float_t         em2_btMeanDist;
  Float_t         em2_btNearbyMaxima;
  Float_t         em2_btNearbyMaximaShared;
  Float_t         em2_btPadsClus;
  Float_t         em2_btPadsRing;
  Float_t         em2_btRingMatrix;
  Float_t         em2_dedx_mdc;
  Float_t         em2_dedx_tof;
  Float_t         em2_id;
  Float_t         em2_isBT;
  Float_t         em2_isOffVertexClust;
  Float_t         em2_isPrimaryVertex;
  Float_t         em2_isUsedVertex;
  Float_t         em2_isring;
  Float_t         em2_isringmdc;
  Float_t         em2_isringnomatch;
  Float_t         em2_isringtrack;
  Float_t         em2_kIsLepton;
  Float_t         em2_kIsUsed;
  Float_t         em2_mdcinnerchi2;
  Float_t         em2_mdcouterchi2;
  Float_t         em2_oa_hadr;
  Float_t         em2_oa_lept;
  Float_t         em2_p;
  Float_t         em2_p_corr_em;
  Float_t         em2_p_corr_ep;
  Float_t         em2_p_corr_p;
  Float_t         em2_p_corr_pim;
  Float_t         em2_p_corr_pip;
  Float_t         em2_phi;
  Float_t         em2_phi_rich;
  Float_t         em2_pid;
  Float_t         em2_q;
  Float_t         em2_r;
  Float_t         em2_resolution;
  Float_t         em2_resoultion;
  Float_t         em2_rich_amp;
  Float_t         em2_rich_centr;
  Float_t         em2_rich_houtra;
  Float_t         em2_rich_padnum;
  Float_t         em2_rich_patmat;
  Float_t         em2_rkchi2;
  Float_t         em2_sector;
  Float_t         em2_shw_sum0;
  Float_t         em2_shw_sum1;
  Float_t         em2_shw_sum2;
  Float_t         em2_system;
  Float_t         em2_theta;
  Float_t         em2_theta_rich;
  Float_t         em2_tof_mom;
  Float_t         em2_tof_new;
  Float_t         em2_tof_rec;
  Float_t         em2_track_length;
  Float_t         em2_tracklength;
  Float_t         em2_z;
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
  Float_t         evtFlashMDC;
  Float_t         evtGood;
  Float_t         evtGoodTrig;
  Float_t         evtLepMult;
  Float_t         evtMDCMult;
  Float_t         evtPileupMDC;
  Float_t         evtPileupMeta;
  Float_t         evtPileupStart;
  Float_t         evtStart;
  Float_t         evtVertCand;
  Float_t         evtVertClust;
  Float_t         fw_beta_1;
  Float_t         fw_beta_2;
  Float_t         fw_beta_3;
  Float_t         fw_charge_1;
  Float_t         fw_charge_2;
  Float_t         fw_charge_3;
  Float_t         fw_cluster_mult;
  Float_t         fw_distance_1;
  Float_t         fw_distance_2;
  Float_t         fw_distance_3;
  Float_t         fw_mult;
  Float_t         fw_p_1;
  Float_t         fw_p_2;
  Float_t         fw_p_3;
  Float_t         fw_phi_1;
  Float_t         fw_phi_2;
  Float_t         fw_phi_3;
  Float_t         fw_size_1;
  Float_t         fw_size_2;
  Float_t         fw_size_3;
  Float_t         fw_spectator_1;
  Float_t         fw_spectator_2;
  Float_t         fw_spectator_3;
  Float_t         fw_theta_1;
  Float_t         fw_theta_2;
  Float_t         fw_theta_3;
  Float_t         fw_time_1;
  Float_t         fw_time_2;
  Float_t         fw_time_3;
  Float_t         fw_time_min_1;
  Float_t         fw_time_min_2;
  Float_t         fw_time_min_3;
  Float_t         fw_x_lab_1;
  Float_t         fw_x_lab_2;
  Float_t         fw_x_lab_3;
  Float_t         fw_y_lab_1;
  Float_t         fw_y_lab_2;
  Float_t         fw_y_lab_3;
  Float_t         fw_z_lab_1;
  Float_t         fw_z_lab_2;
  Float_t         fw_z_lab_3;
  Float_t         hneg_mult;
  Float_t         hpos_mult;
  Float_t         isBest;
  Float_t         lneg_mult;
  Float_t         lpos_mult;
  Float_t         pt_costh_1;
  Float_t         pt_costh_2;
  Float_t         pt_costh_3;
  Float_t         pt_costh_4;
  Float_t         pt_counter;
  Float_t         pt_match_1;
  Float_t         pt_match_2;
  Float_t         pt_match_3;
  Float_t         pt_match_4;
  Float_t         pt_mult;
  Float_t         pt_p_1;
  Float_t         pt_p_2;
  Float_t         pt_p_3;
  Float_t         pt_p_4;
  Float_t         pt_phi0_1;
  Float_t         pt_phi0_2;
  Float_t         pt_phi0_3;
  Float_t         pt_phi0_4;
  Float_t         pt_phi_1;
  Float_t         pt_phi_2;
  Float_t         pt_phi_3;
  Float_t         pt_phi_4;
  Float_t         pt_px_1;
  Float_t         pt_px_2;
  Float_t         pt_px_3;
  Float_t         pt_px_4;
  Float_t         pt_py_1;
  Float_t         pt_py_2;
  Float_t         pt_py_3;
  Float_t         pt_py_4;
  Float_t         pt_pz_1;
  Float_t         pt_pz_2;
  Float_t         pt_pz_3;
  Float_t         pt_pz_4;
  Float_t         pt_theta0_1;
  Float_t         pt_theta0_2;
  Float_t         pt_theta0_3;
  Float_t         pt_theta0_4;
  Float_t         pt_theta_1;
  Float_t         pt_theta_2;
  Float_t         pt_theta_3;
  Float_t         pt_theta_4;
  Float_t         pt_x1_1;
  Float_t         pt_x1_2;
  Float_t         pt_x1_3;
  Float_t         pt_x1_4;
  Float_t         pt_x2_1;
  Float_t         pt_x2_2;
  Float_t         pt_x2_3;
  Float_t         pt_x2_4;
  Float_t         pt_xtarg_1;
  Float_t         pt_xtarg_2;
  Float_t         pt_xtarg_3;
  Float_t         pt_xtarg_4;
  Float_t         pt_y1_1;
  Float_t         pt_y1_2;
  Float_t         pt_y1_3;
  Float_t         pt_y1_4;
  Float_t         pt_y2_1;
  Float_t         pt_y2_2;
  Float_t         pt_y2_3;
  Float_t         pt_y2_4;
  Float_t         pt_ytarg_1;
  Float_t         pt_ytarg_2;
  Float_t         pt_ytarg_3;
  Float_t         pt_ytarg_4;
  Float_t         runnumber;
  Float_t         start_cluster_size_1st;
  Float_t         start_cluster_size_2nd;
  Float_t         start_cluster_size_max;
  Float_t         start_corrflag;
  Float_t         start_counter;
  Float_t         start_flag;
  Float_t         start_module;
  Float_t         start_mult;
  Float_t         start_multipliticy;
  Float_t         start_resolution;
  Float_t         start_strip;
  Float_t         start_time;
  Float_t         start_time_2nd;
  Float_t         start_track;
  Float_t         start_width;
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
  TBranch        *b_em1_beta;   //!
  TBranch        *b_em1_beta_new;   //!
  TBranch        *b_em1_btChargeRing;   //!
  TBranch        *b_em1_btChargeSum;   //!
  TBranch        *b_em1_btChi2;   //!
  TBranch        *b_em1_btClusters;   //!
  TBranch        *b_em1_btMaxima;   //!
  TBranch        *b_em1_btMaximaCharge;   //!
  TBranch        *b_em1_btMaximaChargeShared;   //!
  TBranch        *b_em1_btMaximaChargeSharedFragment;   //!
  TBranch        *b_em1_btMaximaShared;   //!
  TBranch        *b_em1_btMaximaSharedFragment;   //!
  TBranch        *b_em1_btMeanDist;   //!
  TBranch        *b_em1_btNearbyMaxima;   //!
  TBranch        *b_em1_btNearbyMaximaShared;   //!
  TBranch        *b_em1_btPadsClus;   //!
  TBranch        *b_em1_btPadsRing;   //!
  TBranch        *b_em1_btRingMatrix;   //!
  TBranch        *b_em1_dedx_mdc;   //!
  TBranch        *b_em1_dedx_tof;   //!
  TBranch        *b_em1_id;   //!
  TBranch        *b_em1_isBT; //!
  TBranch        *b_em1_isOffVertexClust;   //!
  TBranch        *b_em1_isPrimaryVertex;   //!
  TBranch        *b_em1_isUsedVertex;   //!
  TBranch        *b_em1_isring;   //!
  TBranch        *b_em1_isringmdc;   //!
  TBranch        *b_em1_isringnomatch;   //!
  TBranch        *b_em1_isringtrack;   //!
  TBranch        *b_em1_kIsLepton;   //!
  TBranch        *b_em1_kIsUsed;   //!
  TBranch        *b_em1_mdcinnerchi2;   //!
  TBranch        *b_em1_mdcouterchi2;   //!
  TBranch        *b_em1_oa_hadr;   //!
  TBranch        *b_em1_oa_lept;   //!
  TBranch        *b_em1_p;   //!
  TBranch        *b_em1_p_corr_em;   //!
  TBranch        *b_em1_p_corr_ep;   //!
  TBranch        *b_em1_p_corr_p;   //!
  TBranch        *b_em1_p_corr_pim;   //!
  TBranch        *b_em1_p_corr_pip;   //!
  TBranch        *b_em1_phi;   //!
  TBranch        *b_em1_phi_rich;   //!
  TBranch        *b_em1_pid;   //!
  TBranch        *b_em1_q;   //!
  TBranch        *b_em1_r;   //!
  TBranch        *b_em1_resolution;   //!
  TBranch        *b_em1_resoultion;   //!
  TBranch        *b_em1_rich_amp;   //!
  TBranch        *b_em1_rich_centr;   //!
  TBranch        *b_em1_rich_houtra;   //!
  TBranch        *b_em1_rich_padnum;   //!
  TBranch        *b_em1_rich_patmat;   //!
  TBranch        *b_em1_rkchi2;   //!
  TBranch        *b_em1_sector;   //!
  TBranch        *b_em1_shw_sum0;   //!
  TBranch        *b_em1_shw_sum1;   //!
  TBranch        *b_em1_shw_sum2;   //!
  TBranch        *b_em1_system;   //!
  TBranch        *b_em1_theta;   //!
  TBranch        *b_em1_theta_rich;   //!
  TBranch        *b_em1_tof_mom;   //!
  TBranch        *b_em1_tof_new;   //!
  TBranch        *b_em1_tof_rec;   //!
  TBranch        *b_em1_track_length;   //!
  TBranch        *b_em1_tracklength;   //!
  TBranch        *b_em1_z;   //!
  TBranch        *b_em2_beta;   //!
  TBranch        *b_em2_beta_new;   //!
  TBranch        *b_em2_btChargeRing;   //!
  TBranch        *b_em2_btChargeSum;   //!
  TBranch        *b_em2_btChi2;   //!
  TBranch        *b_em2_btClusters;   //!
  TBranch        *b_em2_btMaxima;   //!
  TBranch        *b_em2_btMaximaCharge;   //!
  TBranch        *b_em2_btMaximaChargeShared;   //!
  TBranch        *b_em2_btMaximaChargeSharedFragment;   //!
  TBranch        *b_em2_btMaximaShared;   //!
  TBranch        *b_em2_btMaximaSharedFragment;   //!
  TBranch        *b_em2_btMeanDist;   //!
  TBranch        *b_em2_btNearbyMaxima;   //!
  TBranch        *b_em2_btNearbyMaximaShared;   //!
  TBranch        *b_em2_btPadsClus;   //!
  TBranch        *b_em2_btPadsRing;   //!
  TBranch        *b_em2_btRingMatrix;   //!
  TBranch        *b_em2_dedx_mdc;   //!
  TBranch        *b_em2_dedx_tof;   //!
  TBranch        *b_em2_id;   //!
  TBranch        *b_em2_isBT; //!
  TBranch        *b_em2_isOffVertexClust;   //!
  TBranch        *b_em2_isPrimaryVertex;   //!
  TBranch        *b_em2_isUsedVertex;   //!
  TBranch        *b_em2_isring;   //!
  TBranch        *b_em2_isringmdc;   //!
  TBranch        *b_em2_isringnomatch;   //!
  TBranch        *b_em2_isringtrack;   //!
  TBranch        *b_em2_kIsLepton;   //!
  TBranch        *b_em2_kIsUsed;   //!
  TBranch        *b_em2_mdcinnerchi2;   //!
  TBranch        *b_em2_mdcouterchi2;   //!
  TBranch        *b_em2_oa_hadr;   //!
  TBranch        *b_em2_oa_lept;   //!
  TBranch        *b_em2_p;   //!
  TBranch        *b_em2_p_corr_em;   //!
  TBranch        *b_em2_p_corr_ep;   //!
  TBranch        *b_em2_p_corr_p;   //!
  TBranch        *b_em2_p_corr_pim;   //!
  TBranch        *b_em2_p_corr_pip;   //!
  TBranch        *b_em2_phi;   //!
  TBranch        *b_em2_phi_rich;   //!
  TBranch        *b_em2_pid;   //!
  TBranch        *b_em2_q;   //!
  TBranch        *b_em2_r;   //!
  TBranch        *b_em2_resolution;   //!
  TBranch        *b_em2_resoultion;   //!
  TBranch        *b_em2_rich_amp;   //!
  TBranch        *b_em2_rich_centr;   //!
  TBranch        *b_em2_rich_houtra;   //!
  TBranch        *b_em2_rich_padnum;   //!
  TBranch        *b_em2_rich_patmat;   //!
  TBranch        *b_em2_rkchi2;   //!
  TBranch        *b_em2_sector;   //!
  TBranch        *b_em2_shw_sum0;   //!
  TBranch        *b_em2_shw_sum1;   //!
  TBranch        *b_em2_shw_sum2;   //!
  TBranch        *b_em2_system;   //!
  TBranch        *b_em2_theta;   //!
  TBranch        *b_em2_theta_rich;   //!
  TBranch        *b_em2_tof_mom;   //!
  TBranch        *b_em2_tof_new;   //!
  TBranch        *b_em2_tof_rec;   //!
  TBranch        *b_em2_track_length;   //!
  TBranch        *b_em2_tracklength;   //!
  TBranch        *b_em2_z;   //!
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
  TBranch        *b_evtFlashMDC;   //!
  TBranch        *b_evtGood;   //!
  TBranch        *b_evtGoodTrig;   //!
  TBranch        *b_evtLepMult;   //!
  TBranch        *b_evtMDCMult;   //!
  TBranch        *b_evtPileupMDC;   //!
  TBranch        *b_evtPileupMeta;   //!
  TBranch        *b_evtPileupStart;   //!
  TBranch        *b_evtStart;   //!
  TBranch        *b_evtVertCand;   //!
  TBranch        *b_evtVertClust;   //!
  TBranch        *b_fw_beta_1;   //!
  TBranch        *b_fw_beta_2;   //!
  TBranch        *b_fw_beta_3;   //!
  TBranch        *b_fw_charge_1;   //!
  TBranch        *b_fw_charge_2;   //!
  TBranch        *b_fw_charge_3;   //!
  TBranch        *b_fw_cluster_mult;   //!
  TBranch        *b_fw_distance_1;   //!
  TBranch        *b_fw_distance_2;   //!
  TBranch        *b_fw_distance_3;   //!
  TBranch        *b_fw_mult;   //!
  TBranch        *b_fw_p_1;   //!
  TBranch        *b_fw_p_2;   //!
  TBranch        *b_fw_p_3;   //!
  TBranch        *b_fw_phi_1;   //!
  TBranch        *b_fw_phi_2;   //!
  TBranch        *b_fw_phi_3;   //!
  TBranch        *b_fw_size_1;   //!
  TBranch        *b_fw_size_2;   //!
  TBranch        *b_fw_size_3;   //!
  TBranch        *b_fw_spectator_1;   //!
  TBranch        *b_fw_spectator_2;   //!
  TBranch        *b_fw_spectator_3;   //!
  TBranch        *b_fw_theta_1;   //!
  TBranch        *b_fw_theta_2;   //!
  TBranch        *b_fw_theta_3;   //!
  TBranch        *b_fw_time_1;   //!
  TBranch        *b_fw_time_2;   //!
  TBranch        *b_fw_time_3;   //!
  TBranch        *b_fw_time_min_1;   //!
  TBranch        *b_fw_time_min_2;   //!
  TBranch        *b_fw_time_min_3;   //!
  TBranch        *b_fw_x_lab_1;   //!
  TBranch        *b_fw_x_lab_2;   //!
  TBranch        *b_fw_x_lab_3;   //!
  TBranch        *b_fw_y_lab_1;   //!
  TBranch        *b_fw_y_lab_2;   //!
  TBranch        *b_fw_y_lab_3;   //!
  TBranch        *b_fw_z_lab_1;   //!
  TBranch        *b_fw_z_lab_2;   //!
  TBranch        *b_fw_z_lab_3;   //!
  TBranch        *b_hneg_mult;   //!
  TBranch        *b_hpos_mult;   //!
  TBranch        *b_isBest;   //!
  TBranch        *b_lneg_mult;   //!
  TBranch        *b_lpos_mult;   //!
  TBranch        *b_pt_costh_1;   //!
  TBranch        *b_pt_costh_2;   //!
  TBranch        *b_pt_costh_3;   //!
  TBranch        *b_pt_costh_4;   //!
  TBranch        *b_pt_counter;   //!
  TBranch        *b_pt_match_1;   //!
  TBranch        *b_pt_match_2;   //!
  TBranch        *b_pt_match_3;   //!
  TBranch        *b_pt_match_4;   //!
  TBranch        *b_pt_mult;   //!
  TBranch        *b_pt_p_1;   //!
  TBranch        *b_pt_p_2;   //!
  TBranch        *b_pt_p_3;   //!
  TBranch        *b_pt_p_4;   //!
  TBranch        *b_pt_phi0_1;   //!
  TBranch        *b_pt_phi0_2;   //!
  TBranch        *b_pt_phi0_3;   //!
  TBranch        *b_pt_phi0_4;   //!
  TBranch        *b_pt_phi_1;   //!
  TBranch        *b_pt_phi_2;   //!
  TBranch        *b_pt_phi_3;   //!
  TBranch        *b_pt_phi_4;   //!
  TBranch        *b_pt_px_1;   //!
  TBranch        *b_pt_px_2;   //!
  TBranch        *b_pt_px_3;   //!
  TBranch        *b_pt_px_4;   //!
  TBranch        *b_pt_py_1;   //!
  TBranch        *b_pt_py_2;   //!
  TBranch        *b_pt_py_3;   //!
  TBranch        *b_pt_py_4;   //!
  TBranch        *b_pt_pz_1;   //!
  TBranch        *b_pt_pz_2;   //!
  TBranch        *b_pt_pz_3;   //!
  TBranch        *b_pt_pz_4;   //!
  TBranch        *b_pt_theta0_1;   //!
  TBranch        *b_pt_theta0_2;   //!
  TBranch        *b_pt_theta0_3;   //!
  TBranch        *b_pt_theta0_4;   //!
  TBranch        *b_pt_theta_1;   //!
  TBranch        *b_pt_theta_2;   //!
  TBranch        *b_pt_theta_3;   //!
  TBranch        *b_pt_theta_4;   //!
  TBranch        *b_pt_x1_1;   //!
  TBranch        *b_pt_x1_2;   //!
  TBranch        *b_pt_x1_3;   //!
  TBranch        *b_pt_x1_4;   //!
  TBranch        *b_pt_x2_1;   //!
  TBranch        *b_pt_x2_2;   //!
  TBranch        *b_pt_x2_3;   //!
  TBranch        *b_pt_x2_4;   //!
  TBranch        *b_pt_xtarg_1;   //!
  TBranch        *b_pt_xtarg_2;   //!
  TBranch        *b_pt_xtarg_3;   //!
  TBranch        *b_pt_xtarg_4;   //!
  TBranch        *b_pt_y1_1;   //!
  TBranch        *b_pt_y1_2;   //!
  TBranch        *b_pt_y1_3;   //!
  TBranch        *b_pt_y1_4;   //!
  TBranch        *b_pt_y2_1;   //!
  TBranch        *b_pt_y2_2;   //!
  TBranch        *b_pt_y2_3;   //!
  TBranch        *b_pt_y2_4;   //!
  TBranch        *b_pt_ytarg_1;   //!
  TBranch        *b_pt_ytarg_2;   //!
  TBranch        *b_pt_ytarg_3;   //!
  TBranch        *b_pt_ytarg_4;   //!
  TBranch        *b_runnumber;   //!
  TBranch        *b_start_cluster_size_1st;   //!
  TBranch        *b_start_cluster_size_2nd;   //!
  TBranch        *b_start_cluster_size_max;   //!
  TBranch        *b_start_corrflag;   //!
  TBranch        *b_start_counter;   //!
  TBranch        *b_start_flag;   //!
  TBranch        *b_start_module;   //!
  TBranch        *b_start_mult;   //!
  TBranch        *b_start_multipliticy;   //!
  TBranch        *b_start_resolution;   //!
  TBranch        *b_start_strip;   //!
  TBranch        *b_start_time;   //!
  TBranch        *b_start_time_2nd;   //!
  TBranch        *b_start_track;   //!
  TBranch        *b_start_width;   //!
  TBranch        *b_totalmult;   //!
  TBranch        *b_trigbit;   //!
  TBranch        *b_trigdec;   //!
  TBranch        *b_trigdownscale;   //!
  TBranch        *b_trigdownscaleflag;   //!

  PPimEmEm(TTree *tree=0);
  virtual ~PPimEmEm();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
};

#endif


