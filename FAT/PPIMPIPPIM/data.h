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
  extern HNtuple *tlo, *n_out, *n_ppim;
  extern HFilter *filter;
  extern float EFF, ACC;
  extern int event_number, event_mult;
  //PPimPipPim*******************************
  extern TH2F *p_p_beta, *pim_p_beta, *pip_p_beta;
  extern TH1F *p_pim_mass, *p_mass, *pim_mass;


  extern TH1F *p_pim1_mass, *p_pim2_mass, *pim_pip_mass,*pim1_pip_mass,*pim2_pip_mass, *p_pim_pip_pim_mass;
  extern TH2F *dist_p_pim_pim_pip;
  extern TH2F *ver_pip_lambda;
  extern TH1F *dist_p_pim, *dist_pim_pip;

  extern TH1F *sum_dist_1, *sum_dist_2, *sum_dist_diff;

  extern TH1F *DL_p_pim1_mass, *DL_p_pim2_mass, *DL_pim_pip_mass,*DL_pim1_pip_mass,*DL_pim2_pip_mass, *DL_p_pim_pip_pim_mass;
  extern TH1F *DL_dist_p_pim, *DL_dist_pim_pip;
  extern TH2F *DL_dist_p_pim_pim_pip;
  extern TH1F *DL_p_pim_mass, *DL_p_mass, *DL_pim_mass, *DL_in_target;

  extern TH1F *chi_p_pim_mass, *chi_pip_pim_mass, *chi_final_mass;
  extern TH2F *chi_lambda_vertex;

  extern TH1F *LM_chi_p_pim_mass, *LM_chi_pip_pim_mass, *LM_chi_final_mass;
  extern TH2F *LM_chi_lambda_vertex;

  extern TH1F *DML_p_pim1_mass, *DML_p_pim2_mass, *DML_pim_pip_mass,*DML_pim1_pip_mass,*DML_pim2_pip_mass, *DML_p_pim_pip_pim_mass;
  extern TH1F *DML_dist_p_pim, *DML_dist_pim_pip;
  extern TH2F *DML_dist_p_pim_pim_pip;
  extern TH1F *DML_p_pim_mass, *DML_p_mass, *DML_pim_mass;

  extern TH1F *DL_target_z, *DL_target_z_diff, *DL_pip_z;
  extern TH1F *DL_pim_pip_z;

  extern TH1F *signal_fit[10][10];

  extern TH2F *vertex_lambda, *vertex_target, *DL_vertex_lambda, *DL_vertex_target, *DLM_vertex_lambda, *DLM_vertex_target;

  //*****************************************

  extern TCutG *pEpS0, *pEpS1, *pEmS0, *pEmS1;
  extern TCutG *pEm1S0, *pEm1S1, *pEm2S0, *pEm2S1;
  extern TCutG *pEp1S0, *pEp1S1, *pEp2S0, *pEp2S1;
  extern TCutG *pvertex_xy, *pvertex_xz, *pvertex_yz;

  extern Bool_t NoLeptonP;
  extern Bool_t NoHadronP;
  extern Bool_t NoLeptonPI;
  extern Bool_t NoHadronPI;

  extern Bool_t Electron;
  extern Bool_t Positron;

  extern Bool_t Electron1;
  extern Bool_t Electron2;
  extern Bool_t Positron1;
  extern Bool_t Positron2;

  extern Bool_t ElectronPositron;
  extern Bool_t ElectronElectron;
  extern Bool_t PositronPositron;

  extern TLorentzVector *p;
  extern TLorentzVector *pi, *pim1, *pim2, *pim, *pip;
  extern TLorentzVector *beam, *miss;
  extern TLorentzVector *proj;
  extern TLorentzVector *targ;
  extern TLorentzVector *gammappi;
  extern TLorentzVector *gammappip;
  extern TLorentzVector *gammappim1;
  extern TLorentzVector *gammappim2;
  extern TLorentzVector *gammapim2pip;
  extern TLorentzVector *gammapim1pip;
  extern TLorentzVector *gammappim1pippim2;
  extern TLorentzVector *ppi;
  extern TLorentzVector *ppi_miss;
  extern TLorentzVector *p_delta;
  extern TLorentzVector *pi_delta;

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
  double trackDistance(double r1, double z1, TLorentzVector v1, double r2, double z2, TLorentzVector v2);
  TVector3 vertex(double r1,double z1,TLorentzVector vec1, double r2,double z2,TLorentzVector vec2);
  double getR(TVector3 vec);
  double trackToPoint(TVector3 base,TVector3 dir, TVector3 point);
}

/*********************************************************************************************/


#endif // DATA_H
