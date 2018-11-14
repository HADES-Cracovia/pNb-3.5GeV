#include "data.h"
#include <TVector3.h>
#include <hgeomvector.h>
#include <hparticletool.h>

/**************************** global histograms repository ***********************************/

namespace PATData
{
  TFile         *outFileData;
  HNtuple       *tlo;
  HFilter       *filter;
  float         EFF, ACC;
  TH1F          *oa_corr;
  TH1F          *em_mom, *em_mom_bt,*ep_mom, *ep_mom_bt;
  TH1F          *SIGNAL, *CB, *SIGNIFICANCE;
  TH1F          *sig_all, *sig_all_bt, *sig_all_back1, *sig_all_back2, *sig_OK, *sig_bt_OK;
  TH1F          *miss_all, *miss_all_back1, *miss_all_back2, *miss_OK;
  TH1F          *sig_all_var, *sig_all_var_bt, *sig_all_var_back1, *sig_all_bt_back1, *sig_all_var_bt_back1, *sig_all_var_back2, *sig_var_OK, *sig_var_bt_OK, *sig_all_bt_back2, *sig_all_var_bt_back2;
  TH1F          *sig_all_var2, *sig_all_var2_back1, *sig_all_var2_back2, *sig_var2_OK;
  TH1F          *cos_ep, *cos_em, *cos_sum;
  TH1F          *cos_ep_cm, *cos_back1_cm, *cos_back2_cm,*cos_ep_cm_OK;
  TH1F          *cos_ep_back1, *cos_em_back1, *cos_sum_back1;
  TH1F          *cos_ep_back2, *cos_em_back2, *cos_sum_back2;
  TH1F          *cos_ep_OK, *cos_em_OK, *cos_sum_OK;
  TH1F          *rapidity_all, *rapidity_back1, *rapidity_back2, *rapidity_OK;
  TH1F          *rapidity_140_all, *rapidity_140_back1, *rapidity_140_back2, *rapidity_140_OK;
  TH1F          *pt_all, *pt_back1, *pt_back2, *pt_OK;
  TH1F          *pt_140_all, *pt_140_back1, *pt_140_back2, *pt_140_OK;
  TH1F          *pureBT_signal, *pureBT_signal_OK, *pureBT_signal_back1, *pureBT_signal_back2;
  TH1F          *pureBT_signal_var, *pureBT_signal_OK_var, *pureBT_signal_back1_var, *pureBT_signal_back2_var;
  TH2F          *ep_beta_mom, *em_beta_mom,*ep_beta_mom_bt, *em_beta_mom_bt, *pureBT_beta_mom;
  TH1F *momentum_spectrum, *momentum_spectrum_bt, *momentum_spectrum_pureBT;
  TH1F          *sig_rf_and_bt,*sig_rf_and_bt_OK,*sig_rf_and_bt_back1,*sig_rf_and_bt_back2;
  TH1F      *sig_to_bg_var, *sig_to_bg_bt_var, *sig_to_bg_pureBT_var;
  TH1F          *sig_rf_and_bt_var,*sig_rf_and_bt_OK_var,*sig_rf_and_bt_back1_var,*sig_rf_and_bt_back2_var;
  TH1F          *sig_sum,*sig_sum_var;
  TH1F      *sig_all_var_back, *sig_all_var_bt_back, *pureBT_signal_back_var;

  TH1F *dist_pim_p, *m_pim_p ;

  TH1I          *bt_rf_stat, *bt_rf_stat_pi,*bt_rf_stat_back1, *bt_rf_stat_back2, *bt_rf_stat_OK,*bt_rf_stat_pi_back1, *bt_rf_stat_pi_back2, *bt_rf_stat_pi_OK;
  TH3F      *rf_freedom;
  TH2F      *rf_f_dtheta, *rf_f_dphi;
  TH2F      *q_vs_p_leptons_RF,*q_vs_p_leptons_BT; 
  TH2F *phi_theta_rich[9];
 
  TFile *file1_cuts, *file2_cuts;

  TCutG *pEpS0, *pEpS1, *pEmS0, *pEmS1;
  TCutG *pEm1S0, *pEm1S1, *pEm2S0, *pEm2S1;
  TCutG *pEp1S0, *pEp1S1, *pEp2S0, *pEp2S1;
  TCutG *pvertex_xy, *pvertex_xz, *pvertex_yz;

  Bool_t NoLeptonE1;
  Bool_t NoHadronE1;
  Bool_t NoLeptonE2;
  Bool_t NoHadronE2;

  Bool_t Electron;
  Bool_t Positron;

  Bool_t Electron1;
  Bool_t Electron2;
  Bool_t Positron1;
  Bool_t Positron2;

  Bool_t ElectronPositron;
  Bool_t ElectronElectron;
  Bool_t PositronPositron;

  TLorentzVector *e1;
  TLorentzVector *e2;
  TLorentzVector *beam;
  TLorentzVector *proj;
  TLorentzVector *targ;
  TLorentzVector *gammae1e2;
  TLorentzVector *e1e2;
  TLorentzVector *e1e2_miss;
  TLorentzVector *e1_delta;
  TLorentzVector *e2_delta;
  TLorentzVector *l_proton;
  TLorentzVector *l_pion;
  TLorentzVector *gamma_protonpion;
  
  Int_t insideTarget;

  Int_t insideEmS0;
  Int_t insideEmS1;
  Int_t insideEpS0;
  Int_t insideEpS1;

  Int_t insideEm1S0;
  Int_t insideEm1S1;
  Int_t insideEm2S0;
  Int_t insideEm2S1;

  Int_t insideEp1S0;
  Int_t insideEp1S1;
  Int_t insideEp2S0;
  Int_t insideEp2S1;

  const double D2R = 1.74532925199432955e-02;
  const double R2D = 57.2957795130823229;


  /************************* M E T H O D S *************************************/

  double openingangle(const TLorentzVector& a, const TLorentzVector& b)
  {
    return TMath::ACos( (a.Px()*b.Px() + a.Py()*b.Py() +  a.Pz()*b.Pz() ) / ( a.Vect().Mag() * b.Vect().Mag() ) );
  }

  double openingangle(const TVector3& a, const TVector3& b)
  {
    return TMath::ACos( (a.Px()*b.Px() + a.Py()*b.Py() +  a.Pz()*b.Pz() ) / ( a.Mag() * b.Mag() ) );
  }


  void normalize(TH1* hist)
  {
    for (Int_t j=1; j<hist->GetNbinsX()+1; ++j)
      {
	hist->SetBinContent( j, hist->GetBinContent(j) / hist->GetBinWidth(j) );
	//         hist->SetBinError( j, TMath::Sqrt( hist->GetBinContent(j) ) );
	hist->SetBinError( j, hist->GetBinError(j) / hist->GetBinWidth(j) );
      }
  }

  void format(TH1* hist, double size)
  {
    hist->SetMarkerSize(size);
    hist->SetMarkerColor(hist->GetLineColor());
    hist->SetMarkerStyle(20);
  }

  TH1* signal(const char* name, TH1* hist, TH1* back1, TH1* back2)
  {
    TH1 *ptr = (TH1*)hist->Clone(name);
    for (Int_t j=1; j<hist->GetNbinsX()+1; ++j)
      {
	ptr->SetBinContent(j, hist->GetBinContent(j) - back1->GetBinContent(j) - back2->GetBinContent(j));
	//ptr->SetBinContent(j, hist->GetBinContent(j) - 2*TMath::Sqrt(back1->GetBinContent(j)*back2->GetBinContent(j)));
	ptr->SetBinError(j, TMath::Sqrt( hist->GetBinError(j)*hist->GetBinError(j) + 
					 back1->GetBinError(j)*back1->GetBinError(j) + 
					 back2->GetBinError(j)*back2->GetBinError(j) ));
      }

    return ptr;
  }
  double parametrization(double y)
  {
    double a=3./40.;
    double b=-50;
    //return (a*y + b);
    return (-40.0-(0.0583*y)+(0.000208333*y*y));
  }
  double trackDistance(double r1, double z1, TVector3 v1, double r2, double z2, TVector3 v2)
  {
    double dist;
    HGeomVector base_1, base_2, dir_1, dir_2;
    HParticleTool p_tool;

    p_tool.calcSegVector(z1,r1,v1.Phi(),v1.Theta(),base_1,dir_1);
    p_tool.calcSegVector(z2,r2,v2.Phi(),v2.Theta(),base_2,dir_2);

    dist=p_tool.calculateMinimumDistance(base_1,dir_1,base_2,dir_2);

    return dist;
  }

  TVector3 vertex(double z1,double r1,TVector3 vec1, double z2,double r2,TVector3 vec2)
  {
    TVector3 out;
    HGeomVector ver;
    HGeomVector base_1, base_2, dir_1, dir_2;
    HParticleTool p_tool;

    p_tool.calcSegVector(z1,r1,vec1.Phi(),vec1.Theta(),base_1,dir_1);
    p_tool.calcSegVector(z2,r2,vec2.Phi(),vec2.Theta(),base_2,dir_2);
    ver=p_tool.calcVertexAnalytical(base_1,dir_1,base_2,dir_2);
    out.SetXYZ(ver.X(),ver.Y(),ver.Z());
    return out; 
  }



}

/*********************************************************************************************/

