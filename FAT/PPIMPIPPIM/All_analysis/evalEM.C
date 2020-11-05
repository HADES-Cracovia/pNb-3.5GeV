int evalEM(void)
{
  TFile *fL1520K0_SB=new TFile("SB_sim_L1520K0thermal.root","read");
  TFile *fL1520_SB=new TFile("SB_sim_L1520thermal.root","read");
  TFile *fL1520K0_EM=new TFile("EM_L1520K0.root","read");
  TFile *fL1520_EM=new TFile("EM_L1520thermal.root","read");
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
  TH1F* hL1116_L1520K0_EM=(TH1F*)fL1520K0_EM->Get("h_EM_for_L1116");
  hL1116_L1520K0_EM->SetName("hl1116_l1520K0_EM");

  TH1F* hL1520_L1520_EM=(TH1F*)fL1520_EM->Get("h_m_inv_p_pim_pip_pim_L1116EM");
  hL1520_L1520_EM->SetName("hL1520_L1520_EM");
  TH1F* hL1520_L1520K0_EM=(TH1F*)fL1520K0_EM->Get("h_m_inv_p_pim_pip_pim_L1116EM");
  hL1520_L1520K0_EM->SetName("hL1520_L1520K0_EM");

  //scale EM
  double xmin=1800;
  double xmax=2000;
  double sig_L1520=hL1520_L1520->Integral(hL1520_L1520->FindBin(xmin),hL1520_L1520->FindBin(xmax));
  double sig_L1520K0=hL1520_L1520K0->Integral(hL1520_L1520->FindBin(xmin),hL1520_L1520->FindBin(xmax));
  double EM1_L1520=hL1520_L1520_EM->Integral(hL1520_L1520_EM->FindBin(xmin),hL1520_L1520_EM->FindBin(xmax));
  double EM1_L1520K0=hL1520_L1520K0_EM->Integral(hL1520_L1520K0_EM->FindBin(xmin),hL1520_L1520K0_EM->FindBin(xmax));

  hL1520_L1520_EM->Scale(sig_L1520/EM1_L1520);
  hL1520_L1520K0_EM->Scale(sig_L1520K0/EM1_L1520K0);


  hL1116_L1520_EM->Scale(sig_L1520/EM1_L1520);
  hL1116_L1520K0_EM->Scale(sig_L1520K0/EM1_L1520K0);


  TCanvas *cL1520=new TCanvas("cL1520");
  cL1520->Divide(2);
  cL1520->cd(1);
  hL1116_L1520->Draw();
  hL1116_L1520->GetXaxis()->SetRangeUser(1000,1300);
  hL1116_L1520_EM->Draw("same");
  cL1520->cd(2);
  hL1520_L1520->Draw();
  hL1520_L1520_EM->Draw("same");

  TCanvas *cL1520K0=new TCanvas("cL1520K0");
  cL1520K0->Divide(2);
  cL1520K0->cd(1);
  hL1116_L1520K0->Draw();
  hL1116_L1520K0->GetXaxis()->SetRangeUser(1000,1300);
  hL1116_L1520K0_EM->Draw("same");
  cL1520K0->cd(2);
  hL1520_L1520K0->Draw();
  hL1520_L1520K0_EM->Draw("same");
  
  return 0;
}
