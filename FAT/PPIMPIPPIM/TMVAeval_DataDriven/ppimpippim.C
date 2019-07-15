#define ppimpippim_cxx
#include "ppimpippim.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TH1F.h>
#include "hntuple.h"
#include "TMVA/Reader.h"
#include <TGraph.h>
#include <TMath.h>

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
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntries();
  Long64_t nbytes = 0, nb = 0;

  TFile* outFileData = new TFile("pp_after_TMVA_DD_z_pNb_n6+4.root","recreate");
  HNtuple *n_out = new HNtuple("ppimpippim","ppimpippim_after TMVA");
  n_out->setFile( outFileData );

  
  TMVA::Reader *reader = new TMVA::Reader();
  reader->AddVariable("dist_p_pim", &dist_p_pim);
  reader->AddVariable("dist_pip_pim", &dist_pip_pim);
  reader->AddVariable("eVert_x",  &eVert_x);
  reader->AddVariable("eVert_y",  &eVert_y);
  reader->AddVariable("eVert_z",  &eVert_z);
  reader->AddVariable("ver_pip_pim_x", &ver_pip_pim_x);
  reader->AddVariable("ver_pip_pim_y", &ver_pip_pim_y);
  reader->AddVariable("ver_pip_pim_z", &ver_pip_pim_z);
  reader->AddVariable("ver_p_pim_x",&ver_p_pim_x);
  reader->AddVariable("ver_p_pim_y",&ver_p_pim_y);
  reader->AddVariable("ver_p_pim_z",&ver_p_pim_z);
  reader->AddVariable("oa_lambda",&oa_lambda);
  reader->AddVariable("dist_p_eVert", &dist_p_eVert);
  reader->AddVariable("dist_pim_eVert", &dist_pim_eVert);
  reader->AddVariable("dist_lambda_eVert",&dist_lambda_eVert);
  reader->AddVariable("dist_lambda_ver_pip_pim",&dist_lambda_ver_pip_pim);
  reader->AddVariable("dist_ver_to_ver",&dist_ver_to_ver);
  
  //reader->BookMVA("kMLP","/lustre/nyx/hades/user/knowakow/PNB/FAT/TMVA/weights/TMVAClassification_data_driven_kMLP_pca_ce_600_n2_no_ev.weights.xml");
  reader->BookMVA("kMLP","/lustre/nyx/hades/user/knowakow/PNB/FAT/TMVA/weights/TMVAClassification_data_driven_kMLP_pca_ce_600_(n6+4)_no_ev.weights.xml");
  
  const int steps=100;
  const double xmin=1110;
  const double xmax=1120;
  TH1F *p_pim_spectrum[steps];
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
      sprintf(sig_name,"sig_%d",k);
      sprintf(bg_name,"bg_%d",k);
      sprintf(sig_bg_name,"sig_bg_%d",k);
      sprintf(spectrum_name,"spectrum_%d",k);
      sprintf(gaus_name,"gauss_%d",k);
      
      p_pim_spectrum[k]=new TH1F(spectrum_name,spectrum_name,1000,1000,2000);
      gaus[k]=new TF1(gaus_name,"gaus",1110,1120);
      sig[k]=new TF1(sig_name,"gaus(0)+pol1(3)",xmin,xmax);
      bg[k]= new TF1(bg_name,"pol4(0)",1080,1350);
      sig_bg[k]= new TF1(sig_bg_name,"gaus(0)+pol4(3)",1100,1135);

      cut[k]=(double)k/steps;
    }
  
  for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
      Long64_t ientry = LoadTree(jentry);
      if(jentry%5000==0)
	cout<<(double)jentry/nentries *100<<"%"<<endl;
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      Double_t mlp_output=reader->EvaluateMVA("kMLP");
      Double_t mlp_response   = reader->GetMVAError();
      
      (*n_out)["isBest"]=isBest;
      (*n_out)["isBest_new"]=isBest_new;
      (*n_out)["event"]=event;
      (*n_out)["hneg_mult"]=hneg_mult;
      (*n_out)["hpos_mult"]=hpos_mult;
      (*n_out)["eVert_x"]=eVert_x;
      (*n_out)["eVert_y"]=eVert_y;
      (*n_out)["eVert_z"]=eVert_z;
      (*n_out)["totalmult"]=totalmult;
      (*n_out)["trigdownscaleflag"]=trigdownscaleflag;
      (*n_out)["trigdownscale"]=trigdownscale;
      (*n_out)["event_mult"]=event_mult;
      (*n_out)["hypothesis"]=hypothesis;
      (*n_out)["hypothesis_quality"]=hypothesis_quality;
  
      (*n_out)["p_p"]=p_p;
      (*n_out)["p_theta"] = p_theta;
      (*n_out)["p_phi"] = p_phi;
      (*n_out)["p_beta"] = p_beta;
      (*n_out)["p_m"] = p_m;
      (*n_out)["p_dedx"]=p_dedx;
      (*n_out)["p_q"]=p_q;
	  
      //(*n_out)["p_sim_p"]=p_sim_p;
      //(*n_out)["p_sim_id"]=p_sim_id;
      //(*n_out)["p_sim_parentid"]=p_sim_parentid;
      //(*n_out)["p_sim_vertex_x"]=p_sim_vertex_x;
      //(*n_out)["p_sim_vertex_y"]=p_sim_vertex_y;
      //(*n_out)["p_sim_vertex_z"]=p_sim_vertex_z;
	  
      (*n_out)["pip_p"]=pip_p;
      (*n_out)["pip_theta"] = pip_theta;
      (*n_out)["pip_phi"] = pip_phi;
      (*n_out)["pip_beta"] = pip_beta;
      (*n_out)["pip_m"] = pip_m;
      (*n_out)["pip_dedx"]=pip_dedx;
      (*n_out)["pip_q"]=pip_q;
	  
      //(*n_out)["pip_sim_p"]=pip_sim_p;
      //(*n_out)["pip_sim_id"]=pip_sim_id;
      //(*n_out)["pip_sim_parentid"]=pip_sim_parentid;
      //(*n_out)["pip_sim_vertex_x"]=pip_sim_vertex_x;
      //(*n_out)["pip_sim_vertex_y"]=pip_sim_vertex_y;
      //(*n_out)["pip_sim_vertex_z"]=pip_sim_vertex_z;
	  
	  
      (*n_out)["pim1_p"]=pim1_p;
      (*n_out)["pim1_theta"] = pim1_theta;
      (*n_out)["pim1_phi"] = pim1_phi;
      (*n_out)["pim1_beta"] = pim1_beta;
      (*n_out)["pim1_m"] = pim1_m;
      (*n_out)["pim1_dedx"]=pim1_dedx;
      (*n_out)["pim1_q"]=pim1_q;
	  
      //(*n_out)["pim1_sim_p"]=pim1_sim_p;
      //(*n_out)["pim1_sim_id"]=pim1_sim_id;
      //(*n_out)["pim1_sim_parentid"]=pim1_sim_parentid;
      //(*n_out)["pim1_sim_vertex_x"]=pim1_sim_vertex_x;
      //(*n_out)["pim1_sim_vertex_y"]=pim1_sim_vertex_y;
      //(*n_out)["pim1_sim_vertex_z"]=pim1_sim_vertex_z;
	  
	  
      (*n_out)["pim2_p"]=pim2_p;
      (*n_out)["pim2_theta"] = pim2_theta;
      (*n_out)["pim2_phi"] = pim2_phi;
      (*n_out)["pim2_beta"] = pim2_beta;
      (*n_out)["pim2_m"] = pim2_m;
      (*n_out)["pim2_dedx"]=pim2_dedx;
      (*n_out)["pim2_q"]=pim2_q;
	  
      //(*n_out)["pim2_sim_p"]=pim2_sim_p;
      //(*n_out)["pim2_sim_id"]=pim2_sim_id;
      //(*n_out)["pim2_sim_parentid"]=pim2_sim_parentid;
      //(*n_out)["pim2_sim_vertex_x"]=pim2_sim_vertex_x;
      //(*n_out)["pim2_sim_vertex_y"]=pim2_sim_vertex_y;
      //(*n_out)["pim2_sim_vertex_z"]= pim2_sim_vertex_z;
	  	  
      //(*n_out)["pim_sim_id"]=pim_sim_id;
      //(*n_out)["pim_sim_parentid"]=pim_sim_parentid;

      (*n_out)["dist_pip_pim1"]=dist_pip_pim1;
      (*n_out)["dist_pip_pim2"] = dist_pip_pim2;
      (*n_out)["dist_pip_pim"] = dist_pip_pim;
      (*n_out)["dist_p_pim1"] = dist_p_pim1;
      (*n_out)["dist_p_pim2"] = dist_p_pim2;
      (*n_out)["dist_p_pim"] = dist_p_pim;
      (*n_out)["dist_lambda1_pim2"] = dist_lambda1_pim2;
      (*n_out)["dist_lambda1_pip"] = dist_lambda1_pip;
      (*n_out)["dist_lambda2_pim1"] = dist_lambda2_pim1;
      (*n_out)["dist_lambda2_pip"] = dist_lambda2_pip;
      (*n_out)["dist_ver_to_ver_1"]=dist_ver_to_ver_1;
      (*n_out)["dist_ver_to_ver_2"]=dist_ver_to_ver_2;
      (*n_out)["dist_ver_to_ver"]=dist_ver_to_ver;
      (*n_out)["dist_lambda1_eVert"]=dist_lambda1_eVert;
      (*n_out)["dist_lambda1_ver_pip_pim"]=dist_lambda1_ver_pip_pim;
      (*n_out)["dist_lambda2_eVert"]=dist_lambda2_eVert;
      (*n_out)["dist_lambda2_ver_pip_pim"]=dist_lambda2_ver_pip_pim;
      (*n_out)["dist_lambda_eVert"]=dist_lambda_eVert;
      (*n_out)["dist_lambda_ver_pip_pim"]=dist_lambda_ver_pip_pim;
      (*n_out)["dist_p1_eVert"]=dist_p1_eVert;
      (*n_out)["dist_pim1_eVert"]=dist_pim1_eVert;
      (*n_out)["dist_p2_eVert"]=dist_p2_eVert;
      (*n_out)["dist_pim2_eVert"]=dist_pim2_eVert;
      (*n_out)["dist_p_eVert"]=dist_p_eVert;
      (*n_out)["dist_pim_eVert"]=dist_pim_eVert;
  
	  
      (*n_out)["m_inv_p_pim1"] = m_inv_p_pim1;
      (*n_out)["m_inv_p_pim2"] = m_inv_p_pim2;
      (*n_out)["m_inv_p_pim"]=m_inv_p_pim;

      (*n_out)["m_inv_pip_pim1"] = m_inv_pip_pim1;
      (*n_out)["m_inv_pip_pim2"] = m_inv_pip_pim2;
      (*n_out)["m_inv_pip_pim"] = m_inv_pip_pim;
      (*n_out)["m_inv_p_pim_pip_pim"] = m_inv_p_pim_pip_pim;
      (*n_out)["m_inv_p_pip"] = m_inv_p_pip;
  
      (*n_out)["ver_p_pim1_x"]=ver_p_pim1_x;
      (*n_out)["ver_p_pim1_y"]=ver_p_pim1_y;
      (*n_out)["ver_p_pim1_z"]=ver_p_pim1_z;

      (*n_out)["ver_p_pim2_x"]=ver_p_pim2_x;
      (*n_out)["ver_p_pim2_y"]=ver_p_pim2_y;
      (*n_out)["ver_p_pim2_z"]=ver_p_pim2_z;

      (*n_out)["ver_p_pim_x"]=ver_p_pim_x;
      (*n_out)["ver_p_pim_y"]=ver_p_pim_y;
      (*n_out)["ver_p_pim_z"]=ver_p_pim_z;

  
      (*n_out)["ver_pip_pim1_x"]=ver_pip_pim1_x;
      (*n_out)["ver_pip_pim1_y"]=ver_pip_pim1_y;
      (*n_out)["ver_pip_pim1_z"]=ver_pip_pim1_z;

      (*n_out)["ver_pip_pim2_x"]=ver_pip_pim2_x;
      (*n_out)["ver_pip_pim2_y"]=ver_pip_pim2_y;
      (*n_out)["ver_pip_pim2_z"]=ver_pip_pim2_z;

      (*n_out)["ver_pip_pim_x"]=ver_pip_pim_x;
      (*n_out)["ver_pip_pim_y"]=ver_pip_pim_y;
      (*n_out)["ver_pip_pim_z"]=ver_pip_pim_z;

      (*n_out)["oa_lambda_1"]=oa_lambda_1;
      (*n_out)["oa_lambda_2"]=oa_lambda_2;
      (*n_out)["oa_lambda"]=oa_lambda;
      (*n_out)["oa_pim1_p"]=oa_pim1_p;
      (*n_out)["oa_pim2_p"]=oa_pim2_p;
      (*n_out)["oa_pim_p"]=oa_pim_p;
      (*n_out)["oa_pip_p"]=oa_pip_p;
      (*n_out)["oa_pim1_pim2"]=oa_pim1_pim2;
      (*n_out)["oa_pim1_pip"]=oa_pim1_pip;
      (*n_out)["oa_pim2_pip"]=oa_pim2_pip;
	 
      (*n_out)["miss_mass_kp"]=miss_mass_kp;
      (*n_out)["lambda_mom_z"]=lambda_mom_z;
      (*n_out)["simon_cuts"]=simon_cuts;
      (*n_out)["mlp_output"]=mlp_output;
      (*n_out)["mlp_response"]=mlp_response;
  
      n_out->fill();

      for(int j=0;j<steps;j++)
	{
	  if(isBest_new==1 && mlp_output>(double)j/steps && miss_mass_kp>1077)
	    p_pim_spectrum[j]->Fill(m_inv_p_pim);
	}
    }
  cout<<"Fitting phase"<<endl;

  for(int k=0; k<steps; k++)
    {
      double ymin=p_pim_spectrum[k]->GetBinContent(p_pim_spectrum[k]->FindBin(xmin));
      double ymax=p_pim_spectrum[k]->GetBinContent(p_pim_spectrum[k]->FindBin(xmax));
      double ymean=(ymin+ymax)/2;

      gaus[k]->SetParameter(1,1116);
      
      p_pim_spectrum[k]->Fit(gaus[k]);
      
      sig[k]->SetParameter(0,gaus[k]->GetParameter(0));
      sig[k]->SetParameter(1,gaus[k]->GetParameter(1));
      sig[k]->SetParameter(2,gaus[k]->GetParameter(2));
      //sig[k]->SetParameter(3,ymean-(ymax-ymin)/(xmax-xmin));
      //sig[k]->SetParameter(4,(ymax-ymin)/(xmax-xmin));
      
      p_pim_spectrum[k]->Fit(sig[k],"R");

      p_pim_spectrum[k]->Fit(bg[k],"R");
      
      sig_bg[k]->SetParameter(0,sig[k]->GetParameter(0));
      sig_bg[k]->SetParameter(1,sig[k]->GetParameter(1));
      sig_bg[k]->SetParameter(2,sig[k]->GetParameter(2));
      sig_bg[k]->SetParameter(3,sig[k]->GetParameter(3));
      sig_bg[k]->SetParameter(4,sig[k]->GetParameter(4));

      //sig_bg[k]->SetParameter(5,bg[k]->GetParameter(2));
      //sig_bg[k]->SetParameter(6,bg[k]->GetParameter(3));
      //sig_bg[k]->SetParameter(7,bg[k]->GetParameter(4));

      sig_bg[k]->SetRange(1105,1130);
      p_pim_spectrum[k]->Fit(sig_bg[k],"R");
      sig_bg[k]->SetRange(1100,1135);
      p_pim_spectrum[k]->Fit(sig_bg[k],"R");
      sig_bg[k]->SetRange(1080,1145);
      p_pim_spectrum[k]->Fit(sig_bg[k],"R");
      //sig_bg[k]->SetRange(1080,1160);
      p_pim_spectrum[k]->Fit(sig_bg[k],"R");

      
      sig[k]->SetParameters(sig_bg[k]->GetParameter(0),
			    sig_bg[k]->GetParameter(1),
			    sig_bg[k]->GetParameter(2)
			    );
      bg[k]->SetParameters(sig_bg[k]->GetParameter(3)
			   ,sig_bg[k]->GetParameter(4)
			   ,sig_bg[k]->GetParameter(5)
			   ,sig_bg[k]->GetParameter(6)
			   ,sig_bg[k]->GetParameter(7)
			   //,sig_bg[k]->GetParameter(8)
			   );

      sig_int[k]=sig[k]->Integral(1110,1120)/p_pim_spectrum[k]->GetBinWidth(10);//divide by bin width
      bg_int[k]=bg[k]->Integral(1110,1120)/p_pim_spectrum[k]->GetBinWidth(10);

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
  
  n_out->Write();
  for(int l=0; l<steps; l++)
    {
      p_pim_spectrum[l]->Write();
      sig[l]->Write();
      bg[l]->Write();
      sig_bg[l]->Write();
    }
  outFileData->Close();
}
