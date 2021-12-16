void set2Range(TH2* h2)
{
  h2->GetXaxis()->SetRangeUser(0,1600);
  h2->GetYaxis()->SetRangeUser(0,1.6);
}

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

  TH2F* h2PtvsYFinal=(TH2F*)fAfterCuts->Get("h2PtvsY");
  h2PtvsYFinal->SetName("h2PtvsYFinal");
  TH2F* h2PtvsYPluto=(TH2F*)fPluto->Get("h2PtvsY");
  h2PtvsYPluto->SetName("h2PtvsYPluto");
  TH2F* h2PtvsYEff=h2PtvsYFinal->Clone("h2PtvsYFinal");
  h2PtvsYEff->SetName("h2PtvsYEff");

  set2Range(h2PtvsYFinal);
  set2Range(h2PtvsYPluto);
  set2Range(h2PtvsYEff);
    
  hPtL1520Pluto->Sumw2();
  hPtL1520Final->Sumw2();
  hPtL1520Eff->Sumw2();

  hYL1520Pluto->Sumw2();
  hYL1520Final->Sumw2();
  hYL1520Eff->Sumw2();

  rescaleHist(hPtL1520Pluto,1000);
  hPtL1520Pluto->Rebin((int)(hPtL1520Pluto->GetNbinsX()/hPtL1520Final->GetNbinsX()));
  hYL1520Pluto->Rebin((int)(hYL1520Pluto->GetNbinsX()/hYL1520Final->GetNbinsX()));

  hPtL1520Eff->Divide(hPtL1520Pluto);
  hYL1520Eff->Divide(hYL1520Pluto);
  h2PtvsYEff->Divide(h2PtvsYPluto);
  
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

  TCanvas* cEff2D=new TCanvas("cEff2D");
  h2PtvsYEff->Draw("colz");
  
  
  TCanvas* cDistribution=new TCanvas("cDistribution","Simulated vs reconstructed events");
  double y_rapidity=1.11788; //cm rapidity
  TLine* particleY=new TLine(0,y_rapidity,1600,y_rapidity);
  particleY->SetLineWidth(2);
  particleY->SetLineColor(kRed);
  
  cDistribution->Divide(2);
  cDistribution->cd(1);
  h2PtvsYPluto->Draw("colz");
  
  particleY->Draw("same");
  cDistribution->cd(2);
  h2PtvsYFinal->Draw("colz");
  particleY->Draw("same");
  
  TCanvas *cPtvsY=new TCanvas("cPtvsY","cPtvsY");
  cPtvsY->Divide(2,2);
  cPtvsY->cd(1);
  h2PtvsYFinal->Draw("colz");
  cPtvsY->cd(2);
  h2PtvsYPluto->Draw("colz");
  cPtvsY->cd(3);
  h2PtvsYEff->Draw("colz");
  h2PtvsYEff->Rebin2D(2,2);
  h2PtvsYEff->Scale(1/4.);
  cPtvsY->cd(4);
  
  cPt->Write();
  cY->Write();
  cEff->Write();
  cDistribution->Write();
  cEff2D->Write();
  cPtvsY->Write();
  
  hPtL1520Pluto->Write();
  hYL1520Pluto->Write();
  hPtL1520Final->Write();
  hYL1520Final->Write();
  hPtL1520Eff->Write();
  hYL1520Eff->Write();

  h2PtvsYFinal->Write();
  h2PtvsYPluto->Write();
  h2PtvsYEff->Write();

  
  fout->Write();
  
  
  return 0;
}
