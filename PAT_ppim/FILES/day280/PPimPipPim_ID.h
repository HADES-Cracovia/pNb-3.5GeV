//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jul 10 15:02:46 2018 by ROOT version 5.34/34
// from TTree PPimPipPim_ID/PPimPipPim_ID
// found on file: be08280235056_dst_gen1_sep08_hadron_out.root
//////////////////////////////////////////////////////////

#ifndef PPimPipPim_ID_h
#define PPimPipPim_ID_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class PPimPipPim_ID {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         isBest;
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

   // List of branches
   TBranch        *b_isBest;   //!
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

   PPimPipPim_ID(TTree *tree=0);
   virtual ~PPimPipPim_ID();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef PPimPipPim_ID_cxx
PPimPipPim_ID::PPimPipPim_ID(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("be08280235056_dst_gen1_sep08_hadron_out.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("be08280235056_dst_gen1_sep08_hadron_out.root");
      }
      f->GetObject("PPimPipPim_ID",tree);

   }
   Init(tree);
}

PPimPipPim_ID::~PPimPipPim_ID()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t PPimPipPim_ID::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t PPimPipPim_ID::LoadTree(Long64_t entry)
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

void PPimPipPim_ID::Init(TTree *tree)
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

   fChain->SetBranchAddress("isBest", &isBest, &b_isBest);
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
   fChain->SetBranchAddress("pim1_beta", &pim1_beta, &b_pim1_beta);
   fChain->SetBranchAddress("pim1_beta_new", &pim1_beta_new, &b_pim1_beta_new);
   fChain->SetBranchAddress("pim1_btChargeRing", &pim1_btChargeRing, &b_pim1_btChargeRing);
   fChain->SetBranchAddress("pim1_btChargeSum", &pim1_btChargeSum, &b_pim1_btChargeSum);
   fChain->SetBranchAddress("pim1_btChi2", &pim1_btChi2, &b_pim1_btChi2);
   fChain->SetBranchAddress("pim1_btClusters", &pim1_btClusters, &b_pim1_btClusters);
   fChain->SetBranchAddress("pim1_btMaxima", &pim1_btMaxima, &b_pim1_btMaxima);
   fChain->SetBranchAddress("pim1_btMaximaCharge", &pim1_btMaximaCharge, &b_pim1_btMaximaCharge);
   fChain->SetBranchAddress("pim1_btMaximaChargeShared", &pim1_btMaximaChargeShared, &b_pim1_btMaximaChargeShared);
   fChain->SetBranchAddress("pim1_btMaximaChargeSharedFragment", &pim1_btMaximaChargeSharedFragment, &b_pim1_btMaximaChargeSharedFragment);
   fChain->SetBranchAddress("pim1_btMaximaShared", &pim1_btMaximaShared, &b_pim1_btMaximaShared);
   fChain->SetBranchAddress("pim1_btMaximaSharedFragment", &pim1_btMaximaSharedFragment, &b_pim1_btMaximaSharedFragment);
   fChain->SetBranchAddress("pim1_btMeanDist", &pim1_btMeanDist, &b_pim1_btMeanDist);
   fChain->SetBranchAddress("pim1_btNearbyMaxima", &pim1_btNearbyMaxima, &b_pim1_btNearbyMaxima);
   fChain->SetBranchAddress("pim1_btNearbyMaximaShared", &pim1_btNearbyMaximaShared, &b_pim1_btNearbyMaximaShared);
   fChain->SetBranchAddress("pim1_btPadsClus", &pim1_btPadsClus, &b_pim1_btPadsClus);
   fChain->SetBranchAddress("pim1_btPadsRing", &pim1_btPadsRing, &b_pim1_btPadsRing);
   fChain->SetBranchAddress("pim1_btRingMatrix", &pim1_btRingMatrix, &b_pim1_btRingMatrix);
   fChain->SetBranchAddress("pim1_dedx_mdc", &pim1_dedx_mdc, &b_pim1_dedx_mdc);
   fChain->SetBranchAddress("pim1_dedx_tof", &pim1_dedx_tof, &b_pim1_dedx_tof);
   fChain->SetBranchAddress("pim1_id", &pim1_id, &b_pim1_id);
   fChain->SetBranchAddress("pim1_isBT", &pim1_isBT, &b_pim1_isBT);
   fChain->SetBranchAddress("pim1_isOffVertexClust", &pim1_isOffVertexClust, &b_pim1_isOffVertexClust);
   fChain->SetBranchAddress("pim1_isPrimaryVertex", &pim1_isPrimaryVertex, &b_pim1_isPrimaryVertex);
   fChain->SetBranchAddress("pim1_isUsedVertex", &pim1_isUsedVertex, &b_pim1_isUsedVertex);
   fChain->SetBranchAddress("pim1_isring", &pim1_isring, &b_pim1_isring);
   fChain->SetBranchAddress("pim1_isringmdc", &pim1_isringmdc, &b_pim1_isringmdc);
   fChain->SetBranchAddress("pim1_isringnomatch", &pim1_isringnomatch, &b_pim1_isringnomatch);
   fChain->SetBranchAddress("pim1_isringtrack", &pim1_isringtrack, &b_pim1_isringtrack);
   fChain->SetBranchAddress("pim1_kIsLepton", &pim1_kIsLepton, &b_pim1_kIsLepton);
   fChain->SetBranchAddress("pim1_kIsUsed", &pim1_kIsUsed, &b_pim1_kIsUsed);
   fChain->SetBranchAddress("pim1_mdcinnerchi2", &pim1_mdcinnerchi2, &b_pim1_mdcinnerchi2);
   fChain->SetBranchAddress("pim1_mdcouterchi2", &pim1_mdcouterchi2, &b_pim1_mdcouterchi2);
   fChain->SetBranchAddress("pim1_oa_hadr", &pim1_oa_hadr, &b_pim1_oa_hadr);
   fChain->SetBranchAddress("pim1_oa_lept", &pim1_oa_lept, &b_pim1_oa_lept);
   fChain->SetBranchAddress("pim1_p", &pim1_p, &b_pim1_p);
   fChain->SetBranchAddress("pim1_p_corr_em", &pim1_p_corr_em, &b_pim1_p_corr_em);
   fChain->SetBranchAddress("pim1_p_corr_ep", &pim1_p_corr_ep, &b_pim1_p_corr_ep);
   fChain->SetBranchAddress("pim1_p_corr_p", &pim1_p_corr_p, &b_pim1_p_corr_p);
   fChain->SetBranchAddress("pim1_p_corr_pim", &pim1_p_corr_pim, &b_pim1_p_corr_pim);
   fChain->SetBranchAddress("pim1_p_corr_pip", &pim1_p_corr_pip, &b_pim1_p_corr_pip);
   fChain->SetBranchAddress("pim1_phi", &pim1_phi, &b_pim1_phi);
   fChain->SetBranchAddress("pim1_phi_rich", &pim1_phi_rich, &b_pim1_phi_rich);
   fChain->SetBranchAddress("pim1_pid", &pim1_pid, &b_pim1_pid);
   fChain->SetBranchAddress("pim1_q", &pim1_q, &b_pim1_q);
   fChain->SetBranchAddress("pim1_r", &pim1_r, &b_pim1_r);
   fChain->SetBranchAddress("pim1_resolution", &pim1_resolution, &b_pim1_resolution);
   fChain->SetBranchAddress("pim1_resoultion", &pim1_resoultion, &b_pim1_resoultion);
   fChain->SetBranchAddress("pim1_rich_amp", &pim1_rich_amp, &b_pim1_rich_amp);
   fChain->SetBranchAddress("pim1_rich_centr", &pim1_rich_centr, &b_pim1_rich_centr);
   fChain->SetBranchAddress("pim1_rich_houtra", &pim1_rich_houtra, &b_pim1_rich_houtra);
   fChain->SetBranchAddress("pim1_rich_padnum", &pim1_rich_padnum, &b_pim1_rich_padnum);
   fChain->SetBranchAddress("pim1_rich_patmat", &pim1_rich_patmat, &b_pim1_rich_patmat);
   fChain->SetBranchAddress("pim1_rkchi2", &pim1_rkchi2, &b_pim1_rkchi2);
   fChain->SetBranchAddress("pim1_sector", &pim1_sector, &b_pim1_sector);
   fChain->SetBranchAddress("pim1_shw_sum0", &pim1_shw_sum0, &b_pim1_shw_sum0);
   fChain->SetBranchAddress("pim1_shw_sum1", &pim1_shw_sum1, &b_pim1_shw_sum1);
   fChain->SetBranchAddress("pim1_shw_sum2", &pim1_shw_sum2, &b_pim1_shw_sum2);
   fChain->SetBranchAddress("pim1_system", &pim1_system, &b_pim1_system);
   fChain->SetBranchAddress("pim1_theta", &pim1_theta, &b_pim1_theta);
   fChain->SetBranchAddress("pim1_theta_rich", &pim1_theta_rich, &b_pim1_theta_rich);
   fChain->SetBranchAddress("pim1_tof_mom", &pim1_tof_mom, &b_pim1_tof_mom);
   fChain->SetBranchAddress("pim1_tof_new", &pim1_tof_new, &b_pim1_tof_new);
   fChain->SetBranchAddress("pim1_tof_rec", &pim1_tof_rec, &b_pim1_tof_rec);
   fChain->SetBranchAddress("pim1_track_length", &pim1_track_length, &b_pim1_track_length);
   fChain->SetBranchAddress("pim1_tracklength", &pim1_tracklength, &b_pim1_tracklength);
   fChain->SetBranchAddress("pim1_z", &pim1_z, &b_pim1_z);
   fChain->SetBranchAddress("pim2_beta", &pim2_beta, &b_pim2_beta);
   fChain->SetBranchAddress("pim2_beta_new", &pim2_beta_new, &b_pim2_beta_new);
   fChain->SetBranchAddress("pim2_btChargeRing", &pim2_btChargeRing, &b_pim2_btChargeRing);
   fChain->SetBranchAddress("pim2_btChargeSum", &pim2_btChargeSum, &b_pim2_btChargeSum);
   fChain->SetBranchAddress("pim2_btChi2", &pim2_btChi2, &b_pim2_btChi2);
   fChain->SetBranchAddress("pim2_btClusters", &pim2_btClusters, &b_pim2_btClusters);
   fChain->SetBranchAddress("pim2_btMaxima", &pim2_btMaxima, &b_pim2_btMaxima);
   fChain->SetBranchAddress("pim2_btMaximaCharge", &pim2_btMaximaCharge, &b_pim2_btMaximaCharge);
   fChain->SetBranchAddress("pim2_btMaximaChargeShared", &pim2_btMaximaChargeShared, &b_pim2_btMaximaChargeShared);
   fChain->SetBranchAddress("pim2_btMaximaChargeSharedFragment", &pim2_btMaximaChargeSharedFragment, &b_pim2_btMaximaChargeSharedFragment);
   fChain->SetBranchAddress("pim2_btMaximaShared", &pim2_btMaximaShared, &b_pim2_btMaximaShared);
   fChain->SetBranchAddress("pim2_btMaximaSharedFragment", &pim2_btMaximaSharedFragment, &b_pim2_btMaximaSharedFragment);
   fChain->SetBranchAddress("pim2_btMeanDist", &pim2_btMeanDist, &b_pim2_btMeanDist);
   fChain->SetBranchAddress("pim2_btNearbyMaxima", &pim2_btNearbyMaxima, &b_pim2_btNearbyMaxima);
   fChain->SetBranchAddress("pim2_btNearbyMaximaShared", &pim2_btNearbyMaximaShared, &b_pim2_btNearbyMaximaShared);
   fChain->SetBranchAddress("pim2_btPadsClus", &pim2_btPadsClus, &b_pim2_btPadsClus);
   fChain->SetBranchAddress("pim2_btPadsRing", &pim2_btPadsRing, &b_pim2_btPadsRing);
   fChain->SetBranchAddress("pim2_btRingMatrix", &pim2_btRingMatrix, &b_pim2_btRingMatrix);
   fChain->SetBranchAddress("pim2_dedx_mdc", &pim2_dedx_mdc, &b_pim2_dedx_mdc);
   fChain->SetBranchAddress("pim2_dedx_tof", &pim2_dedx_tof, &b_pim2_dedx_tof);
   fChain->SetBranchAddress("pim2_id", &pim2_id, &b_pim2_id);
   fChain->SetBranchAddress("pim2_isBT", &pim2_isBT, &b_pim2_isBT);
   fChain->SetBranchAddress("pim2_isOffVertexClust", &pim2_isOffVertexClust, &b_pim2_isOffVertexClust);
   fChain->SetBranchAddress("pim2_isPrimaryVertex", &pim2_isPrimaryVertex, &b_pim2_isPrimaryVertex);
   fChain->SetBranchAddress("pim2_isUsedVertex", &pim2_isUsedVertex, &b_pim2_isUsedVertex);
   fChain->SetBranchAddress("pim2_isring", &pim2_isring, &b_pim2_isring);
   fChain->SetBranchAddress("pim2_isringmdc", &pim2_isringmdc, &b_pim2_isringmdc);
   fChain->SetBranchAddress("pim2_isringnomatch", &pim2_isringnomatch, &b_pim2_isringnomatch);
   fChain->SetBranchAddress("pim2_isringtrack", &pim2_isringtrack, &b_pim2_isringtrack);
   fChain->SetBranchAddress("pim2_kIsLepton", &pim2_kIsLepton, &b_pim2_kIsLepton);
   fChain->SetBranchAddress("pim2_kIsUsed", &pim2_kIsUsed, &b_pim2_kIsUsed);
   fChain->SetBranchAddress("pim2_mdcinnerchi2", &pim2_mdcinnerchi2, &b_pim2_mdcinnerchi2);
   fChain->SetBranchAddress("pim2_mdcouterchi2", &pim2_mdcouterchi2, &b_pim2_mdcouterchi2);
   fChain->SetBranchAddress("pim2_oa_hadr", &pim2_oa_hadr, &b_pim2_oa_hadr);
   fChain->SetBranchAddress("pim2_oa_lept", &pim2_oa_lept, &b_pim2_oa_lept);
   fChain->SetBranchAddress("pim2_p", &pim2_p, &b_pim2_p);
   fChain->SetBranchAddress("pim2_p_corr_em", &pim2_p_corr_em, &b_pim2_p_corr_em);
   fChain->SetBranchAddress("pim2_p_corr_ep", &pim2_p_corr_ep, &b_pim2_p_corr_ep);
   fChain->SetBranchAddress("pim2_p_corr_p", &pim2_p_corr_p, &b_pim2_p_corr_p);
   fChain->SetBranchAddress("pim2_p_corr_pim", &pim2_p_corr_pim, &b_pim2_p_corr_pim);
   fChain->SetBranchAddress("pim2_p_corr_pip", &pim2_p_corr_pip, &b_pim2_p_corr_pip);
   fChain->SetBranchAddress("pim2_phi", &pim2_phi, &b_pim2_phi);
   fChain->SetBranchAddress("pim2_phi_rich", &pim2_phi_rich, &b_pim2_phi_rich);
   fChain->SetBranchAddress("pim2_pid", &pim2_pid, &b_pim2_pid);
   fChain->SetBranchAddress("pim2_q", &pim2_q, &b_pim2_q);
   fChain->SetBranchAddress("pim2_r", &pim2_r, &b_pim2_r);
   fChain->SetBranchAddress("pim2_resolution", &pim2_resolution, &b_pim2_resolution);
   fChain->SetBranchAddress("pim2_resoultion", &pim2_resoultion, &b_pim2_resoultion);
   fChain->SetBranchAddress("pim2_rich_amp", &pim2_rich_amp, &b_pim2_rich_amp);
   fChain->SetBranchAddress("pim2_rich_centr", &pim2_rich_centr, &b_pim2_rich_centr);
   fChain->SetBranchAddress("pim2_rich_houtra", &pim2_rich_houtra, &b_pim2_rich_houtra);
   fChain->SetBranchAddress("pim2_rich_padnum", &pim2_rich_padnum, &b_pim2_rich_padnum);
   fChain->SetBranchAddress("pim2_rich_patmat", &pim2_rich_patmat, &b_pim2_rich_patmat);
   fChain->SetBranchAddress("pim2_rkchi2", &pim2_rkchi2, &b_pim2_rkchi2);
   fChain->SetBranchAddress("pim2_sector", &pim2_sector, &b_pim2_sector);
   fChain->SetBranchAddress("pim2_shw_sum0", &pim2_shw_sum0, &b_pim2_shw_sum0);
   fChain->SetBranchAddress("pim2_shw_sum1", &pim2_shw_sum1, &b_pim2_shw_sum1);
   fChain->SetBranchAddress("pim2_shw_sum2", &pim2_shw_sum2, &b_pim2_shw_sum2);
   fChain->SetBranchAddress("pim2_system", &pim2_system, &b_pim2_system);
   fChain->SetBranchAddress("pim2_theta", &pim2_theta, &b_pim2_theta);
   fChain->SetBranchAddress("pim2_theta_rich", &pim2_theta_rich, &b_pim2_theta_rich);
   fChain->SetBranchAddress("pim2_tof_mom", &pim2_tof_mom, &b_pim2_tof_mom);
   fChain->SetBranchAddress("pim2_tof_new", &pim2_tof_new, &b_pim2_tof_new);
   fChain->SetBranchAddress("pim2_tof_rec", &pim2_tof_rec, &b_pim2_tof_rec);
   fChain->SetBranchAddress("pim2_track_length", &pim2_track_length, &b_pim2_track_length);
   fChain->SetBranchAddress("pim2_tracklength", &pim2_tracklength, &b_pim2_tracklength);
   fChain->SetBranchAddress("pim2_z", &pim2_z, &b_pim2_z);
   fChain->SetBranchAddress("pip_beta", &pip_beta, &b_pip_beta);
   fChain->SetBranchAddress("pip_beta_new", &pip_beta_new, &b_pip_beta_new);
   fChain->SetBranchAddress("pip_btChargeRing", &pip_btChargeRing, &b_pip_btChargeRing);
   fChain->SetBranchAddress("pip_btChargeSum", &pip_btChargeSum, &b_pip_btChargeSum);
   fChain->SetBranchAddress("pip_btChi2", &pip_btChi2, &b_pip_btChi2);
   fChain->SetBranchAddress("pip_btClusters", &pip_btClusters, &b_pip_btClusters);
   fChain->SetBranchAddress("pip_btMaxima", &pip_btMaxima, &b_pip_btMaxima);
   fChain->SetBranchAddress("pip_btMaximaCharge", &pip_btMaximaCharge, &b_pip_btMaximaCharge);
   fChain->SetBranchAddress("pip_btMaximaChargeShared", &pip_btMaximaChargeShared, &b_pip_btMaximaChargeShared);
   fChain->SetBranchAddress("pip_btMaximaChargeSharedFragment", &pip_btMaximaChargeSharedFragment, &b_pip_btMaximaChargeSharedFragment);
   fChain->SetBranchAddress("pip_btMaximaShared", &pip_btMaximaShared, &b_pip_btMaximaShared);
   fChain->SetBranchAddress("pip_btMaximaSharedFragment", &pip_btMaximaSharedFragment, &b_pip_btMaximaSharedFragment);
   fChain->SetBranchAddress("pip_btMeanDist", &pip_btMeanDist, &b_pip_btMeanDist);
   fChain->SetBranchAddress("pip_btNearbyMaxima", &pip_btNearbyMaxima, &b_pip_btNearbyMaxima);
   fChain->SetBranchAddress("pip_btNearbyMaximaShared", &pip_btNearbyMaximaShared, &b_pip_btNearbyMaximaShared);
   fChain->SetBranchAddress("pip_btPadsClus", &pip_btPadsClus, &b_pip_btPadsClus);
   fChain->SetBranchAddress("pip_btPadsRing", &pip_btPadsRing, &b_pip_btPadsRing);
   fChain->SetBranchAddress("pip_btRingMatrix", &pip_btRingMatrix, &b_pip_btRingMatrix);
   fChain->SetBranchAddress("pip_dedx_mdc", &pip_dedx_mdc, &b_pip_dedx_mdc);
   fChain->SetBranchAddress("pip_dedx_tof", &pip_dedx_tof, &b_pip_dedx_tof);
   fChain->SetBranchAddress("pip_id", &pip_id, &b_pip_id);
   fChain->SetBranchAddress("pip_isBT", &pip_isBT, &b_pip_isBT);
   fChain->SetBranchAddress("pip_isOffVertexClust", &pip_isOffVertexClust, &b_pip_isOffVertexClust);
   fChain->SetBranchAddress("pip_isPrimaryVertex", &pip_isPrimaryVertex, &b_pip_isPrimaryVertex);
   fChain->SetBranchAddress("pip_isUsedVertex", &pip_isUsedVertex, &b_pip_isUsedVertex);
   fChain->SetBranchAddress("pip_isring", &pip_isring, &b_pip_isring);
   fChain->SetBranchAddress("pip_isringmdc", &pip_isringmdc, &b_pip_isringmdc);
   fChain->SetBranchAddress("pip_isringnomatch", &pip_isringnomatch, &b_pip_isringnomatch);
   fChain->SetBranchAddress("pip_isringtrack", &pip_isringtrack, &b_pip_isringtrack);
   fChain->SetBranchAddress("pip_kIsLepton", &pip_kIsLepton, &b_pip_kIsLepton);
   fChain->SetBranchAddress("pip_kIsUsed", &pip_kIsUsed, &b_pip_kIsUsed);
   fChain->SetBranchAddress("pip_mdcinnerchi2", &pip_mdcinnerchi2, &b_pip_mdcinnerchi2);
   fChain->SetBranchAddress("pip_mdcouterchi2", &pip_mdcouterchi2, &b_pip_mdcouterchi2);
   fChain->SetBranchAddress("pip_oa_hadr", &pip_oa_hadr, &b_pip_oa_hadr);
   fChain->SetBranchAddress("pip_oa_lept", &pip_oa_lept, &b_pip_oa_lept);
   fChain->SetBranchAddress("pip_p", &pip_p, &b_pip_p);
   fChain->SetBranchAddress("pip_p_corr_em", &pip_p_corr_em, &b_pip_p_corr_em);
   fChain->SetBranchAddress("pip_p_corr_ep", &pip_p_corr_ep, &b_pip_p_corr_ep);
   fChain->SetBranchAddress("pip_p_corr_p", &pip_p_corr_p, &b_pip_p_corr_p);
   fChain->SetBranchAddress("pip_p_corr_pim", &pip_p_corr_pim, &b_pip_p_corr_pim);
   fChain->SetBranchAddress("pip_p_corr_pip", &pip_p_corr_pip, &b_pip_p_corr_pip);
   fChain->SetBranchAddress("pip_phi", &pip_phi, &b_pip_phi);
   fChain->SetBranchAddress("pip_phi_rich", &pip_phi_rich, &b_pip_phi_rich);
   fChain->SetBranchAddress("pip_pid", &pip_pid, &b_pip_pid);
   fChain->SetBranchAddress("pip_q", &pip_q, &b_pip_q);
   fChain->SetBranchAddress("pip_r", &pip_r, &b_pip_r);
   fChain->SetBranchAddress("pip_resolution", &pip_resolution, &b_pip_resolution);
   fChain->SetBranchAddress("pip_resoultion", &pip_resoultion, &b_pip_resoultion);
   fChain->SetBranchAddress("pip_rich_amp", &pip_rich_amp, &b_pip_rich_amp);
   fChain->SetBranchAddress("pip_rich_centr", &pip_rich_centr, &b_pip_rich_centr);
   fChain->SetBranchAddress("pip_rich_houtra", &pip_rich_houtra, &b_pip_rich_houtra);
   fChain->SetBranchAddress("pip_rich_padnum", &pip_rich_padnum, &b_pip_rich_padnum);
   fChain->SetBranchAddress("pip_rich_patmat", &pip_rich_patmat, &b_pip_rich_patmat);
   fChain->SetBranchAddress("pip_rkchi2", &pip_rkchi2, &b_pip_rkchi2);
   fChain->SetBranchAddress("pip_sector", &pip_sector, &b_pip_sector);
   fChain->SetBranchAddress("pip_shw_sum0", &pip_shw_sum0, &b_pip_shw_sum0);
   fChain->SetBranchAddress("pip_shw_sum1", &pip_shw_sum1, &b_pip_shw_sum1);
   fChain->SetBranchAddress("pip_shw_sum2", &pip_shw_sum2, &b_pip_shw_sum2);
   fChain->SetBranchAddress("pip_system", &pip_system, &b_pip_system);
   fChain->SetBranchAddress("pip_theta", &pip_theta, &b_pip_theta);
   fChain->SetBranchAddress("pip_theta_rich", &pip_theta_rich, &b_pip_theta_rich);
   fChain->SetBranchAddress("pip_tof_mom", &pip_tof_mom, &b_pip_tof_mom);
   fChain->SetBranchAddress("pip_tof_new", &pip_tof_new, &b_pip_tof_new);
   fChain->SetBranchAddress("pip_tof_rec", &pip_tof_rec, &b_pip_tof_rec);
   fChain->SetBranchAddress("pip_track_length", &pip_track_length, &b_pip_track_length);
   fChain->SetBranchAddress("pip_tracklength", &pip_tracklength, &b_pip_tracklength);
   fChain->SetBranchAddress("pip_z", &pip_z, &b_pip_z);
   Notify();
}

Bool_t PPimPipPim_ID::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void PPimPipPim_ID::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t PPimPipPim_ID::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef PPimPipPim_ID_cxx
