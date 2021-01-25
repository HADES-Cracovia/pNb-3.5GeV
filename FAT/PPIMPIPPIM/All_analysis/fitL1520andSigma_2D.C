void setStyleData(TH1* h1)
{
  h1->SetMarkerColor(h1->GetLineColor());
  h1->SetMarkerStyle(8);
  h1->SetMarkerSize(1.2);
}
void setStyleSB(TH1* h1)
{
  h1->SetLineColor(kGreen);
  h1->SetMarkerColor(h1->GetLineColor());
  h1->SetMarkerStyle(8);
  h1->SetMarkerSize(1.2);
}

void setStyleLs(TH1* h1)
{
  h1->SetLineColor(kMagenta);
  h1->SetLineWidth(2);
  h1->SetLineStyle(7);
}

void setStyleSs(TH1* h1)
{
  h1->SetLineColor(kRed+2);
  h1->SetLineWidth(2);
  h1->SetLineStyle(7);
}

void setStyleSum(TH1* h1)
{
  h1->SetLineColor(kYellow-3);
  h1->SetLineWidth(4);
  h1->SetLineStyle(1);  
}

int fitL1520andSigma_2D(void)
{
  TFile *fData_SB=new TFile("SB_experiment.root","read");
  //TFile *fL1520_SB=new TFile("SB_sim_L1520thermal.root","read");
  TFile *fL1520_SB=new TFile("SB_sim_L1520thermal_125_600.root","read");
  //TFile *fSsPimKz_SB=new TFile("SB_sim_SsPimKzthermal.root","read");
  TFile *fSsPimKz_SB=new TFile("SB_sim_SsPimKzthermal_125_600.root","read");
  
  TFile *fL1520K0_perfect_L1116=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/L1520K0_true_L1116.root","read");
  TFile *fL1520K0_perfect_L1520=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/L1520K0_true_L1520.root","read");
  //TFile *fL1520_perfect_L1116=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/L1520_true_L1116.root","read");
  //TFile *fL1520_perfect_L1520=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/L1520_true_L1520.root","read");
  //TFile *fSsPimKz_perfect_L1116=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/SsPimKz_real_L1116.root","read");
  
  TFile *fL1520_perfect_L1116=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/L1520_125_600_true_L1116.root","read");
  TFile *fL1520_perfect_L1520=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/L1520_125_600_true_L1520.root","read");
  TFile *fSsPimKz_perfect_L1116=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/SsPimKz_real_L1116.root","read");

  TFile *fout=new TFile("fitL1520andSigma_output.root","recreate");

  int rebin=2;
  
  //P Pim Pip Pim  histogram
  TH1F* hPPimPipPim_data=(TH1F*)fData_SB->Get("data");
  hPPimPipPim_data->SetName("hPPimPipPim_data");
  hPPimPipPim_data->Rebin(rebin);
  TH1F* hPPimPipPim_bcg=(TH1F*)fData_SB->Get("background");
  hPPimPipPim_bcg->SetName("hPPimPipPim_bcg");
  hPPimPipPim_bcg->Rebin(rebin);
  TH1F* hPPimPipPim_L1520=(TH1F*)fL1520_SB->Get("data");
  hPPimPipPim_L1520->SetName("hPPimPipPim_L1520");
  hPPimPipPim_L1520->Rebin(rebin);
  TH1F* hPPimPipPim_Ss=(TH1F*)fSsPimKz_SB->Get("data");
  hPPimPipPim_Ss->SetName("hPPimPipPim_Ss");
  hPPimPipPim_Ss->Rebin(rebin);

  //P Pim Pip   histogram
  TH1F* hPPimPip_data=(TH1F*)fData_SB->Get("hMPPimPip");
  hPPimPip_data->SetName("hPPimPip_data");
  hPPimPip_data->Rebin(rebin);
  TH1F* hPPimPip_bcg=(TH1F*)fData_SB->Get("hMPPimPip_SB");
  hPPimPip_bcg->SetName("hPPimPip_bcg");
  hPPimPip_bcg->Rebin(rebin);
  TH1F* hPPimPip_L1520=(TH1F*)fL1520_SB->Get("hMPPimPip");
  hPPimPip_L1520->SetName("hPPimPip_L1520");
  hPPimPip_L1520->Rebin(rebin);
  TH1F* hPPimPip_Ss=(TH1F*)fSsPimKz_SB->Get("hMPPimPip");
  hPPimPip_Ss->SetName("hPPimPip_Ss");
  hPPimPip_Ss->Rebin(rebin);
  //P Pim Pim   histogram
  TH1F* hPPimPim_data=(TH1F*)fData_SB->Get("hMPPimPim");
  hPPimPim_data->SetName("hPPimPim_data");
  hPPimPim_data->Rebin(rebin);
  TH1F* hPPimPim_bcg=(TH1F*)fData_SB->Get("hMPPimPim_SB");
  hPPimPim_bcg->SetName("hPPimPim_bcg");
  hPPimPim_bcg->Rebin(rebin);
  TH1F* hPPimPim_L1520=(TH1F*)fL1520_SB->Get("hMPPimPim");
  hPPimPim_L1520->SetName("hPPimPim_L1520");
  hPPimPim_L1520->Rebin(rebin);
  TH1F* hPPimPim_Ss=(TH1F*)fSsPimKz_SB->Get("hMPPimPim");
  hPPimPim_Ss->SetName("hPPimPim_Ss");
  hPPimPim_Ss->Rebin(rebin);

  //normalizacja symulacji do 1/2 widma PPimPipPim
  double int_data=hPPimPipPim_data->Integral();
  double int_SB=hPPimPipPim_bcg->Integral();
  double scale=0.5*(int_data-int_SB);
 
  double L1520_eff=hPPimPipPim_L1520->Integral()/(1000*10000)*0.6;
  double S1385plus_eff=hPPimPipPim_Ss->Integral()/(1000*10000)*0.6;
    
  hPPimPipPim_L1520->Scale(scale/hPPimPipPim_L1520->Integral());
  hPPimPipPim_Ss->Scale(scale/hPPimPipPim_Ss->Integral());
  hPPimPip_L1520->Scale(scale/hPPimPip_L1520->Integral());
  hPPimPip_Ss->Scale(scale/hPPimPip_Ss->Integral());
  hPPimPim_L1520->Scale(scale/hPPimPim_L1520->Integral());
  hPPimPim_Ss->Scale(scale/hPPimPim_Ss->Integral());

  //skalowanie wkladow z symulacji
  double scaleL1520=1;
  double scaleSs=1;
  double scaleL1520_opt;
  double scaleSs_opt;
  double ch2_opt=10;
  const int steps=50;
  int N=0;
  TGraph2D *optymal=new TGraph2D();
  optymal->SetTitle("Chi^{2};#Lambda(1520) thermal;#Sigma^{*} thermal;#chi^{2}");
  
  for(int n=1;n<=steps;n++)
    for(int m=1;m<=steps;m++)
      {
	scaleL1520=2.0*n/steps;
	scaleSs=3.0*m/steps;

	TH1F* LPPimPipPim_sum=hPPimPipPim_bcg->Clone("LPPimPipPim_sum");
	LPPimPipPim_sum->Add(hPPimPipPim_L1520,scaleL1520);
	LPPimPipPim_sum->Add(hPPimPipPim_Ss,scaleSs);

	TH1F* LPPimPip_sum=hPPimPip_bcg->Clone("LPPimPip_sum");
	LPPimPip_sum->Add(hPPimPip_L1520,scaleL1520);
	LPPimPip_sum->Add(hPPimPip_Ss,scaleSs);

	TH1F* LPPimPim_sum=hPPimPim_bcg->Clone("LPPimPim_sum");
	LPPimPim_sum->Add(hPPimPim_L1520,scaleL1520);
	LPPimPim_sum->Add(hPPimPim_Ss,scaleSs);

	//chi2 for spectra
	double chi2_PPimPipPim=hPPimPipPim_data->Chi2Test(LPPimPipPim_sum,"CHI2/NDF");
	double chi2_PPimPip=hPPimPip_data->Chi2Test(LPPimPip_sum,"CHI2/NDF");
	double chi2_PPimPim=hPPimPim_data->Chi2Test(LPPimPim_sum,"CHI2/NDF");
	double ch2_total=1.0/3*(chi2_PPimPipPim+chi2_PPimPip+chi2_PPimPim);

	if(ch2_total<ch2_opt)
	  {
	    scaleSs_opt=scaleSs;
	    scaleL1520_opt=scaleL1520;
	    ch2_opt=ch2_total;
	  }
	/*	
	cout<<"Wagi dla Ls i Ss: "<<scaleL1520<<" "<<scaleSs<<endl;
	cout<<"Chi2 dla PPimPipPim: "<<chi2_PPimPipPim<<endl;
	cout<<"Chi2 dla PPimPip: "<<chi2_PPimPip<<endl;
	cout<<"Chi2 dla PPimPim: "<<chi2_PPimPim<<endl;
	cout<<"Chi2 lacznie: "<<ch2_total<<endl;
	*/
	optymal->SetPoint(N,scaleL1520,scaleSs,ch2_total);
	N++;
      }
  cout<<"optymalny punkt o Ch2 = "<<ch2_opt<<endl;
  cout<<"L1520: "<<scaleL1520_opt<<" Ss: "<<scaleSs_opt<<endl;

  hPPimPipPim_L1520->Scale(scaleL1520_opt);
  hPPimPipPim_Ss->Scale(scaleSs_opt);
  hPPimPip_L1520->Scale(scaleL1520_opt);
  hPPimPip_Ss->Scale(scaleSs_opt);
  hPPimPim_L1520->Scale(scaleL1520_opt);
  hPPimPim_Ss->Scale(scaleSs_opt);

  //CS estimation
  double scale=1.04*TMath::Power(10,7);//mb
   
  double L1520_cs=hPPimPipPim_L1520->Integral()/(scale*L1520_eff/3)*1000;// \mu barn
  double S1385plus_cs=hPPimPipPim_Ss->Integral()/(scale*S1385plus_eff/3)*1000;// \mu barn

  cout<<"Cross section estimation"<<endl;
  cout<<"For L(1520):"<<endl;
  cout<<"Efficiency: "<<L1520_eff<< " XC: "<<L1520_cs<< "\mu b"<<endl;
  cout<<"For S(1385)+"<<endl;
  cout<<"Efficiency: "<<S1385plus_eff<< " XC: "<<S1385plus_cs<< "\mu b"<<endl;
  cout<<"A L(1520)/S(1385) ratio"<<endl;
  cout<<L1520_cs/S1385plus_cs<<endl;
  
  TH1F* hPPimPipPim_sum=hPPimPipPim_bcg->Clone("hPPimPipPim_sum");
  hPPimPipPim_sum->Add(hPPimPipPim_L1520);
  hPPimPipPim_sum->Add(hPPimPipPim_Ss);

  TH1F* hPPimPip_sum=hPPimPip_bcg->Clone("hPPimPip_sum");
  hPPimPip_sum->Add(hPPimPip_L1520);
  hPPimPip_sum->Add(hPPimPip_Ss);

  TH1F* hPPimPim_sum=hPPimPim_bcg->Clone("hPPimPim_sum");
  hPPimPim_sum->Add(hPPimPim_L1520);
  hPPimPim_sum->Add(hPPimPim_Ss);
  
  
  TCanvas* cOpt=new TCanvas("cOpt");  
  gPad->SetLogz();
  optymal->Draw("surf1");

  TCanvas* cSpectra=new TCanvas("cSpectra");
  cSpectra->Divide(2,2);
  cSpectra->cd(1);
  hPPimPipPim_data->Draw("e1");
  setStyleData(hPPimPipPim_data);
  hPPimPipPim_bcg->Draw("same");
  setStyleSB(hPPimPipPim_bcg);
  hPPimPipPim_L1520->Draw("samehist");
  setStyleLs(hPPimPipPim_L1520);
  hPPimPipPim_Ss->Draw("samehist");
  setStyleSs(hPPimPipPim_Ss);
  hPPimPipPim_sum->Draw("samehist");
  setStyleSum(hPPimPipPim_sum);
  
  cSpectra->cd(2);
  hPPimPip_data->Draw("e1");
  setStyleData(hPPimPip_data);
  hPPimPip_bcg->Draw("same");
  setStyleSB(hPPimPip_bcg);
  hPPimPip_L1520->Draw("samehist");
  setStyleLs(hPPimPip_L1520);
  hPPimPip_Ss->Draw("samehist");
  setStyleSs(hPPimPip_Ss);
  hPPimPip_sum->Draw("samehist");
  setStyleSum(hPPimPip_sum);
    
  cSpectra->cd(3);
  hPPimPim_data->Draw("e1");
  setStyleData(hPPimPim_data);
  hPPimPim_bcg->Draw("same");
  setStyleSB(hPPimPim_bcg);
  hPPimPim_L1520->Draw("samehist");
  setStyleLs(hPPimPim_L1520);
  hPPimPim_Ss->Draw("samehist");
  setStyleSs(hPPimPim_Ss);
  hPPimPim_sum->Draw("samehist");
  setStyleSum(hPPimPim_sum);
  
  
  cSpectra->cd(4);


  cOpt->Write();
  cSpectra->Write();
  return 0;
}










