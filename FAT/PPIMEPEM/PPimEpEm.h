#ifndef EpEm_h
#define EpEm_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

using namespace std;

/*********************************************************************************************/
class EpEm {

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

   EpEm(TTree *tree=0);
   virtual ~EpEm();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

