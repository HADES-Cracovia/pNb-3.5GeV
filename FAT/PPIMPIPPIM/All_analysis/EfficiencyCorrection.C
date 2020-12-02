void rescaleHist(TH1F* h,double scale=1, double shift=0)
{
  TH1F* temp=(TH1F*)h->Clone("temp");
  int nbins=temp->GetNbinsX();
  h->Reset();
  h->SetBins(temp->GetNbinsX(),temp->GetXaxis()->GetBinLowEdge(1)*scale+shift, temp->GetXaxis()->GetBinUpEdge(nbins)*scale+shift);
  
  for(int i=0;i<=nbins;i++)
    {
      //h->SetBins(i,temp->GetXaxis()->GetBinLowEdge(i)*scale+shift,temp->GetXaxis()->GetBinUpEdge(i)*scale+shift);
      h->SetBinContent(i,temp->GetBinContent(i));
    }
  delete temp;
}
   

int EfficiencyCorrection(void)
{
  TFile* fAfterCuts=new TFile("SB_sim_L1520K0thermal.root","read");
  TFile* fPluto=new TFile("/lustre/hades/user/knowakow/PNB/pluto_gen/output_L1520K0/sprawdzenie_output.root","read");

  TFile* fout=new TFile("eff_output.root","recreate");
  
  TH1F* hPtL1520Pluto=(TH1F*)fPluto->Get("hPtL1520");
  TH1F* hYL1520Pluto=(TH1F*)fPluto->Get("hYL1520");
  TH1F* hPtL1520Final=(TH1F*)fAfterCuts->Get("hL1520_pt");
  TH1F* hYL1520Final=(TH1F*)fAfterCuts->Get("hL1520_w");
  TH1F* hPtL1520Eff=hPtL1520Final->Clone("hPtL1520Eff");
  TH1F* hYL1520Eff=hYL1520Final->Clone("hYL1520Eff");

  
  rescaleHist(hPtL1520Pluto,1000);
  hPtL1520Pluto->Rebin((int)(hPtL1520Pluto->GetNbinsX()/hPtL1520Final->GetNbinsX()));
  hYL1520Pluto->Rebin((int)(hYL1520Pluto->GetNbinsX()/hYL1520Final->GetNbinsX()));

  hPtL1520Eff->Divide(hPtL1520Pluto);
  hYL1520Eff->Divide(hYL1520Pluto);
  
  TCanvas* cPt=new TCanvas("cPt","cPt");
  hPtL1520Pluto->Draw();
  hPtL1520Final->Draw("same");
  
  TCanvas* cY=new TCanvas("cY","cY");
  hYL1520Pluto->Draw();
  hYL1520Final->Draw("same");

  TCanvas* cEff=new TCanvas("cEff","Y and pt efficiency");
  cEff->Divide(2);
  cEff->cd(1);
  hPtL1520Eff->Draw();
  cEff->cd(2);
  hYL1520Eff->Draw();

  cPt->Write();
  cY->Write();
  cEff->Write();
  
  fout->Write();
  
  
  return 0;
}
