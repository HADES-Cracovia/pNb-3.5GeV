void StyleEM(TH1* h1)
{
  h1->SetLineColor(kRed+2);
  //h1->SetMarkerColor(h1->GetLineColor());
  //h1->SetMarkerStyle(8);
  //h1->SetMarkerSize(2);
  h1->SetLineStyle(1);
  h1->SetLineWidth(3);
  h1->SetFillStyle(3345);
  h1->SetFillColor(kRed+2);
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

int evalEM(void)
{
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
  
  TH1F* hL1116_L1520=(TH1F*)fL1520_SB->Get("orginal_spectrum");
  hL1116_L1520->SetName("hL1116_L1520");
  TH1F* hL1116_L1520K0=(TH1F*)fL1520K0_SB->Get("orginal_spectrum");
  hL1116_L1520K0->SetName("hl1116_l1520K0");
  TH1F* hL1116_SsPimKz=(TH1F*)fSsPimKz_SB->Get("orginal_spectrum");
  hL1116_SsPimKz->SetName("hl1116_SsPimKz");
  
  TH1F* hL1520_L1520=(TH1F*)fL1520_SB->Get("data");
  hL1520_L1520->SetName("hL1520_L1520");
  TH1F* hL1520_L1520K0=(TH1F*)fL1520K0_SB->Get("data");
  hL1520_L1520K0->SetName("hL1520_L1520K0");
  TH1F* hL1520_SsPimKz=(TH1F*)fSsPimKz_SB->Get("data");
  hL1520_SsPimKz->SetName("hl1520_SsPimKz");
  
  
  TH1F* hL1116_L1520_EM=(TH1F*)fL1520_EM->Get("h_EM_for_L1116");
  hL1116_L1520_EM->SetName("hL1116_L1520_EM");
  hL1116_L1520_EM->Rebin(2);
  TH1F* hL1116_L1520K0_EM=(TH1F*)fL1520K0_EM->Get("h_EM_for_L1116");
  hL1116_L1520K0_EM->SetName("hl1116_l1520K0_EM");
  hL1116_L1520K0_EM->Rebin(2);
  TH1F* hL1116_SsPimKz_EM=(TH1F*)fSsPimKz_EM->Get("h_EM_for_L1116");
  hL1116_SsPimKz_EM->SetName("hL1116_SsPimKz_EM");
  hL1116_SsPimKz_EM->Rebin(2);
  
  
  TH1F* hL1520_L1520_EM=(TH1F*)fL1520_EM->Get("h_m_inv_p_pim_pip_pim_L1116EM");
  hL1520_L1520_EM->SetName("hL1520_L1520_EM");
  //hL1520_L1520_EM->Rebin(2);
  TH1F* hL1520_L1520K0_EM=(TH1F*)fL1520K0_EM->Get("h_m_inv_p_pim_pip_pim_L1116EM");
  hL1520_L1520K0_EM->SetName("hL1520_L1520K0_EM");
  //hL1520_L1520K0_EM->Rebin(2);
  TH1F* hL1520_SsPimKz_EM=(TH1F*)fSsPimKz_EM->Get("h_m_inv_p_pim_pip_pim_L1116EM");
  hL1520_SsPimKz_EM->SetName("hL1520_SsPimKz_EM");
  //hL1520_SsPimKz_EM->Rebin(2);
 
  
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

  double sig_L1520=hL1520_L1520->Integral(hL1520_L1520->FindBin(xmin),hL1520_L1520->FindBin(xmax));
  double sig_L1520K0=hL1520_L1520K0->Integral(hL1520_L1520K0->FindBin(xmin),hL1520_L1520K0->FindBin(xmax));
  double sig_SsPimKz=hL1520_SsPimKz->Integral(hL1520_SsPimKz->FindBin(xmin),hL1520_SsPimKz->FindBin(xmax));
  double EM1_L1520=hL1520_L1520_EM->Integral(hL1520_L1520_EM->FindBin(xmin),hL1520_L1520_EM->FindBin(xmax));
  double EM1_L1520K0=hL1520_L1520K0_EM->Integral(hL1520_L1520K0_EM->FindBin(xmin),hL1520_L1520K0_EM->FindBin(xmax));
  double EM1_SsPimKz=hL1520_SsPimKz_EM->Integral(hL1520_SsPimKz_EM->FindBin(xmin),hL1520_SsPimKz_EM->FindBin(xmax));

  TH1F* hL1116_L1520K0_EM_copy=(TH1F*)hL1116_L1520K0_EM->Clone("hL1116_L1520K0_EM_copy");
  TH1F* hL1116_L1520_EM_copy=(TH1F*)hL1116_L1520_EM->Clone("hL1116_L1520_EM_copy");

  hL1520_L1520_EM->Scale(sig_L1520K0/EM1_L1520K0);
  hL1520_L1520K0_EM->Scale(sig_L1520K0/EM1_L1520K0);
  hL1520_SsPimKz_EM->Scale(sig_SsPimKz/EM1_SsPimKz);

  hL1116_L1520_EM->Scale(sig_L1520/EM1_L1520);
  hL1116_L1520K0_EM->Scale(sig_L1520K0/EM1_L1520K0);
  hL1116_SsPimKz_EM->Scale(sig_SsPimKz/EM1_SsPimKz);

  
  //hL1116_L1520K0_EM_copy->Scale(hL1520_L1520K0_EM->Integral());
  //hL1116_L1520_EM_copy->Scale();
  

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
  hL1520_L1520_perfect->Draw("same");
  StylePerfectSignal(hL1520_L1520_perfect);
  hL1520_L1520_perfectBG->Draw("samehist");
  StylePerfectBackground(hL1520_L1520_perfectBG);
  hL1520_L1520_SB->Draw("same");
  StyleDataPints(hL1520_L1520_SB);

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
  hL1520_L1520K0_perfect->Draw("same");
  StylePerfectSignal(hL1520_L1520K0_perfect);
  hL1520_L1520K0_perfectBG->Draw("samehist");
  StylePerfectBackground(hL1520_L1520K0_perfectBG);
  hL1520_L1520K0_SB->Draw("same");
  StyleDataPints(hL1520_L1520K0_SB);

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
  //hSsPimKz_SsPimKz_perfect->Draw("same");
  //StylePerfectSignal(hSsPimKz_SsPimKz_perfect);
  //hSsPimKz_SsPimKz_perfectBG->Draw("samehist");
  //StylePerfectBackground(hSsPimKz_SsPimKz_perfectBG);
  hL1520_SsPimKz_SB->Draw("same");
  StyleDataPints(hL1520_SsPimKz_SB);
  

  return 0;
}
