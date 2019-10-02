#define createHistos_cxx
#include "createHistos.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TGraphErrors.h>
#include <TH1F.h>
#include <TFile.h>
#include <iostream>
#include <TF1.h>

using namespace std;

void createHistos::Loop()
{
  //   In a ROOT session, you can do:
  //      root> .L createHistos.C
  //      root> createHistos t
  //      root> t.GetEntry(12); // Fill t data members with entry number 12
  //      root> t.Show();       // Show values of entry 12
  //      root> t.Show(16);     // Read and show values of entry 16
  //      root> t.Loop();       // Loop on all entries
  //

  //     This is the loop skeleton where:
  //    jentry is the global entry number in the chain
  //    ientry is the entry number in the current Tree
  //  Note that the argument to GetEntry must be:
  //    jentry for TChain::GetEntry
  //    ientry for TTree::GetEntry and TBranch::GetEntry
  //
  //       To read only selected branches, Insert statements like:
  // METHOD1:
  //    fChain->SetBranchStatus("*",0);  // disable all branches
  //    fChain->SetBranchStatus("branchname",1);  // activate branchname
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return;
  const int bin=200*2;
  const int xmin=1000;
  const int xmax=2000;
  const int nsignal=20;
  double sidebandmin=10;
  double sidebandmax=20;
  int step;
  TH1F* signal=new TH1F("signal","signal simulated from gaus",bin,xmin,xmax);
  TH1F* background=new TH1F("background","background from side-band;M^{inv}_{p #pi- #pi+ #pi-}[MeV]",bin,xmin,xmax);
  TH1F* data=new TH1F("data","data from experiment;M^{inv}_{p #pi- #pi+ #pi-}[MeV]",bin,xmin,xmax);
  TH1F* oryginal_spectrum=new TH1F("oryginal_spectrum","oryginal spectrum for side-band;M^{inv}_{p #pi- #pi+ #pi-}[MeV]",bin*6,xmin,xmax);
  TGraphErrors* resi=new TGraphErrors(bin);
  TF1* background_fit=new TF1("background_fit","pol2(0)",1000,1200);   

  TFile *MyFile = new TFile("temp2.root","recreate");
 
  Long64_t nentries = fChain->GetEntries();
  Long64_t nbytes = 0, nb = 0;
  step =(int)nentries/15;

  for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
      Long64_t ientry = LoadTree(jentry);
      if(jentry%step==0)
	cout<<"Progresss: "<<(double)jentry/nentries<<endl;
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if(isBest_new!=1
	 ||mlp_output<0.58
	 //||miss_mass_kp<1350
	 ||m_inv_pip_pim>410
	 ||dist_ver_to_ver<25
	 ||(oa_lambda>10 && oa_lambda<170)
	 //||dist_pip_pim>15
	 //||dist_pip_pim>150
	 //||ver_p_pim_z<-5
	 //||dist_ver_to_ver<14
	 )
	continue;

      oryginal_spectrum->Fill(m_inv_p_pim);
      
      if(m_inv_p_pim<1116+sidebandmin && m_inv_p_pim>1116-sidebandmin)
	data->Fill(m_inv_p_pim_pip_pim);

      if((m_inv_p_pim<1116.-sidebandmin && m_inv_p_pim>1116.-sidebandmax)
	 ||(m_inv_p_pim>1116.+sidebandmin && m_inv_p_pim<1116.+sidebandmax))
	background->Fill(m_inv_p_pim_pip_pim);
    }

  //normalize background to signal
  TCanvas* cFit1116=new TCanvas("cFit1116");
  cFit1116->cd();

  oryginal_spectrum->Sumw2();
   
  TF1* fVoigt_bg= new TF1("fVoigt_bg","[0]*TMath::Voigt(x-[1],[2],[3])+pol5(4)",1090.00,1156.67);
  TF1* fVoigt= new TF1("fVoigt","[0]*TMath::Voigt(x-[1],[2],[3])",1090.00,1156.67);
  TF1* fbg= new TF1("fbg","pol5(0)",1090.00,1156.67);

  fVoigt_bg->SetParameters(527.3,1114,2.73,1,-9266,1.7,0.0061,5.51379e-6,1.23803e-9,-5.64175e-12);
  fVoigt_bg->SetParLimits(3,0,2);
  fVoigt_bg->SetParLimits(1,1112,1117);
  fVoigt_bg->SetRange(1106,1121);
  oryginal_spectrum->Fit(fVoigt_bg,"R");
  fVoigt_bg->SetRange(1100,1126);
  oryginal_spectrum->Fit(fVoigt_bg,"R");
  fVoigt_bg->SetRange(1092,1137);
  oryginal_spectrum->Fit(fVoigt_bg,"R");
  fVoigt_bg->SetRange(1088,1141); 
  oryginal_spectrum->Fit(fVoigt_bg,"R");
  fVoigt_bg->SetRange(1082,1141); 
  oryginal_spectrum->Fit(fVoigt_bg,"R");


  oryginal_spectrum->Draw();
  fbg->SetParameters(fVoigt_bg->GetParameter(4),fVoigt_bg->GetParameter(5),fVoigt_bg->GetParameter(6),fVoigt_bg->GetParameter(7),fVoigt_bg->GetParameter(8),fVoigt_bg->GetParameter(9));
  fVoigt->SetParameters(fVoigt_bg->GetParameter(0),fVoigt_bg->GetParameter(1),fVoigt_bg->GetParameter(2),fVoigt_bg->GetParameter(3));
  fVoigt->Draw("same");
  fVoigt->SetLineColor(kGreen);
  fbg->Draw("same");
  fbg->SetLineColor(kBlue);
   
  double intS=fVoigt->Integral(1116-sidebandmin,1116+sidebandmin)/oryginal_spectrum->GetBinWidth(1);
  double intB=fbg->Integral(1116-sidebandmin,1116+sidebandmin)/oryginal_spectrum->GetBinWidth(1);
  double intsideband=(fbg->Integral(1116-sidebandmax,1116-sidebandmin)+fbg->Integral(1116+sidebandmin,1116+sidebandmax))/oryginal_spectrum->GetBinWidth(1);
  double intAll=fVoigt_bg->Integral(1116-sidebandmin,1116+sidebandmin)/oryginal_spectrum->GetBinWidth(1);
  
  cout<<"signal integral: "<<intS<<endl<<"beckground integral: "<<intB<<endl<<"sideband integral: "<<intsideband<<endl;
  cout<<"all in signal range: "<<intAll<<endl;

  background->Scale(intB/intsideband);

  //Fill random signal
  //TF1* L1520Spectral=new TF1("L1520Spectral","100*exp(-0.5*((x-1520)/16)**2)",xmin,xmax);
  TF1* L1520Spectral=new TF1("L1520Spectral","TMath::BreitWigner(x,1519.5,15.6)",xmin,xmax);
  signal->FillRandom("L1520Spectral",10000);

  signal->Scale((double)nsignal/10000);
  //Calculate residuals
  for(int i=0;i<bin;i++)
    {
      resi->SetPoint(i,background->GetBinCenter(i),data->GetBinContent(i)-background->GetBinContent(i));
      resi->SetPointError(i,background->GetBinWidth(i),TMath::Sqrt(TMath::Power(data->GetBinError(i),2)+TMath::Power(background->GetBinError(i),2)));
    }

  cFit1116->Write();
  fVoigt->Write();
  fbg->Write();
  fVoigt_bg->Write();
  resi->Write();
  signal->Write();
  background->Write();
  data->Write();
  oryginal_spectrum->Write();
  MyFile->Close();
}
