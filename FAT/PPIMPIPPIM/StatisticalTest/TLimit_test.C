#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TFile.h>
#include <TConfidenceLevel.h>
#include <TLimitDataSource.h>
#include <TF1.h>
#include <iostream>
#include <TMath.h>
#include <TLimit.h>
#include <TGraph.h>
#include <TSystem.h>

using namespace std;

double calcchi2(TH1F* hist, TF1* fuc, double xmin=0, double xmax=-1)
{
  int nbin=0;
  int binmin=0;
  int binmax=0;
  double chi2=0;
  if(xmax>xmin)
    {
      binmax=hist->FindBin(xmax);
      binmin=hist->FindBin(xmin);
      nbin=binmax-binmin+1;
      //cout<<"Calculate bin min and max from arguments"<<endl;
      //cout<<"binmin: "<<binmin<<" binmax: "<<binmax<<" nbin: "<<nbin<<endl;
    }
  else
    {
      binmin=0;
      binmax=hist->GetNbinsX()-1;
      nbin=hist->GetNbinsX();
      //cout<<"Calculate bin min and max automaticly"<<endl;
      //cout<<"binmin: "<<binmin<<" binmax: "<<binmax<<" nbin: "<<nbin<<endl;
    }

  for(int i=binmin;i<binmax;i++)
    {
      double chi2_i=TMath::Power(hist->GetBinContent(i)-fuc->Eval((hist->GetBinCenter(i))),2);
      double sigma2=hist->GetBinContent(i)+fuc->Eval((hist->GetBinCenter(i)));
      chi2=chi2+chi2_i/sigma2;
    }
  return (chi2/(nbin-1));
}

double calcchi2( TF1* fuc, TH1F* hist, double xmin=0, double xmax=-1)
{
  return calcchi2(hist, fuc, xmin, xmax);
}


void TLimit_test()
{
  TCanvas* cTLimit=new TCanvas("cTLimit");
  //TCanvas* cFit1116=new TCanvas("cFit1116");
  TFile* infile=new TFile("Event.root","READ");
  double chi2;
  TH1F* sh=(TH1F*)infile->Get("signal");
  sh->Scale(1);
  TH1F* bh=(TH1F*)infile->Get("background");
  TH1F* dh=(TH1F*)infile->Get("data");
  //TH1F* l1116=(TH1F*)infile->Get("oryginal_spectrum");

  /*
  cFit1116->cd();
  
  TF1* fVoigt_bg= new TF1("fVoigt_bg","[0]*TMath::Voigt(x-[1],[2],[3])+pol5(4)",1090.00,1156.67);
  TF1* fVoigt= new TF1("fVoigt","[0]*TMath::Voigt(x-[1],[2],[3])",1090.00,1156.67);
  TF1* fbg= new TF1("fbg","pol5(4)",1090.00,1156.67);

  fVoigt_bg->SetParameters(13406.8,1114.78,0.1819,15.63,-53756.9,9.35043,0.0342083,3.07071e-5,7.00426e-9,-3.02549e-11);
  l1116->Fit(fVoigt_bg,"R");
  fVoigt_bg->SetRange(1080,1165);
  //l1116->Fit(fVoigt_bg,"R");
  l1116->Draw();
  fbg->SetParameters(fVoigt_bg->GetParameter(4),fVoigt_bg->GetParameter(5),fVoigt_bg->GetParameter(6),fVoigt_bg->GetParameter(7),fVoigt_bg->GetParameter(8),fVoigt_bg->GetParameter(9));
  fVoigt->SetParameters(fVoigt_bg->GetParameter(0),fVoigt_bg->GetParameter(1),fVoigt_bg->GetParameter(2),fVoigt_bg->GetParameter(3));
  fVoigt->Draw("same");
  fVoigt->SetLineColor(kGreen);
  fbg->Draw("same");
  fbg->SetLineColor(kBlue);
  */
  
  cTLimit->cd();    
  sh->Sumw2();
  bh->Sumw2();
  dh->Sumw2();
  

  TLimitDataSource* mydatasource = new TLimitDataSource(sh,bh,dh);
  TConfidenceLevel *myconfidence = TLimit::ComputeLimit(mydatasource,100000);

  std::cout << "  CLs    : " << myconfidence->CLs()  << std::endl;
  std::cout << "  CLsb   : " << myconfidence->CLsb() << std::endl;
  std::cout << "  CLb    : " << myconfidence->CLb()  << std::endl;
  std::cout << "< CLs >  : " << myconfidence->GetExpectedCLs_b()  << std::endl;
  std::cout << "< CLsb > : " << myconfidence->GetExpectedCLsb_b() << std::endl;
  std::cout << "< CLb >  : " << myconfidence->GetExpectedCLb_b()  << std::endl;

 
  myconfidence->Draw();

  //chi2 test
  TCanvas* cChi2=new TCanvas("cChi2");
  cChi2->Divide(2);
  cChi2->cd(1);
  double fit_min=1440;
  double fit_max=1600;
  int amp_steps=1000;
  TGraph* chi2_vs_ampl=new TGraph(amp_steps);
  
  TF1* bg=new TF1("bg","pol3(0)",fit_min,fit_max);

  dh->Fit(bg,"r");

  chi2 = calcchi2(bg,dh,fit_min,fit_max);
  cout<<"chi2 by my program= "<<chi2<<endl;

  //amplitude scan

  for(int j = 0; j<amp_steps+1;j++)
    {
      //TF1* bg_sig=new TF1("bg_sig","pol3(3)+[0]*exp(-0.5*((x-[1])/[2])**2)",fit_min,fit_max);
      TF1* bg_sig=new TF1("bg_sig","pol3(0)+[4]*TMath::BreitWigner(x,1519.5,15.6)",fit_min,fit_max);
      //bg_sig->SetParameters(j,1520,16,bg->GetParameter(0),bg->GetParameter(1),bg->GetParameter(2),bg->GetParameter(3));
      bg_sig->SetParameters(bg->GetParameter(0),bg->GetParameter(1),bg->GetParameter(2),bg->GetParameter(3),j);
      //bg_sig->Draw();
      double chi2_l=calcchi2(bg_sig,dh,fit_min,fit_max);
      chi2_vs_ampl->SetPoint(j,j,chi2_l);
    }

  cChi2->cd(2);
  chi2_vs_ampl->Draw("A*");   
  //delete myconfidence;
  //delete mydatasource;
  //infile->Close(); 

}
