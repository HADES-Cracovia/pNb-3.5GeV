void set_Y_name(TH1* hist)
{
  char name[10000]; // enough to hold all numbers up to 64-bits
  sprintf(name, "#frac{counts}{%.1f MeV}", hist->GetBinWidth(2));
  cout<<"Y axis name: "<<name<<endl;
  hist->GetYaxis()->SetTitle(name);
}

void setHistogramStyleData(TH1* hist)
{
  hist->SetLineWidth(2);

  hist->SetMarkerColor(hist->GetLineColor());
  hist->SetMarkerSize(2);
  hist->SetMarkerStyle(8);
  set_Y_name(hist);

  //hist->GetXaxis()->SetLabelFont(42);
  hist->GetXaxis()->SetNdivisions(508);
  //hist->GetXaxis()->SetLabelSize(0.05);
  // hist->GetXaxis()->SetTitleSize(0.05);
  //hist->GetXaxis()->SetTitleOffset(1.1);
  //hist->GetXaxis()->SetTitleFont(42);

  hist->GetYaxis()->SetNdivisions(508);
  //hist->GetYaxis()->SetLabelFont(42);
  //hist->GetYaxis()->SetLabelSize(0.05);
  //hist->GetYaxis()->SetTitleOffset(0.8);
  //hist->GetYaxis()->SetTitleSize(0.05);
  //hist->GetYaxis()->SetTitleFont(42);

}

void setHistogramStyleSimul(TH1* hist)
{
  hist->SetLineWidth(2);

  hist->SetMarkerColor(hist->GetLineColor());
  hist->SetMarkerSize(2);
  hist->SetMarkerStyle(8);
  hist->SetFillColor(hist->GetLineColor());
  set_Y_name(hist);
  hist->SetFillStyle(3145);

  //hist->GetXaxis()->SetLabelFont(42);
  hist->GetXaxis()->SetNdivisions(508);
  //hist->GetXaxis()->SetLabelSize(0.05);
  //hist->GetXaxis()->SetTitleSize(0.05);
  //hist->GetXaxis()->SetTitleOffset(1.1);
  //hist->GetXaxis()->SetTitleFont(42);

  hist->GetYaxis()->SetNdivisions(508);
  //hist->GetYaxis()->SetLabelFont(42);
  //hist->GetYaxis()->SetLabelSize(0.05);
  //hist->GetYaxis()->SetTitleOffset(0.8);
  //hist->GetYaxis()->SetTitleSize(0.05);
  //hist->GetYaxis()->SetTitleFont(42);

}

void setLineStyle(TLine* line)
{
  line->SetLineWidth(4);
  line->SetLineStyle(9);
  line->SetLineColor(kRed-3);
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

void scale_error(TH1* hist, double err,bool verbose=0)
{
  cout<<endl<<"***scaling the histogram errors according to one relative error***"<<endl;
  cout<<"hist name"<<hist->GetName()<<endl;
  cout<<"scaling error"<<err<<endl;

  int nbin_min=1;
  int nbin_max=hist->GetNbinsX();
  for(int i=nbin_min;i<=nbin_max;i++)
    {
      double cont=hist->GetBinContent(i);
      double error=hist->GetBinContent(i)*err;
      if(verbose)
	{
	  cout<<"bin number: "<<i<<" bin contetnt: "<<cont<<endl;
	  cout<<"                       bin error:  "<<error<<endl;
	}
      hist->SetBinError(i,error);
    }

  cout<<"***end of scale_error function***"<<endl<<endl;

}

/*
void normalize(TH1* hist)
{
  for (Int_t j=1; j<hist->GetNbinsX()+1; ++j)
    {
      double scale=1.0/(3.13 * TMath::Power(10,8)) *1000; //to get micro barn
      double binErr=hist->GetBinError(j);
      hist->SetBinContent(j, hist->GetBinContent(j) / hist->GetBinWidth(j) *scale);
      //hist->SetBinError( j, TMath::Sqrt( hist->GetBinContent(j) ) );
      hist->SetBinError( j,  binErr/ hist->GetBinWidth(j) * scale );
      hist->GetYaxis()->SetTitle("#frac{dN}{dE} [#frac{#mu b}{MeV}]");
    }
    }  */

int draw_norm(void)
{

  TFile *fileS1385 = new TFile("SB_sim_S1385pK0.root","READ");
  TFile *fileSDpp = new TFile("SB_sim_SDppK0.root","READ");
  TFile *fileLDpp = new TFile("SB_sim_LDppK0.root","READ");
  TFile *fileL1520= new TFile("SB_sim_L1520pippim.root","READ");
  TFile *fileLK0=new TFile("SB_sim_LK0ppip.root","READ");
  TFile *fileExp= new TFile("SB_experiment.root","READ");
  //TFile *fileEM=new TFile("nowa_kolejnosc.root","READ");
  TFile *fileEM=new TFile("EM2.root","READ");


  TH1F *hexperiment_L=(TH1F*)fileExp->Get("hMPPim_TMVA_K0mass");
  TH1F *hexperiemnt_K0=(TH1F*)fileExp->Get("hMPipPim_TMVA_Lmass");
  TH1F *hsim_L=(TH1F*)fileLK0->Get("hMPPim_TMVA_K0mass");
  TH1F *hsim_K0=(TH1F*)fileLK0->Get("hMPipPim_TMVA_Lmass");
  TF1 *fK0_experiment_fit=(TF1 *)fileExp->Get("K0_fit");
  TF1 *fK0_experiment_sig=(TF1 *)fileExp->Get("K0_signal");
  TF1 *fL1116_experiment_fit=(TF1 *)fileExp->Get("L1116_fit");
  TF1 *fL1116_experiment_sig=(TF1 *)fileExp->Get("L1116_signal");
  TH1F *hexperiment_SB_spectrum=(TH1F*)fileExp->Get("orginal_spectrum");


  TF1* fVoigt_bg=(TF1*)fileExp->Get("fVoigt_bg");
  TF1* fVoigt=(TF1*)fileExp->Get("fVoigt");
  TF1* fbg=(TF1*)fileExp->Get("fbg");
  TF1 *voigt=new TF1("signal_voit","[0]*TMath::Voigt(x-[1],[2],[3],4)",1380,1750); //only for pure signal

  TLine* line1=(TLine*)fileExp->Get("line1");
  TLine* line2=(TLine*)fileExp->Get("line2");
  TLine* line3=(TLine*)fileExp->Get("line3");
  TLine* line4=(TLine*)fileExp->Get("line4");


  //TFile *output= new TFile("pictures.root","RECREATE");
  TH1F *hS1385_data = (TH1F*)fileS1385->Get("data");
  hS1385_data->SetName("hS1385_data");
  hS1385_data->Sumw2(kFALSE);
  TH1F *hSDpp_data = (TH1F*)fileSDpp->Get("data");
  hSDpp_data->SetName("hSDpp_data");
  hSDpp_data->Sumw2(kFALSE);;
  TH1F *hLDpp_data = (TH1F*)fileLDpp->Get("data");
  hLDpp_data->SetName("hLDpp_data");
  hLDpp_data->Sumw2(kFALSE);
  TH1F *hexperiment_data=(TH1F*)fileExp->Get("data");
  hexperiment_data->SetName("hexperiment_data");
  //hexperiment_data->Sumw2();
  TH1F *hL1520_data=(TH1F*)fileL1520->Get("data");
  hL1520_data->SetName("hL1520_data");
  hL1520_data->Sumw2(kFALSE);
  TH1F *hsum_data=(TH1F*)hS1385_data->Clone("hsum_data");
  hsum_data->Reset();

  TH1F *hS1385_hMPipPim_signal = (TH1F*)fileS1385->Get("hMPipPim_signal");
  hS1385_hMPipPim_signal->SetName("hS1385_hMPipPim_signal");
  hS1385_hMPipPim_signal->Sumw2(kFALSE);
  TH1F *hSDpp_hMPipPim_signal = (TH1F*)fileSDpp->Get("hMPipPim_signal");
  hSDpp_hMPipPim_signal->SetName("hSDpp_hMPipPim_signal");
  hSDpp_hMPipPim_signal->Sumw2(kFALSE);;
  TH1F *hLDpp_hMPipPim_signal = (TH1F*)fileLDpp->Get("hMPipPim_signal");
  hLDpp_hMPipPim_signal->SetName("hLDpp_hMPipPim_signal");
  hLDpp_hMPipPim_signal->Sumw2(kFALSE);
  TH1F *hexperiment_hMPipPim_signal=(TH1F*)fileExp->Get("hMPipPim_signal");
  hexperiment_hMPipPim_signal->SetName("hexperiment_hMPipPim_signal");
  //hexperiment_hMPipPim_signal->Sumw2();
  TH1F *hL1520_hMPipPim_signal=(TH1F*)fileL1520->Get("hMPipPim_signal");
  hL1520_hMPipPim_signal->SetName("hL1520_hMPipPim_signal");
  hL1520_hMPipPim_signal->Sumw2(kFALSE);
  TH1F *hsum_hMPipPim_signal=(TH1F*)hS1385_hMPipPim_signal->Clone("hsum_hMPipPim_signal");
  hsum_hMPipPim_signal->Reset();

  TH1F *hS1385_background = (TH1F*)fileS1385->Get("background");
  hS1385_background->SetName("hS1385_background");
  hS1385_background->Sumw2(kFALSE);
  TH1F *hSDpp_background = (TH1F*)fileSDpp->Get("background");
  hSDpp_background->SetName("hSDpp_background");
  hSDpp_background->Sumw2(kFALSE);
  TH1F *hLDpp_background = (TH1F*)fileLDpp->Get("background");
  hLDpp_background->SetName("hLDpp_background");
  hLDpp_background->Sumw2(kFALSE);
  TH1F *hexperiment_background=(TH1F*)fileExp->Get("background");
  hexperiment_background->SetName("hexperiment_background");
  //hexperiment_background->Sumw2();
  TH1F *hL1520_background=(TH1F*)fileL1520->Get("background");
  hL1520_background->SetName("hL1520_background");
  hL1520_background->Sumw2(kFALSE);

  TH1F *hS1385_hMPipPim_background = (TH1F*)fileS1385->Get("hMPipPim_background");
  hS1385_hMPipPim_background->SetName("hS1385_hMPipPim_background");
  hS1385_hMPipPim_background->Sumw2(kFALSE);
  TH1F *hSDpp_hMPipPim_background = (TH1F*)fileSDpp->Get("hMPipPim_background");
  hSDpp_hMPipPim_background->SetName("hSDpp_hMPipPim_background");
  hSDpp_hMPipPim_background->Sumw2(kFALSE);
  TH1F *hLDpp_hMPipPim_background = (TH1F*)fileLDpp->Get("hMPipPim_background");
  hLDpp_hMPipPim_background->SetName("hLDpp_hMPipPim_background");
  hLDpp_hMPipPim_background->Sumw2(kFALSE);
  TH1F *hexperiment_hMPipPim_background=(TH1F*)fileExp->Get("hMPipPim_background");
  hexperiment_hMPipPim_background->SetName("hexperiment_hMPipPim_background");
  //hexperiment_hMPipPim_background->Sumw2();
  TH1F *hL1520_hMPipPim_background=(TH1F*)fileL1520->Get("hMPipPim_background");
  hL1520_hMPipPim_background->SetName("hL1520_hMPipPim_background");
  hL1520_hMPipPim_background->Sumw2(kFALSE);

  TH1F *hEM_data=(TH1F*)fileEM->Get("h_m_inv_p_pim_pip_pim_signal");
  hEM_data->SetName("hEM_data");
  hEM_data->Sumw2();
  TH1F *hEM_background=(TH1F*)fileEM->Get("h_m_inv_p_pim_pip_pim_SB");
  hEM_background->SetName("hEM_background");
  hEM_background->Sumw2();

  //w part
  TH1F *hexperiment_L1520_w=(TH1F*)fileExp->Get("hL1520_w");
  hexperiment_L1520_w->SetName("hexperiment_L1520_w");
  hexperiment_L1520_w->Sumw2();
  TH1F *hL1520_L1520_w=(TH1F*)fileL1520->Get("hL1520_w");
  hL1520_L1520_w->SetName("hL1520_L1520_w");
  hL1520_L1520_w->Sumw2(kFALSE);
  TH1F *hLDpp_L1520_w=(TH1F*)fileExp->Get("hL1520_w");
  hLDpp_L1520_w->SetName("hLDpp_L1520_w");
  hLDpp_L1520_w->Sumw2(kFALSE);
  TH1F *hSDpp_L1520_w=(TH1F*)fileExp->Get("hL1520_w");
  hSDpp_L1520_w->SetName("hSDpp_L1520_w");
  hSDpp_L1520_w->Sumw2(kFALSE);
  TH1F *hS1385_L1520_w=(TH1F*)fileExp->Get("hL1520_w");
  hS1385_L1520_w->SetName("hS1385_L1520_w");
  hS1385_L1520_w->Sumw2(kFALSE);
  TH1F *hEM_L1520_w=(TH1F*)fileEM->Get("hL1520_w");
  hEM_L1520_w->SetName("hEM_L1520_w");
  hEM_L1520_w->Sumw2();

  TH1F *hexperiment_L1520_w_SB=(TH1F*)fileExp->Get("hL1520_w_SB");
  hexperiment_L1520_w_SB->SetName("hexperiment_L1520_w_SB");
  hexperiment_L1520_w_SB->Sumw2();
  TH1F *hL1520_L1520_w_SB=(TH1F*)fileL1520->Get("hL1520_w_SB");
  hL1520_L1520_w_SB->SetName("hL1520_L1520_w_SB");
  hL1520_L1520_w_SB->Sumw2(kFALSE);
  TH1F *hLDpp_L1520_w_SB=(TH1F*)fileExp->Get("hL1520_w_SB");
  hLDpp_L1520_w_SB->SetName("hLDpp_L1520_w_SB");
  hLDpp_L1520_w_SB->Sumw2(kFALSE);
  TH1F *hSDpp_L1520_w_SB=(TH1F*)fileExp->Get("hL1520_w_SB");
  hSDpp_L1520_w_SB->SetName("hSDpp_L1520_w_SB");
  hSDpp_L1520_w_SB->Sumw2(kFALSE);
  TH1F *hS1385_L1520_w_SB=(TH1F*)fileExp->Get("hL1520_w_SB");
  hS1385_L1520_w_SB->SetName("hS1385_L1520_w_SB");
  hS1385_L1520_w_SB->Sumw2(kFALSE);
  TH1F *hEM_L1520_w_SB=(TH1F*)fileEM->Get("hL1520_w_SB");
  hEM_L1520_w_SB->SetName("hEM_L1520_w_SB");
  hEM_L1520_w_SB->Sumw2();
  //the and w

  //pt part
  TH1F *hexperiment_L1520_pt=(TH1F*)fileExp->Get("hL1520_pt");
  hexperiment_L1520_pt->SetName("hexperiment_L1520_pt");
  hexperiment_L1520_pt->Sumw2();
  TH1F *hL1520_L1520_pt=(TH1F*)fileL1520->Get("hL1520_pt");
  hL1520_L1520_pt->SetName("hL1520_L1520_pt");
  hL1520_L1520_pt->Sumw2(kFALSE);
  TH1F *hLDpp_L1520_pt=(TH1F*)fileExp->Get("hL1520_pt");
  hLDpp_L1520_pt->SetName("hLDpp_L1520_pt");
  hLDpp_L1520_pt->Sumw2(kFALSE);
  TH1F *hSDpp_L1520_pt=(TH1F*)fileExp->Get("hL1520_pt");
  hSDpp_L1520_pt->SetName("hSDpp_L1520_pt");
  hSDpp_L1520_pt->Sumw2(kFALSE);
  TH1F *hS1385_L1520_pt=(TH1F*)fileExp->Get("hL1520_pt");
  hS1385_L1520_pt->SetName("hS1385_L1520_pt");
  hS1385_L1520_pt->Sumw2(kFALSE);
  TH1F *hEM_L1520_pt=(TH1F*)fileEM->Get("hL1520_pt");
  hEM_L1520_pt->SetName("hEM_L1520_pt");
  hEM_L1520_pt->SetTitle("p_{t} for #Lambda(1520) from Event Mixing");
  hEM_L1520_pt->Sumw2();

  TH1F *hexperiment_L1520_pt_SB=(TH1F*)fileExp->Get("hL1520_pt_SB");
  hexperiment_L1520_pt_SB->SetName("hexperiment_L1520_pt_SB");
  hexperiment_L1520_pt_SB->Sumw2();
  TH1F *hL1520_L1520_pt_SB=(TH1F*)fileL1520->Get("hL1520_pt_SB");
  hL1520_L1520_pt_SB->SetName("hL1520_L1520_pt_SB");
  hL1520_L1520_pt_SB->Sumw2(kFALSE);
  TH1F *hLDpp_L1520_pt_SB=(TH1F*)fileExp->Get("hL1520_pt_SB");
  hLDpp_L1520_pt_SB->SetName("hLDpp_L1520_pt_SB");
  hLDpp_L1520_pt_SB->Sumw2(kFALSE);
  TH1F *hSDpp_L1520_pt_SB=(TH1F*)fileExp->Get("hL1520_pt_SB");
  hSDpp_L1520_pt_SB->SetName("hSDpp_L1520_pt_SB");
  hSDpp_L1520_pt_SB->Sumw2(kFALSE);
  TH1F *hS1385_L1520_pt_SB=(TH1F*)fileExp->Get("hL1520_pt_SB");
  hS1385_L1520_pt_SB->SetName("hS1385_L1520_pt_SB");
  hS1385_L1520_pt_SB->Sumw2(kFALSE);
  TH1F *hEM_L1520_pt_SB=(TH1F*)fileEM->Get("hL1520_pt_SB");
  hEM_L1520_pt_SB->SetName("hEM_L1520_pt_SB");
  hEM_L1520_pt_SB->Sumw2();
  //the and pt

  TH1F *hsum_background=(TH1F*)hS1385_background->Clone("hsum_background");
  TH1F *hclean_background=(TH1F*)hS1385_background->Clone("hclean_background");
  TH1F *hclean_experiment=(TH1F*)hexperiment_background->Clone("hclean_experiment");
  TH1F *hclean_L1520=(TH1F*)hL1520_background->Clone("hclean_L1520");
  TH1F *hclean_sum=(TH1F*)hL1520_background->Clone("hclean_sum");
  TH1F *hclean_L1520_ren=(TH1F*)hL1520_background->Clone("hclean_L1520_ren");
  TH1F *hclean_sum_ren=(TH1F*)hL1520_background->Clone("hclean_sum_ren");
  TH1F *hpure_signal=(TH1F*)hL1520_background->Clone("hpure_signal");

  TH1F *hsum_background_PipPim=(TH1F*)hS1385_hMPipPim_background->Clone("hsum_background_PipPim");
  TH1F *hclean_background_PipPim=(TH1F*)hS1385_hMPipPim_background->Clone("hclean_background_PipPim");
  TH1F *hclean_experiment_PipPim=(TH1F*)hexperiment_hMPipPim_background->Clone("hclean_experiment_PipPim");
  TH1F *hclean_L1520_PipPim=(TH1F*)hL1520_hMPipPim_background->Clone("hclean_L1520_PipPim");
  TH1F *hclean_sum_PipPim=(TH1F*)hL1520_hMPipPim_background->Clone("hclean_sum_PipPim");
  TH1F *hclean_L1520_ren_PipPim=(TH1F*)hL1520_hMPipPim_background->Clone("hclean_L1520_ren_PipPim");
  TH1F *hclean_sum_ren_PipPim=(TH1F*)hL1520_hMPipPim_background->Clone("hclean_sum_ren_PipPim");
  TH1F *hpure_signal_PipPim=(TH1F*)hL1520_hMPipPim_background->Clone("hpure_signal_PipPim");
  TH1F *hclean_EM=(TH1F*)hEM_data->Clone("hclean_EM");

  //pt and w
  TH1F *hsum_w_background=(TH1F*)hSDpp_L1520_w_SB->Clone("hsum_w_background");
  TH1F *hsum_pt_background=(TH1F*)hSDpp_L1520_pt_SB->Clone("hsum_pt_background");

  TH1F *hsum_w_background_SB=(TH1F*)hSDpp_L1520_w_SB->Clone("hsum_w_background_SB");
  TH1F *hsum_pt_background_SB=(TH1F*)hSDpp_L1520_pt_SB->Clone("hsum_pt_background_SB");

  TH1F *hclean_w_background=(TH1F*)hSDpp_L1520_w_SB->Clone("hclean_w_background");
  TH1F *hclean_pt_background=(TH1F*)hSDpp_L1520_pt_SB->Clone("hclean_pt_background");
  TH1F *hclean_w_L1520=(TH1F*)hSDpp_L1520_w_SB->Clone("hclean_w_L1520");
  TH1F *hclean_pt_L1520=(TH1F*)hSDpp_L1520_pt_SB->Clone("hclean_pt_L1520");
  TH1F *hclean_w_experiment=(TH1F*)hSDpp_L1520_w_SB->Clone("hclean_w_experiment");
  TH1F *hclean_pt_experiment=(TH1F*)hSDpp_L1520_pt_SB->Clone("hclean_pt_experiment");
  TH1F *hclean_w_experiment_sum=(TH1F*)hSDpp_L1520_w_SB->Clone("hclean_w_experiment");
  TH1F *hclean_pt_experiment_sum=(TH1F*)hSDpp_L1520_pt_SB->Clone("hclean_pt_experiment");
  TH1F *hclean_w_EM=(TH1F*)hSDpp_L1520_w_SB->Clone("hclean_w_EM");
  TH1F *hclean_pt_EM=(TH1F*)hSDpp_L1520_pt_SB->Clone("hclean_pt_EM");
  //pt and w the end

  hsum_background->Reset();
  hclean_background->Reset();
  hclean_experiment->Reset();
  hclean_L1520->Reset();
  hclean_sum->Reset();
  hclean_L1520_ren->Reset();
  hclean_sum_ren->Reset();
  hpure_signal->Reset();
  hclean_EM->Reset();


  hsum_background_PipPim->Reset();
  hclean_background_PipPim->Reset();
  hclean_experiment_PipPim->Reset();
  hclean_L1520_PipPim->Reset();
  hclean_sum_PipPim->Reset();
  hclean_L1520_ren_PipPim->Reset();
  hclean_sum_ren_PipPim->Reset();
  hpure_signal_PipPim->Reset();


  hsum_w_background->Reset();
  hsum_pt_background->Reset();
  hsum_w_background_SB->Reset();
  hsum_pt_background_SB->Reset();
  hclean_w_background->Reset();
  hclean_pt_background->Reset();
  hclean_w_L1520->Reset();
  hclean_pt_L1520->Reset();
  hclean_w_experiment->Reset();
  hclean_pt_experiment->Reset();
  hclean_w_experiment_sum->Reset();
  hclean_pt_experiment_sum->Reset();
  hclean_w_EM->Reset();
  hclean_pt_EM->Reset();

  //scale according to CS
  //double nsim=40*TMath::Power(10,6);//number of simulated events
  double arbitrary_scaling=1;
  double nsim=40*TMath::Power(10,6);
  double scale=1.04*TMath::Power(10,7);
  double downscale=3;//trigger downscale for simulated events
  double nuc_factor=TMath::Power(93,2./3.)*arbitrary_scaling;
    double cs[5]=
      {14.05/1000*scale/(nsim*downscale)*nuc_factor,//S1385
       9.26/1000*scale/(nsim*downscale)*nuc_factor,//SDpp
       29.45/1000*scale/(nsim*downscale)*nuc_factor,//LDpp
       5.6/1000*scale/(100*100000*downscale)*nuc_factor,//L(1520)pK+->Lpi+pi-pK+
       (3.5+2.57+14.05+9.26+29.45)/1000*scale/(100*100000*downscale)*0.5*nuc_factor//L K0 p pi+ (0.5 because of Ks i Kl)
      };
      double err[5]=
	{2.25/14.05,//S1385
	 1.47/9.26,//SDpp
	 2.55/29.45,//LDpp
	 2/5.6,//L(1520)pK+->Lpi+pi-pK+
	 TMath::Sqrt(2.06*2.06+1.67*1.67+0.65*0.65+1.+1.+2.*2.+3.5*0.2*3.5*0.2)*0.5*nuc_factor
	};
      double cs_sig;
      // cs in \mu barns, have to me re-calculated to mb!!

      hS1385_background->Scale(cs[0]);
      hSDpp_background->Scale(cs[1]);
      hLDpp_background->Scale(cs[2]);
      hL1520_background->Scale(cs[3]);
      hS1385_hMPipPim_background->Scale(cs[0]);
      hSDpp_hMPipPim_background->Scale(cs[1]);
      hLDpp_hMPipPim_background->Scale(cs[2]);
      hL1520_hMPipPim_background->Scale(cs[3]);
      hsim_L->Scale(cs[4]);
      hsim_K0->Scale(cs[4]);
      hS1385_L1520_pt_SB->Scale(cs[0]);
      hSDpp_L1520_pt_SB->Scale(cs[1]);
      hLDpp_L1520_pt_SB->Scale(cs[2]);
      hL1520_L1520_pt_SB->Scale(cs[3]);
      hS1385_L1520_w_SB->Scale(cs[0]);
      hSDpp_L1520_w_SB->Scale(cs[1]);
      hLDpp_L1520_w_SB->Scale(cs[2]);
      hL1520_L1520_w_SB->Scale(cs[3]);
      /*  hS1385_background->Sumw2();
  hSDpp_background->Sumw2();
  hLDpp_background->Sumw2();
  hL1520_background->Sumw2();
      */
      scale_error(hS1385_background,err[0]);
      scale_error(hSDpp_background,err[1]);
      scale_error(hLDpp_background,err[2]);
      scale_error(hL1520_background,err[3]);
      scale_error(hS1385_hMPipPim_background,err[0]);
      scale_error(hSDpp_hMPipPim_background,err[1]);
      scale_error(hLDpp_hMPipPim_background,err[2]);
      scale_error(hL1520_hMPipPim_background,err[3]);
      scale_error(hS1385_L1520_pt_SB,err[0]);
      scale_error(hSDpp_L1520_pt_SB,err[1]);
      scale_error(hLDpp_L1520_pt_SB,err[2]);
      scale_error(hL1520_L1520_pt_SB,err[3]);
      scale_error(hS1385_L1520_w_SB,err[0]);
      scale_error(hSDpp_L1520_w_SB,err[1]);
      scale_error(hLDpp_L1520_w_SB,err[2]);
      scale_error(hL1520_L1520_w_SB,err[3]);

      hS1385_data->Scale(cs[0]);
      hSDpp_data->Scale(cs[1]);
      hLDpp_data->Scale(cs[2]);
      hL1520_data->Scale(cs[3]);
      hS1385_hMPipPim_signal->Scale(cs[0]);
      hSDpp_hMPipPim_signal->Scale(cs[1]);
      hLDpp_hMPipPim_signal->Scale(cs[2]);
      hL1520_hMPipPim_signal->Scale(cs[3]);
      hS1385_L1520_pt->Scale(cs[0]);
      hSDpp_L1520_pt->Scale(cs[1]);
      hLDpp_L1520_pt->Scale(cs[2]);
      hL1520_L1520_pt->Scale(cs[3]);
      hS1385_L1520_w->Scale(cs[0]);
      hSDpp_L1520_w->Scale(cs[1]);
      hLDpp_L1520_w->Scale(cs[2]);
      hL1520_L1520_w->Scale(cs[3]);
      /*
  hS1385_data->Sumw2();
  hSDpp_data->Sumw2();
  hLDpp_data->Sumw2();
  hL1520_data->Sumw2();
      */
      scale_error(hS1385_data,err[0]);
      scale_error(hSDpp_data,err[1]);
      scale_error(hLDpp_data,err[2]);
      scale_error(hL1520_data,err[3]);
      scale_error(hS1385_hMPipPim_signal,err[0]);
      scale_error(hSDpp_hMPipPim_signal,err[1]);
      scale_error(hLDpp_hMPipPim_signal,err[2]);
      scale_error(hL1520_hMPipPim_signal,err[3]);
      scale_error(hS1385_L1520_pt,err[0]);
      scale_error(hSDpp_L1520_pt,err[1]);
      scale_error(hLDpp_L1520_pt,err[2]);
      scale_error(hL1520_L1520_pt,err[3]);
      scale_error(hS1385_L1520_w,err[0]);
      scale_error(hSDpp_L1520_w,err[1]);
      scale_error(hLDpp_L1520_w,err[2]);
      scale_error(hL1520_L1520_w,err[3]);

      hsum_background->Add(hS1385_background);
      hsum_background->Add(hSDpp_background);
      hsum_background->Add(hLDpp_background);
      hsum_background_PipPim->Add(hS1385_hMPipPim_background);
      hsum_background_PipPim->Add(hSDpp_hMPipPim_background);
      hsum_background_PipPim->Add(hLDpp_hMPipPim_background);

      hsum_pt_background_SB->Add(hS1385_L1520_pt_SB);
      hsum_pt_background_SB->Add(hSDpp_L1520_pt_SB);
      hsum_pt_background_SB->Add(hLDpp_L1520_pt_SB);

      hsum_w_background_SB->Add(hS1385_L1520_w_SB);
      hsum_w_background_SB->Add(hSDpp_L1520_w_SB);
      hsum_w_background_SB->Add(hLDpp_L1520_w_SB);

      hsum_data->Add(hS1385_data);
      hsum_data->Add(hSDpp_data);
      hsum_data->Add(hLDpp_data);
      hsum_hMPipPim_signal->Add(hS1385_hMPipPim_signal);
      hsum_hMPipPim_signal->Add(hSDpp_hMPipPim_signal);
      hsum_hMPipPim_signal->Add(hLDpp_hMPipPim_signal);

      hsum_pt_background->Add(hS1385_L1520_pt);
      hsum_pt_background->Add(hSDpp_L1520_pt);
      hsum_pt_background->Add(hLDpp_L1520_pt);

      hsum_w_background->Add(hS1385_L1520_w);
      hsum_w_background->Add(hSDpp_L1520_w);
      hsum_w_background->Add(hLDpp_L1520_w);

      hclean_background->Add(hsum_data,hsum_background,1,-1);
      hclean_experiment->Add(hexperiment_data,hexperiment_background,1,-1);
      hclean_L1520->Add(hL1520_data,hL1520_background,1,-1);
      hclean_sum->Add(hclean_L1520,hclean_background,1,1);
      //cs_sig=1/(hclean_L1520->Integral())*20;
      //hclean_L1520->Scale(cs_sig);

      hclean_background_PipPim->Add(hsum_hMPipPim_signal,hsum_background_PipPim,1,-1);
      hclean_experiment_PipPim->Add(hexperiment_hMPipPim_signal,hexperiment_hMPipPim_background,1,-1);
      hclean_L1520_PipPim->Add(hL1520_hMPipPim_signal,hL1520_hMPipPim_background,1,-1);
      hclean_sum_PipPim->Add(hclean_L1520_PipPim,hclean_background_PipPim,1,1);

      hclean_w_background->Add(hsum_w_background,hsum_w_background_SB,1,-1);
      hclean_pt_background->Add(hsum_pt_background,hsum_pt_background_SB,1,-1);
      hclean_w_L1520->Add(hL1520_L1520_w,hL1520_L1520_w_SB,1,-1);
      hclean_pt_L1520->Add(hL1520_L1520_pt,hL1520_L1520_pt_SB,1,-1);
      hclean_pt_experiment->Add(hexperiment_L1520_pt,hexperiment_L1520_pt_SB,1,-1);
      hclean_w_experiment->Add(hexperiment_L1520_w,hexperiment_L1520_w_SB,1,-1);

      hclean_w_experiment_sum->Add(hclean_w_L1520,hclean_w_background,1,1);
      hclean_pt_experiment_sum->Add(hclean_pt_L1520,hclean_pt_background,1,1);
      hclean_pt_EM->Add(hEM_L1520_pt,hEM_L1520_pt_SB,1,-1);
      hclean_w_EM->Add(hEM_L1520_w,hEM_L1520_w_SB,1,-1);

      
      //cs_sig=1/(hclean_L1520->Integral())*20;
      //hclean_L1520->Scale(cs_sig);

      hclean_EM->Add(hEM_data,hEM_background,1,-1);
      //scale Event mixing to data
      double int_min_1=1650;
      double int_max_1=1980;

      double EM_int=hclean_EM->Integral(hclean_EM->FindBin(int_min_1),hclean_EM->FindBin(int_max_1));
      double sig_EM_int=hclean_experiment->Integral(hclean_experiment->FindBin(int_min_1),hclean_experiment->FindBin(int_max_1));

      hclean_EM->Scale(sig_EM_int/EM_int);
      hclean_w_EM->Scale(sig_EM_int/EM_int);
      hclean_pt_EM->Scale(sig_EM_int/EM_int);

      hclean_w_experiment_sum->Add(hclean_w_experiment,hclean_w_EM,1,-1);
      hclean_pt_experiment_sum->Add(hclean_pt_experiment,hclean_pt_EM,1,-1);
      
      //scale signal to difference between signal and background
      double int_min=1410;
      double int_max=1600;
      double err_sum;
      double err_sum_EM;

      double sig_int=hclean_L1520->Integral(hclean_L1520->FindBin(int_min),hclean_L1520->FindBin(int_max));
      double backgroud_int=hclean_EM->Integral(hclean_EM->FindBin(int_min),hclean_EM->FindBin(int_max));
      double experiment_int=hclean_experiment->Integral(hclean_experiment->FindBin(int_min),hclean_experiment->FindBin(int_max));

      hclean_L1520_ren->Add(hclean_L1520,1);
      hclean_L1520_ren->Scale((experiment_int-backgroud_int)/sig_int);
      hclean_sum_ren->Add(hclean_L1520_ren,1);
      hclean_sum_ren->Add(hclean_EM,1);

      TCanvas *cPt_simul=new TCanvas("cPt_simul","transver momentum for simulated channels");
      cPt_simul->Divide(2,2);
      cPt_simul->cd(1);
      hS1385_L1520_pt->Draw("e1");
      hS1385_L1520_pt_SB->Draw("samee1");
      hS1385_L1520_pt_SB->SetLineColor(kRed);
      cPt_simul->cd(2);
      hSDpp_L1520_pt->Draw("e1");
      hSDpp_L1520_pt_SB->Draw("samee1");
      hSDpp_L1520_pt_SB->SetLineColor(kRed);
      cPt_simul->cd(3);
      hLDpp_L1520_pt->Draw("e1");
      hLDpp_L1520_pt_SB->Draw("samee1");
      hLDpp_L1520_pt_SB->SetLineColor(kRed);
      cPt_simul->cd(4);
      hL1520_L1520_pt->Draw("e1");
      hL1520_L1520_pt_SB->Draw("samee1");
      hL1520_L1520_pt_SB->SetLineColor(kRed);

      TCanvas *cW_simul=new TCanvas("cW_simul","rapidity for simulated channels");
      cW_simul->Divide(2,2);
      cW_simul->cd(1);
      hS1385_L1520_w->Draw("e1");
      hS1385_L1520_w_SB->Draw("samee1");
      hS1385_L1520_w_SB->SetLineColor(kRed);
      cW_simul->cd(2);
      hSDpp_L1520_w->Draw("e1");
      hSDpp_L1520_w_SB->Draw("samee1");
      hSDpp_L1520_w_SB->SetLineColor(kRed);
      cW_simul->cd(3);
      hLDpp_L1520_w->Draw("e1");
      hLDpp_L1520_w_SB->Draw("samee1");
      hLDpp_L1520_w_SB->SetLineColor(kRed);
      cW_simul->cd(4);
      hL1520_L1520_w->Draw("e1");
      hL1520_L1520_w_SB->Draw("samee1");
      hL1520_L1520_w_SB->SetLineColor(kRed);

      int rebin_sig=2;
      TCanvas* cPt_signal=new TCanvas("cPt_signal", "p_{t} for signal");
      TLine* line_Ptmean=new TLine(hclean_pt_experiment->GetMean(),0,hclean_pt_experiment->GetMean(),100);
      line_Ptmean->SetLineWidth(4);
      line_Ptmean->SetLineColor(kGreen-2);
      line_Ptmean->SetLineStyle(10); 

      cPt_signal->Divide(2);
      cPt_signal->cd(1);
      hexperiment_L1520_pt->Draw("e1");
      hexperiment_L1520_pt_SB->Draw("samee1");
      hexperiment_L1520_pt_SB->SetLineColor(kRed);

      cPt_signal->cd(2);
      //hclean_pt_experiment->Draw("e1");
      hclean_pt_experiment->Rebin(rebin_sig);
      setHistogramStyleData(hclean_pt_experiment);
      hclean_pt_experiment_sum->Draw("samee1");
      hclean_pt_experiment_sum->Rebin(rebin_sig);
      hclean_pt_experiment_sum->SetLineColor(kGreen-2);
      setHistogramStyleData(hclean_pt_experiment_sum);
      hclean_pt_EM->Draw("samee1");
      hclean_pt_EM->SetLineColor(kRed);
      hclean_pt_EM->Rebin(rebin_sig);
      setHistogramStyleData(hclean_pt_EM);
      line_Ptmean->Draw("same");
      /*hclean_pt_L1520->Draw("samee2");
  hclean_pt_L1520->SetLineColor(kGreen);
  setHistogramStyleSimul(hclean_pt_L1520);
  hclean_pt_background->Draw("samee2");
  hclean_pt_background->SetLineColor(kRed);
  setHistogramStyleSimul(hclean_pt_background);
  hclean_pt_experiment_sum->Draw("samee2");
  hclean_pt_experiment_sum->SetLineColor(kMagenta);
  setHistogramStyleSimul(hclean_pt_experiment_sum);
      */
      TCanvas* cW_signal=new TCanvas("cW_signal", "rapidity for signal");
      TLine* line_Wmean=new TLine(hclean_w_experiment_sum->GetMean(),0,hclean_w_experiment_sum->GetMean(),150);
      line_Wmean->SetLineWidth(4);
      line_Wmean->SetLineColor(kGreen-2);
      line_Wmean->SetLineStyle(10);

      
      cW_signal->Divide(2);
      cW_signal->cd(1);
      hexperiment_L1520_w->Draw("e1");
      hexperiment_L1520_w_SB->Draw("samee1");
      hexperiment_L1520_w_SB->SetLineColor(kRed);
     
      cW_signal->cd(2);
      //hclean_w_experiment->Draw("e1");
      hclean_w_experiment->Rebin(rebin_sig);
      setHistogramStyleData(hclean_w_experiment);
      hclean_w_experiment_sum->Draw("samee1");
      hclean_w_experiment_sum->Rebin(rebin_sig);
      hclean_w_experiment_sum->SetLineColor(kGreen-2);
      setHistogramStyleData(hclean_w_experiment_sum);
      hclean_w_EM->Draw("samee1");
      hclean_w_EM->SetLineColor(kRed);
      hclean_w_EM->Rebin(rebin_sig);
      setHistogramStyleData(hclean_w_EM);
      line_Wmean->Draw();
      
      /*hclean_w_L1520->Draw("samee2");
	hclean_w_L1520->SetLineColor(kGreen);
	setHistogramStyleSimul(hclean_w_L1520);
	hclean_w_background->Draw("samee2");
	hclean_w_background->SetLineColor(kRed);
	setHistogramStyleSimul(hclean_w_background);
	hclean_w_experiment_sum->Draw("samee2");
	hclean_w_experiment_sum->SetLineColor(kMagenta);
	setHistogramStyleSimul(hclean_w_experiment_sum);
      */
      int rebin_res=2;
      TCanvas *cRes=new TCanvas("cRes","cRes");
      cRes->Divide(2,2);
      cRes->cd(1);
      hS1385_data->Rebin(rebin_res);
      set_Y_name(hS1385_data);
      hS1385_data->SetAxisRange(1350,1800);
      hS1385_data->Draw("e1");
      hS1385_background->Rebin(rebin_res);
      hS1385_background->SetLineColor(kRed);
      hS1385_background->Draw("samee1");

      cRes->cd(2);
      hSDpp_data->Rebin(rebin_res);
      set_Y_name(hSDpp_data);
      hSDpp_data->SetAxisRange(1350,1800);
      hSDpp_data->Draw("e1");
      hSDpp_background->SetLineColor(kRed);
      hSDpp_background->Rebin(rebin_res);
      hSDpp_background->SetAxisRange(1350,1800);
      hSDpp_background->Draw("samee1");

      cRes->cd(3);
      hLDpp_data->Rebin(rebin_res);
      set_Y_name(hLDpp_data);
      hLDpp_data->SetAxisRange(1350,1800);
      hLDpp_data->Draw("e1");
      hLDpp_background->SetLineColor(kRed);
      hLDpp_background->Rebin(rebin_res);
      hLDpp_background->SetAxisRange(1350,1800);
      hLDpp_background->Draw("samee1");

      cRes->cd(4);
      hL1520_data->Rebin(rebin_res);
      set_Y_name(hL1520_data);
      hL1520_data->SetAxisRange(1350,1800);
      hL1520_data->Draw("e1");
      hL1520_background->SetLineColor(kRed);
      hL1520_background->Rebin(rebin_res);
      hL1520_background->SetAxisRange(1350,1800);
      hL1520_background->Draw("samee1");

      TCanvas *cRes_PipPim=new TCanvas("cRes_PipPim","cRes_PipPim");
      cRes_PipPim->Divide(2,2);
      cRes_PipPim->cd(1);
      hS1385_hMPipPim_signal->Rebin(rebin_res);
      set_Y_name(hS1385_hMPipPim_signal);
      hS1385_hMPipPim_signal->SetAxisRange(250,450);
      hS1385_hMPipPim_signal->Draw("e1");
      hS1385_hMPipPim_background->Rebin(rebin_res);
      hS1385_hMPipPim_background->SetLineColor(kRed);
      hS1385_hMPipPim_background->Draw("samee1");

      cRes_PipPim->cd(2);
      hSDpp_hMPipPim_signal->Rebin(rebin_res);
      set_Y_name(hSDpp_hMPipPim_signal);
      hSDpp_hMPipPim_signal->SetAxisRange(250,450);
      hSDpp_hMPipPim_signal->Draw("e1");
      hSDpp_hMPipPim_background->SetLineColor(kRed);
      hSDpp_hMPipPim_background->Rebin(rebin_res);
      //hSDpp_hMPipPim_background->SetAxisRange(1350,1800);
      hSDpp_hMPipPim_background->Draw("samee1");

      cRes_PipPim->cd(3);
      hLDpp_hMPipPim_signal->Rebin(rebin_res);
      set_Y_name(hLDpp_hMPipPim_signal);
      hLDpp_hMPipPim_signal->SetAxisRange(250,450);
      hLDpp_hMPipPim_signal->Draw("e1");
      hLDpp_hMPipPim_background->SetLineColor(kRed);
      hLDpp_hMPipPim_background->Rebin(rebin_res);
      //hLDpp_hMPipPim_background->SetAxisRange(1350,1800);
      hLDpp_hMPipPim_background->Draw("samee1");

      cRes_PipPim->cd(4);
      hL1520_hMPipPim_signal->Rebin(rebin_res);
      set_Y_name(hL1520_hMPipPim_signal);
      hL1520_hMPipPim_signal->SetAxisRange(250,450);
      hL1520_hMPipPim_signal->Draw("e1");
      hL1520_hMPipPim_background->SetLineColor(kRed);
      hL1520_hMPipPim_background->Rebin(rebin_res);
      //hL1520_hMPipPim_background->SetAxisRange(1350,1800);
      hL1520_hMPipPim_background->Draw("samee1");

      TCanvas *cEventMixing=new TCanvas("cEventMixing");
      hEM_data->Rebin(rebin_res);
      hEM_data->Draw("e1");
      hEM_background->Rebin(rebin_res);
      hEM_background->SetLineColor(kBlue);
      hEM_background->Draw("samee1");

      setHistogramStyleData(hEM_data);
      setHistogramStyleData(hEM_background);



      int rebin2=2; //wrong error propagation for simul events
      TCanvas *cSum=new TCanvas("cSum","cSum");
      hexperiment_data->Rebin(rebin2);
      hexperiment_data->SetAxisRange(1300,1800);
      hexperiment_data->Draw("e1");
      setHistogramStyleData(hexperiment_data);

      hexperiment_background->Rebin(rebin2);
      hexperiment_background->SetLineColor(kRed);
      hexperiment_background->Draw("samee1");
      setHistogramStyleData(hexperiment_background);

      hsum_data->Rebin(rebin2);
      hsum_data->Draw("samee1");
      setHistogramStyleSimul(hsum_data);

      hsum_background->Rebin(rebin2);
      hsum_background->SetLineColor(kRed);
      setHistogramStyleSimul(hsum_background);
      hsum_background->Draw("samee1");

      TCanvas *cSum_PipPim=new TCanvas("cSum_PipPim","cSumPipPim");
      hexperiment_hMPipPim_signal->Rebin(rebin2);
      hexperiment_hMPipPim_signal->SetAxisRange(250,450);
      hexperiment_hMPipPim_signal->Draw("e1");
      setHistogramStyleData(hexperiment_hMPipPim_signal);

      hexperiment_hMPipPim_background->Rebin(rebin2);
      hexperiment_hMPipPim_background->SetLineColor(kRed);
      hexperiment_hMPipPim_background->Draw("samee1");
      setHistogramStyleData(hexperiment_hMPipPim_background);

      hsum_hMPipPim_signal->Rebin(rebin2);
      hsum_hMPipPim_signal->Draw("samee1");
      setHistogramStyleSimul(hsum_hMPipPim_signal);

      hsum_background_PipPim->Rebin(rebin2);
      hsum_background_PipPim->SetLineColor(kRed);
      setHistogramStyleSimul(hsum_background_PipPim);
      hsum_background_PipPim->Draw("samee1");


      int rebin=4;
      TCanvas *cClean=new TCanvas("cClean","cClean");

      hclean_experiment->Draw("e1");
      hclean_experiment->Rebin(rebin);
      hclean_experiment->GetXaxis()->SetRangeUser(1360,2300);
      setHistogramStyleData(hclean_experiment);

      hclean_background->SetLineColor(kRed);
      hclean_background->SetFillColor(kRed);
      hclean_background->Rebin(rebin);
      hclean_background->Draw("samee2");
      setHistogramStyleSimul(hclean_background);

      hclean_L1520->SetLineColor(kGreen+3);
      hclean_L1520->Rebin(rebin);
      hclean_L1520->Draw("samee2");
      hclean_L1520->SetFillStyle(3154);
      setHistogramStyleSimul(hclean_L1520);

      hclean_sum->Rebin(rebin);
      hclean_sum->SetLineColor(kMagenta);
      hclean_sum->SetFillStyle(3145);
      hclean_sum->Draw("samee2");
      setHistogramStyleSimul(hclean_sum);

      hclean_EM->Rebin(rebin);
      hclean_EM->Draw("samee1");
      hclean_EM->SetLineColor(kRed);
      setHistogramStyleData(hclean_EM);

      int rebin_pippim=2;
      TCanvas *cClean_PipPim=new TCanvas("cClean_PipPim","cClean_PipPim");

      hclean_experiment_PipPim->Draw("e1");
      hclean_experiment_PipPim->Rebin(rebin_pippim);
      hclean_experiment_PipPim->GetXaxis()->SetRangeUser(250,450);
      setHistogramStyleData(hclean_experiment_PipPim);

      hclean_background_PipPim->SetLineColor(kRed);
      hclean_background_PipPim->SetFillColor(kRed);
      hclean_background_PipPim->Rebin(rebin_pippim);
      hclean_background_PipPim->Draw("samee2");
      setHistogramStyleSimul(hclean_background_PipPim);

      hclean_L1520_PipPim->SetLineColor(kGreen+3);
      hclean_L1520_PipPim->Rebin(rebin_pippim);
      hclean_L1520_PipPim->Draw("samee2");
      hclean_L1520_PipPim->SetFillStyle(3154);
      setHistogramStyleSimul(hclean_L1520_PipPim);

      hclean_sum_PipPim->Rebin(rebin_pippim);
      hclean_sum_PipPim->SetLineColor(kMagenta);
      hclean_sum_PipPim->SetFillStyle(3145);
      hclean_sum_PipPim->Draw("samee2");
      setHistogramStyleSimul(hclean_sum_PipPim);


      TCanvas *cClean_ren=new TCanvas("cClean_ren","cClean_ren");
      cClean_ren->Divide(2);
      cClean_ren->cd(1);
      hclean_experiment->Draw("e1");

      //hclean_experiment->Rebin(rebin);
      //hclean_background->SetLineColor(kRed);
      //hclean_background->Rebin(rebin);
      //hclean_background->Draw("samee2");
      //setHistogramStyleSimul(hclean_background);
      //hclean_background->SetFillStyle(3125);

      hclean_L1520_ren->SetLineColor(kGreen+3);
      hclean_L1520_ren->Rebin(rebin);
      setHistogramStyleSimul(hclean_L1520_ren);
      hclean_L1520_ren->SetFillStyle(3154);
      //hclean_L1520_ren->Draw("samee2");

      hclean_EM->Draw("same");

      hclean_sum_ren->Rebin(rebin);
      hclean_sum_ren->SetLineColor(kMagenta);
      hclean_sum_ren->SetFillColor(kMagenta);
      setHistogramStyleSimul(hclean_sum_ren);
      hclean_sum_ren->SetFillStyle(3145);
      //hclean_sum_ren->Draw("samee2");



      cClean_ren->cd(2);
      hpure_signal->Rebin(rebin);
      hpure_signal->GetXaxis()->SetRangeUser(1360,1780);
      hpure_signal->Draw("e1");

      //fit Voigt to data
      hpure_signal->Add(hclean_experiment,hclean_EM,1,-1);
      setHistogramStyleData(hpure_signal);
      voigt->SetParameter(0,2412);
      voigt->SetParameter(1,1500);
      voigt->SetParameter(2,5);
      voigt->FixParameter(2,21.21);
      voigt->SetParameter(3,50);
      hpure_signal->Fit(voigt,"RL");
      hpure_signal->Fit(voigt,"RL");

      TLatex *printFormula1 = new TLatex();
      double high=0.85;
      char text4[10000];
      char text5[10000];
      char text6[10000];
      char text7[10000];
      char text8[10000];
      sprintf(text4, "#sigma = %.2f MeV",voigt->GetParameter(2));
      sprintf(text5, "#Gamma = %.2f MeV",voigt->GetParameter(3));
      sprintf(text6, "#bar{M_{p #pi^{-} #pi^{+} #pi^{-}}} = %.1f MeV",voigt->GetParameter(1));
      sprintf(text7, "#int_{1400 MeV}^{1620 MeV} = %.1f ",voigt->Integral(int_min,int_max)/hpure_signal->GetBinWidth(2));
      sprintf(text8, "#sum_{1400 MeV}^{1620 MeV} = %.1f #pm %.1f ",hpure_signal->Integral(hpure_signal->FindBin(int_min),hpure_signal->FindBin(int_max)),hist_error(hpure_signal,int_min,int_max));
      printFormula1->SetNDC();
      printFormula1->SetTextFont(32);
      printFormula1->SetTextColor(1);
      printFormula1->SetTextSize(0.04);
      printFormula1->SetTextAlign(13);
      printFormula1->DrawLatex(0.5,high,text4);
      printFormula1->DrawLatex(0.5,high-printFormula1->GetTextSize(),text5);
      printFormula1->DrawLatex(0.5,high-printFormula1->GetTextSize()*2,text6);
      printFormula1->DrawLatex(0.5,high-printFormula1->GetTextSize()*4,text7);
      printFormula1->DrawLatex(0.5,high-printFormula1->GetTextSize()*7,text8);
      
      TCanvas *cSB=new TCanvas("cSB","Spectrum for side-band");
      hexperiment_SB_spectrum->SetAxisRange(1050,1250);
      setHistogramStyleData(hexperiment_SB_spectrum);
      hexperiment_SB_spectrum->Draw();
      fVoigt->Draw("same");
      fVoigt->SetLineColor(kGreen);
      fbg->Draw("same");
      fbg->SetLineColor(kBlue);
      setLineStyle(line1);
      setLineStyle(line2);
      setLineStyle(line3);
      setLineStyle(line4);
      line1->Draw("same");
      line2->Draw("same");
      line3->Draw("same");
      line4->Draw("same");

      TLatex *printFormula = new TLatex();
      double high=0.8;
      char text1[10000];
      char text2[10000];
      char text3[10000];
      sprintf(text1, "#sigma = %.1f MeV",fVoigt->GetParameter(2));
      sprintf(text2, "#Gamma = %.1f MeV",fVoigt->GetParameter(3));
      sprintf(text3, "#bar{M_{p#pi^{-}}} = %.1f MeV",fVoigt->GetParameter(1));
      printFormula->SetNDC();
      printFormula->SetTextFont(32);
      printFormula->SetTextColor(1);
      printFormula->SetTextSize(0.05);
      printFormula->SetTextAlign(13);
      printFormula->DrawLatex(0.6,high, text1);
      printFormula->DrawLatex(0.6,high-printFormula->GetTextSize(), text2);
      printFormula->DrawLatex(0.6,high-printFormula->GetTextSize()*2 , text3);


      int npx=300;
      TCanvas* cL=new TCanvas("cL", "Signal for final state p #pi^{+} #L^{0} K^{0}");
      TF1* L_sim_bg=new TF1("L_sim_bg","pol1(0)",1095,1135);
      TF1* L_sim_sig_bg=new TF1("L_sim_sig_bg","[0]*TMath::Voigt(x-[1],[2],[3])+pol1(4)",1095,1135);
      TF1* fL1116_experiment_fit_bg=new TF1("fL1116_experiment_fit_bg","pol2(0)",1095,1135);
      fL1116_experiment_fit_bg->SetParameters(fL1116_experiment_fit->GetParameter(4),fL1116_experiment_fit->GetParameter(5),fL1116_experiment_fit->GetParameter(6));
      L_sim_sig_bg->SetParameters(1494,1115,0.0004,5.4,47.3,-0.033);
      hexperiment_L->SetAxisRange(1080,1200);
      hexperiment_L->SetMinimum(0);
      hexperiment_L->Draw("e1");
      hsim_L->Draw("samee1");
      hsim_L->SetLineColor(kMagenta+1);
      L_sim_bg->SetLineColor(kMagenta);
      L_sim_bg->SetLineWidth(3);
      L_sim_bg->SetLineStyle(2);
      L_sim_sig_bg->SetLineColor(kMagenta);
      L_sim_sig_bg->SetLineWidth(3);
      L_sim_sig_bg->SetLineStyle(1);
      L_sim_sig_bg->SetNpx(npx);

      hsim_L->Fit(L_sim_sig_bg,"R");
      L_sim_bg->SetParameters(L_sim_sig_bg->GetParameter(4),L_sim_sig_bg->GetParameter(5));
      L_sim_bg->Draw("same");

      //fL1116_experiment_sig->SetNpx(npx);
      fL1116_experiment_fit->SetLineWidth(3);
      fL1116_experiment_fit->SetLineColor(kBlue);
      fL1116_experiment_fit->Draw("same");
      //fL1116_experiment_sig->Draw("same");
      //fL1116_experiment_sig->SetLineWidth(3);

      fL1116_experiment_fit_bg->SetLineWidth(3);
      fL1116_experiment_fit_bg->SetLineColor(kBlue);
      fL1116_experiment_fit_bg->SetLineStyle(2);
      fL1116_experiment_fit_bg->Draw("same");

      TLatex *printFormula2 = new TLatex();
      double high2=0.90;
      char text9[10000];
      char text10[10000];
      char text11[10000];
      sprintf(text9, "I_{exp}=#int_{1095}^{1135} S_{exp} = %.1f",fL1116_experiment_sig->Integral(1095,1135)/hsim_L->GetBinWidth(3));
      sprintf(text10, "I_{simul}=#int_{1095}^{1135} S_{simul} = %.1f",(L_sim_sig_bg->Integral(1095,1135)-L_sim_bg->Integral(1095,1135))/hsim_L->GetBinWidth(3));
      sprintf(text11, "I_{exp}/I_{simul} = %.2f",fL1116_experiment_sig->Integral(1095,1135)/(L_sim_sig_bg->Integral(1095,1135)-L_sim_bg->Integral(1095,1135)));
      
      printFormula2->SetNDC();
      printFormula2->SetTextFont(32);
      printFormula2->SetTextColor(1);
      printFormula2->SetTextSize(0.05);
      printFormula2->SetTextAlign(13);
      printFormula2->DrawLatex(0.6,high2, text9);
      printFormula2->DrawLatex(0.6,high2-printFormula->GetTextSize()*4, text10);
      printFormula2->DrawLatex(0.6,high2-printFormula->GetTextSize()*8 , text11);


      TCanvas* cK0=new TCanvas("cK0", "Signal for final state p #pi^{+} #L^{0} K^{0}");
      TF1* K0_sim_bg=new TF1("K0_sim_bg","pol1(0)",450,550);
      TF1* K0_sim_sig_bg=new TF1("K0_sim_sig_bg","[0]*TMath::Voigt(x-[1],[2],[3])+pol1(4)",450,550);
      TF1* fK0_experiment_fit_bg=new TF1("fK0_experiment_fit_bg","pol2(0)",450,550);
      fK0_experiment_fit_bg->SetParameters(fK0_experiment_fit->GetParameter(4),fK0_experiment_fit->GetParameter(5),fK0_experiment_fit->GetParameter(6));
      K0_sim_sig_bg->SetParameters(1490,495,3.21,9.54,60.71,-0.1);
      hexperiemnt_K0->SetAxisRange(300,650);
      hexperiemnt_K0->SetMinimum(0);
      hexperiemnt_K0->Draw("e1");
      hsim_K0->Draw("samee1");
      hsim_K0->SetLineColor(kMagenta+1);

      K0_sim_bg->SetLineColor(kMagenta);
      K0_sim_bg->SetLineWidth(4);
      K0_sim_bg->SetLineStyle(2);
      K0_sim_sig_bg->SetLineColor(kMagenta);
      K0_sim_sig_bg->SetLineWidth(4);
      K0_sim_sig_bg->SetLineStyle(1);
      K0_sim_sig_bg->SetNpx(npx);

      hsim_K0->Fit(K0_sim_sig_bg,"R");
      K0_sim_bg->SetParameters(K0_sim_sig_bg->GetParameter(4),K0_sim_sig_bg->GetParameter(5));
      K0_sim_bg->Draw("same");

      fK0_experiment_fit->SetLineWidth(4);
      fK0_experiment_fit->SetLineColor(kBlue);
      fK0_experiment_fit->Draw("same");
      //fK0_experiment_sig->Draw("same");
      //fK0_experiment_sig->SetLineWidth(3);

      fK0_experiment_fit_bg->SetLineWidth(4);
      fK0_experiment_fit_bg->SetLineColor(kBlue);
      fK0_experiment_fit_bg->SetLineStyle(2);
      fK0_experiment_fit_bg->Draw("same");

      TLatex *printFormula3 = new TLatex();
      double high3=0.90;
      char text12[10000];
      char text13[10000];
      char text14[10000];
      sprintf(text12, "I_{exp}=#int_{450}^{550} S_{exp} = %.1f",fK0_experiment_sig->Integral(450,550)/hsim_K0->GetBinWidth(3));
      sprintf(text13, "I_{simul}=#int_{450}^{550} S_{simul} = %.1f",(K0_sim_sig_bg->Integral(450,550)-K0_sim_bg->Integral(450,550))/hsim_L->GetBinWidth(3));
      sprintf(text14, "I_{exp}/I_{simul} = %.2f",fK0_experiment_sig->Integral(450,550)/(K0_sim_sig_bg->Integral(450,550)-K0_sim_bg->Integral(450,550)));
      printFormula3->SetNDC();
      printFormula3->SetTextFont(32);
      printFormula3->SetTextColor(1);
      printFormula3->SetTextSize(0.05);
      printFormula3->SetTextAlign(13);
      printFormula3->DrawLatex(0.6,high2, text12);
      printFormula3->DrawLatex(0.6,high2-printFormula->GetTextSize()*4, text13);
      printFormula3->DrawLatex(0.6,high2-printFormula->GetTextSize()*8 , text14);


      TCanvas* cLK0=new TCanvas("cLK0", "Signal for final state p #pi^{+} #L^{0} K^{0}");
      TH1F* hsigL_pure=(TH1F*)hexperiment_L->Clone("hsigL_pure");
      TH1F* hsigK0_pure=(TH1F*)hexperiemnt_K0->Clone("hsigK0_pure");
      hsigL_pure->Add(fL1116_experiment_fit_bg,-1);
      hsigK0_pure->Add(fK0_experiment_fit_bg,-1);
      TH1F* hsigL_pure_sim=(TH1F*)hsim_L->Clone("hsigL_pure_sim");
      TH1F* hsigK0_pure_sim=(TH1F*)hsim_K0->Clone("hsigK0_pure");
      hsigL_pure_sim->Add(L_sim_bg,-1);
      hsigK0_pure_sim->Add(K0_sim_bg,-1);
      cLK0->Divide(2);

      cLK0->cd(1);
      hexperiment_L->SetAxisRange(1080,1200);
      hexperiment_L->SetMinimum(0);
      hexperiment_L->Draw("e1");
      hsim_L->Draw("samehist");
      hsim_L->SetLineColor(kMagenta+1);
      fL1116_experiment_fit->SetNpx(npx);
      //fL1116_experiment_sig->SetNpx(npx);
      fL1116_experiment_fit->Draw("same");
      //fL1116_experiment_sig->Draw("same");
      fL1116_experiment_sig->SetLineWidth(3);
      fL1116_experiment_fit_bg->Draw("same");
      L_sim_bg->Draw("same");

      TLatex *printFormula4 = new TLatex();
      double nuc_cs=(3.5+2.57+14.05+9.26+29.45+5.0+3.5+2.3+14)*0.5*nuc_factor;
      double high4=0.85;
      double cs_L_sim,cs_L,cs_L_err;
      cs_L=hsigL_pure->IntegralAndError(hsigL_pure->FindBin(1100),hsigL_pure->FindBin(1130),cs_L_err);
      cs_L_sim=hsigL_pure_sim->Integral(hsigL_pure_sim->FindBin(1100),hsigL_pure_sim->FindBin(1130));
      //cout<<cs_L_sim<<" "<<cs_L<<" "<<cs_L_err<<endl;
      char text15[10000];
      char text16[10000];
      sprintf(text15, " #sigma_{simul} = #sigma_{pp} A^{2/3} =%.0f #pm %0.0f #mu b",nuc_cs,err_sum[4]);
      sprintf(text16, "#sigma_{exp} = %.0f #pm %.0f #mu b",nuc_cs*cs_L/cs_L_sim,nuc_cs*cs_L_err/cs_L_sim);
      printFormula4->SetNDC();
      printFormula4->SetTextFont(32);
      printFormula4->SetTextColor(1);
      printFormula4->SetTextSize(0.04);
      printFormula4->SetTextAlign(13);
      printFormula4->DrawLatex(0.35,high4, text15);
      printFormula4->DrawLatex(0.35,high4-printFormula->GetTextSize()*2, text16);

      
      cLK0->cd(2);
      hexperiemnt_K0->SetAxisRange(300,650);
      hexperiemnt_K0->SetMinimum(0);
      hexperiemnt_K0->Draw("e1");
      hsim_K0->Draw("samehist");
      hsim_K0->SetLineColor(kMagenta+1);
      //fK0_experiment_sig->SetNpx(npx);
      fK0_experiment_fit->SetNpx(npx);
      fK0_experiment_fit->Draw("same");
      //fK0_experiment_sig->Draw("same");
      fK0_experiment_sig->SetLineWidth(3);
      fK0_experiment_fit_bg->Draw("same");
      K0_sim_bg->Draw("same");

      TLatex *printFormula5 = new TLatex();
      double high5=0.85;
      double cs_K0_sim,cs_K0,cs_K0_err;
      cs_K0=hsigK0_pure->IntegralAndError(hsigK0_pure->FindBin(450),hsigK0_pure->FindBin(550),cs_K0_err);
      cs_K0_sim=hsigK0_pure_sim->Integral(hsigK0_pure_sim->FindBin(450),hsigK0_pure_sim->FindBin(550));
      
      char text17[10000];
      char text18[10000];
      sprintf(text17,  " #sigma_{simul} = #sigma_{pp} A^{2/3} =%.0f #pm %0.0f #mu b",nuc_cs,err_sum[4]);
      sprintf(text18, "#sigma_{exp} = %.0f #pm %.0f #mu b",nuc_cs*cs_K0/cs_K0_sim,nuc_cs*cs_K0_err/cs_K0_sim);
      printFormula5->SetNDC();
      printFormula5->SetTextFont(32);
      printFormula5->SetTextColor(1);
      printFormula5->SetTextSize(0.04);
      printFormula5->SetTextAlign(13);
      printFormula5->DrawLatex(0.3,high4, text17);
      printFormula5->DrawLatex(0.35,high4-printFormula->GetTextSize()*2, text18);

      TCanvas* cWithoutSB=new TCanvas("cWithoutSB","cWithoutSB");
      TH1F* h1520_exp_EM=(TH1F*)hexperiment_data->Clone("h1520_exp_EM");
      TH1F* hEM_data_sclad=(TH1F*)hEM_data->Clone("hEM_data_sclad");

      double int_min_2=1550;
      double int_max_2=1990;
      double int_exp=hexperiment_data->Integral(hexperiment_data->FindBin(int_min_2),hexperiment_data->FindBin(int_max_2));
      double int_EM_bg=hEM_data->Integral(hEM_data->FindBin(int_min_2),hEM_data->FindBin(int_max_2));

      hEM_data_sclad->Scale(int_exp/int_EM_bg);
      
      h1520_exp_EM->Add(hEM_data_sclad,-1);
      cWithoutSB->Divide(2);

      cWithoutSB->cd(1);
      hexperiment_data->SetAxisRange(1300,2000);
      hexperiment_data->Draw();
      hEM_data_sclad->SetLineColor(kCyan-2);
      hEM_data_sclad->SetMarkerColor(kCyan-2);
      setHistogramStyleData(hEM_data);
      hEM_data_sclad->Draw("same");

      cWithoutSB->cd(2);
      TF1* voigt2= new TF1("voigt2","[0]*TMath::Voigt(x-[1],[2],[3],4)",1380,1750);
      h1520_exp_EM->Draw();
      voigt2->SetParameter(0,2412);
      voigt2->SetParameter(1,1520);
      voigt2->SetParameter(2,5);
      voigt2->FixParameter(2,21.21);
      voigt2->SetParameter(3,50);
      h1520_exp_EM->Fit(voigt2,"RL");
      

      TLatex *printFormula6 = new TLatex();
      double high=0.85;
      char text19[10000];
      char text20[10000];
      char text21[10000];
      char text22[10000];
      char text23[10000];
      sprintf(text19, "#sigma = %.2f MeV",voigt2->GetParameter(2));
      sprintf(text20, "#Gamma = %.2f MeV",voigt2->GetParameter(3));
      sprintf(text21, "#bar{M_{p #pi^{-} #pi^{+} #pi^{-}}} = %.1f MeV",voigt2->GetParameter(1));
      sprintf(text22, "#int_{1400 MeV}^{1620 MeV} = %.1f ",voigt2->Integral(int_min,int_max)/h1520_exp_EM->GetBinWidth(2));
      sprintf(text23, "#sum_{1400 MeV}^{1620 MeV} = %.1f #pm %.1f ",h1520_exp_EM->Integral(h1520_exp_EM->FindBin(int_min),h1520_exp_EM->FindBin(int_max)),hist_error(h1520_exp_EM,int_min,int_max));
      printFormula6->SetNDC();
      printFormula6->SetTextFont(32);
      printFormula6->SetTextColor(1);
      printFormula6->SetTextSize(0.04);
      printFormula6->SetTextAlign(13);
      printFormula6->DrawLatex(0.5,high,text19);
      printFormula6->DrawLatex(0.5,high-printFormula6->GetTextSize(),text20);
      printFormula6->DrawLatex(0.5,high-printFormula6->GetTextSize()*2,text21);
      printFormula6->DrawLatex(0.5,high-printFormula6->GetTextSize()*4,text22);
      printFormula6->DrawLatex(0.5,high-printFormula6->GetTextSize()*7,text23);

      double sig_int_EM=h1520_exp_EM->Integral(h1520_exp_EM->FindBin(int_min),h1520_exp_EM->FindBin(int_max));

      err_sum=hist_error(hpure_signal,int_min,int_max);
      err_sum_EM=hist_error(h1520_exp_EM,int_min,int_max);

      double int_sim_SB=hclean_L1520->Integral(hclean_L1520->FindBin(int_min),hclean_L1520->FindBin(int_max));
      double int_sim_wo_SB=hL1520_data->Integral(hL1520_data->FindBin(int_min),hL1520_data->FindBin(int_max));
      cout<<"Integral for pK0L(1520) (CS from Laura paper), after SB:"<<endl;
      cout<<int_sim_SB<<endl;
      cout<<"Integral for pK0L(1520) (CS from Laura paper), without SB:"<<endl;
      cout<<int_sim_wo_SB<<endl;
      //cout<<"Integral for inclusive L(1520) production:"<<endl;
      //cout<<hclean_L1520_ren->Integral()<<endl;
      cout<<"C-S for pp->pK0L(1520):"<<endl;
      cout<<"5.6*93^{2/3} \mu b:"<<endl;
      cout<<"inclusive L(1520) production C-S, with SB:"<<endl;
      cout<<5.6*nuc_factor*(hpure_signal->Integral(hpure_signal->FindBin(int_min),hpure_signal->FindBin(int_max)))/sig_int<<endl;
      cout<<"inclusive L(1520) production C-S, without SB:"<<endl;
      cout<<5.6*nuc_factor*(sig_int_EM/hL1520_data->Integral(hL1520_data->FindBin(int_min),hL1520_data->FindBin(int_max)))<<endl;
      cout<<"a scaling factor"<<endl;
      cout<<(experiment_int-backgroud_int)/sig_int<<endl;
      cout<<"****************error estimation****************"<<endl;
      cout<<"error sum= "<<err_sum/int_sim_SB*5.6*nuc_factor<<"\mu b"<<endl;
      cout<<"error sum EM= "<<err_sum_EM/int_sim_wo_SB*5.6*nuc_factor<<"\mu b"<<endl;
      cout<<endl<<endl;

      
      //save all
      TFile* output=new TFile("final_output.root","recreate");

      hS1385_data->Write();
      hSDpp_data->Write();
      hLDpp_data->Write();
      hexperiment_data->Write();
      hL1520_data->Write();
      hsum_data->Write();

      hS1385_background->Write();
      hSDpp_background->Write();
      hLDpp_background->Write();
      hexperiment_background->Write();
      hL1520_background->Write();

      hsum_background->Write();
      hclean_background->Write();
      hclean_experiment->Write();
      hclean_L1520->Write();
      hclean_sum->Write();
      hexperiment_SB_spectrum->Write();

      hclean_L1520_ren->Write();
      hclean_sum_ren->Write();
      hpure_signal->Write();

      hexperiemnt_K0->Write();
      hexperiment_L->Write();
      hsim_K0->Write();
      hsim_L->Write();

      hEM_background->Write();
      hEM_data->Write();
      hclean_EM->Write();

      fK0_experiment_fit->Write();
      fK0_experiment_sig->Write();
      fL1116_experiment_fit->Write();
      fL1116_experiment_sig->Write();

      hexperiment_L1520_w->Write();
      hL1520_L1520_w->Write();
      hLDpp_L1520_w->Write();
      hSDpp_L1520_w->Write();
      hS1385_L1520_w->Write();

      hexperiment_L1520_w_SB->Write();
      hL1520_L1520_w_SB->Write();
      hLDpp_L1520_w_SB->Write();
      hSDpp_L1520_w_SB->Write();
      hS1385_L1520_w_SB->Write();

      hexperiment_L1520_pt->Write();
      hL1520_L1520_pt->Write();
      hLDpp_L1520_pt->Write();
      hSDpp_L1520_pt->Write();
      hS1385_L1520_pt->Write();

      hexperiment_L1520_pt_SB->Write();
      hL1520_L1520_pt_SB->Write();
      hLDpp_L1520_pt_SB->Write();
      hSDpp_L1520_pt_SB->Write();
      hS1385_L1520_pt_SB->Write();

      hsum_w_background->Write();
      hsum_pt_background->Write();
      hsum_w_background_SB->Write();
      hsum_pt_background_SB->Write();
      hclean_w_background->Write();
      hclean_pt_background->Write();
      hclean_w_L1520->Write();
      hclean_pt_L1520->Write();
      hclean_w_experiment->Write();
      hclean_pt_experiment->Write();

      line1->Write();
      line2->Write();
      line3->Write();
      line4->Write();

      fbg->Write();
      fVoigt_bg->Write();
      fVoigt->Write();

      cClean_ren->Write();
      cRes->Write();
      cRes_PipPim->Write();
      cClean->Write();
      cClean_PipPim->Write();
      cSum->Write();
      cSB->Write();
      cLK0->Write();
      cK0->Write();
      cL->Write();
      cPt_simul->Write();
      cW_simul->Write();
      cPt_signal->Write();
      cW_signal->Write();
      cWithoutSB->Write();
}
