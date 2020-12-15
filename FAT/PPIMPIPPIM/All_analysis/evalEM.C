void StyleEM(TH1* h1, int col=1)
{
  switch(col)
    {
    case 1:
      h1->SetLineColor(kRed+2);
      h1->SetFillStyle(3345);
      break;
    case 2:
      h1->SetLineColor(kRed-7);
      h1->SetFillStyle(3354);
      break;
    default:
      h1->SetLineColor(kBlue);
      h1->SetFillStyle(3144);
      break;
    }
  //h1->SetMarkerColor(h1->GetLineColor());
  //h1->SetMarkerStyle(8);
  //h1->SetMarkerSize(2);
  h1->SetLineStyle(1);
  h1->SetLineWidth(3);
  h1->SetFillColor(h1->GetLineColor());
}


void StylePerfectSignal(TH1* hist)
{
  hist->SetLineColor(kGreen+2);
  hist->SetLineWidth(2);
  hist->SetLineStyle(7);
}

void StylePerfectBackground(TH1* hist)
{
  
  hist->SetLineColor(kMagenta+1);
  hist->SetLineWidth(3);
  hist->SetLineStyle(7);
  hist->SetFillStyle(3354);
  hist->SetFillColor(kMagenta+1);
}

void StyleDataPints(TH1F* h1)
{
  h1->SetMarkerColor(h1->GetLineColor());
  h1->SetMarkerStyle(8);
  h1->SetMarkerSize(1.2);
}

void StyleSB(TH1F* h1)
{
  h1->SetLineColor(kGreen);
  h1->SetMarkerColor(h1->GetLineColor());
  h1->SetMarkerStyle(8);
  h1->SetMarkerSize(1.2);
}

int evalEM(void)
{
  TFile *fData_SB=new TFile("SB_experiment.root","read");
  TFile *fData_EM=new TFile("EM_data_temp.root","read");
  TFile *fData_EM_4p=new TFile("output_4p_new_hist.root","read");
  TFile *fL1520K0_SB=new TFile("SB_sim_L1520K0thermal.root","read");
  TFile *fL1520_SB=new TFile("SB_sim_L1520thermal.root","read");
  TFile *fSsPimKz_SB=new TFile("SB_sim_SsPimKzthermal.root","read");
  TFile *fL1520K0_EM=new TFile("EM_L1520K0.root","read");
  TFile *fL1520_EM=new TFile("EM_L1520thermal.root","read");
  TFile *fSsPimKz_EM=new TFile("EM_SsPimKzthermal.root","read");
  TFile *fL1520K0_perfect_L1116=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/L1520K0_true_L1116.root","read");
  TFile *fL1520_perfect_L1116=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/L1520_true_L1116.root","read");
  TFile *fL1520K0_perfect_L1520=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/L1520K0_true_L1520.root","read");
  TFile *fL1520_perfect_L1520=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/L1520_true_L1520.root","read");
  TFile *fSsPimKz_perfect_L1116=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/SsPimKz_real_L1116.root","read");
  
  if(fL1520K0_SB && fL1520_SB && fL1520K0_EM && fL1520_EM && fL1520K0_perfect_L1116 && fL1520_perfect_L1116 && fL1520K0_perfect_L1520 && fL1520_perfect_L1520 && fSsPimKz_perfect_L1116 && fSsPimKz_EM)
    cout<<"files open succesfully!!!"<<endl;
  else
    cout<<"problem with files!!!"<<endl;

  
  TH1F* hL1116_data=(TH1F*)fData_SB->Get("orginal_spectrum");
  hL1116_data->SetName("hL1116_data");
  TH1F* hL1116_L1520=(TH1F*)fL1520_SB->Get("orginal_spectrum");
  hL1116_L1520->SetName("hL1116_L1520");
  TH1F* hL1116_L1520K0=(TH1F*)fL1520K0_SB->Get("orginal_spectrum");
  hL1116_L1520K0->SetName("hl1116_l1520K0");
  TH1F* hL1116_SsPimKz=(TH1F*)fSsPimKz_SB->Get("orginal_spectrum");
  hL1116_SsPimKz->SetName("hl1116_SsPimKz");
  
  TH1F* hL1520_data=(TH1F*)fData_SB->Get("data");
  hL1520_data->SetName("hL1520_data");
  TH1F* hL1520_L1520=(TH1F*)fL1520_SB->Get("data");
  hL1520_L1520->SetName("hL1520_L1520");
  TH1F* hL1520_L1520K0=(TH1F*)fL1520K0_SB->Get("data");
  hL1520_L1520K0->SetName("hL1520_L1520K0");
  TH1F* hL1520_SsPimKz=(TH1F*)fSsPimKz_SB->Get("data");
  hL1520_SsPimKz->SetName("hl1520_SsPimKz");

  TH1F* hL1116_data_EM=(TH1F*)fData_EM->Get("h_EM_for_L1116");
  hL1116_data_EM->SetName("hL1116_data_EM");
  hL1116_data_EM->Rebin(2);
  TH1F* hL1116_L1520_EM=(TH1F*)fL1520_EM->Get("h_EM_for_L1116");
  hL1116_L1520_EM->SetName("hL1116_L1520_EM");
  hL1116_L1520_EM->Rebin(2);
  TH1F* hL1116_L1520K0_EM=(TH1F*)fL1520K0_EM->Get("h_EM_for_L1116");
  hL1116_L1520K0_EM->SetName("hl1116_l1520K0_EM");
  hL1116_L1520K0_EM->Rebin(2);
  TH1F* hL1116_SsPimKz_EM=(TH1F*)fSsPimKz_EM->Get("h_EM_for_L1116");
  hL1116_SsPimKz_EM->SetName("hL1116_SsPimKz_EM");
  hL1116_SsPimKz_EM->Rebin(2);

  TH1F* hPipPim_data=(TH1F*)fData_SB->Get("hMPipPim_signal");
  hPipPim_data->SetName("hPipPim_data");
  TH1F* hPipPim_L1520=(TH1F*)fL1520_SB->Get("hMPipPim_signal");
  hPipPim_L1520->SetName("hPipPim_L1520");
  TH1F* hPipPim_L1520K0=(TH1F*)fL1520K0_SB->Get("hMPipPim_signal");
  hPipPim_L1520K0->SetName("hPipPim_L1520K0");
  TH1F* hPipPim_SsPimKz=(TH1F*)fSsPimKz_SB->Get("hMPipPim_signal");
  hPipPim_SsPimKz->SetName("hl1520_SsPimKz");
  
  TH1F* hPipPim_data_SB=(TH1F*)fData_SB->Get("hMPipPim_background");
  hPipPim_data_SB->SetName("hPipPim_data_SB");
  TH1F* hPipPim_L1520_SB=(TH1F*)fL1520_SB->Get("hMPipPim_background");
  hPipPim_L1520_SB->SetName("hPipPim_L1520_SB");
  TH1F* hPipPim_L1520K0_SB=(TH1F*)fL1520K0_SB->Get("hMPipPim_background");
  hPipPim_L1520K0_SB->SetName("hPipPim_L1520K0_SB");
  TH1F* hPipPim_SsPimKz_SB=(TH1F*)fSsPimKz_SB->Get("hMPipPim_background");
  hPipPim_SsPimKz_SB->SetName("hl1520_SsPimKz_SB");

  /*
    TH1F* hPipPim_data_EM=(TH1F*)fData_EM->Get("hMPipPim_background");
    hPipPim_data_EM->SetName("hPipPim_data_EM");
    TH1F* hPipPim_L1520_EM=(TH1F*)fL1520_EM->Get("hMPipPim_background");
    hPipPim_L1520_EM->SetName("hPipPim_L1520_EM");
    TH1F* hPipPim_L1520K0_EM=(TH1F*)fL1520K0_EM->Get("hMPipPim_background");
    hPipPim_L1520K0_EM->SetName("hPipPim_L1520K0_EM");
    TH1F* hPipPim_SsPimKz_EM=(TH1F*)fSsPimKz_EM->Get("hMPipPim_background");
    hPipPim_SsPimKz_EM->SetName("hl1520_SsPimKz_EM");
  */
  
  //EM for L1520, but only pim in L1116 mixed
  TH1F* hL1520_data_EM=(TH1F*)fData_EM->Get("h_m_inv_p_pim_pip_pim_L1116EM");
  hL1520_data_EM->SetName("hL1520_data_EM");
  TH1F* hL1520_L1520_EM=(TH1F*)fL1520_EM->Get("h_m_inv_p_pim_pip_pim_L1116EM");
  hL1520_L1520_EM->SetName("hL1520_L1520_EM");
  //hL1520_L1520_EM->Rebin(2);
  TH1F* hL1520_L1520K0_EM=(TH1F*)fL1520K0_EM->Get("h_m_inv_p_pim_pip_pim_L1116EM");
  hL1520_L1520K0_EM->SetName("hL1520_L1520K0_EM");
  //hL1520_L1520K0_EM->Rebin(2);
  TH1F* hL1520_SsPimKz_EM=(TH1F*)fSsPimKz_EM->Get("h_m_inv_p_pim_pip_pim_L1116EM");
  hL1520_SsPimKz_EM->SetName("hL1520_SsPimKz_EM");
  //hL1520_SsPimKz_EM->Rebin(2);

  //EM for L1520, pim pip mixed
  TH1F* hL1520_data_EM_normal=(TH1F*)fData_EM->Get("h_m_inv_p_pim_pip_pim_signal");
  hL1520_data_EM_normal->SetName("hL1520_data_EM_normal");
  TH1F* hL1520_data_EM_4p=(TH1F*)fData_EM_4p->Get("h_m_inv_p_pim_pip_pim_signal_4p");
  hL1520_data_EM_4p->SetName("hL1520_data_EM_4p");
  //hL1520_data_EM_4p->Rebin(2);
  TH1F* hL1520_L1520_EM_normal=(TH1F*)fL1520_EM->Get("h_m_inv_p_pim_pip_pim_signal");
  hL1520_L1520_EM_normal->SetName("hL1520_L1520_EM_normal");
  //hL1520_L1520_EM_normal->Rebin(2);
  TH1F* hL1520_L1520K0_EM_normal=(TH1F*)fL1520K0_EM->Get("h_m_inv_p_pim_pip_pim_signal");
  hL1520_L1520K0_EM_normal->SetName("hL1520_L1520K0_EM_normal");
  //hL1520_L1520K0_EM_normal->Rebin(2);
  TH1F* hL1520_SsPimKz_EM_normal=(TH1F*)fSsPimKz_EM->Get("h_m_inv_p_pim_pip_pim_signal");
  hL1520_SsPimKz_EM_normal->SetName("hL1520_SsPimKz_EM_normal");
  //hL1520_SsPimKz_EM_normal->Rebin(2);
 
  TH1F* hL1116_L1520_perfect=(TH1F*)fL1520_perfect_L1116->Get("h2");
  hL1116_L1520_perfect->SetName("hL1116_L1520_perfect");
  //hL1116_L1520_perfect->Rebin(2);
  TH1F* hL1116_L1520K0_perfect=(TH1F*)fL1520K0_perfect_L1116->Get("h2");
  hL1116_L1520K0_perfect->SetName("hL1116_L1520K0_perfect");
  //hL1116_L1520K0_perfect->Rebin(2);
  TH1F* hL1116_SsPimKz_perfect=(TH1F*)fSsPimKz_perfect_L1116->Get("h2");
  hL1116_SsPimKz_perfect->SetName("hL1116_SsPimKz_perfect");
  //hL1116_L1520K0_perfect->Rebin(2);

  
  TH1F* hL1520_L1520_perfect=(TH1F*)fL1520_perfect_L1520->Get("h2");
  hL1520_L1520_perfect->SetName("hL1520_L1520_perfect");
  hL1520_L1520_perfect->Rebin(2);
  TH1F* hL1520_L1520K0_perfect=(TH1F*)fL1520K0_perfect_L1520->Get("h2");
  hL1520_L1520K0_perfect->SetName("hL1520_L1520K0_perfect");
  hL1520_L1520K0_perfect->Rebin(2);


  TH1F* hL1520_data_SB=(TH1F*)fData_SB->Get("background");
  hL1520_data_SB->SetName("hL1520_data_SB");
  //hL1520_data_SB->Rebin(2);
  TH1F* hL1520_L1520_SB=(TH1F*)fL1520K0_SB->Get("background");
  hL1520_L1520_SB->SetName("hL1520_L1520_SB");
  //hL1520_L1520_EM->Rebin(2);
  TH1F* hL1520_L1520K0_SB=(TH1F*)fL1520K0_SB->Get("background");
  hL1520_L1520K0_SB->SetName("hL1520_L1520K0_SB");
  //hL1520_L1520K0_EM->Rebin(2);
  TH1F* hL1520_SsPimKz_SB=(TH1F*)fSsPimKz_SB->Get("background");
  hL1520_SsPimKz_SB->SetName("hL1520_SsPimKz_SB");
  //hL1520_SsPimKz_EM->Rebin(2);

  TF1* fBg_L1520=(TF1*)fL1520_SB->Get("fbg");
  fBg_L1520->SetName("fBg_L1520");
  TF1* fBg_L1520K0=(TF1*)fL1520K0_SB->Get("fbg");
  fBg_L1520K0->SetName("fBg_L1520K0");
  TF1* fBg_SsPimKz=(TF1*)fSsPimKz_SB->Get("fbg");
  fBg_SsPimKz->SetName("fBg_SsPimKz");


  
  //Sigma+ Sigma-
  TH1F* hSp_data=(TH1F*)fData_SB->Get("hMPPimPip");
  hSp_data->SetName("hSp_data");
  TH1F* hSp_data_SB=(TH1F*)fData_SB->Get("hMPPimPip_SB");
  hSp_data_SB->SetName("hSp_data_SB");
  TH1F* hSp_data_EM_4p=(TH1F*)fData_EM_4p->Get("hMPPimPip_4p");
  hSp_data_EM_4p->SetName("hSp_data_EM_4p");
  TH1F* hSp_data_EM=(TH1F*)fData_EM->Get("hMPPimPip");
  hSp_data_EM->SetName("hSp_data_EM");
  
  TH1F* hSm_data=(TH1F*)fData_SB->Get("hMPPimPim");
  hSm_data->SetName("hSm_data");
  TH1F* hSm_data_SB=(TH1F*)fData_SB->Get("hMPPimPim_SB");
  hSm_data_SB->SetName("hSm_data_SB");
  TH1F* hSm_data_EM=(TH1F*)fData_EM->Get("hMPPimPim");
  hSm_data_EM->SetName("hSm_data_EM");
  TH1F* hSm_data_EM_4p=(TH1F*)fData_EM_4p->Get("hMPPimPim_4p");
  hSm_data_EM_4p->SetName("hSm_data_EM_4p");

  
  cout<<"binning for different histograms"<<endl;
  cout<<"hL1116_L1520_perfect: "<<hL1116_L1520_perfect->GetBinWidth(1)<<endl;
  cout<<"hL1116_L1520K0_perfect: "<<hL1116_L1520K0_perfect->GetBinWidth(1)<<endl;
  cout<<"hL1116_L1520: "<<hL1116_L1520->GetBinWidth(1)<<endl;
  cout<<"hL1116_L1520K0: "<<hL1116_L1520K0->GetBinWidth(1)<<endl;
  
  
  TH1F* hL1116_L1520_perfectBG=(TH1F*)hL1116_L1520->Clone("hL1116_L1520_perfectBG");
  hL1116_L1520_perfectBG->Add(hL1116_L1520_perfect,-1);
  TH1F* hL1116_L1520K0_perfectBG=(TH1F*)hL1116_L1520K0->Clone("hL1116_L1520K0_perfectBG");
  hL1116_L1520K0_perfectBG->Add(hL1116_L1520K0_perfect,-1);
  TH1F* hL1116_SsPimKz_perfectBG=(TH1F*)hL1116_SsPimKz->Clone("hL1116_SsPimKz_perfectBG");
  hL1116_SsPimKz_perfectBG->Add(hL1116_SsPimKz_perfect,-1);

  TH1F* hL1520_L1520_perfectBG=(TH1F*)hL1520_L1520->Clone("hL1520_L1520_perfectBG");
  hL1520_L1520_perfectBG->Add(hL1520_L1520_perfect,-1);
  TH1F* hL1520_L1520K0_perfectBG=(TH1F*)hL1520_L1520K0->Clone("hL1520_L1520K0_perfectBG");
  hL1520_L1520K0_perfectBG->Add(hL1520_L1520K0_perfect,-1);
  
  
  //scale EM
  double xmin=1600;
  double xmax=2000;
  double xmin1=1106;
  double xmax1=1126;

  
  double sig_data=hL1520_data->Integral(hL1520_data->FindBin(xmin),hL1520_data->FindBin(xmax));
  double sig_L1520=hL1520_L1520->Integral(hL1520_L1520->FindBin(xmin),hL1520_L1520->FindBin(xmax));
  double sig_L1520K0=hL1520_L1520K0->Integral(hL1520_L1520K0->FindBin(xmin),hL1520_L1520K0->FindBin(xmax));
  double sig_SsPimKz=hL1520_SsPimKz->Integral(hL1520_SsPimKz->FindBin(xmin),hL1520_SsPimKz->FindBin(xmax));

  double EM1_data=hL1520_data_EM->Integral(hL1520_data_EM->FindBin(xmin),hL1520_data_EM->FindBin(xmax));
  double EM1_data_4p=hL1520_data_EM_4p->Integral(hL1520_data_EM_4p->FindBin(xmin),hL1520_data_EM_4p->FindBin(xmax));
  double EM1_L1520=hL1520_L1520_EM->Integral(hL1520_L1520_EM->FindBin(xmin),hL1520_L1520_EM->FindBin(xmax));
  double EM1_L1520K0=hL1520_L1520K0_EM->Integral(hL1520_L1520K0_EM->FindBin(xmin),hL1520_L1520K0_EM->FindBin(xmax));
  double EM1_SsPimKz=hL1520_SsPimKz_EM->Integral(hL1520_SsPimKz_EM->FindBin(xmin),hL1520_SsPimKz_EM->FindBin(xmax));

  double EM1_data_n=hL1520_data_EM_normal->Integral(hL1520_data_EM_normal->FindBin(xmin),hL1520_data_EM_normal->FindBin(xmax));
  double EM1_L1520_n=hL1520_L1520_EM_normal->Integral(hL1520_L1520_EM_normal->FindBin(xmin),hL1520_L1520_EM_normal->FindBin(xmax));
  double EM1_L1520K0_n=hL1520_L1520K0_EM_normal->Integral(hL1520_L1520K0_EM_normal->FindBin(xmin),hL1520_L1520K0_EM_normal->FindBin(xmax));
  double EM1_SsPimKz_n=hL1520_SsPimKz_EM_normal->Integral(hL1520_SsPimKz_EM_normal->FindBin(xmin),hL1520_SsPimKz_EM_normal->FindBin(xmax));
  
  double EM2_data=hL1116_data_EM->Integral(hL1116_data_EM->FindBin(xmin1),hL1116_data_EM->FindBin(xmax1));
  double EM2_L1520=hL1116_L1520_EM->Integral(hL1116_L1520_EM->FindBin(xmin1),hL1116_L1520_EM->FindBin(xmax1));
  double EM2_L1520K0=hL1116_L1520K0_EM->Integral(hL1116_L1520K0_EM->FindBin(xmin1),hL1116_L1520K0_EM->FindBin(xmax1));
  double EM2_SsPimKz=hL1116_SsPimKz_EM->Integral(hL1116_SsPimKz_EM->FindBin(xmin1),hL1116_SsPimKz_EM->FindBin(xmax1));


  
  TH1F* hL1116_L1520K0_EM_copy=(TH1F*)hL1116_L1520K0_EM->Clone("hL1116_L1520K0_EM_copy");
  TH1F* hL1116_L1520_EM_copy=(TH1F*)hL1116_L1520_EM->Clone("hL1116_L1520_EM_copy");

  hL1520_data_EM->Scale(sig_data/EM1_data);
  hL1520_L1520_EM->Scale(sig_L1520K0/EM1_L1520K0);
  hL1520_L1520K0_EM->Scale(sig_L1520K0/EM1_L1520K0);
  hL1520_SsPimKz_EM->Scale(sig_SsPimKz/EM1_SsPimKz);

  hL1520_data_EM_4p->Scale(sig_data/EM1_data_4p);
  hSp_data_EM_4p->Scale(sig_data/EM1_data_4p);
  hSm_data_EM_4p->Scale(sig_data/EM1_data_4p);
  
  hL1520_data_EM_normal->Scale(sig_data/EM1_data_n);
  hL1520_L1520_EM_normal->Scale(sig_L1520K0/EM1_L1520K0_n);
  hL1520_L1520K0_EM_normal->Scale(sig_L1520K0/EM1_L1520K0_n);
  hL1520_SsPimKz_EM_normal->Scale(sig_SsPimKz/EM1_SsPimKz_n);

  hSp_data_EM->Scale(sig_data/EM1_data_n);
  hSm_data_EM->Scale(sig_data/EM1_data_n);
  
  hL1116_data_EM->Scale(1/EM2_data*hL1520_data_EM->Integral());
  hL1116_L1520_EM->Scale(1/EM2_L1520*hL1520_L1520_EM->Integral());
  hL1116_L1520K0_EM->Scale(1/EM2_L1520K0*hL1520_L1520K0_EM->Integral());
  hL1116_SsPimKz_EM->Scale(1/EM2_SsPimKz*hL1520_SsPimKz_EM->Integral());

  
  //hL1116_L1520K0_EM_copy->Scale(hL1520_L1520K0_EM->Integral());
  //hL1116_L1520_EM_copy->Scale();
  
  int rebin_data=2;
  TCanvas *cdata=new TCanvas("cdata","cdata");
  cdata->Divide(2);
  cdata->cd(1);
  hL1116_data->Draw();
  StyleDataPints(hL1116_data);
  hL1116_data->GetXaxis()->SetRangeUser(1070,1300);
  hL1116_data_EM->Draw("same");
  StyleEM(hL1116_data_EM); 

  cdata->cd(2);
  hL1520_data->Draw();
  hL1520_data->Rebin(rebin_data);
  StyleDataPints(hL1520_data);
  hL1520_data->GetXaxis()->SetRangeUser(1300,2000);
  hL1520_data_EM->Draw("same");
  hL1520_data_EM->Rebin(rebin_data);
  hL1520_data_EM_normal->Draw("same");
  hL1520_data_EM_normal->Rebin(rebin_data);
  StyleEM(hL1520_data_EM);
  StyleEM(hL1520_data_EM_normal,2);
  hL1520_data_SB->Draw("same");
  hL1520_data_SB->Rebin(rebin_data);
  StyleSB(hL1520_data_SB);
  hL1520_data_EM_4p->Draw("same");
  hL1520_data_EM_4p->Rebin(rebin_data);
  
  TCanvas *cL1520=new TCanvas("cL1520","cL1520");
  cL1520->Divide(2);
  cL1520->cd(1);
  hL1116_L1520->Draw();
  StyleDataPints(hL1116_L1520);
  hL1116_L1520->GetXaxis()->SetRangeUser(1070,1160);
  hL1116_L1520_EM->Draw("same");
  StyleEM(hL1116_L1520_EM);  
  hL1116_L1520_perfect->Draw("same");
  StylePerfectSignal(hL1116_L1520_perfect);
  hL1116_L1520_perfectBG->Draw("samehist");
  StylePerfectBackground(hL1116_L1520_perfectBG);
  //hL1116_L1520_EM_copy->Draw("same");
  fBg_L1520->Draw("same");

  cL1520->cd(2);
  hL1520_L1520->Draw();
  StyleDataPints(hL1520_L1520);
  hL1520_L1520->GetXaxis()->SetRangeUser(1300,1850);
  hL1520_L1520_EM->Draw("same");
  StyleEM(hL1520_L1520_EM);
  hL1520_L1520_EM_normal->Draw("same");
  StyleEM(hL1520_L1520_EM_normal,2);
  hL1520_L1520_perfect->Draw("same");
  StylePerfectSignal(hL1520_L1520_perfect);
  hL1520_L1520_perfectBG->Draw("samehist");
  StylePerfectBackground(hL1520_L1520_perfectBG);
  hL1520_L1520_SB->Draw("same");
  StyleSB(hL1520_L1520_SB);

  TCanvas *cL1520K0=new TCanvas("cL1520K0","cL1520K0");
  cL1520K0->Divide(2);
  cL1520K0->cd(1);
  hL1116_L1520K0->Draw();
  StyleDataPints(hL1116_L1520K0);
  hL1116_L1520K0->GetXaxis()->SetRangeUser(1070,1160);
  hL1116_L1520K0_EM->Draw("same");
  StyleEM(hL1116_L1520K0_EM);
  hL1116_L1520K0_perfect->Draw("same");
  StylePerfectSignal(hL1116_L1520K0_perfect);
  hL1116_L1520K0_perfectBG->Draw("samehist");
  StylePerfectBackground(hL1116_L1520K0_perfectBG);
  fBg_L1520K0->Draw("same");
  //hL1116_L1520K0_EM_copy->Draw("same");

  cL1520K0->cd(2);
  hL1520_L1520K0->Draw();
  StyleDataPints(hL1520_L1520K0);
  hL1520_L1520K0->GetXaxis()->SetRangeUser(1300,1850);
  hL1520_L1520K0_EM->Draw("same");
  StyleEM(hL1520_L1520K0_EM);
  hL1520_L1520K0_EM_normal->Draw("same");
  StyleEM(hL1520_L1520K0_EM_normal,2);
  hL1520_L1520K0_perfect->Draw("same");
  StylePerfectSignal(hL1520_L1520K0_perfect);
  hL1520_L1520K0_perfectBG->Draw("samehist");
  StylePerfectBackground(hL1520_L1520K0_perfectBG);
  hL1520_L1520K0_SB->Draw("same");
  StyleSB(hL1520_L1520K0_SB);

  TCanvas *cSsPimKz=new TCanvas("cSsPimKz","cSsPimKz");
  cSsPimKz->Divide(2);
  cSsPimKz->cd(1);
  hL1116_SsPimKz->Draw();
  StyleDataPints(hL1116_SsPimKz);
  hL1116_SsPimKz->GetXaxis()->SetRangeUser(1070,1160);
  hL1116_SsPimKz_EM->Draw("same");
  StyleEM(hL1116_SsPimKz_EM);  
  hL1116_SsPimKz_perfect->Draw("same");
  StylePerfectSignal(hL1116_SsPimKz_perfect);
  hL1116_SsPimKz_perfectBG->Draw("samehist");
  StylePerfectBackground(hL1116_SsPimKz_perfectBG);
  //hL1116_SsPimKz_EM_copy->Draw("same");
  fBg_SsPimKz->Draw("same");

  cSsPimKz->cd(2);
  hL1520_SsPimKz->Draw();
  StyleDataPints(hL1520_SsPimKz);
  hL1520_SsPimKz->GetXaxis()->SetRangeUser(1300,1850);
  hL1520_SsPimKz_EM->Draw("same");
  StyleEM(hL1520_SsPimKz_EM);
  hL1520_SsPimKz_EM_normal->Draw("same");
  StyleEM(hL1520_SsPimKz_EM_normal,2);
  //hSsPimKz_SsPimKz_perfect->Draw("same");
  //StylePerfectSignal(hSsPimKz_SsPimKz_perfect);
  //hSsPimKz_SsPimKz_perfectBG->Draw("samehist");
  //StylePerfectBackground(hSsPimKz_SsPimKz_perfectBG);
  hL1520_SsPimKz_SB->Draw("same");
  StyleSB(hL1520_SsPimKz_SB);

  int rebin_sigmas=4;
  TCanvas* cSp=new TCanvas("cSp","cSp");
  hSp_data->GetXaxis()->SetRangeUser(1200,1500);
  hSp_data->Draw();   
  hSp_data->Rebin(rebin_sigmas);
  StyleDataPints(hSp_data);
  hSp_data_EM->Draw("same");
  hSp_data_EM->Rebin(rebin_sigmas);
  StyleEM(hSp_data_EM,2);
  hSp_data_SB->Draw("same");
  hSp_data_SB->Rebin(rebin_sigmas);
  StyleSB(hSp_data_SB);
  hSp_data_EM_4p->Draw("same");
  hSp_data_EM_4p->Rebin(rebin_sigmas);
  
  TCanvas* cSm=new TCanvas("cSm","cSm");
  hSm_data->GetXaxis()->SetRangeUser(1200,1500);
  hSm_data->Draw();   
  hSm_data->Rebin(rebin_sigmas);
  StyleDataPints(hSm_data);
  hSm_data_EM->Draw("same");
  hSm_data_EM->Rebin(rebin_sigmas);
  StyleEM(hSm_data_EM,2);
  hSm_data_SB->Draw("same");
  hSm_data_SB->Rebin(rebin_sigmas);
  StyleSB(hSm_data_SB);
  hSm_data_EM_4p->Draw("same");
  hSm_data_EM_4p->Rebin(rebin_sigmas);
  
  return 0;
}
