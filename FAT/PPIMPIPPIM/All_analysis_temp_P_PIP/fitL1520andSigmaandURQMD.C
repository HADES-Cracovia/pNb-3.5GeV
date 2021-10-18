double CalcIntegral(TH1 *h, double x1, double x2)
{
  return h->Integral(h->FindBin(x1),h->FindBin(x2));
}


double hist_error(TH1* hist, double x1=2, double x2=1)
{
  int nbin_min;
  int nbin_max;
  double err_sum=0;

  cout<<endl<<"***calculating sum of errors in range***"<<endl;
  cout<<"min value= "<<x1<<endl;
  cout<<"max value= "<<x2<<endl;

  if(x1>x2)
    {
      nbin_min=1;
      nbin_max=hist->GetNbinsX();
    }
  else
    {
      nbin_min=hist->FindBin(x1);
      nbin_max=hist->FindBin(x2);
    }
  cout<<"min bin= "<<nbin_min<<endl;
  cout<<"max bin= "<<nbin_max<<endl;

  for(int i=nbin_min;i<=nbin_max;i++)
    {
      cout<<"bin number: "<<i<<" bin error: "<<hist->GetBinError(i)<<endl;
      err_sum=err_sum+hist->GetBinError(i)*hist->GetBinError(i);
    }

  cout<<"***end of hist_error function***"<<endl<<endl;
  return TMath::Sqrt(err_sum);
}

double test_ch2(TH1F* h1, TH1F* h2, bool include_err=true)
{
  double n1=h1->GetNbinsX();
  double n2=h2->GetNbinsX();
  double ch2=0;
  double err=0;
  if(n1!=n2)
    {
      cout<<"wrong number of bins!"<<endl;
      return -1;
    }
  
  for(int i=0;i<=n1;i++)
    {
      if(include_err)
	{
	  double err1=h1->GetBinError(i);
	  double err2=h2->GetBinError(i);
	  err=err1*err1+err2*err2;
	}
      else
	err=1;

      if(err!=0)
	ch2=ch2+(h1->GetBinContent(i)-h2->GetBinContent(i))*(h1->GetBinContent(i)-h2->GetBinContent(i))/err;
      
    }
  return ch2/((double)n1-1);
}

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

void setStyleSsp(TH1* h1)
{
  h1->SetLineColor(kCyan-3);
  h1->SetLineWidth(2);
  h1->SetLineStyle(7);
}


void setStyleSum(TH1* h1)
{
  h1->SetLineColor(kYellow-3);
  h1->SetLineWidth(4);
  h1->SetLineStyle(1);  
}

void setStyleDpp(TH1* h1)
{
  h1->SetLineColor(kBlack);
  h1->SetLineWidth(2);
  h1->SetLineStyle(7);
}


int fitL1520andSigmaandURQMD(void)
{
  TFile *fData_SB=new TFile("SB_experiment.root","read");
  //TFile *fL1520_SB=new TFile("SB_sim_L1520thermal.root","read");
  TFile *fL1520_SB=new TFile("SB_sim_L1520thermal_125_600.root","read");
  //TFile *fSsPimKz_SB=new TFile("SB_sim_SsPimKzthermal.root","read");
  TFile *fSsPimKz_SB=new TFile("SB_sim_SsPimKzthermal_125_600.root","read");
  TFile *fSsPipKz_SB=new TFile("SB_sim_SsPipKzthermal_125_600.root","read");
  TFile *fSDppK0_SB=new TFile("SB_sim_SDppK0.root","read");
  //TFile *fLDppK0_SB=new TFile("SB_sim_LDppK0.root","read");
  TFile *furqmd_SB=new TFile("SB_sim_urqmd.root","read");
  //TFile *fL1520K0_perfect_L1116=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/L1520K0_true_L1116.root","read");
  //TFile *fL1520K0_perfect_L1520=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/L1520K0_true_L1520.root","read");
  //TFile *fL1520_perfect_L1116=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/L1520_true_L1116.root","read");
  //TFile *fL1520_perfect_L1520=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/L1520_true_L1520.root","read");
  //TFile *fSsPimKz_perfect_L1116=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/SsPimKz_real_L1116.root","read");
  
  //TFile *fL1520_perfect_L1116=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/L1520_125_600_true_L1116.root","read");
  //TFile *fL1520_perfect_L1520=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/L1520_125_600_true_L1520.root","read");
  //TFile *fSsPimKz_perfect_L1116=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/SsPimKz_real_L1116.root","read");
  //TFile *fPPdata=new TFile("../../../../PP/FAT/PPIMPIPPIM/All_analysis_wo_miss_mass/final_output_10_27_0.58_20.0_5.0.root");
  TFile *fPPdata=new TFile("../../../../PP/FAT/PPIMPIPPIM/All_analysis_wo_miss_mass/final_output_10_27_0.58_20.0_5.0.root");
  
  TFile *fout=new TFile("fitL1520andSigmaandURQMD_output.root","recreate");

  int rebin=4;
  int rebin2=4;
  
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
  TH1F* hPPimPipPim_Ssp=(TH1F*)fSsPipKz_SB->Get("data");
  hPPimPipPim_Ssp->SetName("hPPimPipPim_Ssp");
  hPPimPipPim_Ssp->Rebin(rebin);
  TH1F* hPPimPipPim_urqmd=(TH1F*)furqmd_SB->Get("data");
  hPPimPipPim_urqmd->SetName("hPPimPipPim_urqmd");
  hPPimPipPim_urqmd->Rebin(rebin);
  TH1F* hPPimPipPim_urqmd_bcg=(TH1F*)furqmd_SB->Get("background");
  hPPimPipPim_urqmd_bcg->SetName("hPPimPipPim_urqmd_bcg");
  hPPimPipPim_urqmd_bcg->Rebin(rebin);
  TH1F* hPPimPipPim_SDppKz=(TH1F*)fSDppK0_SB->Get("data");
  hPPimPipPim_SDppKz->SetName("hPPimPipPim_SDppKz");
  hPPimPipPim_SDppKz->Rebin(rebin);

  //P Pim Pip   histogram
  TH1F* hPPimPip_data=(TH1F*)fData_SB->Get("hMPPimPip");
  hPPimPip_data->SetName("hPPimPip_data");
  hPPimPip_data->Rebin(rebin2);
  TH1F* hPPimPip_bcg=(TH1F*)fData_SB->Get("hMPPimPip_SB");
  hPPimPip_bcg->SetName("hPPimPip_bcg");
  hPPimPip_bcg->Rebin(rebin2);
  TH1F* hPPimPip_L1520=(TH1F*)fL1520_SB->Get("hMPPimPip");
  hPPimPip_L1520->SetName("hPPimPip_L1520");
  hPPimPip_L1520->Rebin(rebin2);
  TH1F* hPPimPip_Ss=(TH1F*)fSsPimKz_SB->Get("hMPPimPip");
  hPPimPip_Ss->SetName("hPPimPip_Ss");
  hPPimPip_Ss->Rebin(rebin2);
  TH1F* hPPimPip_Ssp=(TH1F*)fSsPipKz_SB->Get("hMPPimPip");
  hPPimPip_Ssp->SetName("hPPimPip_Ssp");
  hPPimPip_Ssp->Rebin(rebin2);
  TH1F* hPPimPip_urqmd=(TH1F*)furqmd_SB->Get("hMPPimPip");
  hPPimPip_urqmd->SetName("hPPimPip_urqmd");
  hPPimPip_urqmd->Rebin(rebin2);
  TH1F* hPPimPip_urqmd_bcg=(TH1F*)furqmd_SB->Get("hMPPimPip_SB");
  hPPimPip_urqmd_bcg->SetName("hPPimPip_urqmd_bcg");
  hPPimPip_urqmd_bcg->Rebin(rebin2);
  TH1F* hPPimPip_SDppKz=(TH1F*)fSDppK0_SB->Get("hMPPimPip");
  hPPimPip_SDppKz->SetName("hPPimPip_SDppKz");
  hPPimPip_SDppKz->Rebin(rebin2);


  //P Pim Pim   histogram
  TH1F* hPPimPim_data=(TH1F*)fData_SB->Get("hMPPimPim");
  hPPimPim_data->SetName("hPPimPim_data");
  hPPimPim_data->Rebin(rebin2);
  TH1F* hPPimPim_bcg=(TH1F*)fData_SB->Get("hMPPimPim_SB");
  hPPimPim_bcg->SetName("hPPimPim_bcg");
  hPPimPim_bcg->Rebin(rebin2);
  TH1F* hPPimPim_L1520=(TH1F*)fL1520_SB->Get("hMPPimPim");
  hPPimPim_L1520->SetName("hPPimPim_L1520");
  hPPimPim_L1520->Rebin(rebin2);
  TH1F* hPPimPim_Ss=(TH1F*)fSsPimKz_SB->Get("hMPPimPim");
  hPPimPim_Ss->SetName("hPPimPim_Ss");
  hPPimPim_Ss->Rebin(rebin2);
  TH1F* hPPimPim_Ssp=(TH1F*)fSsPipKz_SB->Get("hMPPimPim");
  hPPimPim_Ssp->SetName("hPPimPim_Ssp");
  hPPimPim_Ssp->Rebin(rebin2);
  TH1F* hPPimPim_urqmd=(TH1F*)furqmd_SB->Get("hMPPimPim");
  hPPimPim_urqmd->SetName("hPPimPim_urqmd");
  hPPimPim_urqmd->Rebin(rebin2);
  TH1F* hPPimPim_urqmd_bcg=(TH1F*)furqmd_SB->Get("hMPPimPim_SB");
  hPPimPim_urqmd_bcg->SetName("hPPimPim_urqmd_bcg");
  hPPimPim_urqmd_bcg->Rebin(rebin2);
  TH1F* hPPimPim_SDppKz=(TH1F*)fSDppK0_SB->Get("hMPPimPim");
  hPPimPim_SDppKz->SetName("hPPimPim_SDppKz");
  hPPimPim_SDppKz->Rebin(rebin2);

  int rebin3=10;
  //PPim   histogram
  TH1F* hPPip_data=(TH1F*)fData_SB->Get("hMPPip_final");
  hPPip_data->SetName("hPPip_data");
  hPPip_data->Rebin(rebin3);
  TH1F* hPPip_bcg=(TH1F*)fData_SB->Get("hMPPip_final_SB");
  hPPip_bcg->SetName("hPPip_bcg");
  hPPip_bcg->Rebin(rebin3);
  TH1F* hPPip_L1520=(TH1F*)fL1520_SB->Get("hMPPip_final");
  hPPip_L1520->SetName("hPPip_L1520");
  hPPip_L1520->Rebin(rebin3);
  TH1F* hPPip_Ss=(TH1F*)fSsPimKz_SB->Get("hMPPip_final");
  hPPip_Ss->SetName("hPPip_Ss");
  hPPip_Ss->Rebin(rebin3);
  TH1F* hPPip_Ssp=(TH1F*)fSsPipKz_SB->Get("hMPPip_final");
  hPPip_Ssp->SetName("hPPip_Ssp");
  hPPip_Ssp->Rebin(rebin3);
  TH1F* hPPip_urqmd=(TH1F*)furqmd_SB->Get("hMPPip_final");
  hPPip_urqmd->SetName("hPPip_urqmd");
  hPPip_urqmd->Rebin(rebin3);
  TH1F* hPPip_urqmd_bcg=(TH1F*)furqmd_SB->Get("hMPPip_final_SB");
  hPPip_urqmd_bcg->SetName("hPPip_urqmd_bcg");
  hPPip_urqmd_bcg->Rebin(rebin3);
  TH1F* hPPip_SDppKz=(TH1F*)fSDppK0_SB->Get("hMPPip_final");
  hPPip_SDppKz->SetName("hPPip_SDppKz");
  hPPip_SDppKz->Rebin(rebin3);


  int rebin4=2;
  int rebin5=1;
  //pt   histogram
  
  TH1F* h_pt_data=(TH1F*)fData_SB->Get("hL1520_pt");
  h_pt_data->SetName("h_pt_data");
  h_pt_data->Rebin(rebin4);
  TH1F* h_pt_bcg=(TH1F*)fData_SB->Get("hL1520_pt_SB");
  h_pt_bcg->SetName("h_pt_bcg");
  h_pt_bcg->Rebin(rebin4);
  TH1F* h_pt_L1520=(TH1F*)fL1520_SB->Get("hL1520_pt");
  h_pt_L1520->SetName("h_pt_L1520");
  h_pt_L1520->Rebin(rebin4);
  TH1F* h_pt_Ss=(TH1F*)fSsPimKz_SB->Get("hL1520_pt");
  h_pt_Ss->SetName("h_pt_Ss");
  h_pt_Ss->Rebin(rebin4);
  TH1F* h_pt_Ssp=(TH1F*)fSsPipKz_SB->Get("hL1520_pt");
  h_pt_Ssp->SetName("h_pt_Ssp");
  h_pt_Ssp->Rebin(rebin4);
  TH1F* h_pt_urqmd=(TH1F*)furqmd_SB->Get("hL1520_pt");
  h_pt_urqmd->SetName("h_pt_urqmd");
  h_pt_urqmd->Rebin(rebin4);
  TH1F* h_pt_urqmd_bcg=(TH1F*)furqmd_SB->Get("hL1520_pt_SB");
  h_pt_urqmd_bcg->SetName("h_pt_urqmd_bcg");
  h_pt_urqmd_bcg->Rebin(rebin4);
  TH1F* h_pt_SDppKz=(TH1F*)fSDppK0_SB->Get("hL1520_pt");
  h_pt_SDppKz->SetName("h_pt_SDppKz");
  h_pt_SDppKz->Rebin(rebin4);

  //theta   histogram
  
  TH1F* h_theta_data=(TH1F*)fData_SB->Get("hL1520_theta");
  h_theta_data->SetName("h_theta_data");
  h_theta_data->Rebin(rebin5);
  TH1F* h_theta_bcg=(TH1F*)fData_SB->Get("hL1520_theta_SB");
  h_theta_bcg->SetName("h_theta_bcg");
  h_theta_bcg->Rebin(rebin5);
  TH1F* h_theta_L1520=(TH1F*)fL1520_SB->Get("hL1520_theta");
  h_theta_L1520->SetName("h_theta_L1520");
  h_theta_L1520->Rebin(rebin5);
  TH1F* h_theta_Ss=(TH1F*)fSsPimKz_SB->Get("hL1520_theta");
  h_theta_Ss->SetName("h_theta_Ss");
  h_theta_Ss->Rebin(rebin5);
  TH1F* h_theta_Ssp=(TH1F*)fSsPipKz_SB->Get("hL1520_theta");
  h_theta_Ssp->SetName("h_theta_Ssp");
  h_theta_Ssp->Rebin(rebin5);
  TH1F* h_theta_urqmd=(TH1F*)furqmd_SB->Get("hL1520_theta");
  h_theta_urqmd->SetName("h_theta_urqmd");
  h_theta_urqmd->Rebin(rebin5);
  TH1F* h_theta_urqmd_bcg=(TH1F*)furqmd_SB->Get("hL1520_theta_SB");
  h_theta_urqmd_bcg->SetName("h_theta_urqmd_bcg");
  h_theta_urqmd_bcg->Rebin(rebin5);
  TH1F* h_theta_SDppKz=(TH1F*)fSDppK0_SB->Get("hL1520_theta");
  h_theta_SDppKz->SetName("h_theta_SDppKz");
  h_theta_SDppKz->Rebin(rebin5);

  //w   histogram
  
  TH1F* h_w_data=(TH1F*)fData_SB->Get("hL1520_w");
  h_w_data->SetName("h_w_data");
  h_w_data->Rebin(rebin4);
  TH1F* h_w_bcg=(TH1F*)fData_SB->Get("hL1520_w_SB");
  h_w_bcg->SetName("h_w_bcg");
  h_w_bcg->Rebin(rebin4);
  TH1F* h_w_L1520=(TH1F*)fL1520_SB->Get("hL1520_w");
  h_w_L1520->SetName("h_w_L1520");
  h_w_L1520->Rebin(rebin4);
  TH1F* h_w_Ss=(TH1F*)fSsPimKz_SB->Get("hL1520_w");
  h_w_Ss->SetName("h_w_Ss");
  h_w_Ss->Rebin(rebin4);
  TH1F* h_w_Ssp=(TH1F*)fSsPipKz_SB->Get("hL1520_w");
  h_w_Ssp->SetName("h_w_Ssp");
  h_w_Ssp->Rebin(rebin4);
  TH1F* h_w_urqmd=(TH1F*)furqmd_SB->Get("hL1520_w");
  h_w_urqmd->SetName("h_w_urqmd");
  h_w_urqmd->Rebin(rebin4);
  TH1F* h_w_urqmd_bcg=(TH1F*)furqmd_SB->Get("hL1520_w_SB");
  h_w_urqmd_bcg->SetName("h_w_urqmd_bcg");
  h_w_urqmd_bcg->Rebin(rebin4);
  TH1F* h_w_SDppKz=(TH1F*)fSDppK0_SB->Get("hL1520_w");
  h_w_SDppKz->SetName("h_w_SDppKz");
  h_w_SDppKz->Rebin(rebin4);

  //p  histogram
  
  TH1F* h_p_data=(TH1F*)fData_SB->Get("hL1520_p");
  h_p_data->SetName("h_p_data");
  h_p_data->Rebin(rebin5);
  TH1F* h_p_bcg=(TH1F*)fData_SB->Get("hL1520_p_SB");
  h_p_bcg->SetName("h_p_bcg");
  h_p_bcg->Rebin(rebin5);
  TH1F* h_p_L1520=(TH1F*)fL1520_SB->Get("hL1520_p");
  h_p_L1520->SetName("h_p_L1520");
  h_p_L1520->Rebin(rebin5);
  TH1F* h_p_Ss=(TH1F*)fSsPimKz_SB->Get("hL1520_p");
  h_p_Ss->SetName("h_p_Ss");
  h_p_Ss->Rebin(rebin5);
  TH1F* h_p_Ssp=(TH1F*)fSsPipKz_SB->Get("hL1520_p");
  h_p_Ssp->SetName("h_p_Ssp");
  h_p_Ssp->Rebin(rebin5);
  TH1F* h_p_urqmd=(TH1F*)furqmd_SB->Get("hL1520_p");
  h_p_urqmd->SetName("h_p_urqmd");
  h_p_urqmd->Rebin(rebin5);
  TH1F* h_p_urqmd_bcg=(TH1F*)furqmd_SB->Get("hL1520_p_SB");
  h_p_urqmd_bcg->SetName("h_p_urqmd_bcg");
  h_p_urqmd_bcg->Rebin(rebin5);
  TH1F* h_p_SDppKz=(TH1F*)fSDppK0_SB->Get("hL1520_p");
  h_p_SDppKz->SetName("h_p_SDppKz");
  h_p_SDppKz->Rebin(rebin5);

  
  //substruct SB for URQMD
  //commented out because L1116 fit failed
  hPPimPipPim_urqmd->Add(hPPimPipPim_urqmd_bcg,-1);
  hPPimPim_urqmd->Add(hPPimPim_urqmd_bcg,-1);
  hPPimPip_urqmd->Add(hPPimPip_urqmd_bcg,-1);
  hPPip_urqmd->Add(hPPip_urqmd_bcg,-1);
  h_p_urqmd->Add(h_p_urqmd_bcg,-1);
  h_w_urqmd->Add(h_w_urqmd_bcg,-1);
  h_pt_urqmd->Add(h_pt_urqmd_bcg,-1);
  h_theta_urqmd->Add(h_theta_urqmd_bcg,-1);
  

  //Data from PP
  TH1F* hPP_L1520=(TH1F*)fPPdata->Get("hclean_experiment");
  TH1F* hPP_pt=(TH1F*)fPPdata->Get("hclean_pt_experiment");
  TH1F* hPP_p=(TH1F*)fPPdata->Get("hclean_p_experiment");
  TH1F* hPP_w=(TH1F*)fPPdata->Get("hclean_w_experiment");
  TH1F* hPP_theta=(TH1F*)fPPdata->Get("hclean_theta_experiment");
 

  //sum
  TH1F* LPPimPipPim_sum=hPPimPipPim_bcg->Clone("LPPimPipPim_sum");
  TH1F* LPPimPip_sum=hPPimPip_bcg->Clone("LPPimPip_sum");
  TH1F* LPPimPim_sum=hPPimPim_bcg->Clone("LPPimPim_sum");
  TH1F* LPPip_sum=hPPip_bcg->Clone("LPPip_sum");

  
  //normalizacja symulacji do 1/2 widma PPimPipPim
  double int_data=hPPimPipPim_data->Integral();
  double int_SB=hPPimPipPim_bcg->Integral();
  double scale=0.5*(int_data-int_SB);

  double L1520_eff=hPPimPipPim_L1520->Integral()/(1000*10000);
  double S1385plus_eff=hPPimPipPim_Ss->Integral()/(1000*10000);
  double S1385minus_eff=hPPimPipPim_Ssp->Integral()/(1000*10000);
  double urqmd_eff=hPPimPipPim_urqmd->Integral()/(120.*TMath::Power(10,6));
  double SDppKz_eff=hPPimPipPim_SDppKz->Integral()/(120.*TMath::Power(10,6));
  
  double lum=1.04*TMath::Power(10,7);//mb
  double arbitrary_scale=1;
  bool bscaleURQMD=false;
  bool bfixSs=false;
  bool bincludeSigmaM=false;

  hPPimPipPim_L1520->Scale(scale/hPPimPipPim_L1520->Integral());
  hPPimPipPim_Ss->Scale(scale/hPPimPipPim_Ss->Integral());
  hPPimPipPim_Ssp->Scale(scale/hPPimPipPim_Ssp->Integral());
  //hPPimPipPim_urqmd->Scale(1./hPPimPipPim_urqmd->Integral()*lum*urqmd_eff/3*29.45/1000*TMath::Power(93,2/3)*arbitrary_scale);
  //hPPimPipPim_SDppKz->Scale(1./hPPimPipPim_SDppKz->Integral()*lum*SDppKz_eff/3*9.26/1000*TMath::Power(93,2/3)*arbitrary_scale);
  if(bscaleURQMD)
    hPPimPipPim_urqmd->Scale(scale/hPPimPipPim_urqmd->Integral());
  hPPimPipPim_SDppKz->Scale(scale/hPPimPipPim_SDppKz->Integral());
 
  hPPimPip_L1520->Scale(scale/hPPimPip_L1520->Integral());
  hPPimPip_Ss->Scale(scale/hPPimPip_Ss->Integral());
  hPPimPip_Ssp->Scale(scale/hPPimPip_Ssp->Integral());
  //hPPimPip_urqmd->Scale(1./hPPimPip_urqmd->Integral()*lum*urqmd_eff/3*29.45/1000*TMath::Power(93,2/3)*arbitrary_scale);
  //hPPimPip_SDppKz->Scale(1./hPPimPip_SDppKz->Integral()*lum*SDppKz_eff/3*9.26/1000*TMath::Power(93,2/3)*arbitrary_scale);
  if(bscaleURQMD)
    hPPimPip_urqmd->Scale(scale/hPPimPip_urqmd->Integral());
  hPPimPip_SDppKz->Scale(scale/hPPimPip_SDppKz->Integral());
 
  
  hPPip_L1520->Scale(scale/hPPimPim_L1520->Integral());
  hPPip_Ss->Scale(scale/hPPimPim_Ss->Integral());
  hPPip_Ssp->Scale(scale/hPPimPim_Ssp->Integral());
  //hPPip_urqmd->Scale(1./hPPimPim_urqmd->Integral()*lum*urqmd_eff/3*29.45/1000*TMath::Power(93,2/3)*arbitrary_scale);
  //hPPip_SDppKz->Scale(1./hPPimPim_SDppKz->Integral()*lum*SDppKz_eff/3*9.26/1000*TMath::Power(93,2/3)*arbitrary_scale);
  if(bscaleURQMD)
    hPPip_urqmd->Scale(scale/hPPip_urqmd->Integral());
  hPPip_SDppKz->Scale(scale/hPPip_SDppKz->Integral());
 
  
  hPPimPim_L1520->Scale(scale/hPPimPim_L1520->Integral());
  hPPimPim_Ss->Scale(scale/hPPimPim_Ss->Integral());
  hPPimPim_Ssp->Scale(scale/hPPimPim_Ssp->Integral());
  //hPPimPim_urqmd->Scale(1./hPPimPim_urqmd->Integral()*lum*urqmd_eff/3*29.45/1000*TMath::Power(93,2/3)*arbitrary_scale);
  //hPPimPim_SDppKz->Scale(1./hPPimPim_SDppKz->Integral()*lum*SDppKz_eff/3*9.26/1000*TMath::Power(93,2/3)*arbitrary_scale);
  if(bscaleURQMD)
    hPPimPim_urqmd->Scale(scale/hPPimPim_urqmd->Integral());
  hPPimPim_SDppKz->Scale(scale/hPPimPim_SDppKz->Integral());

  hPPip_L1520->Scale(scale/hPPip_L1520->Integral());
  hPPip_Ss->Scale(scale/hPPip_Ss->Integral());
  hPPip_Ssp->Scale(scale/hPPip_Ssp->Integral());
  //hPPip_urqmd->Scale(1./hPPip_urqmd->Integral()*lum*urqmd_eff/3*29.45/1000*TMath::Power(93,2/3)*arbitrary_scale);
  //hPPip_SDppKz->Scale(1./hPPip_SDppKz->Integral()*lum*SDppKz_eff/3*9.26/1000*TMath::Power(93,2/3)*arbitrary_scale);
  if(bscaleURQMD)
    hPPip_urqmd->Scale(scale/hPPip_urqmd->Integral());
  hPPip_SDppKz->Scale(scale/hPPip_SDppKz->Integral());

  h_pt_L1520->Scale(scale/h_pt_L1520->Integral());
  h_pt_Ss->Scale(scale/h_pt_Ss->Integral());
  h_pt_Ssp->Scale(scale/h_pt_Ssp->Integral());
  //h_pt_urqmd->Scale(1./h_pt_urqmd->Integral()*lum*urqmd_eff/3*29.45/1000*TMath::Power(93,2/3)*arbitrary_scale);
  //h_pt_SDppKz->Scale(1./h_pt_SDppKz->Integral()*lum*SDppKz_eff/3*9.26/1000*TMath::Power(93,2/3)*arbitrary_scale);
  if(bscaleURQMD)
    h_pt_urqmd->Scale(scale/h_pt_urqmd->Integral());
  h_pt_SDppKz->Scale(scale/h_pt_SDppKz->Integral());

  h_theta_L1520->Scale(scale/h_theta_L1520->Integral());
  h_theta_Ss->Scale(scale/h_theta_Ss->Integral());
  h_theta_Ssp->Scale(scale/h_theta_Ssp->Integral());
  //h_theta_urqmd->Scale(1./h_theta_urqmd->Integral()*lum*urqmd_eff/3*29.45/1000*TMath::Power(93,2/3)*arbitrary_scale);
  //h_theta_SDppKz->Scale(1./h_theta_SDppKz->Integral()*lum*SDppKz_eff/3*9.26/1000*TMath::Power(93,2/3)*arbitrary_scale);
  if(bscaleURQMD)
    h_theta_urqmd->Scale(scale/h_theta_urqmd->Integral());
  h_theta_SDppKz->Scale(scale/h_theta_SDppKz->Integral());

  
  h_w_L1520->Scale(scale/h_w_L1520->Integral());
  h_w_Ss->Scale(scale/h_w_Ss->Integral());
  h_w_Ssp->Scale(scale/h_w_Ssp->Integral());
  //h_w_urqmd->Scale(1./h_w_urqmd->Integral()*lum*urqmd_eff/3*29.45/1000*TMath::Power(93,2/3)*arbitrary_scale);
  //h_w_SDppKz->Scale(1./h_w_SDppKz->Integral()*lum*SDppKz_eff/3*9.26/1000*TMath::Power(93,2/3)*arbitrary_scale);
  if(bscaleURQMD)
    h_w_urqmd->Scale(scale/h_w_urqmd->Integral());
  h_w_SDppKz->Scale(scale/h_w_SDppKz->Integral());

  h_p_L1520->Scale(scale/h_p_L1520->Integral());
  h_p_Ss->Scale(scale/h_p_Ss->Integral());
  h_p_Ssp->Scale(scale/h_p_Ssp->Integral());
  //h_p_urqmd->Scale(1./h_p_urqmd->Integral()*lum*urqmd_eff/3*29.45/1000*TMath::Power(93,2/3)*arbitrary_scale);
  //h_p_SDppKz->Scale(1./h_p_SDppKz->Integral()*lum*SDppKz_eff/3*9.26/1000*TMath::Power(93,2/3)*arbitrary_scale);
  if(bscaleURQMD)
    h_p_urqmd->Scale(scale/h_p_urqmd->Integral());
  h_p_SDppKz->Scale(scale/h_p_SDppKz->Integral());

  
  //skalowanie wkladow z symulacji
  double scaleL1520=0.54321;
  double scaleSs=0.54321;
  double scaleSsp=0.54321;
  double scaleURQMD;
  if(bscaleURQMD)
    scaleURQMD=0.54321;
  else
    scaleURQMD=2;
  double scaleL1520_opt=0.001;
  double scaleSs_opt=0.0001;
  double scaleSsp_opt=0.0001;
  double scaleURQMD_opt=0.0001;
  double ch2_opt=100000;
  const int steps=60;
  int N=0;
  
  TGraph2D *optymal=new TGraph2D();
  optymal->SetTitle("Chi^{2};#Lambda(1520) thermal;#Sigma^{*} thermal;#chi^{2}");
  TH3D *optymal_3D=new TH3D("optymal_3D","A 3D opymization;#Lambda(1520) thermal;#Sigma^{+*} thermal;#Sigma^{-*} thermal",3*steps,0,1,3*steps,0,1,3*steps,0,1);
  
  
  for(int n=1;n<=steps;n++)
    {
      for(int m=1;m<=steps;m++)
	{
	  //if(m%5==0)
	  //cout<<"n="<<n<<" m="<<m<<endl;
	  for(int l=1;l<=steps;l++)
	    {
	      //if(l!=m)
	      //continue;
	      scaleL1520=1.2*(double)n*1./steps;
	      scaleSs=1.2*(double)m*1./steps;
	      if(bfixSs)
		scaleSs=scaleL1520;
	      if(bscaleURQMD)
		scaleURQMD=1.8*(double)l*1./steps;
	      if(!bscaleURQMD && l>1)
		continue;
	      if(bincludeSigmaM)
		scaleSsp=scaleSs;
	      //scaleSs=0.001;
	      //scaleSsp=1.4*l*1./steps;
	      //scaleSsp=0.001;
	      //scaleSsp=scaleSs;
	      
	      LPPimPipPim_sum->Reset();
	      LPPimPipPim_sum->Add(hPPimPipPim_bcg);
	      LPPimPipPim_sum->Add(hPPimPipPim_L1520,scaleL1520);
	      LPPimPipPim_sum->Add(hPPimPipPim_Ss,scaleSs);
	      LPPimPipPim_sum->Add(hPPimPipPim_urqmd,scaleURQMD);
	      if(bincludeSigmaM)
		LPPimPipPim_sum->Add(hPPimPipPim_Ssp,scaleSsp);
	
	      LPPimPip_sum->Reset();
	      LPPimPip_sum->Add(hPPimPip_bcg);
	      LPPimPip_sum->Add(hPPimPip_L1520,scaleL1520);
	      LPPimPip_sum->Add(hPPimPip_Ss,scaleSs);
	      LPPimPip_sum->Add(hPPimPip_urqmd,scaleURQMD);
	      if(bincludeSigmaM)
		LPPimPip_sum->Add(hPPimPip_Ssp,scaleSsp);

	      LPPimPim_sum->Reset();
	      LPPimPim_sum->Add(hPPimPim_bcg);
	      LPPimPim_sum->Add(hPPimPim_L1520,scaleL1520);
	      LPPimPim_sum->Add(hPPimPim_Ss,scaleSs);
	      LPPimPim_sum->Add(hPPimPim_urqmd,scaleURQMD);
	      if(bincludeSigmaM)
		LPPimPim_sum->Add(hPPimPim_Ssp,scaleSsp);

	      LPPip_sum->Reset();
	      LPPip_sum->Add(hPPip_bcg);
	      LPPip_sum->Add(hPPip_L1520,scaleL1520);
	      LPPip_sum->Add(hPPip_Ss,scaleSs);
	      LPPip_sum->Add(hPPip_urqmd,scaleURQMD);
	      if(bincludeSigmaM)
		LPPip_sum->Add(hPPip_Ssp,scaleSsp);

	      
	      /*
		double chi2_PPimPipPim=hPPimPipPim_data->Chi2Test(LPPimPipPim_sum,"chi2/NDF");
		double chi2_PPimPip=hPPimPip_data->Chi2Test(LPPimPip_sum,"chi2/NDF");
		double chi2_PPimPim=hPPimPim_data->Chi2Test(LPPimPim_sum,"chi2/NDF");
	      */
	      double chi2_PPimPipPim=test_ch2(hPPimPipPim_data,LPPimPipPim_sum);
	      double chi2_PPimPip=test_ch2(hPPimPip_data,LPPimPip_sum);
	      double chi2_PPimPim=test_ch2(hPPimPim_data,LPPimPim_sum);
	      double chi2_PPip=test_ch2(hPPip_data,LPPip_sum);
	      
	      double ch2_total=1.0/3.0*(chi2_PPimPipPim+chi2_PPimPip+chi2_PPimPim);
	      //double ch2_total=1.0/4.0*(chi2_PPimPipPim+chi2_PPimPip+chi2_PPimPim+chi2_PPip);
	      //double ch2_total=1.0*chi2_PPimPipPim;
	      if(ch2_total<ch2_opt)
		{
		  scaleSs_opt=scaleSs;
		  scaleL1520_opt=scaleL1520;
		  scaleSsp_opt=scaleSsp;
		  scaleURQMD_opt=scaleURQMD;
		  ch2_opt=ch2_total;
		  
		}
	      /*
		cout<<"Wagi dla Ls i S*+ i S*-: "<<scaleL1520<<", "<<scaleSs<<", "<<scaleSsp<<endl;
		cout<<"Chi2 dla PPimPipPim: "<<chi2_PPimPipPim<<endl;
		cout<<"Chi2 dla PPimPip: "<<chi2_PPimPip<<endl;
		cout<<"Chi2 dla PPimPim: "<<chi2_PPimPim<<endl;
		cout<<"Chi2 lacznie: "<<ch2_total<<endl;
	      */
	      if(ch2_total<2)
		optymal_3D->SetBinContent(n*3,m*3,l*3,ch2_total);
	      
	    }
	  optymal->SetPoint(N,scaleL1520,scaleSs,ch2_total);
	  N++;
	}
    }
  cout<<"optymalny punkt o Ch2 = "<<ch2_opt<<endl;
  if(bscaleURQMD)
    cout<<"L1520: "<<scaleL1520_opt<<" S(1385)+: "<<scaleSs_opt<<" URQMD: "<<scaleURQMD_opt<<endl;
  else
    cout<<"L1520: "<<scaleL1520_opt<<" S(1385)+: "<<scaleSs_opt<<" URQMD: "<< "natural scaling"<<endl;
  
  hPPimPipPim_L1520->Scale(scaleL1520_opt);
  hPPimPipPim_Ss->Scale(scaleSs_opt);
  hPPimPipPim_Ssp->Scale(scaleSsp_opt);
  hPPimPipPim_urqmd->Scale(scaleURQMD_opt);
 
  hPPimPip_L1520->Scale(scaleL1520_opt);
  hPPimPip_Ss->Scale(scaleSs_opt);
  hPPimPip_Ssp->Scale(scaleSsp_opt);
  hPPimPip_urqmd->Scale(scaleURQMD_opt);

  hPPimPim_L1520->Scale(scaleL1520_opt);
  hPPimPim_Ss->Scale(scaleSs_opt);
  hPPimPim_Ssp->Scale(scaleSsp_opt);
  hPPimPim_urqmd->Scale(scaleURQMD_opt);

  hPPip_L1520->Scale(scaleL1520_opt);
  hPPip_Ss->Scale(scaleSs_opt);
  hPPip_Ssp->Scale(scaleSsp_opt);
  hPPip_urqmd->Scale(scaleURQMD_opt);

  h_pt_L1520->Scale(scaleL1520_opt);
  h_pt_Ss->Scale(scaleSs_opt);
  h_pt_Ssp->Scale(scaleSsp_opt);
  h_pt_urqmd->Scale(scaleURQMD_opt);

  h_theta_L1520->Scale(scaleL1520_opt);
  h_theta_Ss->Scale(scaleSs_opt);
  h_theta_Ssp->Scale(scaleSsp_opt);
  h_theta_urqmd->Scale(scaleURQMD_opt);
 
  h_w_L1520->Scale(scaleL1520_opt);
  h_w_Ss->Scale(scaleSs_opt);
  h_w_Ssp->Scale(scaleSsp_opt);
  h_w_urqmd->Scale(scaleURQMD_opt);

  h_p_L1520->Scale(scaleL1520_opt);
  h_p_Ss->Scale(scaleSs_opt);
  h_p_Ssp->Scale(scaleSsp_opt);
  h_p_urqmd->Scale(scaleURQMD_opt);

  //cout<<"aaa"<<endl;
  //additional histograms, just for drwaings
  TH1F* hPPimPipPim_sum=hPPimPipPim_bcg->Clone("hPPimPipPim_sum");
  hPPimPipPim_sum->Add(hPPimPipPim_L1520);
  hPPimPipPim_sum->Add(hPPimPipPim_Ss);
  if(bincludeSigmaM)
    hPPimPipPim_sum->Add(hPPimPipPim_Ssp);
  hPPimPipPim_sum->Add(hPPimPipPim_urqmd);
  

  TH1F* hPPimPip_sum=hPPimPip_bcg->Clone("hPPimPip_sum");
  hPPimPip_sum->Add(hPPimPip_L1520);
  hPPimPip_sum->Add(hPPimPip_Ss);
  if(bincludeSigmaM)
    hPPimPip_sum->Add(hPPimPip_Ssp);
  hPPimPip_sum->Add(hPPimPip_urqmd);
  
  TH1F* hPPimPim_sum=hPPimPim_bcg->Clone("hPPimPim_sum");
  hPPimPim_sum->Add(hPPimPim_L1520);
  hPPimPim_sum->Add(hPPimPim_Ss);
  if(bincludeSigmaM)
    hPPimPim_sum->Add(hPPimPim_Ssp);
  hPPimPim_sum->Add(hPPimPim_urqmd);
  

  TH1F* hPPip_sum=hPPip_bcg->Clone("hPPip_sum");
  hPPip_sum->Add(hPPip_L1520);
  hPPip_sum->Add(hPPip_Ss);
  if(bincludeSigmaM)
    hPPip_sum->Add(hPPip_Ssp);
  hPPip_sum->Add(hPPip_urqmd);

  TH1F* h_pt_sum=h_pt_bcg->Clone("h_pt_sum");
  h_pt_sum->Add(h_pt_L1520);
  h_pt_sum->Add(h_pt_Ss);
  if(bincludeSigmaM)
    h_pt_sum->Add(h_pt_Ssp);
  h_pt_sum->Add(h_pt_urqmd);

  TH1F* h_w_sum=h_w_bcg->Clone("h_w_sum");
  h_w_sum->Add(h_w_L1520);
  h_w_sum->Add(h_w_Ss);
  if(bincludeSigmaM)
    h_w_sum->Add(h_w_Ssp);
  h_w_sum->Add(h_w_urqmd);

   TH1F* h_p_sum=h_p_bcg->Clone("h_p_sum");
  h_p_sum->Add(h_p_L1520);
  h_p_sum->Add(h_p_Ss);
  if(bincludeSigmaM)
    h_p_sum->Add(h_p_Ssp);
  h_p_sum->Add(h_p_urqmd);

  //cout<<"bbb"<<endl;
  //with substructed SB
  TH1F* hPPimPipPim_sum_clean=hPPimPipPim_Ssp->Clone("hPPimPipPim_sum_clean");
  hPPimPipPim_sum_clean->Reset();
  hPPimPipPim_sum_clean->Add(hPPimPipPim_L1520);
  hPPimPipPim_sum_clean->Add(hPPimPipPim_Ss);
  hPPimPipPim_sum_clean->Add(hPPimPipPim_urqmd);
  
  TH1F* hPPimPip_sum_clean=hPPimPip_Ssp->Clone("hPPimPip_sum_clean");
  hPPimPip_sum_clean->Reset();
  hPPimPip_sum_clean->Add(hPPimPip_L1520);
  hPPimPip_sum_clean->Add(hPPimPip_Ss);
  hPPimPip_sum_clean->Add(hPPimPip_urqmd);
  
  TH1F* hPPimPim_sum_clean=hPPimPim_Ssp->Clone("hPPimPim_sum_clean");
  hPPimPim_sum_clean->Reset();
  hPPimPim_sum_clean->Add(hPPimPim_L1520);
  hPPimPim_sum_clean->Add(hPPimPim_Ss);
  hPPimPim_sum_clean->Add(hPPimPim_urqmd);
  //cout<<"ccc"<<endl;
  TH1F* hPPip_sum_clean=hPPip_Ssp->Clone("hPPip_sum_clean");
  hPPip_sum_clean->Reset();
  hPPip_sum_clean->Add(hPPip_L1520);
  hPPip_sum_clean->Add(hPPip_Ss);
  hPPip_sum_clean->Add(hPPip_urqmd);

  TH1F* h_pt_sum_clean=h_pt_Ssp->Clone("h_pt_sum_clean");
  h_pt_sum_clean->Reset();
  h_pt_sum_clean->Add(h_pt_L1520);
  h_pt_sum_clean->Add(h_pt_Ss);
  h_pt_sum_clean->Add(h_pt_urqmd);

  TH1F* h_theta_sum_clean=h_theta_Ssp->Clone("h_theta_sum_clean");
  h_theta_sum_clean->Reset();
  h_theta_sum_clean->Add(h_theta_L1520);
  h_theta_sum_clean->Add(h_theta_Ss);
  h_theta_sum_clean->Add(h_theta_urqmd);
  
  TH1F* h_w_sum_clean=h_w_Ssp->Clone("h_w_sum_clean");
  h_w_sum_clean->Reset();
  h_w_sum_clean->Add(h_w_L1520);
  h_w_sum_clean->Add(h_w_Ss);
  h_w_sum_clean->Add(h_w_urqmd);

    TH1F* h_p_sum_clean=h_p_Ssp->Clone("h_p_sum_clean");
  h_p_sum_clean->Reset();
  h_p_sum_clean->Add(h_p_L1520);
  h_p_sum_clean->Add(h_p_Ss);
  h_p_sum_clean->Add(h_p_urqmd);

  //cout<<"ddd"<<endl;
  TH1F* hPPimPipPim_data_clean=hPPimPipPim_data->Clone("hPPimPipPim_data_clean");
  hPPimPipPim_data_clean->Add(hPPimPipPim_bcg,-1);
  TH1F* hPPimPip_data_clean=hPPimPip_data->Clone("hPPimPip_data_clean");
  hPPimPip_data_clean->Add(hPPimPip_bcg,-1);
  TH1F* hPPimPim_data_clean=hPPimPim_data->Clone("hPPimPim_data_clean");
  hPPimPim_data_clean->Add(hPPimPim_bcg,-1);
  TH1F* h_pt_data_clean=h_pt_data->Clone("h_pt_data_clean");
  h_pt_data_clean->Add(h_pt_bcg,-1);
  TH1F* h_theta_data_clean=h_theta_data->Clone("h_theta_data_clean");
  h_theta_data_clean->Add(h_theta_bcg,-1);
  TH1F* h_w_data_clean=h_w_data->Clone("h_w_data_clean");
  h_w_data_clean->Add(h_w_bcg,-1);
  TH1F* h_p_data_clean=h_p_data->Clone("h_p_data_clean");
  h_p_data_clean->Add(h_p_bcg,-1);

  //CS estimation
  double intmin=1480;//1400;
  double intmax=1560;//1620;
  double L1520_cs=(CalcIntegral(hPPimPipPim_data_clean,intmin,intmax)-CalcIntegral(hPPimPipPim_urqmd,intmin,intmax)-CalcIntegral(hPPimPipPim_Ss,intmin,intmax))/(lum*L1520_eff/3)*1000.*100./6.666;// \mu barn
  //double L1520_cs=(CalcIntegral(hPPimPipPim_data_clean,intmin,intmax)-CalcIntegral(hPPimPipPim_urqmd,intmin,intmax)-CalcIntegral(hPPimPipPim_Ss,intmin,intmax))/(lum*L1520_eff/3)*1000.*100./6.666;// \mu barn
 
  cout<<"URQMD integral:"<<endl;
  cout<<CalcIntegral(hPPimPipPim_urqmd,intmin,intmax)<<endl;
  cout<<"Ss integral:"<<endl;
  cout<<CalcIntegral(hPPimPipPim_Ss,intmin,intmax)<<endl;
  cout<<"Clean signal integral"<<endl;
  cout<<CalcIntegral(hPPimPipPim_data_clean,intmin,intmax)<<endl;
  double L1520_error=hist_error(hPPimPipPim_data_clean,intmin,intmax)/(lum*L1520_eff/3)*1000*100./6.666;

  cout<<"Cross section estimation"<<endl;
  cout<<"For L(1520):"<<endl;
  cout<<"Efficiency: "<<L1520_eff<< " XC: "<<L1520_cs << "\mu b"<<endl;
  cout<<"L(1520) error: "<< L1520_error<<endl;
  //cout<<"For S(1385)+"<<endl;
  //cout<<"Efficiency: "<<S1385plus_eff<< " XC: "<<S1385plus_cs<< "\mu b"<<endl;
  //cout<<"For S(1385)-"<<endl;
  //cout<<"Efficiency: "<<S1385minus_eff<< " XC: "<<S1385minus_cs<< "\mu b"<<endl;
  //cout<<"A L(1520)/S(1385)+ ratio"<<endl;
  //cout<<L1520_cs/S1385plus_cs<<endl;
  //cout<<"A L(1520)/S(1385)- ratio"<<endl;
  //cout<<L1520_cs/S1385minus_cs<<endl;
  
  TCanvas* cOpt=new TCanvas("cOpt");  
  cOpt->Divide(2);
  cOpt->cd(1);
  //gPad->SetLogz();
  optymal->Draw("surf1");
  cOpt->cd(2);
  optymal_3D->SetMinimum(ch2_opt);
  optymal_3D->Draw("BOX2 Z");
  
  TCanvas* cSpectra=new TCanvas("cSpectra");
  cSpectra->Divide(2,2);
  cSpectra->cd(1);
  hPPimPipPim_data->Draw("e1");
  setStyleData(hPPimPipPim_data);
  hPPimPipPim_data->GetXaxis()->SetRangeUser(1300,2000);
  hPPimPipPim_bcg->Draw("same");
  setStyleSB(hPPimPipPim_bcg);
  hPPimPipPim_L1520->Draw("samehist");
  setStyleLs(hPPimPipPim_L1520);
  hPPimPipPim_Ss->Draw("samehist");
  setStyleSs(hPPimPipPim_Ss);
  //hPPimPipPim_Ssp->Draw("samehist");
  //setStyleSsp(hPPimPipPim_Ssp);
  hPPimPipPim_sum->Draw("samehist");
  setStyleSum(hPPimPipPim_sum);
  hPPimPipPim_urqmd->Draw("samehist");
  setStyleDpp(hPPimPipPim_urqmd);
  
  cSpectra->cd(2);
  hPPimPip_data->Draw("e1");
  setStyleData(hPPimPip_data);
  hPPimPip_data->GetXaxis()->SetRangeUser(1220,1500);
  hPPimPip_bcg->Draw("same");
  setStyleSB(hPPimPip_bcg);
  hPPimPip_L1520->Draw("samehist");
  setStyleLs(hPPimPip_L1520);
  hPPimPip_Ss->Draw("samehist");
  setStyleSs(hPPimPip_Ss);
  //hPPimPip_Ssp->Draw("samehist");
  //setStyleSsp(hPPimPip_Ssp);
  hPPimPip_sum->Draw("samehist");
  setStyleSum(hPPimPip_sum);
  hPPimPip_urqmd->Draw("samehist");
  setStyleDpp(hPPimPip_urqmd);
 
  
  cSpectra->cd(3);
  hPPimPim_data->Draw("e1");
  setStyleData(hPPimPim_data);
  hPPimPim_data->GetXaxis()->SetRangeUser(1220,1500);
  hPPimPim_bcg->Draw("same");
  setStyleSB(hPPimPim_bcg);
  hPPimPim_L1520->Draw("samehist");
  setStyleLs(hPPimPim_L1520);
  hPPimPim_Ss->Draw("samehist");
  setStyleSs(hPPimPim_Ss);
  //hPPimPim_Ssp->Draw("samehist");
  //setStyleSsp(hPPimPim_Ssp);
  hPPimPim_sum->Draw("samehist");
  setStyleSum(hPPimPim_sum);
  hPPimPim_urqmd->Draw("samehist");
  setStyleDpp(hPPimPim_urqmd);
 
  
  cSpectra->cd(4);

  TCanvas* cSpectra_clean=new TCanvas("cSpectra_clean");
  cSpectra_clean->Divide(2,2);
  cSpectra_clean->cd(1);
  hPPimPipPim_data_clean->Draw("e1");
  setStyleData(hPPimPipPim_data_clean);
  hPPimPipPim_data_clean->GetXaxis()->SetRangeUser(1300,2000);
  //hPPimPipPim_bcg->Draw("same");
  //setStyleSB(hPPimPipPim_bcg);
  hPPimPipPim_L1520->Draw("samehist");
  setStyleLs(hPPimPipPim_L1520);
  hPPimPipPim_Ss->Draw("samehist");
  setStyleSs(hPPimPipPim_Ss);
  //hPPimPipPim_Ssp->Draw("samehist");
  //setStyleSsp(hPPimPipPim_Ssp);
  hPPimPipPim_sum_clean->Draw("samehist");
  setStyleSum(hPPimPipPim_sum_clean);
  hPPimPipPim_urqmd->Draw("samehist");
  setStyleDpp(hPPimPipPim_urqmd);
  
  cSpectra_clean->cd(2);
  hPPimPip_data_clean->Draw("e1");
  setStyleData(hPPimPip_data_clean);
  hPPimPip_data_clean->GetXaxis()->SetRangeUser(1220,1500);
  //hPPimPip_bcg->Draw("same");
  //setStyleSB(hPPimPip_bcg);
  hPPimPip_L1520->Draw("samehist");
  setStyleLs(hPPimPip_L1520);
  hPPimPip_Ss->Draw("samehist");
  setStyleSs(hPPimPip_Ss);
  //hPPimPip_Ssp->Draw("samehist");
  //setStyleSsp(hPPimPip_Ssp);
  hPPimPip_sum_clean->Draw("samehist");
  setStyleSum(hPPimPip_sum_clean);
  hPPimPip_urqmd->Draw("samehist");
  setStyleDpp(hPPimPip_urqmd);
 
  
  cSpectra_clean->cd(3);
  hPPimPim_data_clean->Draw("e1");
  setStyleData(hPPimPim_data_clean);
  hPPimPim_data_clean->GetXaxis()->SetRangeUser(1220,1500);
  //hPPimPim_bcg->Draw("same");
  //setStyleSB(hPPimPim_bcg);
  hPPimPim_L1520->Draw("samehist");
  setStyleLs(hPPimPim_L1520);
  hPPimPim_Ss->Draw("samehist");
  setStyleSs(hPPimPim_Ss);
  //hPPimPim_Ssp->Draw("samehist");
  //setStyleSsp(hPPimPim_Ssp);
  hPPimPim_sum_clean->Draw("samehist");
  setStyleSum(hPPimPim_sum_clean);
  hPPimPim_urqmd->Draw("samehist");
  setStyleDpp(hPPimPim_urqmd);
 
  
  cSpectra_clean->cd(4);
  
  
  TCanvas* cPPip=new TCanvas("cPPip");
  hPPip_data->Draw("e1");
  setStyleData(hPPip_data);
  //hPPip_data->GetXaxis()->SetRangeUser(1220,1500);
  hPPip_bcg->Draw("samee1");
  setStyleSB(hPPip_bcg);
  hPPip_L1520->Draw("samehist");
  setStyleLs(hPPip_L1520);
  hPPip_Ss->Draw("samehist");
  setStyleSs(hPPip_Ss);
  //hPPip_Ssp->Draw("samehist");
  //setStyleSsp(hPPip_Ssp);
  hPPip_sum->Draw("samehist");
  setStyleSum(hPPip_sum);
  hPPip_urqmd->Draw("samehist");
  setStyleDpp(hPPip_urqmd);

  TCanvas* cPtY=new TCanvas("cPtY");
  cPtY->Divide(2);
  cPtY->cd(1);
  h_pt_data->Draw("e1");
  setStyleData(h_pt_data);
  //h_pt_data->GetXaxis()->SetRangeUser(1220,1500);
  h_pt_bcg->Draw("samee1");
  setStyleSB(h_pt_bcg);
  h_pt_L1520->Draw("samehist");
  setStyleLs(h_pt_L1520);
  h_pt_Ss->Draw("samehist");
  setStyleSs(h_pt_Ss);
  //h_pt_Ssp->Draw("samehist");
  //setStyleSsp(h_pt_Ssp);
  h_pt_sum->Draw("samehist");
  setStyleSum(h_pt_sum);
  h_pt_urqmd->Draw("samehist");
  setStyleDpp(h_pt_urqmd);
  cPtY->cd(2);
  h_w_data->Draw("e1");
  setStyleData(h_w_data);
  //h_w_data->GetXaxis()->SetRangeUser(1220,1500);
  h_w_bcg->Draw("samee1");
  setStyleSB(h_w_bcg);
  h_w_L1520->Draw("samehist");
  setStyleLs(h_w_L1520);
  h_w_Ss->Draw("samehist");
  setStyleSs(h_w_Ss);
  //h_w_Ssp->Draw("samehist");
  //setStyleSsp(h_w_Ssp);
  h_w_sum->Draw("samehist");
  setStyleSum(h_w_sum);
  h_w_urqmd->Draw("samehist");
  setStyleDpp(h_w_urqmd);

  TCanvas* cPtY_clean=new TCanvas("cPtY_clean");
  cPtY_clean->Divide(2);
  cPtY_clean->cd(1);
  h_pt_data_clean->Draw("e1");
  setStyleData(h_pt_data_clean);
  //h_pt_data_clean->GetXaxis()->SetRangeUser(1300,2000);
  //h_pt_bcg->Draw("same");
  //setStyleSB(h_pt_bcg);
  h_pt_L1520->Draw("samehist");
  setStyleLs(h_pt_L1520);
  h_pt_Ss->Draw("samehist");
  setStyleSs(h_pt_Ss);
  //h_pt_Ssp->Draw("samehist");
  //setStyleSsp(h_pt_Ssp);
  h_pt_sum_clean->Draw("samehist");
  setStyleSum(h_pt_sum_clean);
  h_pt_urqmd->Draw("samehist");
  setStyleDpp(h_pt_urqmd);
  hPP_pt->Draw("same");
  
  cPtY_clean->cd(2);
  h_w_data_clean->Draw("e1");
  setStyleData(h_w_data_clean);
  //h_w_data_clean->GetXaxis()->SetRangeUser(1220,1500);
  //h_w_bcg->Draw("same");
  //setStyleSB(h_w_bcg);
  h_w_L1520->Draw("samehist");
  setStyleLs(h_w_L1520);
  h_w_Ss->Draw("samehist");
  setStyleSs(h_w_Ss);
  //h_w_Ssp->Draw("samehist");
  //setStyleSsp(h_w_Ssp);
  h_w_sum_clean->Draw("samehist");
  setStyleSum(h_w_sum_clean);
  h_w_urqmd->Draw("samehist");
  setStyleDpp(h_w_urqmd);
  hPP_w->Draw("same");
  
  TCanvas* cThetaP_clean=new TCanvas("cThetaP_clean");
  cThetaP_clean->Divide(2);
  cThetaP_clean->cd(1);
  h_theta_data_clean->Draw("e1");
  setStyleData(h_theta_data_clean);
  //h_theta_data_clean->GetXaxis()->SetRangeUser(1300,2000);
  //h_theta_bcg->Draw("same");
  //setStyleSB(h_theta_bcg);
  h_theta_L1520->Draw("samehist");
  setStyleLs(h_theta_L1520);
  h_theta_Ss->Draw("samehist");
  setStyleSs(h_theta_Ss);
  //h_theta_Ssp->Draw("samehist");
  //setStyleSsp(h_theta_Ssp);
  h_theta_sum_clean->Draw("samehist");
  setStyleSum(h_theta_sum_clean);
  h_theta_urqmd->Draw("samehist");
  setStyleDpp(h_theta_urqmd);
  
  cThetaP_clean->cd(2);
  h_p_data_clean->Draw("e1");
  setStyleData(h_p_data_clean);
  //h_p_data_clean->GetXaxis()->SetRangeUser(1220,1500);
  //h_p_bcg->Draw("same");
  //setStyleSB(h_p_bcg);
  h_p_L1520->Draw("samehist");
  setStyleLs(h_p_L1520);
  h_p_Ss->Draw("samehist");
  setStyleSs(h_p_Ss);
  //h_p_Ssp->Draw("samehist");
  //setStyleSsp(h_p_Ssp);
  h_p_sum_clean->Draw("samehist");
  setStyleSum(h_p_sum_clean);
  h_p_urqmd->Draw("samehist");
  setStyleDpp(h_p_urqmd);

  TH1F *hPPimPipPim_data_URQMD_substructed=(TH1F*)hPPimPipPim_data_clean->Clone("hPPimPipPim_data_URQMD_substructed");
  hPPimPipPim_data_URQMD_substructed->Add(hPPimPipPim_urqmd, -1);
  TCanvas* cComparison=new TCanvas("cComparison","cComparison");
  cComparison->cd();
  hPPimPipPim_data_clean->Draw();
  hPP_L1520->Scale(hPPimPipPim_data_URQMD_substructed->GetBinContent(hPPimPipPim_data_URQMD_substructed->GetMaximumBin())/hPP_L1520->GetBinContent(hPP_L1520->GetMaximumBin()));
  hPPimPipPim_data_URQMD_substructed->Draw("same");
  hPPimPipPim_data_URQMD_substructed->SetLineColor(kRed);
  hPPimPipPim_data_URQMD_substructed->SetMarkerColor(kRed);
  hPPimPipPim_data_URQMD_substructed->SetLineWidth(3);
  hPP_L1520->Draw("same");
  hPP_L1520->SetLineColor(kGray+2);
  hPP_L1520->SetMarkerColor(kGray+2);

  cOpt->Write();
  cSpectra->Write();
  cSpectra_clean->Write();
  cPtY_clean->Write();
  cThetaP_clean->Write();
  cPPip->Write();
  cPtY->Write();
  cComparison->Write();
  return 0;
}










