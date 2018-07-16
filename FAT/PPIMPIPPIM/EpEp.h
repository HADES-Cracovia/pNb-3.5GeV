#ifndef EpEp_h
#define EpEp_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class EpEp {

public :

   float ep1_acc, ep1_acc_err, ep2_acc, ep2_acc_err;
   float ep1_eff, ep1_eff_err, ep2_eff, ep2_eff_err;

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
   Float_t         ep1_beta;
   Float_t         ep1_beta_new;
   Float_t         ep1_btChargeRing;
   Float_t         ep1_btChargeSum;
   Float_t         ep1_btChi2;
   Float_t         ep1_btClusters;
   Float_t         ep1_btMaxima;
   Float_t         ep1_btMaximaCharge;
   Float_t         ep1_btMaximaChargeShared;
   Float_t         ep1_btMaximaChargeSharedFragment;
   Float_t         ep1_btMaximaShared;
   Float_t         ep1_btMaximaSharedFragment;
   Float_t         ep1_btMeanDist;
   Float_t         ep1_btNearbyMaxima;
   Float_t         ep1_btNearbyMaximaShared;
   Float_t         ep1_btPadsClus;
   Float_t         ep1_btPadsRing;
   Float_t         ep1_btRingMatrix;
   Float_t         ep1_dedx_mdc;
   Float_t         ep1_dedx_tof;
   Float_t         ep1_id;
   Float_t         ep1_isBT;
   Float_t         ep1_isOffVertexClust;
   Float_t         ep1_isPrimaryVertex;
   Float_t         ep1_isUsedVertex;
   Float_t         ep1_isring;
   Float_t         ep1_isringmdc;
   Float_t         ep1_isringnomatch;
   Float_t         ep1_isringtrack;
   Float_t         ep1_kIsLepton;
   Float_t         ep1_kIsUsed;
   Float_t         ep1_mdcinnerchi2;
   Float_t         ep1_mdcouterchi2;
   Float_t         ep1_oa_hadr;
   Float_t         ep1_oa_lept;
   Float_t         ep1_p;
   Float_t         ep1_p_corr_em;
   Float_t         ep1_p_corr_ep;
   Float_t         ep1_p_corr_p;
   Float_t         ep1_p_corr_pim;
   Float_t         ep1_p_corr_pip;
   Float_t         ep1_phi;
   Float_t         ep1_phi_rich;
   Float_t         ep1_pid;
   Float_t         ep1_q;
   Float_t         ep1_r;
   Float_t         ep1_resolution;
   Float_t         ep1_resoultion;
   Float_t         ep1_rich_amp;
   Float_t         ep1_rich_centr;
   Float_t         ep1_rich_houtra;
   Float_t         ep1_rich_padnum;
   Float_t         ep1_rich_patmat;
   Float_t         ep1_rkchi2;
   Float_t         ep1_sector;
   Float_t         ep1_shw_sum0;
   Float_t         ep1_shw_sum1;
   Float_t         ep1_shw_sum2;
   Float_t         ep1_system;
   Float_t         ep1_theta;
   Float_t         ep1_theta_rich;
   Float_t         ep1_tof_mom;
   Float_t         ep1_tof_new;
   Float_t         ep1_tof_rec;
   Float_t         ep1_track_length;
   Float_t         ep1_tracklength;
   Float_t         ep1_z;
   Float_t         ep2_beta;
   Float_t         ep2_beta_new;
   Float_t         ep2_btChargeRing;
   Float_t         ep2_btChargeSum;
   Float_t         ep2_btChi2;
   Float_t         ep2_btClusters;
   Float_t         ep2_btMaxima;
   Float_t         ep2_btMaximaCharge;
   Float_t         ep2_btMaximaChargeShared;
   Float_t         ep2_btMaximaChargeSharedFragment;
   Float_t         ep2_btMaximaShared;
   Float_t         ep2_btMaximaSharedFragment;
   Float_t         ep2_btMeanDist;
   Float_t         ep2_btNearbyMaxima;
   Float_t         ep2_btNearbyMaximaShared;
   Float_t         ep2_btPadsClus;
   Float_t         ep2_btPadsRing;
   Float_t         ep2_btRingMatrix;
   Float_t         ep2_dedx_mdc;
   Float_t         ep2_dedx_tof;
   Float_t         ep2_id;
   Float_t         ep2_isBT;
   Float_t         ep2_isOffVertexClust;
   Float_t         ep2_isPrimaryVertex;
   Float_t         ep2_isUsedVertex;
   Float_t         ep2_isring;
   Float_t         ep2_isringmdc;
   Float_t         ep2_isringnomatch;
   Float_t         ep2_isringtrack;
   Float_t         ep2_kIsLepton;
   Float_t         ep2_kIsUsed;
   Float_t         ep2_mdcinnerchi2;
   Float_t         ep2_mdcouterchi2;
   Float_t         ep2_oa_hadr;
   Float_t         ep2_oa_lept;
   Float_t         ep2_p;
   Float_t         ep2_p_corr_em;
   Float_t         ep2_p_corr_ep;
   Float_t         ep2_p_corr_p;
   Float_t         ep2_p_corr_pim;
   Float_t         ep2_p_corr_pip;
   Float_t         ep2_phi;
   Float_t         ep2_phi_rich;
   Float_t         ep2_pid;
   Float_t         ep2_q;
   Float_t         ep2_r;
   Float_t         ep2_resolution;
   Float_t         ep2_resoultion;
   Float_t         ep2_rich_amp;
   Float_t         ep2_rich_centr;
   Float_t         ep2_rich_houtra;
   Float_t         ep2_rich_padnum;
   Float_t         ep2_rich_patmat;
   Float_t         ep2_rkchi2;
   Float_t         ep2_sector;
   Float_t         ep2_shw_sum0;
   Float_t         ep2_shw_sum1;
   Float_t         ep2_shw_sum2;
   Float_t         ep2_system;
   Float_t         ep2_theta;
   Float_t         ep2_theta_rich;
   Float_t         ep2_tof_mom;
   Float_t         ep2_tof_new;
   Float_t         ep2_tof_rec;
   Float_t         ep2_track_length;
   Float_t         ep2_tracklength;
   Float_t         ep2_z;
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
   TBranch        *b_ep1_beta;   //!
   TBranch        *b_ep1_beta_new;   //!
   TBranch        *b_ep1_btChargeRing;   //!
   TBranch        *b_ep1_btChargeSum;   //!
   TBranch        *b_ep1_btChi2;   //!
   TBranch        *b_ep1_btClusters;   //!
   TBranch        *b_ep1_btMaxima;   //!
   TBranch        *b_ep1_btMaximaCharge;   //!
   TBranch        *b_ep1_btMaximaChargeShared;   //!
   TBranch        *b_ep1_btMaximaChargeSharedFragment;   //!
   TBranch        *b_ep1_btMaximaShared;   //!
   TBranch        *b_ep1_btMaximaSharedFragment;   //!
   TBranch        *b_ep1_btMeanDist;   //!
   TBranch        *b_ep1_btNearbyMaxima;   //!
   TBranch        *b_ep1_btNearbyMaximaShared;   //!
   TBranch        *b_ep1_btPadsClus;   //!
   TBranch        *b_ep1_btPadsRing;   //!
   TBranch        *b_ep1_btRingMatrix;   //!
   TBranch        *b_ep1_dedx_mdc;   //!
   TBranch        *b_ep1_dedx_tof;   //!
   TBranch        *b_ep1_id;   //!
   TBranch        *b_ep1_isBT;
   TBranch        *b_ep1_isOffVertexClust;   //!
   TBranch        *b_ep1_isPrimaryVertex;   //!
   TBranch        *b_ep1_isUsedVertex;   //!
   TBranch        *b_ep1_isring;   //!
   TBranch        *b_ep1_isringmdc;   //!
   TBranch        *b_ep1_isringnomatch;   //!
   TBranch        *b_ep1_isringtrack;   //!
   TBranch        *b_ep1_kIsLepton;   //!
   TBranch        *b_ep1_kIsUsed;   //!
   TBranch        *b_ep1_mdcinnerchi2;   //!
   TBranch        *b_ep1_mdcouterchi2;   //!
   TBranch        *b_ep1_oa_hadr;   //!
   TBranch        *b_ep1_oa_lept;   //!
   TBranch        *b_ep1_p;   //!
   TBranch        *b_ep1_p_corr_em;   //!
   TBranch        *b_ep1_p_corr_ep;   //!
   TBranch        *b_ep1_p_corr_p;   //!
   TBranch        *b_ep1_p_corr_pim;   //!
   TBranch        *b_ep1_p_corr_pip;   //!
   TBranch        *b_ep1_phi;   //!
   TBranch        *b_ep1_phi_rich;   //!
   TBranch        *b_ep1_pid;   //!
   TBranch        *b_ep1_q;   //!
   TBranch        *b_ep1_r;   //!
   TBranch        *b_ep1_resolution;   //!
   TBranch        *b_ep1_resoultion;   //!
   TBranch        *b_ep1_rich_amp;   //!
   TBranch        *b_ep1_rich_centr;   //!
   TBranch        *b_ep1_rich_houtra;   //!
   TBranch        *b_ep1_rich_padnum;   //!
   TBranch        *b_ep1_rich_patmat;   //!
   TBranch        *b_ep1_rkchi2;   //!
   TBranch        *b_ep1_sector;   //!
   TBranch        *b_ep1_shw_sum0;   //!
   TBranch        *b_ep1_shw_sum1;   //!
   TBranch        *b_ep1_shw_sum2;   //!
   TBranch        *b_ep1_system;   //!
   TBranch        *b_ep1_theta;   //!
   TBranch        *b_ep1_theta_rich;   //!
   TBranch        *b_ep1_tof_mom;   //!
   TBranch        *b_ep1_tof_new;   //!
   TBranch        *b_ep1_tof_rec;   //!
   TBranch        *b_ep1_track_length;   //!
   TBranch        *b_ep1_tracklength;   //!
   TBranch        *b_ep1_z;   //!
   TBranch        *b_ep2_beta;   //!
   TBranch        *b_ep2_beta_new;   //!
   TBranch        *b_ep2_btChargeRing;   //!
   TBranch        *b_ep2_btChargeSum;   //!
   TBranch        *b_ep2_btChi2;   //!
   TBranch        *b_ep2_btClusters;   //!
   TBranch        *b_ep2_btMaxima;   //!
   TBranch        *b_ep2_btMaximaCharge;   //!
   TBranch        *b_ep2_btMaximaChargeShared;   //!
   TBranch        *b_ep2_btMaximaChargeSharedFragment;   //!
   TBranch        *b_ep2_btMaximaShared;   //!
   TBranch        *b_ep2_btMaximaSharedFragment;   //!
   TBranch        *b_ep2_btMeanDist;   //!
   TBranch        *b_ep2_btNearbyMaxima;   //!
   TBranch        *b_ep2_btNearbyMaximaShared;   //!
   TBranch        *b_ep2_btPadsClus;   //!
   TBranch        *b_ep2_btPadsRing;   //!
   TBranch        *b_ep2_btRingMatrix;   //!
   TBranch        *b_ep2_dedx_mdc;   //!
   TBranch        *b_ep2_dedx_tof;   //!
   TBranch        *b_ep2_id;   //!
   TBranch        *b_ep2_isBT;
   TBranch        *b_ep2_isOffVertexClust;   //!
   TBranch        *b_ep2_isPrimaryVertex;   //!
   TBranch        *b_ep2_isUsedVertex;   //!
   TBranch        *b_ep2_isring;   //!
   TBranch        *b_ep2_isringmdc;   //!
   TBranch        *b_ep2_isringnomatch;   //!
   TBranch        *b_ep2_isringtrack;   //!
   TBranch        *b_ep2_kIsLepton;   //!
   TBranch        *b_ep2_kIsUsed;   //!
   TBranch        *b_ep2_mdcinnerchi2;   //!
   TBranch        *b_ep2_mdcouterchi2;   //!
   TBranch        *b_ep2_oa_hadr;   //!
   TBranch        *b_ep2_oa_lept;   //!
   TBranch        *b_ep2_p;   //!
   TBranch        *b_ep2_p_corr_em;   //!
   TBranch        *b_ep2_p_corr_ep;   //!
   TBranch        *b_ep2_p_corr_p;   //!
   TBranch        *b_ep2_p_corr_pim;   //!
   TBranch        *b_ep2_p_corr_pip;   //!
   TBranch        *b_ep2_phi;   //!
   TBranch        *b_ep2_phi_rich;   //!
   TBranch        *b_ep2_pid;   //!
   TBranch        *b_ep2_q;   //!
   TBranch        *b_ep2_r;   //!
   TBranch        *b_ep2_resolution;   //!
   TBranch        *b_ep2_resoultion;   //!
   TBranch        *b_ep2_rich_amp;   //!
   TBranch        *b_ep2_rich_centr;   //!
   TBranch        *b_ep2_rich_houtra;   //!
   TBranch        *b_ep2_rich_padnum;   //!
   TBranch        *b_ep2_rich_patmat;   //!
   TBranch        *b_ep2_rkchi2;   //!
   TBranch        *b_ep2_sector;   //!
   TBranch        *b_ep2_shw_sum0;   //!
   TBranch        *b_ep2_shw_sum1;   //!
   TBranch        *b_ep2_shw_sum2;   //!
   TBranch        *b_ep2_system;   //!
   TBranch        *b_ep2_theta;   //!
   TBranch        *b_ep2_theta_rich;   //!
   TBranch        *b_ep2_tof_mom;   //!
   TBranch        *b_ep2_tof_new;   //!
   TBranch        *b_ep2_tof_rec;   //!
   TBranch        *b_ep2_track_length;   //!
   TBranch        *b_ep2_tracklength;   //!
   TBranch        *b_ep2_z;   //!
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

   EpEp(TTree *tree=0);
   virtual ~EpEp();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif


