#define ppimpippim_LM_cxx
#include "ppimpippim_LM.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void ppimpippim_LM::Loop()
{
  //   In a ROOT session, you can do:
  //      root> .L ppimpippim_LM.C
  //      root> ppimpippim_LM t
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
  int beta_min=0;
  double beta_max=1.2;
  int beta_n=240;
  int p_min=0;
  int p_max=3000;
  int p_n=3000;

 TFile f("output_histograms_LM.root","RECREATE");
  
  const int xi2n=60;
  const int xi2step=20;
  const int xi2min=100;
  
  TH2F* p_p_beta=new TH2F("p_p_beta","Momentum vs. beta for protons",p_n,p_min,p_max,beta_n,beta_min,beta_max);
  TH2F* pim_p_beta=new TH2F("pim_p_beta","Momentum vs. beta for #pi^{-}",p_n,p_min,p_max,beta_n,beta_min,beta_max);
  TH2F* pip_p_beta=new TH2F("pip_p_beta","Momentum vs. beta for #pi^{+}",p_n,p_min,p_max,beta_n,beta_min,beta_max);

  TH1F* sum=new TH1F("sum","sum of distances;dist[mm]",200,0,200);
  TH1F* sum2=new TH1F("sum2","Sum of dist^{2};#Sigma dist^{2}[mm^{2}]",1000,0,1000);
  TF1* sig_ppim[xi2n];
  TF1* bg_ppim[xi2n];
  TF1* sig_bg_ppim[xi2n];
  TF1* sig_pippim[xi2n];
  TF1* bg_pippim[xi2n];
  TF1* sig_bg_pippim[xi2n];

  TH1F* p_pim_mass[xi2n];
  TH1F* pim_pip_mass[xi2n];

  double signal_K0[xi2n];
  double background_K0[xi2n];
  double s_to_b_K0[xi2n];
  double signif_K0[xi2n];
  
  double signal_L[xi2n];
  double background_L[xi2n];
  double cut[xi2n];
  double s_to_b_L[xi2n];
  double signif_L[xi2n];
    
  for(int i=0;i<xi2n;i++)                                                                                                                                                                                   
    {
        char hname1[20]; 
        char htitle1[40];
	char hname2[20]; 
        char htitle2[40];

	
        sprintf(htitle1,"p #pi^{-} for chi^{2} < %d; M_{#pi^{-} p}", xi2min+i*xi2step);
        sprintf(hname1,"p_pim_chi2_%d",xi2min+i*xi2step);
        p_pim_mass[i]=new TH1F(hname1,htitle1,1000,1000,2000);

        sprintf(htitle2,"#pi^{+} #pi^{-} for chi^{2} < %d; M_{#pi^{-} p}", xi2min+i*xi2step);
        sprintf(hname2,"pip_pim_chi2_%d",xi2min+i*xi2step);
        pim_pip_mass[i]=new TH1F(hname2,htitle2,1000,200,1200);

	char fname1[30]; 
       	char fname2[30]; 
       	char fname3[30]; 
   
        sprintf(fname1,"f_ppim_gaus_chi2_%d",xi2min+i*xi2step);
	sprintf(fname2,"f_ppim_bg_chi2_%d",xi2min+i*xi2step);	
	sprintf(fname3,"f_ppim_gaus_bg_chi2_%d",xi2min+i*xi2step);

	sig_ppim[i]=new TF1(fname1,"gaus(0)+pol1(4)",1110,1120);
	bg_ppim[i]=new TF1(fname2,"pol4(0)",1000,1500);
	sig_bg_ppim[i]=new TF1(fname3,"gaus(0)+pol4(3)",1000,1500);

	char fname4[30]; 
       	char fname5[30]; 
       	char fname6[30]; 
   
        sprintf(fname4,"f_pippim_gaus_chi2_%d",xi2min+i*xi2step);
	sprintf(fname5,"f_pippim_bg_chi2_%d",xi2min+i*xi2step);	
	sprintf(fname6,"f_pippim_gaus_bg_chi2_%d",xi2min+i*xi2step);

	sig_pippim[i]=new TF1(fname4,"gaus(0)+pol1(4)",400,600);
	bg_pippim[i]=new TF1(fname5,"pol4(0)",300,800);
	sig_bg_pippim[i]=new TF1(fname6,"gaus(0)+pol4(3)",300,800);
    } 
  
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;

  cout<<"no of entries: "<<nentries<<endl;
  for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
      if(jentry%15000==0)
	cout<<"analysis progress. :"<<((float)jentry)/nentries * 100.0 <<" %"<<endl;
      
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      //if (Cut(ientry) < 0) continue;

      bool m1=(m_inv_p_pim1<1120 && m_inv_p_pim1>1110);
      bool m2=(m_inv_p_pim2<1120 && m_inv_p_pim2>1110);
      
      p_p_beta->Fill(p_p,p_beta);
      pip_p_beta->Fill(pip_p,pip_beta);
      pim_p_beta->Fill(pim1_p,pim1_beta);
      pim_p_beta->Fill(pim2_p,pim2_beta);

      if(m1)
	{
	  sum->Fill(sum_dist_1);
	  sum2->Fill(sum_dist2_1);
	}
      
      if(m2)
	{
	  sum->Fill(sum_dist_2);
	  sum2->Fill(sum_dist2_2);
	}
      

      //scan over ch2
      for(int i=0;i<xi2n;i++)
	{
	  if(sum_dist2_1<xi2min+i*xi2step && m1)
	    {
	      p_pim_mass[i]->Fill(m_inv_p_pim1);
	      pim_pip_mass[i]->Fill(m_inv_pip_pim2);
	    }
	  if(sum_dist2_2<xi2min+i*xi2step && m2)
	    {
	      p_pim_mass[i]->Fill(m_inv_p_pim2);
	      pim_pip_mass[i]->Fill(m_inv_pip_pim1);
	    }
	}
    }
  
  //Fit histograms
  cout<<"Fit histograms"<<endl;
  for(int i=0;i<xi2n;i++)
    {
      ppimpippim_LM::FitL1115(p_pim_mass[i],sig_ppim[i],bg_ppim[i],sig_bg_ppim[i]);
      ppimpippim_LM::FitK0(pim_pip_mass[i],sig_pippim[i],bg_pippim[i],sig_bg_pippim[i]);

      double k0_min=480;
      double k0_max=500;
      double L_min=1110;
      double L_max=1120;
      
      cut[i]=xi2min+xi2step*i;
      background_K0[i]=bg_pippim[i]->Integral(k0_min,k0_max);
      signal_K0[i]=sig_bg_pippim[i]->Integral(k0_min,k0_max)-background_K0[i];
      s_to_b_K0[i]=signal_K0[i]/background_K0[i];
      signif_K0[i]=signal_K0[i]/TMath::Sqrt(background_K0[i]+signal_K0[i]);
      
      background_L[i]=bg_ppim[i]->Integral(L_min,L_max);
      signal_L[i]=sig_bg_ppim[i]->Integral(L_min,L_max)-background_L[i];
      s_to_b_L[i]=signal_L[i]/background_L[i];
      signif_L[i]=signal_L[i]/TMath::Sqrt(background_L[i]+signal_L[i]);
      
    }
  cout<<"End of fitting procedure"<<endl;
  //EOF

  //save histograms
  TGraph *g_s_to_b_K0=new TGraph(xi2n,cut,s_to_b_K0);
  TGraph *g_s_to_b_L=new TGraph(xi2n,cut,s_to_b_L);
  TGraph *g_signif_K0=new TGraph(xi2n,cut,signif_K0);
  TGraph *g_signif_L=new TGraph(xi2n,cut,signif_L);

  g_s_to_b_K0->Draw("AC*");
  g_s_to_b_L->Draw("AC*");
  g_signif_K0->Draw("AC*");
  g_signif_L->Draw("AC*");

  g_s_to_b_K0->SetName("s/b K0");
  g_s_to_b_L->SetName("s/b #Lambda");
  g_signif_K0->SetName("s/Sqrt(s+b) K0");
  g_signif_L->SetName("s/Sqrt(s+b) #Lambda");

  
  g_s_to_b_K0->Write();
  g_s_to_b_L->Write();
  g_signif_K0->Write();
  g_signif_L->Write();

  
  p_p_beta->Write();
  pim_p_beta->Write();
  pip_p_beta->Write();

  sum->Write();
  sum2->Write();
 
  for(int i=0;i<xi2n;i++)                                                                                                                                                                                   
    {
      p_pim_mass[i]->Draw();
      sig_ppim[i]->Draw("same");
      bg_ppim[i]->Draw("same");
      sig_bg_ppim[i]->Draw("same");
 
      p_pim_mass[i]->Write();

      pim_pip_mass[i]->Draw();
      sig_pippim[i]->Draw("same");
      bg_pippim[i]->Draw("same");
      sig_bg_pippim[i]->Draw("same");
 
      pim_pip_mass[i]->Write();
    }  

  f.Close();
  //EOS
}
