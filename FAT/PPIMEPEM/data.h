#ifndef DATA_H
#define DATA_H

#include <TROOT.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TCutG.h>
#include <TCut.h>
#include <TLorentzVector.h>
#include <TVector3.h>
#include "hntuple.h"
#include "HFilter.h"



/**************************** global histograms repository ***********************************/

namespace PATData {
  extern TFile *outFileData;
  extern HNtuple *tlo;
  extern HFilter *filter;
  extern float EFF, ACC;
  extern TH1F          *oa_corr;
  extern TH1F          *em_mom, *em_mom_bt, *ep_mom, *ep_mom_bt;
  extern TH1F          *SIGNAL, *CB, *SIGNIFICANCE;
  extern TH1F          *sig_all, *sig_all_bt, *sig_all_back1, *sig_all_back2, *sig_OK, *sig_bt_OK, *sig_rf_and_bt;
  extern TH1F          *miss_all, *miss_all_back1, *miss_all_back2, *miss_OK;
  extern TH1F   *sig_all_var, *sig_all_var_bt, *sig_all_var_back1, *sig_all_bt_back1, *sig_all_var_bt_back1, *sig_all_var_back2, *sig_var_OK, *sig_var_bt_OK, *sig_all_bt_back2, *sig_all_var_bt_back2;
  extern TH1F   *sig_all_var2, *sig_all_var2_back1, *sig_all_var2_back2, *sig_var2_OK;
  extern TH1F 	*cos_ep, *cos_em, *cos_sum;
  extern TH1F 	*cos_ep_back1, *cos_em_back1, *cos_sum_back1;
  extern TH1F 			*cos_ep_back2, *cos_em_back2, *cos_sum_back2;
  extern TH1F			*cos_ep_OK, *cos_em_OK, *cos_sum_OK;
  extern TH1F			*cos_ep_cm_OK, *cos_back1_cm, *cos_back2_cm, *cos_ep_cm;
  extern TH1F			*rapidity_all, *rapidity_back1, *rapidity_back2, *rapidity_OK;
  extern TH1F			*rapidity_140_all, *rapidity_140_back1, *rapidity_140_back2, *rapidity_140_OK;
  extern TH1F			*pt_all, *pt_back1, *pt_back2, *pt_OK;
  extern TH1F			*pt_140_all, *pt_140_back1, *pt_140_back2, *pt_140_OK;
  extern TH1F      *sig_all_var_back, *sig_all_var_bt_back, *pureBT_signal_back_var;
  extern TH1F      *sig_to_bg_var, *sig_to_bg_bt_var, *sig_to_bg_pureBT_var;

  extern TH1F *dist_pim_p, *m_pim_p, *m_pim_p_ep_em;
  extern TH1F *m_pim_p_ZD, *m_pim_p_ep_em_ZD;
  
  extern TH1F                   *pureBT_signal, *pureBT_signal_OK, *pureBT_signal_back1, *pureBT_signal_back2;
  extern TH1F          *pureBT_signal_var, *pureBT_signal_OK_var, *pureBT_signal_back1_var, *pureBT_signal_back2_var;
  extern TH2F			*ep_beta_mom, *em_beta_mom,*ep_beta_mom_bt, *em_beta_mom_bt, *pureBT_beta_mom;

  extern TH1F                   *sig_rf_and_bt,*sig_rf_and_bt_OK,*sig_rf_and_bt_back1,*sig_rf_and_bt_back2;
  extern TH1F                   *sig_rf_and_bt_var,*sig_rf_and_bt_OK_var,*sig_rf_and_bt_back1_var,*sig_rf_and_bt_back2_var;
  extern TH1F                   *sig_sum, *sig_sum_var;
  extern TH1F *momentum_spectrum, *momentum_spectrum_bt, *momentum_spectrum_pureBT;
  extern TH1I          *bt_rf_stat, *bt_rf_stat_pi, *bt_rf_stat_back1, *bt_rf_stat_back2, *bt_rf_stat_OK,*bt_rf_stat_pi_back1, *bt_rf_stat_pi_back2, *bt_rf_stat_pi_OK;
  extern TH2F *q_vs_p_leptons_RF,*q_vs_p_leptons_BT;
  extern TH3F      *rf_freedom;
  extern TH2F      *rf_f_dtheta, *rf_f_dphi;
  extern TH2F *lambda_vertex;
  extern TFile *file1_cuts, *file2_cuts;

  extern TH2F  *phi_theta_rich[9];
  
  extern TCutG *pEpS0, *pEpS1, *pEmS0, *pEmS1;
  extern TCutG *pEm1S0, *pEm1S1, *pEm2S0, *pEm2S1;
  extern TCutG *pEp1S0, *pEp1S1, *pEp2S0, *pEp2S1;
  extern TCutG *pvertex_xy, *pvertex_xz, *pvertex_yz;

  extern Bool_t NoLeptonE1;
  extern Bool_t NoHadronE1;
  extern Bool_t NoLeptonE2;
  extern Bool_t NoHadronE2;

  extern Bool_t Electron;
  extern Bool_t Positron;

  extern Bool_t Electron1;
  extern Bool_t Electron2;
  extern Bool_t Positron1;
  extern Bool_t Positron2;

  extern Bool_t ElectronPositron;
  extern Bool_t ElectronElectron;
  extern Bool_t PositronPositron;

  extern TLorentzVector *e1;
  extern TLorentzVector *e2;
  extern TLorentzVector *beam;
  extern TLorentzVector *proj;
  extern TLorentzVector *targ;
  extern TLorentzVector *gammae1e2;
  extern TLorentzVector *e1e2;
  extern TLorentzVector *e1e2_miss;
  extern TLorentzVector *e1_delta;
  extern TLorentzVector *e2_delta;
  extern  TLorentzVector *l_proton;
  extern TLorentzVector *l_pion;
  extern TLorentzVector *gamma_protonpion;
 
  
  extern Int_t insideTarget;

  extern Int_t insideEmS0;
  extern Int_t insideEmS1;
  extern Int_t insideEpS0;
  extern Int_t insideEpS1;

  extern Int_t insideEm1S0;
  extern Int_t insideEm1S1;
  extern Int_t insideEm2S0;
  extern Int_t insideEm2S1;

  extern Int_t insideEp1S0;
  extern Int_t insideEp1S1;
  extern Int_t insideEp2S0;
  extern Int_t insideEp2S1;

  extern const double D2R;
  extern const double R2D;


  /************************* M E T H O D S *************************************/

  double openingangle(const TLorentzVector& a, const TLorentzVector& b);
  double openingangle(const TVector3& a, const TVector3& b);
  void normalize(TH1* hist);
  void format(TH1* hist,double size=0.9);
  TH1* signal(const char* name, TH1* hist, TH1* back1, TH1* back2);
  double parametrization(double y);
  double trackDistance(double r1, double z1, TVector3 v1, double r2, double z2, TVector3 v2);
  TVector3 vertex(double z1,double r1,TVector3 vec1, double z2,double r2,TVector3 vec2);
}

/*********************************************************************************************/


#endif // DATA_H
