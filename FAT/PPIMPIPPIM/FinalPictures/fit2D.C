#include "TH2D.h"
#include "TF2.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TRandom3.h"
#include "TVirtualFitter.h"
#include "TList.h"

#include <iostream>

double gauss2D(double *x, double *par)
{
  double z1 = double((x[0]-par[1])/par[2]);
  double z2 = double((x[1]-par[3])/par[4]);
  return par[0]*exp(-0.5*(z1*z1+z2*z2));
}

double my2Dfunc(double *x, double *par)
{
  return gauss2D(x,&par[0]);
}

int fit2D()
{

  int xlow2=1100;
  int xup2=1130;
  int ylow2=460;
  int yup2=530;
  
  TF2 * func = new TF2("func",my2Dfunc,xlow2,xup2,ylow2,yup2, 5);
  func->SetParameter(0,53);
  func->SetParameter(1,1116);
  func->SetParameter(2,3);
  func->SetParameter(3,490);
  func->SetParameter(4,3);
  
  TFile *f = new TFile("pictures.root","R");
  f.ls();

  TH2F * h2 = (TH2F*)f->Get("h2_m_inv");
  h2->Draw("colz");
  h2->Sumw2();

  // fit independently
  //->Fit(func);
  h2->Fit(func,"R");
  

  // Create a new canvas.
  TCanvas * c2 = new TCanvas("c2","Two HIstogram Fit example",100,10,900,800);
  c2->Divide(2);
  gStyle->SetOptFit();
  gStyle->SetStatY(0.6);

  c2->cd(1);
  //h1->Draw();
  //func->SetRange(xlow1,ylow1,xup1,yup1);
  //func->DrawCopy("cont1 same");
  //c2->cd(2);
  //h1->Draw("lego");
  //func->DrawCopy("surf1 same");
  //c2->cd(3);
  //func->SetRange(xlow2,ylow2,xup2,yup2);
  h2->Draw();
  func->DrawCopy("cont1 same");
  c2->cd(2);
  h2->Draw("lego");
  gPad->SetLogz();
  func->Draw("surf1 same");

  return 0;

}
