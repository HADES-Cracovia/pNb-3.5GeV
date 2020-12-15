#define EventMixing2_cxx
#include "EventMixing2.h"
#include <TH2.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TVector3.h>
#include <iostream>
#include "hntuple.h"

void EventMixing2::Loop(char*  output)
{
  //   In a ROOT session, you can do:
  //      Root > .L EventMixing2.C
  //      Root > EventMixing2 t
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
  TLorentzVector p, pim1, pip, pim2, l1116, l1520, p_l1116,pim_l1116, pim2_l1116, pip_l1116, sigmap, sigmam;
  const int bin=250;
  const int xmin=1000; 
  const int xmax=2000;
  int dM=1;
  int Lmin=1000;
  int Lmax=1500;
  int LdM=(Lmax-Lmin)/dM;
  int Kmin=250;
  int Kmax=950;
  int KdM=(Kmax-Kmin)/dM;
  TH1F* h_m_inv_p_pim=new TH1F("h_m_inv_p_pim","A #Lambda(1116) invariant mass; M_{p #pi^{-}[MeV]};N",bin*2,xmin,xmax);
  TH1F* h_m_inv_p_pim_pip_pim_signal=new TH1F("h_m_inv_p_pim_pip_pim_signal","A #Lambda(1520) invariant mass from event mixing for signal; M_{p #pi^{-} #pi^{+} #pi^{-} [MeV]};N",bin,xmin,xmax);
  //TH1F* h_m_inv_p_pim_pip_pim_signal_4p=new TH1F("h_m_inv_p_pim_pip_pim_signal_4p","A #Lambda(1520) invariant mass from event mixing for signal; M_{p #pi^{-} #pi^{+} #pi^{-} [MeV]};N",bin,xmin,xmax);
  TH1F* h_m_inv_p_pim_pip_pim_SB=new TH1F("h_m_inv_p_pim_pip_pim_SB","A #Lambda(1520) invariant mass from event mixing for SB; M_{p #pi^{-} #pi^{+} #pi^{-} [MeV]};N",bin,xmin,xmax);
  TH1F* hL1520_w=new TH1F("hL1520_w","Rapidity for #Lambda (1520) events; w",20,0,1.5);
  TH1F* hL1520_pt=new TH1F("hL1520_pt","p_{T} for #Lambda(1520) events;p_{t}[MeV]",30,0,1600);
  //TH1F* hL1116_w=new TH1F("hL1116_w","Rapidity for #Lambda (1116) events; w",20,0,1.5);
  //TH1F* hL1116_pt=new TH1F("hL1116_pt","p_{T} for #Lambda(1116) events;p_{t}[MeV]",30,0,1600);
  TH1F* hL1520_w_SB=new TH1F("hL1520_w_SB","Rapidity for SB events; w",20,0,1.5);
  TH1F* hL1520_pt_SB=new TH1F("hL1520_pt_SB","p_{T} for SB events;p_{t}[MeV]",30,0,1600);
  TH1F* hL1116_w_SB=new TH1F("hL1116_w_SB","Rapidity for #Lambda (1116) events; w",20,0,1.5);
  TH1F* hL1116_pt_SB=new TH1F("hL1116_pt_SB","p_{T} for #Lambda(1116) events;p_{t}[MeV]",30,0,1600);
  TH1F* hL1116_EM=new TH1F("hL1116_EM","#Lambda(1116) from event mixing; M_{p #pi^{-}}^{inv}[MeV]",LdM,Lmin,Lmax);
  TH1F* hK0_EM=new TH1F("hK0_EM","K^{0} from event mixing; M_{p #pi^{-}}^{inv}[MeV]",KdM,Kmin,Kmax);

  TH1F* hMPPimPip=new TH1F("hMPPimPip","Invariant mass for #Lambda #pi^{+};M^{inv}_{p #pi^{+}}[MeV];counts",400,1000,2000);
  TH1F* hMPPimPim=new TH1F("hMPPimPim","Invariant mass for #Lambda #pi^{-};M^{inv}_{p #pi^{-}}[MeV];counts",400,1000,2000);
  //TH1F* hMPPimPip_4p=new TH1F("hMPPimPip_4p","Invariant mass for #Lambda #pi^{+};M^{inv}_{p #pi^{+}}[MeV];counts",400,1000,2000);
  //TH1F* hMPPimPim_4p=new TH1F("hMPPimPim_4p","Invariant mass for #Lambda #pi^{-};M^{inv}_{p #pi^{-}}[MeV];counts",400,1000,2000);
  TH2F* h2MPPimPip_MPPimPim=new TH2F("h2MPPimPip_MPPimPim","M^{inv}_{#Lambda #pi^{+}} vs. M^{inv}_{#Lambda #pi^{-}};M^{inv}_{p #pi^{-}}[MeV];M^{inv}_{p #pi^{+}}[MeV]",100,1000,2000,100,1000,2000); 

  TH1F* hMPPimPip_SB=new TH1F("hMPPimPip_SB","Invariant mass for #Lambda #pi^{+};M^{inv}_{p #pi^{+}}[MeV];counts",400,1000,2000);
  TH1F* hMPPimPim_SB=new TH1F("hMPPimPim_SB","Invariant mass for #Lambda #pi^{-};M^{inv}_{p #pi^{-}}[MeV];counts",400,1000,2000);
  TH2F* h2MPPimPip_MPPimPim_SB=new TH2F("h2MPPimPip_MPPimPim_SB","M^{inv}_{#Lambda #pi^{+}} vs. M^{inv}_{#Lambda #pi^{-}};M^{inv}_{p #pi^{-}}[MeV];M^{inv}_{p #pi^{+}}[MeV]",100,1000,2000,100,1000,2000); 
  
  TH1F* hBetaGamma=new TH1F("hBetaGamma","#beta #gamma for #Lambda(1520) events",100,0,3);
  TH1F* h_EM_for_L1116=new TH1F("h_EM_for_L1116","A #Lambda(1116) from event mixing",500,1000,1500);

  TH1F* h_m_inv_p_pim_pip_pim_L1116EM=new TH1F("h_m_inv_p_pim_pip_pim_L1116EM","A #Lambda(1520) invariant mass from event mixing for #Lambda(1116); M_{p #pi^{-} #pi^{+} #pi^{-} [MeV]};N",bin,xmin,xmax);
    
  TH2F* h2BetaGamma_MPPimPipPim_EM=new TH2F("h2BetaGamma_MPPimPipPim_EM","#beta #gamma vs M^{inv}_{p #pi^{-}#pi^{+}#pi^{-}};#beta #gamma;M^{inv}_{p #pi^{-}#pi^{+}#pi^{-}}",100,0,2,125,1000,2000);
  TH2F* h2BetaGamma_MPPimPipPim_EM_SB=new TH2F("h2BetaGamma_MPPimPipPim_EM_SB","#beta #gamma vs M^{inv}_{p #pi^{-}#pi^{+}#pi^{-}};#beta #gamma;M^{inv}_{p #pi^{-}#pi^{+}#pi^{-}}",100,0,2,125,1000,2000);
  
  
  //int delta=10000;
  int delta=1000;
  bool isL=false;
  bool isK0=false;
  bool isp=false;
  bool ispim=false;
 
  double sidebandmin=10;
  double sidebandmax=22;
  const double D2R = 1.74532925199432955e-02;
  const double R2D = 57.2957795130823229;

  
  Long64_t nentries = fChain->GetEntries();
  Long64_t nbytes = 0, nb = 0;

  //EM for ppimpippim
  for(Long64_t jentry=0; jentry<nentries;jentry++)
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      if(jentry%10000==0)
	cout<<(double)jentry/nentries *100<<"%"<<endl;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
      if(Cut(ientry) && hypothesis==1)
	{
	  double F = 1.006;
	  //double F=1;
	  TVector3 v1, v2, v3,v4;
	  v1.SetXYZ(F*p_p*sin(D2R*p_theta)*cos(D2R*p_phi),F*p_p*sin(D2R*p_theta)*sin(D2R*p_phi),F*p_p*cos(D2R*p_theta));
	  v2.SetXYZ(F*pim1_p*sin(D2R*pim1_theta)*cos(D2R*pim1_phi),F*pim1_p*sin(D2R*pim1_theta)*sin(D2R*pim1_phi),F*pim1_p*cos(D2R*pim1_theta));
	  v3.SetXYZ(F*pim2_p*sin(D2R*pim2_theta)*cos(D2R*pim2_phi),F*pim2_p*sin(D2R*pim2_theta)*sin(D2R*pim2_phi),F*pim2_p*cos(D2R*pim2_theta));
	  v4.SetXYZ(F*pip_p*sin(D2R*pip_theta)*cos(D2R*pip_phi),F*pip_p*sin(D2R*pip_theta)*sin(D2R*pip_phi),F*pip_p*cos(D2R*pip_theta));

	  p.SetVectM( v1, 938.272013 );
	  pim1.SetVectM( v2, 139.57018 );
	  pim_l1116.SetVectM( v2, 139.57018 );
	  pip_l1116.SetVectM( v4, 139.57018 );
	  pim2_l1116.SetVectM( v3, 139.57018 );
	  isL=true;
	  ispim=true;
	}
      if(Cut(ientry) && hypothesis==2)
	{
	  double F = 1.006;
	  //double F=1;
	  TVector3 v1, v2,v3,v4;
	  v1.SetXYZ(F*p_p*sin(D2R*p_theta)*cos(D2R*p_phi),F*p_p*sin(D2R*p_theta)*sin(D2R*p_phi),F*p_p*cos(D2R*p_theta));
	  v2.SetXYZ(F*pim2_p*sin(D2R*pim2_theta)*cos(D2R*pim2_phi),F*pim2_p*sin(D2R*pim2_theta)*sin(D2R*pim2_phi),F*pim2_p*cos(D2R*pim2_theta));
	  v3.SetXYZ(F*pim1_p*sin(D2R*pim1_theta)*cos(D2R*pim1_phi),F*pim1_p*sin(D2R*pim1_theta)*sin(D2R*pim1_phi),F*pim1_p*cos(D2R*pim1_theta));
	  v4.SetXYZ(F*pip_p*sin(D2R*pip_theta)*cos(D2R*pip_phi),F*pip_p*sin(D2R*pip_theta)*sin(D2R*pip_phi),F*pip_p*cos(D2R*pip_theta));

	  p.SetVectM( v1, 938.272013 );
	  pim1.SetVectM( v2, 139.57018 );
	  pim_l1116.SetVectM( v2, 139.57018 );
	  pip_l1116.SetVectM( v4, 139.57018 );
	  pim2_l1116.SetVectM( v3, 139.57018 );
	  isL=true;
	  ispim=true;
	}
      //if(isL)cout<<"event no. "<<jentry<<" isL "<<isL<<endl;
      if(isL)
	for(Long64_t jentry2=1; jentry2<delta;jentry2++)
	  {
	    if(jentry2+jentry>=nentries)
	      continue;
	    Long64_t ientry2 = LoadTree(jentry2+jentry);
	    if (ientry2 < 0) break;
	    nb = fChain->GetEntry(jentry2+jentry);   nbytes += nb;
	    if(jentry2%200==0 && jentry%10000==0 )
	      cout<<jentry2<<" from "<<delta<< "event number"<<jentry+jentry2<<endl;
	    
	    
	    if(Cut(ientry2) && hypothesis==1)
	      {
		double F = 1.006;
		//double F=1;
		TVector3 v1, v2,v3;
		v1.SetXYZ(F*pip_p*sin(D2R*pip_theta)*cos(D2R*pip_phi),F*pip_p*sin(D2R*pip_theta)*sin(D2R*pip_phi),F*pip_p*cos(D2R*pip_theta));
		v2.SetXYZ(F*pim2_p*sin(D2R*pim2_theta)*cos(D2R*pim2_phi),F*pim2_p*sin(D2R*pim2_theta)*sin(D2R*pim2_phi),F*pim2_p*cos(D2R*pim2_theta));
		v3.SetXYZ(F*p_p*sin(D2R*p_theta)*cos(D2R*p_phi),F*p_p*sin(D2R*p_theta)*sin(D2R*p_phi),F*p_p*cos(D2R*p_theta));

		pip.SetVectM( v1, 139.57018 );
		pim2.SetVectM( v2, 139.57018 );
		p_l1116.SetVectM(v3, 938.272013);
		isK0=true;
		isp=true;
	      }
	    if(Cut(ientry2) && hypothesis==2)
	      {
		double F = 1.006;
		//double F=1;
		TVector3 v1, v2,v3;
		v1.SetXYZ(F*pip_p*sin(D2R*pip_theta)*cos(D2R*pip_phi),F*pip_p*sin(D2R*pip_theta)*sin(D2R*pip_phi),F*pip_p*cos(D2R*pip_theta));
		v2.SetXYZ(F*pim1_p*sin(D2R*pim1_theta)*cos(D2R*pim1_phi),F*pim1_p*sin(D2R*pim1_theta)*sin(D2R*pim1_phi),F*pim1_p*cos(D2R*pim1_theta));
		v3.SetXYZ(F*p_p*sin(D2R*p_theta)*cos(D2R*p_phi),F*p_p*sin(D2R*p_theta)*sin(D2R*p_phi),F*p_p*cos(D2R*p_theta));

		pip.SetVectM( v1, 139.57018 );
		pim2.SetVectM( v2, 139.57018 );
		p_l1116.SetVectM(v3, 938.272013);
		isK0=true;
		isp=true;
	      }
	    if(isK0 && isL)
	      {
		l1116=p+pim1;
		l1520=p+pim1+pim2+pip;
		sigmap=p+pim1+pip;
		sigmam=p+pim1+pim2;
		h_m_inv_p_pim->Fill(l1116.M());
		if(l1116.M()<1116+sidebandmin && l1116.M()>1116-sidebandmin)
		  {
		    h_m_inv_p_pim_pip_pim_signal->Fill(l1520.M());
		    h2BetaGamma_MPPimPipPim_EM->Fill(l1520.P()/l1520.M(),l1520.M());
		     		    
		    if(l1520.M()>1440 && l1520.M()<1600)
		      {
			hL1520_pt->Fill(l1520.Pt());
			hL1520_w->Fill(l1520.Rapidity());

			hBetaGamma->Fill(l1520.P()/l1520.M());
			hMPPimPim->Fill(sigmam.M());
			hMPPimPip->Fill(sigmap.M());
			h2MPPimPip_MPPimPim->Fill(sigmap.M(),sigmam.M());
		      }
		  }
		if((l1116.M()<1116+sidebandmax && l1116.M()>1116+sidebandmin)
		   ||(l1116.M()>1116-sidebandmax && l1116.M()<1116-sidebandmin)
		   )
		  {
		    h_m_inv_p_pim_pip_pim_SB->Fill(l1520.M());
		    h2BetaGamma_MPPimPipPim_EM_SB->Fill(l1520.P()/l1520.M(),l1520.M());
		     
		    if(l1520.M()>1440 && l1520.M()<1600)
		      {
			hL1520_pt_SB->Fill(l1520.Pt());
			hL1520_w_SB->Fill(l1520.Rapidity());

			hMPPimPim_SB->Fill(sigmam.M());
			hMPPimPip_SB->Fill(sigmap.M());
			h2MPPimPip_MPPimPim_SB->Fill(sigmap.M(),sigmam.M());
		      }
		  }
	      }//end of if(isK0 && isL)
	    if(isp==true && ispim==true)
	      {
		h_EM_for_L1116->Fill((p_l1116+pim_l1116).M());
		h_m_inv_p_pim_pip_pim_L1116EM->Fill((p_l1116+pim_l1116+pim2_l1116+pip_l1116).M());
	      }
	    //if(isK0)cout<<"   event no. "<<jentry+jentry2<<" isK0 "<<isK0<<endl;
	    isK0=false;
	    isp=false;
	  }
      isL=false;
      ispim=false;
      //SB for K0 L
      
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
  hL1520_pt_SB->Scale(intB/intsideband);
  hL1520_w_SB->Scale(intB/intsideband);

  
  cFit1116->Write();
  outFileData->Write();
}
