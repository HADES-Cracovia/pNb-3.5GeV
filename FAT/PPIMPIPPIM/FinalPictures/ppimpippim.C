#define ppimpippim_cxx
#include "ppimpippim.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

void ppimpippim::Loop()
{
  //   In a ROOT session, you can do:
  //      Root > .L ppimpippim.C
  //      Root > ppimpippim t
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
  TFile *MyFile = new TFile("pictures.root","RECREATE");
  if ( MyFile->IsOpen() ) printf("File opened successfully\n");
  else
    printf("Cann't open a file\n");
    
  const int npt=10;
  const int nw=10;

  int pt_points=800;
  int w_points=500;
  double ptmax=1600;
  double wmax=2;

  char L_pt_name[50];
  char L_w_name[50];
  char L_pt_title[50];
  char L_w_title[50];

  char K0_pt_name[50];
  char K0_w_name[50];
  char K0_pt_title[50];
  char K0_w_title[50];
    
  TH1F* h1Lambda_pt[npt];
  TH1F* h1Lambda_pt_k0cut[nw];
  TH1F* h1Lambda_w[nw];
  TH1F* h1Lambda_w_k0cut[nw];
  TH1F* h1K0_pt[npt];
  TH1F* h1K0_pt_Lcut[nw];
  TH1F* h1K0_w[nw];
  TH1F* h1K0_w_Lcut[nw];

  TH2F *h2Lambda_wpt=new TH2F("h2Lambda_wpt","Rapidity vs. p_{t} for #Lambda",w_points,0,wmax,pt_points,0,ptmax);
  TH2F *h2K0_wpt=new TH2F("h2K0_wpt","Rapidity vs. p_{t} for K^{0}",w_points,0,wmax,pt_points,0,ptmax);
  TH2F *h2_m_inv=new TH2F("h2_m_inv","M^{inv}_{#pi^{-} #pi^{+}} vs. M^{inv}_{#pi^{-} p}",300,1000,1600,300,200,800); 
  
  TH1F *h1Lambda_pt_all=new TH1F("h1lambda_pt_all","p_{t} for #Lambda",pt_points,0,ptmax);
  TH1F *h1K0_pt_all=new TH1F("h1K0_pt_all","p_{t} for K^{0}",pt_points,0,ptmax);

  TH1F *h1Lambda_w_all=new TH1F("h1lambda_w_all","w for #Lambda",w_points,0,wmax);
  TH1F *h1K0_w_all=new TH1F("h1K0_w_all","w for K^{0}",w_points,0,wmax);

  TH1F *h1Lambda_m_all=new TH1F("h1Lambda_m_all","M^{inv}_{p #pi^{-}}",1000,1000,2000);
  TH1F *h1k0_m_all=new TH1F("h1k0_m_all","M^{inv}_{#pi^{+} #pi^{-}}",1000,200,1200);
  
  cout<<endl<<"Init pt histograms"<<endl;
  for(int i=0;i<npt;i++)
    {
      sprintf(L_pt_name,"Lambda_pt_%.0f_%.0f",ptmax*(double)i/npt,ptmax*(double)(i+1)/npt);
      sprintf(L_pt_title,"P^{T}_{#Lambda(1116)} (%.2f, %.2f)",ptmax*(double)i/npt,ptmax*(double)(i+1)/npt);

      sprintf(K0_pt_name,"K0_pt_%.0f_%.0f",ptmax*(double)i/npt,ptmax*(double)(i+1)/npt);
      sprintf(K0_pt_title,"P^{T}_{K^{0}} (%.2f, %.2f)",ptmax*(double)i/npt,ptmax*(double)(i+1)/npt);

      cout<<"pt_name: "<<L_pt_name<<" "<<K0_pt_name<<endl;
      cout<<"pt_title: "<<L_pt_title<<" "<<K0_pt_title<<endl;
      
      h1Lambda_pt[i]=new TH1F(L_pt_name,L_pt_title,pt_points,0,ptmax);
      h1K0_pt[i]=new TH1F(K0_pt_name,K0_pt_title,pt_points,0,ptmax);

      sprintf(L_pt_name,"Lambda_pt_%.2f_%.2f_k0cut",ptmax*(double)i/npt,ptmax*(double)(i+1)/npt);
      sprintf(L_pt_title,"pt_{#Lambda(1116)}(%.2f, %.2f) K^{0} cut;M^{inv}_{p #pim^{-}}[MeV]",ptmax*(double)i/npt,ptmax*(double)(i+1)/npt);
      
      sprintf(K0_pt_name,"K0_pt_%.2f_%.2f_Lcut",ptmax*(double)i/npt,ptmax*(double)(i+1)/npt);
      sprintf(K0_pt_title,"pt_{K^{0}} (%.2f, %.2f) L(1116) cut; M^{inv}_{p #pim^{-}}[MeV]",ptmax*(double)i/npt,ptmax*(double)(i+1)/npt);

      h1Lambda_pt_k0cut[i]=new TH1F(L_pt_name,L_pt_title,pt_points,0,ptmax);
      h1K0_pt_Lcut[i]=new TH1F(K0_pt_name,K0_pt_title,pt_points,0,ptmax);
    }
  /*
  for(int i=0;i<npt;i++)
    {
      cout<<"i: "<<i<<endl;
      h1Lambda_pt[i]->Print();
      h1K0_pt[i]->Print();
    }
  */
  cout<<endl<<"Init w histograms"<<endl;
  for(int i=0;i<nw;i++)
    {
      sprintf(L_w_name,"Lambda_w_%.2f_%.2f",wmax*(double)i/nw,wmax*(double)(i+1)/nw);
      sprintf(L_w_title,"w_{#Lambda(1116)} (%.2f, %.2f)",wmax*(double)i/nw,wmax*(double)(i+1)/nw);
      
      sprintf(K0_w_name,"K0_w_%.2f_%.2f",wmax*(double)i/nw,wmax*(double)(i+1)/nw);
      sprintf(K0_w_title,"w_{K^{0}} (%.2f, %.2f)",wmax*(double)i/nw,wmax*(double)(i+1)/nw);

      cout<<"w_name: "<<L_w_name<<" "<<K0_w_name<<endl;
      cout<<"w_title: "<<L_w_title<<" "<<K0_w_title<<endl;
      
      h1Lambda_w[i]=new TH1F(L_w_name,L_w_title,w_points,0,wmax);
      h1K0_w[i]=new TH1F(K0_w_name,K0_w_title,w_points,0,wmax);
      
      sprintf(L_w_name,"Lambda_w_%.2f_%.2f_k0cut",wmax*(double)i/nw,wmax*(double)(i+1)/nw);
      sprintf(L_w_title,"w_{#Lambda(1116)}(%.2f, %.2f) K^{0} cut; M^{inv}_{p #pim^{-}}[MeV]",wmax*(double)i/nw,wmax*(double)(i+1)/nw);
      
      sprintf(K0_w_name,"K0_w_%.2f_%.2f_Lcut",wmax*(double)i/nw,wmax*(double)(i+1)/nw);
      sprintf(K0_w_title,"w_{K^{0}} (%.2f, %.2f) L(1116) cut; M^{inv}_{p #pim^{-}}[MeV]",wmax*(double)i/nw,wmax*(double)(i+1)/nw);

      h1Lambda_w_k0cut[i]=new TH1F(L_w_name,L_w_title,w_points,0,wmax);
      h1K0_w_Lcut[i]=new TH1F(K0_w_name,K0_w_title,w_points,0,wmax);
          
    }
  /*
  for(int ii=0;ii<nw;ii++)
    {
      cout<<"ii: "<<ii<<endl;
      h1K0_w[ii]->Print();
      h1Lambda_w[ii]->Print();
      //h1K0_w_Lcut[ii]->Print();
      //h1Lambda_w_k0cut[ii]->Print();
    }
  */
  //Main loop
  cout<<"start main loop"<<endl;
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;

  
  for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if (Cut(ientry) < 0
	  || isBest_new!=1
	  || mlp_output<0.58
	  || miss_mass_kp<1077
	  )
	continue;

      if(jentry%10000==0)
	std::cout<<(double)jentry/nentries*100<<"% "<<endl;
      
      h2Lambda_wpt->Fill(lambda_w,lambda_pt);
      h2K0_wpt->Fill(k0_w,k0_pt);

      h1Lambda_pt_all->Fill(lambda_pt);
      h1K0_pt_all->Fill(k0_pt);
      
      h1Lambda_w_all->Fill(lambda_w);
      h1K0_w_all->Fill(k0_w);

      h1k0_m_all->Fill(m_inv_pip_pim);
      h1Lambda_m_all->Fill(m_inv_p_pim);
      
      h2_m_inv->Fill(m_inv_p_pim,m_inv_pip_pim);
      //fill histograms for pt and w slides
      for(int i=0; i<npt; i++)
	{
	  //cout<<"m_inv_p_pim: "<<m_inv_p_pim<<endl;
	  //cout<<"npt:"<<npt<<" i:"<<i<<endl;
	  double pt_min=(double)i/npt*ptmax;
	  double pt_max=(double)(i+1)/npt*ptmax;
	  //h1Lambda_pt[i]->Print();
	  //h1K0_pt[i]->Print();
	  
	  if(lambda_pt<pt_max && lambda_pt>pt_min)
	    {
	      h1Lambda_pt[i]->Fill(m_inv_p_pim);
	      if(m_inv_pip_pim<510 && m_inv_pip_pim>490)
		h1Lambda_pt_k0cut[i]->Fill(m_inv_p_pim);
	    }
	  //cout<<"aab"<<endl;
	  if(k0_pt<pt_max && k0_pt>pt_min)
	    {
	      h1K0_pt[i]->Fill(m_inv_pip_pim);
	      if(m_inv_p_pim<1120 && m_inv_p_pim>1110)
		h1K0_pt_Lcut[i]->Fill(m_inv_pip_pim);
	    }
	}
      for(int i=0;i<nw;i++)
	{
	  
	  double w_min=(double)i/nw*wmax;
	  double w_max=(double)(i+1)/nw*wmax;
	  if(lambda_w<w_max && lambda_w>w_min)
	    {
	      h1Lambda_w[i]->Fill(m_inv_p_pim);
	      if(m_inv_pip_pim<510 && m_inv_pip_pim>490)
		h1Lambda_w_k0cut[i]->Fill(m_inv_p_pim);
	    }
	  if(k0_w<w_max && k0_w>w_min)
	    {
	      h1K0_w[i]->Fill(m_inv_pip_pim);
	      if(m_inv_p_pim<1120 && m_inv_p_pim>1110)
		h1K0_w_Lcut[i]->Fill(m_inv_pip_pim);
	    }
	}
    }
  //End of main loop
  cout<<"End of main loop"<<endl;
  
  //Save histograms
  h2K0_wpt->Write();
  h2Lambda_wpt->Write();

  h2Lambda_wpt->Write();
  h2K0_wpt->Write();

  h2_m_inv->Write();
  
  h1Lambda_pt_all->Write();
  h1K0_pt_all->Write();

  h1Lambda_w_all->Write();
  h1K0_w_all->Write();

  h1Lambda_m_all->Write();
  h1k0_m_all->Write();

  for(int i=0;i<npt;i++)
    {
      h1K0_pt[i]->Write();
      h1Lambda_pt[i]->Write();
      h1K0_pt_Lcut[i]->Write();
      h1Lambda_pt_k0cut[i]->Write();
    }
  
  for(int i=0;i<nw;i++)
    {
      h1K0_w[i]->Write();
      h1Lambda_w[i]->Write();
      h1K0_w_Lcut[i]->Write();
      h1Lambda_w_k0cut[i]->Write();
    }
    
  MyFile->Close();
}
