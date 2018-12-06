#include "data.h"
#include <TVector3.h>
#include <hgeomvector.h>
#include <hparticletool.h>  
//#include <hgeomvector.h>
/**************************** Global histograms repository ***********************************/


namespace PATData
{

  TFile         *outFileData;

  HNtuple       *tlo;

  HFilter       *filter;
  float         EFF, ACC;

  //PPimPipPim*******************************
  TH2F *p_p_beta, *pim_p_beta, *pip_p_beta;
  TH1F *p_pim_mass, *p_mass, *pim_mass;

  
  TH1F *p_pim1_mass, *p_pim2_mass, *pim_pip_mass,*pim1_pip_mass,*pim2_pip_mass, *p_pim_pip_pim_mass;
  TH2F *dist_p_pim_pim_pip;
  TH2F *ver_pip_lambda;
  TH1F *dist_p_pim, *dist_pim_pip;

  TH1F *sum_dist_1, *sum_dist_2, *sum_dist_diff;

  TH1F *DL_p_pim1_mass, *DL_p_pim2_mass, *DL_pim_pip_mass,*DL_pim1_pip_mass,*DL_pim2_pip_mass, *DL_p_pim_pip_pim_mass;
  TH1F *DL_dist_p_pim, *DL_dist_pim_pip;
  TH2F *DL_dist_p_pim_pim_pip;
  TH1F *DL_p_pim_mass, *DL_p_mass, *DL_pim_mass, *DL_in_target;

  TH1F *chi_p_pim_mass, *chi_pip_pim_mass, *chi_final_mass;
  TH2F *chi_lambda_vertex;

  TH1F *LM_chi_p_pim_mass, *LM_chi_pip_pim_mass, *LM_chi_final_mass;
  TH2F *LM_chi_lambda_vertex;
  
  TH1F *DML_p_pim1_mass, *DML_p_pim2_mass, *DML_pim_pip_mass,*DML_pim1_pip_mass,*DML_pim2_pip_mass, *DML_p_pim_pip_pim_mass;
  TH1F *DML_dist_p_pim, *DML_dist_pim_pip;
  TH2F *DML_dist_p_pim_pim_pip;
  TH1F *DML_p_pim_mass, *DML_p_mass, *DML_pim_mass;

  TH1F *DL_target_z, *DL_target_z_diff, *DL_pip_z;
  TH1F *DL_pim_pip_z;

  TH1F *signal_fit[10][10];

  TH2F *vertex_lambda, *vertex_target, *DL_vertex_lambda, *DL_vertex_target, *DLM_vertex_lambda, *DLM_vertex_target;
  //***************************************** 

  TFile *filp_cuts, *filpi_cuts;

  TCutG *pEpS0, *pEpS1, *pEmS0, *pEmS1;
  TCutG *pEm1S0, *pEm1S1, *pEm2S0, *pEm2S1;
  TCutG *pEp1S0, *pEp1S1, *pEp2S0, *pEp2S1;
  TCutG *pvertex_xy, *pvertex_xz, *pvertex_yz;

  Bool_t NoLeptonP;
  Bool_t NoHadronP;
  Bool_t NoLeptonPI;
  Bool_t NoHadronPI;

  Bool_t Electron;
  Bool_t Positron;

  Bool_t Electron1;
  Bool_t Electron2;
  Bool_t Positron1;
  Bool_t Positron2;

  Bool_t ElectronPositron;
  Bool_t ElectronElectron;
  Bool_t PositronPositron;

  TLorentzVector *p;
  TLorentzVector *pi, *pim, *pim1, *pim2, *pip;
  TLorentzVector *beam;
  TLorentzVector *proj;
  TLorentzVector *targ;
  TLorentzVector *gammappi;
  TLorentzVector *gammappim1;
  TLorentzVector *gammappim2;
  TLorentzVector *gammapim1pip;
  TLorentzVector *gammapim2pip;
  TLorentzVector *gammappim1pippim2;
  
  TLorentzVector *ppi;
  TLorentzVector *ppi_miss;
  TLorentzVector *p_delta;
  TLorentzVector *pi_delta;
  TLorentzVector *miss;
  
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

  TVector3 trackToPoint(TVector3 base,TVector3 dir, TVector3 point)
  {
    HGeomVector point1, dir1, base1, res;
    TVector3 res1;
    point1.setXYZ(point.X(), point.Y(), point.Z());
    dir1.setXYZ(dir.X(), dir.Y(), dir.Z());
    base1.setXYZ(base.X(), base.Y(), base.Z());

    //cout<<"direction vec: "<<dir1.X()<<" "<<dir1.Y()<<" "<<dir1.Z()<<" "<<endl;
    HParticleTool p_tool;
    res=p_tool.calculatePointOfClosestApproachStraightToPoint(base1, dir1, point1);
    //cout<<res.X()<<" "<<res.Z()<<endl;
    res1.SetXYZ(res.X(),res.Y(),res.Z());
    return res1;

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

  double getR(TVector3 vec)
  {
    return TMath::Sqrt(vec.X()*vec.X()+vec.Y()*vec.Y());
  }
}

/*********************************************************************************************/

