
int evalEM(void)
{
  TFile *fL1520K0_SB=new TFile("SB_sim_L1520K0thermal.root","read");
  TFile *fL1520_SB=new TFile("SB_sim_L1520thermal.root","read");
  TFile *fL1520K0_EM=new TFile("EM_L1520K0.root","read");
  TFile *fL1520_EM=new TFile("EM_L1520thermal.root","read");
  TFile *fL1520K0_perfect=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/L1520K0_true_L1116.root","read");
  TFile *fL1520_perfect=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/L1520K0_true_L1116.root","read");

  
  if(fL1520K0_SB && fL1520_SB && fL1520K0_EM && fL1520_EM)
    cout<<"files open succesfully!!!"<<endl;
  else
    cout<<"problem with files!!!"<<endl;
  
  TH1F* hL1116_L1520=(TH1F*)fL1520_SB->Get("orginal_spectrum");
  hL1116_L1520->SetName("hL1116_L1520");
  TH1F* hL1116_L1520K0=(TH1F*)fL1520K0_SB->Get("orginal_spectrum");
  hL1116_L1520K0->SetName("hl1116_l1520K0");

  TH1F* hL1520_L1520=(TH1F*)fL1520_SB->Get("data");
  hL1520_L1520->SetName("hL1520_L1520");
  TH1F* hL1520_L1520K0=(TH1F*)fL1520K0_SB->Get("data");
  hL1520_L1520K0->SetName("hL1520_L1520K0");

  TH1F* hL1116_L1520_EM=(TH1F*)fL1520_EM->Get("h_EM_for_L1116");
  hL1116_L1520_EM->SetName("hL1116_L1520_EM");
  hL1116_L1520_EM->Rebin(2);
  TH1F* hL1116_L1520K0_EM=(TH1F*)fL1520K0_EM->Get("h_EM_for_L1116");
  hL1116_L1520K0_EM->SetName("hl1116_l1520K0_EM");
  hL1116_L1520K0_EM->Rebin(2);
  
  TH1F* hL1520_L1520_EM=(TH1F*)fL1520_EM->Get("h_m_inv_p_pim_pip_pim_L1116EM");
  hL1520_L1520_EM->SetName("hL1520_L1520_EM");
  //hL1520_L1520_EM->Rebin(2);
  TH1F* hL1520_L1520K0_EM=(TH1F*)fL1520K0_EM->Get("h_m_inv_p_pim_pip_pim_L1116EM");
  hL1520_L1520K0_EM->SetName("hL1520_L1520K0_EM");
  //hL1520_L1520K0_EM->Rebin(2);
  
  TH1F* hL1116_L1520_perfect=(TH1F*)fL1520_perfect->Get("h2");
  hL1116_L1520_perfect->SetName("hL1116_L1520_perfect");
  //hL1116_L1520_perfect->Rebin(2);
  TH1F* hL1116_L1520K0_perfect=(TH1F*)fL1520K0_perfect->Get("h2");
  hL1116_L1520K0_perfect->SetName("hL1116_L1520K0_perfect");
  //hL1116_L1520K0_perfect->Rebin(2);

  cout<<"binning for different histograms"<<endl;
  cout<<"hL1116_L1520_perfect: "<<hL1116_L1520_perfect->GetBinWidth(1)<<endl;
  cout<<"hL1116_L1520K0_perfect: "<<hL1116_L1520K0_perfect->GetBinWidth(1)<<endl;
  cout<<"hL1116_L1520: "<<hL1116_L1520->GetBinWidth(1)<<endl;
  cout<<"hL1116_L1520K0: "<<hL1116_L1520K0->GetBinWidth(1)<<endl;
  
  
  TH1F* hL1116_L1520_perfectBG=(TH1F*)hL1116_L1520->Clone("hL1116_L1520_perfectBG");
  hL1116_L1520_perfectBG->Add(hL1116_L1520_perfect,-1);
  TH1F* hL1116_L1520K0_perfectBG=(TH1F*)hL1116_L1520K0->Clone("hL1116_L1520K0_perfectBG");
  hL1116_L1520K0_perfectBG->Add(hL1116_L1520K0_perfect,-1);
  
  
  //scale EM
  double xmin=1600;
  double xmax=2000;

  double sig_L1520=hL1520_L1520->Integral(hL1520_L1520->FindBin(xmin),hL1520_L1520->FindBin(xmax));
  double sig_L1520K0=hL1520_L1520K0->Integral(hL1520_L1520->FindBin(xmin),hL1520_L1520->FindBin(xmax));
  double EM1_L1520=hL1520_L1520_EM->Integral(hL1520_L1520_EM->FindBin(xmin),hL1520_L1520_EM->FindBin(xmax));
  double EM1_L1520K0=hL1520_L1520K0_EM->Integral(hL1520_L1520K0_EM->FindBin(xmin),hL1520_L1520K0_EM->FindBin(xmax));

  TH1F* hL1116_L1520K0_EM_copy=(TH1F*)hL1116_L1520K0_EM->Clone("hL1116_L1520K0_EM_copy");
  TH1F* hL1116_L1520_EM_copy=(TH1F*)hL1116_L1520_EM->Clone("hL1116_L1520_EM_copy");

  hL1520_L1520_EM->Scale(sig_L1520K0/EM1_L1520K0);
  hL1520_L1520K0_EM->Scale(sig_L1520K0/EM1_L1520K0);

  hL1116_L1520_EM->Scale(sig_L1520/EM1_L1520);
  hL1116_L1520K0_EM->Scale(sig_L1520K0/EM1_L1520K0);

  //hL1116_L1520K0_EM_copy->Scale(hL1520_L1520K0_EM->Integral());
  //hL1116_L1520_EM_copy->Scale();
  

  TCanvas *cL1520=new TCanvas("cL1520");
  cL1520->Divide(2);
  cL1520->cd(1);
  hL1116_L1520->Draw();
  hL1116_L1520->GetXaxis()->SetRangeUser(1000,1300);
  hL1116_L1520_EM->Draw("same");
  hL1116_L1520_perfect->Draw("same");
  hL1116_L1520_perfectBG->Draw("same");
  //hL1116_L1520_EM_copy->Draw("same");
  cL1520->cd(2);
  hL1520_L1520->Draw();
  hL1520_L1520_EM->Draw("same");
  

  TCanvas *cL1520K0=new TCanvas("cL1520K0");
  cL1520K0->Divide(2);
  cL1520K0->cd(1);
  hL1116_L1520K0->Draw();
  hL1116_L1520K0->GetXaxis()->SetRangeUser(1000,1300);
  hL1116_L1520K0_EM->Draw("same");
  hL1116_L1520K0_perfect->Draw("same");
  hL1116_L1520K0_perfectBG->Draw("same");
  //hL1116_L1520K0_EM_copy->Draw("same");
  cL1520K0->cd(2);
  hL1520_L1520K0->Draw();
  hL1520_L1520K0_EM->Draw("same");
  
  
  return 0;
}
