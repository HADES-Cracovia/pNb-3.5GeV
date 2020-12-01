int EfficiencyCorrection(void)
{
  TFile* fAfterCuts=new TFile("SB_sim_L1520K0thermal.root","read");
  TFile* fPluto=new TFile("/lustre/hades/user/knowakow/PNB/pluto_gen/output_L1520K0/sprawdzenie_output.root","read");

  TFile* fout=new TFile("eff_output.root","recreate");
  
  TH1F* hPtL1520Pluto=(TH1F*)fPluto->Get("hPtL1520");
  TH1F* hYL1520Pluto=(TH1F*)fPluto->Get("hYL1520");
  TH1F* hPtL1520Final=(TH1F*)fAfterCuts->Get("hL1520_pt");
  TH1F* hYL1520Final=(TH1F*)fAfterCuts->Get("hL1520_w");

  TH1F* hPtL1520Final_rescale=(TH1F*)hPtL1520Pluto->Clone("hPtL1520Final_rescale");
  hPtL1520Final_rescale->Reset();
  TH1F* hYL1520Final_rescale=(TH1F*)hYL1520Final->Clone("hYL1520Final_rescale");
  hYL1520Final_rescale->Reset();

  //wypelnienie histogramow
  
  
  TCanvas* cPt=new TCanvas("cPt","cPt");
  hPtL1520Pluto->Draw();
  hPtL1520Final->Draw("same");
  
  TCanvas* cY=new TCanvas("cY","cY");
  hYL1520Pluto->Draw();
  hYL1520Final->Draw("same");

  cPt->Write();
  cY->Write();
  
  fout->Write();
  
  
  return 0;
}
