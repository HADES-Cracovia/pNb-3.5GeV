
#define EventMixing_cxx
#include "EventMixing.h"
#include <TH2.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TVector3.h>
#include <iostream>
#include "hntuple.h"

void EventMixing::Loop(char*  output)
{
  //   In a ROOT session, you can do:
  //      Root > .L EventMixing.C
  //      Root > EventMixing t
  //      Root > t.GetEntry(12); // Fill t data members with entry number 12
  //      Root > t.Show();       // Show values of entry 12
  //      Root > t.Show(16);     // Read and show values of entry 16
  //      Root > t.Loop();       // Loop on all entries
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

  TFile* outFileData = new TFile(output,"recreate");
  if(outFileData!=0)
    std::cout<<"Output file created: "<<output<<endl;
  TLorentzVector p, pim1, pip, pim2, l1116, l1520;
  const int bin=250;
  const int xmin=1000;
  const int xmax=2000;
  TH1F* h_m_inv_p_pim=new TH1F("h_m_inv_p_pim","A #Lambda(1116) invariant mass; M_{p #pi^{-}[MeV]};N",bin*2,xmin,xmax);
  TH1F* h_m_inv_p_pim_pip_pim_signal=new TH1F("h_m_inv_p_pim_pip_pim_signal","A #Lambda(1520) invariant mass from event mixing for signal; M_{p #pi^{-} #pi^{+} #pi^{-} [MeV]};N",bin,xmin,xmax);
  TH1F* h_m_inv_p_pim_pip_pim_SB=new TH1F("h_m_inv_p_pim_pip_pim_SB","A #Lambda(1520) invariant mass from event mixing for SB; M_{p #pi^{-} #pi^{+} #pi^{-} [MeV]};N",bin,xmin,xmax);
  bool isL=false;
  bool isK0=false;
  double sidebandmin=10;
  double sidebandmax=22;
  const double D2R = 1.74532925199432955e-02;
  const double R2D = 57.2957795130823229;

  
  Long64_t nentries = fChain->GetEntries();
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      if(jentry%50000==0)
	cout<<(double)jentry/nentries *100<<"%"<<endl;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if(!isK0 && isL)
	{
	  if(Cut(ientry) && hypothesis==1)
	    {
	      double F = 1.006;
	      //double F=1;
	      TVector3 v1, v2;
	      v1.SetXYZ(F*pip_p*sin(D2R*pip_theta)*cos(D2R*pip_phi),F*pip_p*sin(D2R*pip_theta)*sin(D2R*pip_phi),F*pip_p*cos(D2R*pip_theta));
	      v2.SetXYZ(F*pim2_p*sin(D2R*pim2_theta)*cos(D2R*pim2_phi),F*pim2_p*sin(D2R*pim2_theta)*sin(D2R*pim2_phi),F*pim2_p*cos(D2R*pim2_theta));
	      pip.SetVectM( v1, 139.57018 );
	      pim2.SetVectM( v2, 139.57018 );
	      isK0=true;
	    }
	  if(Cut(ientry) && hypothesis==2)
	    {
	      double F = 1.006;
	      //double F=1;
	      TVector3 v1, v2;
	      v1.SetXYZ(F*pip_p*sin(D2R*pip_theta)*cos(D2R*pip_phi),F*pip_p*sin(D2R*pip_theta)*sin(D2R*pip_phi),F*pip_p*cos(D2R*pip_theta));
	      v2.SetXYZ(F*pim1_p*sin(D2R*pim1_theta)*cos(D2R*pim1_phi),F*pim1_p*sin(D2R*pim1_theta)*sin(D2R*pim1_phi),F*pim1_p*cos(D2R*pim1_theta));
	      pip.SetVectM( v1, 139.57018 );
	      pim2.SetVectM( v2, 139.57018 );
	      isK0=true;
	    }
	}
      if(isK0 && isL)
	{
	  l1116=p+pim1;
	  l1520=p+pim1+pim2+pip;
	  h_m_inv_p_pim->Fill(l1116.M());
	  if(l1116.M()<1116+sidebandmin && l1116.M()>1116-sidebandmin)
	    {
	      h_m_inv_p_pim_pip_pim_signal->Fill(l1520.M());
	    }
	  if((l1116.M()<1116+sidebandmax && l1116.M()>1116+sidebandmin)
	     ||(l1116.M()>1116-sidebandmax && l1116.M()<1116-sidebandmin)
	     )
	    {
	      h_m_inv_p_pim_pip_pim_SB->Fill(l1520.M());
	    }
	  isK0=false;
	  isL=false;
	}

      if(!isL)
	{
	  if(Cut(ientry) && hypothesis==1)
	    {
	      double F = 1.006;
	      //double F=1;
	      TVector3 v1, v2;
	      v1.SetXYZ(F*p_p*sin(D2R*p_theta)*cos(D2R*p_phi),F*p_p*sin(D2R*p_theta)*sin(D2R*p_phi),F*p_p*cos(D2R*p_theta));
	      v2.SetXYZ(F*pim1_p*sin(D2R*pim1_theta)*cos(D2R*pim1_phi),F*pim1_p*sin(D2R*pim1_theta)*sin(D2R*pim1_phi),F*pim1_p*cos(D2R*pim1_theta));
	      p.SetVectM( v1, 938.272013 );
	      pim1.SetVectM( v2, 139.57018 );
	      isL=true;
	    }
	  if(Cut(ientry) && hypothesis==2)
	    {
	      double F = 1.006;
	      //double F=1;
	      TVector3 v1, v2;
	      v1.SetXYZ(F*p_p*sin(D2R*p_theta)*cos(D2R*p_phi),F*p_p*sin(D2R*p_theta)*sin(D2R*p_phi),F*p_p*cos(D2R*p_theta));
	      v2.SetXYZ(F*pim2_p*sin(D2R*pim2_theta)*cos(D2R*pim2_phi),F*pim2_p*sin(D2R*pim2_theta)*sin(D2R*pim2_phi),F*pim2_p*cos(D2R*pim2_theta));
	      p.SetVectM( v1, 938.272013 );
	      pim1.SetVectM( v2, 139.57018 );
	      isL=true;
	    }
	}
      
      
      
    }
  //normalize background to signal
  TCanvas* cFit1116=new TCanvas("cFit1116");
  cFit1116->cd();
     
  TF1* fVoigt_bg= new TF1("fVoigt_bg","[0]*TMath::Voigt(x-[1],[2],[3])+pol5(4)",1090.00,1156.67);
  TF1* fVoigt= new TF1("fVoigt","[0]*TMath::Voigt(x-[1],[2],[3])",1090.00,1156.67);
  TF1* fbg= new TF1("fbg","pol5(0)",1090.00,1156.67);

  fVoigt_bg->SetParameters(585,1115,1.3,2,-126137,160,0.06,-6.5e-5,-7.8e-8,5.0e-11);
  fVoigt_bg->SetParLimits(3,0,2);
  fVoigt_bg->SetParLimits(1,1112,1117);
  fVoigt_bg->SetRange(1106,1122);
  h_m_inv_p_pim->Fit(fVoigt_bg,"R");
  fVoigt_bg->SetRange(1104,1124);
  h_m_inv_p_pim->Fit(fVoigt_bg,"R");
  fVoigt_bg->SetRange(1100,1126);
  h_m_inv_p_pim->Fit(fVoigt_bg,"R");
  fVoigt_bg->SetRange(1092,1137);
  h_m_inv_p_pim->Fit(fVoigt_bg,"R");
  fVoigt_bg->SetRange(1090,1141); 
  h_m_inv_p_pim->Fit(fVoigt_bg,"R");
  fVoigt_bg->SetRange(1092,1145); 
  h_m_inv_p_pim->Fit(fVoigt_bg,"R");


  h_m_inv_p_pim->Draw();
  fbg->SetParameters(fVoigt_bg->GetParameter(4),fVoigt_bg->GetParameter(5),fVoigt_bg->GetParameter(6),fVoigt_bg->GetParameter(7),fVoigt_bg->GetParameter(8),fVoigt_bg->GetParameter(9));
  fVoigt->SetParameters(fVoigt_bg->GetParameter(0),fVoigt_bg->GetParameter(1),fVoigt_bg->GetParameter(2),fVoigt_bg->GetParameter(3));
  fVoigt->Draw("same");
  fVoigt->SetLineColor(kGreen);
  fbg->Draw("same");
  fbg->SetLineColor(kBlue);
   
  double intS=fVoigt->Integral(1116-sidebandmin,1116+sidebandmin)/h_m_inv_p_pim->GetBinWidth(1);
  double intB=fbg->Integral(1116-sidebandmin,1116+sidebandmin)/h_m_inv_p_pim->GetBinWidth(1);
  double intsideband=(fbg->Integral(1116-sidebandmax,1116-sidebandmin)+fbg->Integral(1116+sidebandmin,1116+sidebandmax))/h_m_inv_p_pim->GetBinWidth(1);
  double intAll=fVoigt_bg->Integral(1116-sidebandmin,1116+sidebandmin)/h_m_inv_p_pim->GetBinWidth(1);
  
  cout<<"signal integral: "<<intS<<endl<<"beckground integral: "<<intB<<endl<<"sideband integral: "<<intsideband<<endl;
  cout<<"all in signal range: "<<intAll<<endl;

  h_m_inv_p_pim_pip_pim_SB->Scale(intB/intsideband);
  
  cFit1116->Write();
  outFileData->Write();
}
