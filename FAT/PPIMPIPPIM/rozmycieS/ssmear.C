#define ssmear_cxx
#include "ssmear.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TH1F.h>
#include "hntuple.h"
#include "TMVA/Reader.h"
#include <TGraph.h>
#include <TMath.h>

void ssmear::Loop()
{
  //   In a ROOT session, you can do:
  //      Root > .L ssmear.C
  //      Root > ssmear t
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
  const int steps=600;
  const double xmin=400;
  const double xmax=1600;
  TH1F *pip_pim_spectrum[steps];
  TH2F *miss_mass_K0=new TH2F("miss_mass_K0","missing mass vs #pi^{+} #pi^{-}",1000,xmin,xmax,600,200,800);
  TF1 *gaus[steps];
  TF1 *sig[steps];
  TF1 *bg[steps];
  TF1 *sig_bg[steps];
  char gaus_name[20];
  char sig_name[20];
  char bg_name[20];
  char sig_bg_name[20];
  char spectrum_name[20];
  double sig_int[steps];
  double bg_int[steps];
  double sig_eff[steps];
  double bg_eff[steps];
  double bg_rej[steps];
  double signif[steps];
  double sig_to_bg[steps];
  double sig2_to_bg[steps];
  double cut[steps];
  
  for(int k=0;k<steps;k++)
    {
      cut[k]=xmin+(xmax-xmin)*((double)k)/steps;
      
      sprintf(sig_name,"sig_%f",cut[k]);
      sprintf(bg_name,"bg_%f",cut[k]);
      sprintf(sig_bg_name,"sig_bg_%f",cut[k]);
      sprintf(spectrum_name,"spectrum_%f",cut[k]);
      sprintf(gaus_name,"gauss_%f",cut[k]);
      
      pip_pim_spectrum[k]=new TH1F(spectrum_name,spectrum_name,1000,0,1000);
      gaus[k]=new TF1(gaus_name,"gaus",478,507);
      sig[k]=new TF1(sig_name,"gaus(0)+pol1(3)",478,507);
      bg[k]= new TF1(bg_name,"pol4(0)",480,500);
      sig_bg[k]= new TF1(sig_bg_name,"gaus(0)+pol1(3)",478,507);
    }



  if (fChain == 0) return;

  TFile* outFileData = new TFile("output.root","recreate");
  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
      Long64_t ientry = LoadTree(jentry);
      if(jentry%50000==0)
	cout<<(double)jentry/nentries *100<<"%"<<endl;
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if (mlp_output<0.58 
	  || isBest_new<1
	  )
	continue;
      
      miss_mass_kp->Fill(miss_mass_kp,m_inv_pip_pim);
      for(int i=0;i<steps;i++)
	{
	  double miss_thr=cut[i];
	  if(miss_mass_kp>miss_thr)
	    pip_pim_spectrum[i]->Fill(m_inv_pip_pim);
	}
    }

  cout<<"Fitting phase"<<endl;

  for(int k=0; k<steps; k++)
    {
      double ymin=pip_pim_spectrum[k]->GetBinContent(pip_pim_spectrum[k]->FindBin(470));
      double ymax=pip_pim_spectrum[k]->GetBinContent(pip_pim_spectrum[k]->FindBin(507));
      double ymean=(ymin+ymax)/2;
      double a1=(ymax-ymin)/(508-470);
      double a0=ymin-470*a1;
      
      gaus[k]->SetParameter(1,490);
      
      pip_pim_spectrum[k]->Fit(gaus[k]);
      
      //sig[k]->SetParameter(0,gaus[k]->GetParameter(0));
      sig[k]->SetParameter(1,gaus[k]->GetParameter(1));
      sig[k]->SetParameter(2,gaus[k]->GetParameter(2));
      sig[k]->SetParameter(3,a0);
      sig[k]->SetParameter(4,a1);
      
      pip_pim_spectrum[k]->Fit(sig[k],"R");

      //pip_pim_spectrum[k]->Fit(bg[k],"R");
      
      sig_bg[k]->SetParameter(0,sig[k]->GetParameter(0));
      sig_bg[k]->SetParameter(1,sig[k]->GetParameter(1));
      sig_bg[k]->SetParameter(2,sig[k]->GetParameter(2));
      sig_bg[k]->SetParameter(3,sig[k]->GetParameter(3));
      sig_bg[k]->SetParameter(4,sig[k]->GetParameter(4));

      pip_pim_spectrum[k]->Fit(sig_bg[k],"R");
      //sig_bg[k]->SetParameter(5,bg[k]->GetParameter(2));
      //sig_bg[k]->SetParameter(6,bg[k]->GetParameter(3));
      //sig_bg[k]->SetParameter(7,bg[k]->GetParameter(4));

      sig_bg[k]->SetRange(459,535);
      pip_pim_spectrum[k]->Fit(sig_bg[k],"R");
      sig_bg[k]->SetRange(426,563);
      pip_pim_spectrum[k]->Fit(sig_bg[k],"R");
      //sig_bg[k]->SetRange(450,540);
      //pip_pim_spectrum[k]->Fit(sig_bg[k],"R");
      //sig_bg[k]->SetRange(1080,1160);
      pip_pim_spectrum[k]->Fit(sig_bg[k],"R");

      
      sig[k]->SetParameters(sig_bg[k]->GetParameter(0),
			    sig_bg[k]->GetParameter(1),
			    sig_bg[k]->GetParameter(2)
			    );
      bg[k]->SetParameters(sig_bg[k]->GetParameter(3)
			   ,sig_bg[k]->GetParameter(4)
			   //,sig_bg[k]->GetParameter(5)
			   //,sig_bg[k]->GetParameter(6)
			   //,sig_bg[k]->GetParameter(7)
			   //,sig_bg[k]->GetParameter(8)
			   );

      sig_int[k]=sig[k]->Integral(483,503)/pip_pim_spectrum[k]->GetBinWidth(10);//divide by bin width
      bg_int[k]=bg[k]->Integral(483,503)/pip_pim_spectrum[k]->GetBinWidth(10);

      bg_eff[k]=bg_int[k]/bg_int[0];
      sig_eff[k]=sig_int[k]/sig_int[0];
      bg_rej[k]=1-bg_eff[k];
      signif[k]=sig_int[k]/TMath::Sqrt(sig_int[k]+bg_int[k]);
      sig_to_bg[k]=sig_int[k]/bg_int[k];
      sig2_to_bg[k]=(sig_int[k]*sig_int[k])/bg_int[k];
    }

  TGraph* gRoc=new TGraph(steps,sig_eff,bg_rej);
  gRoc->SetTitle("ROC curve");
  gRoc->SetName("ROCcurve");
  gRoc->Draw("AC*");
  TGraph* gSigEff=new TGraph(steps,cut,sig_eff);
  gSigEff->SetTitle("signal efficiency");
  gSigEff->SetName("EigEff");
  gSigEff->Draw("AC*");
  TGraph* gBgEff=new TGraph(steps,cut,bg_eff);
  gBgEff->SetTitle("background efficiency");
  gBgEff->SetName("BgEff");
  gBgEff->Draw("AC*");
  TGraph* gSignif=new TGraph(steps,cut,signif);
  gSignif->SetTitle("S/Sqrt(S+B)");
  gSignif->SetName("Signif");
  gSignif->Draw("AC*");
  TGraph* gSigToBack=new TGraph(steps,cut,sig_to_bg);
  gSigToBack->SetTitle("S/B");
  gSigToBack->SetName("signal_to_background");
  gSigToBack->Draw("AC*");
  TGraph* gSig2ToBack=new TGraph(steps,cut,sig2_to_bg);
  gSig2ToBack->SetTitle("S^{2}/B");
  gSig2ToBack->SetName("signal2_to_background");
  gSig2ToBack->Draw("AC*");
  
  
  cout<<"Writing the files"<<endl;
  
  gRoc->Write();
  gSigEff->Write();
  gBgEff->Write();
  gSignif->Write();
  gSigToBack->Write();
  gSig2ToBack->Write();
  
  for(int l=0; l<steps; l++)
    {
      pip_pim_spectrum[l]->Write();
      sig[l]->Write();
      bg[l]->Write();
      sig_bg[l]->Write();
    }
  outFileData->Close();
}
