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


int fitL1520andSigmaandDpp(void)
{
  TFile *fData_SB=new TFile("SB_experiment.root","read");
  //TFile *fL1520_SB=new TFile("SB_sim_L1520thermal.root","read");
  TFile *fL1520_SB=new TFile("SB_sim_L1520thermal_125_600.root","read");
  //TFile *fSsPimKz_SB=new TFile("SB_sim_SsPimKzthermal.root","read");
  TFile *fSsPimKz_SB=new TFile("SB_sim_SsPimKzthermal_125_600.root","read");
  TFile *fSsPipKz_SB=new TFile("SB_sim_SsPipKzthermal_125_600.root","read");
  TFile *fSDppK0_SB=new TFile("SB_sim_SDppK0.root","read");
  TFile *fLDppK0_SB=new TFile("SB_sim_LDppK0.root","read");
  //TFile *fL1520K0_perfect_L1116=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/L1520K0_true_L1116.root","read");
  //TFile *fL1520K0_perfect_L1520=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/L1520K0_true_L1520.root","read");
  //TFile *fL1520_perfect_L1116=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/L1520_true_L1116.root","read");
  //TFile *fL1520_perfect_L1520=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/L1520_true_L1520.root","read");
  //TFile *fSsPimKz_perfect_L1116=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/SsPimKz_real_L1116.root","read");
  
  //TFile *fL1520_perfect_L1116=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/L1520_125_600_true_L1116.root","read");
  //TFile *fL1520_perfect_L1520=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/L1520_125_600_true_L1520.root","read");
  //TFile *fSsPimKz_perfect_L1116=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/SsPimKz_real_L1116.root","read");

  TFile *fout=new TFile("fitL1520andSigmaandDpp_output.root","recreate");

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
  TH1F* hPPimPipPim_LDppKz=(TH1F*)fLDppK0_SB->Get("data");
  hPPimPipPim_LDppKz->SetName("hPPimPipPim_LDppKz");
  hPPimPipPim_LDppKz->Rebin(rebin);
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
  TH1F* hPPimPip_LDppKz=(TH1F*)fLDppK0_SB->Get("hMPPimPip");
  hPPimPip_LDppKz->SetName("hPPimPip_LDppKz");
  hPPimPip_LDppKz->Rebin(rebin2);
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
  TH1F* hPPimPim_LDppKz=(TH1F*)fLDppK0_SB->Get("hMPPimPim");
  hPPimPim_LDppKz->SetName("hPPimPim_LDppKz");
  hPPimPim_LDppKz->Rebin(rebin2);
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
  TH1F* hPPip_LDppKz=(TH1F*)fLDppK0_SB->Get("hMPPip_final");
  hPPip_LDppKz->SetName("hPPip_LDppKz");
  hPPip_LDppKz->Rebin(rebin3);
  TH1F* hPPip_SDppKz=(TH1F*)fSDppK0_SB->Get("hMPPip_final");
  hPPip_SDppKz->SetName("hPPip_SDppKz");
  hPPip_SDppKz->Rebin(rebin3);

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
  double LDppKz_eff=hPPimPipPim_LDppKz->Integral()/(120.*TMath::Power(10,6));
  double SDppKz_eff=hPPimPipPim_SDppKz->Integral()/(120.*TMath::Power(10,6));
  
  double lum=1.04*TMath::Power(10,7);//mb
  double arbitrary_scale=1;
  
  hPPimPipPim_L1520->Scale(scale/hPPimPipPim_L1520->Integral());
  hPPimPipPim_Ss->Scale(scale/hPPimPipPim_Ss->Integral());
  hPPimPipPim_Ssp->Scale(scale/hPPimPipPim_Ssp->Integral());
  //hPPimPipPim_LDppKz->Scale(1./hPPimPipPim_LDppKz->Integral()*lum*LDppKz_eff/3*29.45/1000*TMath::Power(93,2/3)*arbitrary_scale);
  //hPPimPipPim_SDppKz->Scale(1./hPPimPipPim_SDppKz->Integral()*lum*SDppKz_eff/3*9.26/1000*TMath::Power(93,2/3)*arbitrary_scale);
  hPPimPipPim_LDppKz->Scale(scale/hPPimPipPim_LDppKz->Integral());
  hPPimPipPim_SDppKz->Scale(scale/hPPimPipPim_SDppKz->Integral());
 
  hPPimPip_L1520->Scale(scale/hPPimPip_L1520->Integral());
  hPPimPip_Ss->Scale(scale/hPPimPip_Ss->Integral());
  hPPimPip_Ssp->Scale(scale/hPPimPip_Ssp->Integral());
  //hPPimPip_LDppKz->Scale(1./hPPimPip_LDppKz->Integral()*lum*LDppKz_eff/3*29.45/1000*TMath::Power(93,2/3)*arbitrary_scale);
  //hPPimPip_SDppKz->Scale(1./hPPimPip_SDppKz->Integral()*lum*SDppKz_eff/3*9.26/1000*TMath::Power(93,2/3)*arbitrary_scale);
  hPPimPip_LDppKz->Scale(scale/hPPimPip_LDppKz->Integral());
  hPPimPip_SDppKz->Scale(scale/hPPimPip_SDppKz->Integral());
 
  
  hPPip_L1520->Scale(scale/hPPimPim_L1520->Integral());
  hPPip_Ss->Scale(scale/hPPimPim_Ss->Integral());
  hPPip_Ssp->Scale(scale/hPPimPim_Ssp->Integral());
  //hPPip_LDppKz->Scale(1./hPPimPim_LDppKz->Integral()*lum*LDppKz_eff/3*29.45/1000*TMath::Power(93,2/3)*arbitrary_scale);
  //hPPip_SDppKz->Scale(1./hPPimPim_SDppKz->Integral()*lum*SDppKz_eff/3*9.26/1000*TMath::Power(93,2/3)*arbitrary_scale);
  hPPip_LDppKz->Scale(scale/hPPip_LDppKz->Integral());
  hPPip_SDppKz->Scale(scale/hPPip_SDppKz->Integral());
 
  
  hPPimPim_L1520->Scale(scale/hPPimPim_L1520->Integral());
  hPPimPim_Ss->Scale(scale/hPPimPim_Ss->Integral());
  hPPimPim_Ssp->Scale(scale/hPPimPim_Ssp->Integral());
  //hPPimPim_LDppKz->Scale(1./hPPimPim_LDppKz->Integral()*lum*LDppKz_eff/3*29.45/1000*TMath::Power(93,2/3)*arbitrary_scale);
  //hPPimPim_SDppKz->Scale(1./hPPimPim_SDppKz->Integral()*lum*SDppKz_eff/3*9.26/1000*TMath::Power(93,2/3)*arbitrary_scale);
  hPPimPim_LDppKz->Scale(scale/hPPimPim_LDppKz->Integral());
  hPPimPim_SDppKz->Scale(scale/hPPimPim_SDppKz->Integral());
 
  
  //skalowanie wkladow z symulacji
  double scaleL1520=0.54321;
  double scaleSs=0.54321;
  double scaleSsp=0.54321;
  double scaleDpp=0.54321;
  double scaleL1520_opt=0.001;
  double scaleSs_opt=0.0001;
  double scaleSsp_opt=0.0001;
  double scaleDpp_opt=0.0001;
  double ch2_opt=100000;
  const int steps=50;
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
	      scaleL1520=2.0*n*1./steps;
	      scaleSs=1.0*m*1./steps;
	      scaleDpp=2.0*l*1./steps;
	      //scaleSs=0.001;
	      //scaleSsp=1.4*l*1./steps;
	      //scaleSsp=0.001;
	      //scaleSsp=scaleSs;
	      
	      LPPimPipPim_sum->Reset();
	      LPPimPipPim_sum->Add(hPPimPipPim_bcg);
	      LPPimPipPim_sum->Add(hPPimPipPim_L1520,scaleL1520);
	      LPPimPipPim_sum->Add(hPPimPipPim_Ss,scaleSs);
	      LPPimPipPim_sum->Add(hPPimPipPim_LDppKz,scaleDpp);
	      //LPPimPipPim_sum->Add(hPPimPipPim_Ssp,scaleSsp);
	
	      LPPimPip_sum->Reset();
	      LPPimPip_sum->Add(hPPimPip_bcg);
	      LPPimPip_sum->Add(hPPimPip_L1520,scaleL1520);
	      LPPimPip_sum->Add(hPPimPip_Ss,scaleSs);
	      LPPimPip_sum->Add(hPPimPip_LDppKz,scaleDpp);
	      //LPPimPip_sum->Add(hPPimPip_Ssp,scaleSsp);

	      LPPimPim_sum->Reset();
	      LPPimPim_sum->Add(hPPimPim_bcg);
	      LPPimPim_sum->Add(hPPimPim_L1520,scaleL1520);
	      LPPimPim_sum->Add(hPPimPim_Ss,scaleSs);
	      LPPimPim_sum->Add(hPPimPim_LDppKz,scaleDpp);
	      //LPPimPim_sum->Add(hPPimPim_Ssp,scaleSsp);

	      
	      /*
	      double chi2_PPimPipPim=hPPimPipPim_data->Chi2Test(LPPimPipPim_sum,"chi2/NDF");
	      double chi2_PPimPip=hPPimPip_data->Chi2Test(LPPimPip_sum,"chi2/NDF");
	      double chi2_PPimPim=hPPimPim_data->Chi2Test(LPPimPim_sum,"chi2/NDF");
	      */
	      double chi2_PPimPipPim=test_ch2(hPPimPipPim_data,LPPimPipPim_sum);
	      double chi2_PPimPip=test_ch2(hPPimPip_data,LPPimPip_sum);
	      double chi2_PPimPim=test_ch2(hPPimPim_data,LPPimPim_sum);
	      
	      double ch2_total=1.0/3.0*(chi2_PPimPipPim+chi2_PPimPip+chi2_PPimPim);
	      //double ch2_total=chi2_PPimPip+chi2_PPimPipPim;
	      
	      if(ch2_total<ch2_opt)
		{
		  scaleSs_opt=scaleSs;
		  scaleL1520_opt=scaleL1520;
		  scaleSsp_opt=scaleSsp;
		  scaleDpp_opt=scaleDpp;
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
  cout<<"L1520: "<<scaleL1520_opt<<" S(1385)+: "<<scaleSs_opt<<" D++: "<<scaleDpp_opt<<endl;
  
  hPPimPipPim_L1520->Scale(scaleL1520_opt);
  hPPimPipPim_Ss->Scale(scaleSs_opt);
  hPPimPipPim_Ssp->Scale(scaleSsp_opt);
  hPPimPipPim_LDppKz->Scale(scaleDpp_opt);
 
  hPPimPip_L1520->Scale(scaleL1520_opt);
  hPPimPip_Ss->Scale(scaleSs_opt);
  hPPimPip_Ssp->Scale(scaleSsp_opt);
  hPPimPip_LDppKz->Scale(scaleDpp_opt);

  hPPimPim_L1520->Scale(scaleL1520_opt);
  hPPimPim_Ss->Scale(scaleSs_opt);
  hPPimPim_Ssp->Scale(scaleSsp_opt);
  hPPimPim_LDppKz->Scale(scaleDpp_opt);

  hPPip_L1520->Scale(scaleL1520_opt);
  hPPip_Ss->Scale(scaleSs_opt);
  hPPip_Ssp->Scale(scaleSsp_opt);
  hPPip_LDppKz->Scale(scaleDpp_opt);

  //additional histograms, just for drwaings
  TH1F* hPPimPipPim_sum=hPPimPipPim_bcg->Clone("hPPimPipPim_sum");
  hPPimPipPim_sum->Add(hPPimPipPim_L1520);
  hPPimPipPim_sum->Add(hPPimPipPim_Ss);
  //hPPimPipPim_sum->Add(hPPimPipPim_Ssp);
  hPPimPipPim_sum->Add(hPPimPipPim_LDppKz);
  

  TH1F* hPPimPip_sum=hPPimPip_bcg->Clone("hPPimPip_sum");
  hPPimPip_sum->Add(hPPimPip_L1520);
  hPPimPip_sum->Add(hPPimPip_Ss);
  //hPPimPip_sum->Add(hPPimPip_Ssp);
  hPPimPip_sum->Add(hPPimPip_LDppKz);
  
  TH1F* hPPimPim_sum=hPPimPim_bcg->Clone("hPPimPim_sum");
  hPPimPim_sum->Add(hPPimPim_L1520);
  hPPimPim_sum->Add(hPPimPim_Ss);
  //hPPimPim_sum->Add(hPPimPim_Ssp);
  hPPimPim_sum->Add(hPPimPim_LDppKz);
  

  TH1F* hPPip_sum=hPPip_bcg->Clone("hPPip_sum");
  hPPip_sum->Add(hPPip_L1520);
  hPPip_sum->Add(hPPip_Ss);
  //hPPip_sum->Add(hPPip_Ssp);
  hPPip_sum->Add(hPPip_LDppKz);

  //with substructed SB
  TH1F* hPPimPipPim_sum_clean=hPPimPipPim_Ssp->Clone("hPPimPipPim_sum_clean");
  hPPimPipPim_sum_clean->Reset();
  hPPimPipPim_sum_clean->Add(hPPimPipPim_L1520);
  hPPimPipPim_sum_clean->Add(hPPimPipPim_Ss);
  hPPimPipPim_sum_clean->Add(hPPimPipPim_LDppKz);
  
  TH1F* hPPimPip_sum_clean=hPPimPip_Ssp->Clone("hPPimPip_sum_clean");
  hPPimPip_sum_clean->Reset();
  hPPimPip_sum_clean->Add(hPPimPip_L1520);
  hPPimPip_sum_clean->Add(hPPimPip_Ss);
  hPPimPip_sum_clean->Add(hPPimPip_LDppKz);
  
  TH1F* hPPimPim_sum_clean=hPPimPim_Ssp->Clone("hPPimPim_sum_clean");
  hPPimPim_sum_clean->Reset();
  hPPimPim_sum_clean->Add(hPPimPim_L1520);
  hPPimPim_sum_clean->Add(hPPimPim_Ss);
  hPPimPim_sum_clean->Add(hPPimPim_LDppKz);
    
  TH1F* hPPip_sum_clean=hPPip_Ssp->Clone("hPPip_sum_clean");
  hPPip_sum_clean->Reset();
  hPPip_sum_clean->Add(hPPip_L1520);
  hPPip_sum_clean->Add(hPPip_Ss);
  hPPip_sum_clean->Add(hPPip_LDppKz);
    
  TH1F* hPPimPipPim_data_clean=hPPimPipPim_data->Clone("hPPimPipPim_data_clean");
  hPPimPipPim_data_clean->Add(hPPimPipPim_bcg,-1);
  TH1F* hPPimPip_data_clean=hPPimPip_data->Clone("hPPimPip_data_clean");
  hPPimPip_data_clean->Add(hPPimPip_bcg,-1);
  TH1F* hPPimPim_data_clean=hPPimPim_data->Clone("hPPimPim_data_clean");
  hPPimPim_data_clean->Add(hPPimPim_bcg,-1);

  //CS estimation
  double intmin=1400;
  double intmax=1620;
  double L1520_cs=(CalcIntegral(hPPimPipPim_data_clean,intmin,intmax)-CalcIntegral(hPPimPipPim_LDppKz,intmin,intmax)-CalcIntegral(hPPimPipPim_Ss,intmin,intmax))/(lum*L1520_eff/3)*1000.*100./6.666;// \mu barn
  double L1520_error=hist_error(hPPimPipPim_data_clean,intmin,intmax)/(lum*L1520_eff/3)*1000*100./6.666;

  cout<<"Cross section estimation"<<endl;
  cout<<"For L(1520):"<<endl;
  cout<<"Efficiency: "<<L1520_eff<< " XC: "<<L1520_cs << "\mu b"<<endl;
  cout<<"L(1520) error: "<< L1520_error<<endl;
  cout<<"For S(1385)+"<<endl;
  //cout<<"Efficiency: "<<S1385plus_eff<< " XC: "<<S1385plus_cs<< "\mu b"<<endl;
  cout<<"For S(1385)-"<<endl;
  //cout<<"Efficiency: "<<S1385minus_eff<< " XC: "<<S1385minus_cs<< "\mu b"<<endl;
  cout<<"A L(1520)/S(1385)+ ratio"<<endl;
  //cout<<L1520_cs/S1385plus_cs<<endl;
  cout<<"A L(1520)/S(1385)- ratio"<<endl;
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
  hPPimPipPim_LDppKz->Draw("samehist");
  setStyleDpp(hPPimPipPim_LDppKz);
  
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
  hPPimPip_LDppKz->Draw("samehist");
  setStyleDpp(hPPimPip_LDppKz);
 
  
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
  hPPimPim_LDppKz->Draw("samehist");
  setStyleDpp(hPPimPim_LDppKz);
 
  
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
  hPPimPipPim_LDppKz->Draw("samehist");
  setStyleDpp(hPPimPipPim_LDppKz);
  
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
  hPPimPip_LDppKz->Draw("samehist");
  setStyleDpp(hPPimPip_LDppKz);
 
  
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
  hPPimPim_LDppKz->Draw("samehist");
  setStyleDpp(hPPimPim_LDppKz);
 
  
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
  hPPip_LDppKz->Draw("samehist");
  setStyleDpp(hPPip_LDppKz);
 
  

  cOpt->Write();
  cSpectra->Write();
  cSpectra_clean->Write();
  cPPip->Write();
  return 0;
}










