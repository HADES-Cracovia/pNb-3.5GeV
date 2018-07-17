
int fit_dist()
{
  TFile *f = new TFile("pNb_ppim_280.root");
  TCanvas* c1=new TCanvas("c1","c1");
  TCanvas* c2=new TCanvas("c2","c2");

  c1->Divide(5,5);
  c2->Divide(2);
  
  TH1F *hists[25];
  f.ls();
  char hname[40];
  char new_name[40];
  char f_bg[40];
  char f_sg[40];
  char f_al[40];
  char f_sc[40];
  char f_bc[40];

  TF1 *bg[25];
  TF1 *signal[25];
  TF1 *all[25];
  TF1 *signal_cp[25];
  TF1 *bg_cp[25];
  //Load histograms
  double d_cut[25];
  double d_signal[25];
  double d_bcg[25];
  double d_sig_to_bg[25];
  double d_signif[25];

  
  for(int n=1;n<=25;n++)
    {
      sprintf(hname,"D_p_pim_mass_%d",n*2);
      sprintf(new_name,"mass_%d",n*2);
      hists[n-1]=new TH1F("new_name","new_name",2000,500,2500);
      hists[n-1]=(TH1F*)f->Get(hname);
      d_cut[n-1]=2*n;
    }
  //fit histograms
  for(int j=0;j<25;j++)
    {
      c1->cd(j+1);
      hists[j]->GetXaxis()->SetRange(hists[j]->FindFixBin(1070),hists[j]->FindFixBin(1200));
      hists[j]->Draw();
      sprintf(f_bg,"background_%d",(n+1)*2);
      sprintf(f_sg,"signal_%d",(n+1)*2);
      sprintf(f_al,"all_%d",(n+1)*2);
      sprintf(f_sc,"signal_copy_%d",(n+1)*2);
      sprintf(f_bc,"background_copy_%d",(n+1)*2);
      
      bg[j]=new TF1(f_bg,"pol4",1080,1180);
      bg[j]->SetLineColor(kBlue);

      signal[j]=new TF1(f_sg,"gaus(0)+pol1(4)",1110,1120);
      signal[j]->SetLineColor(kGreen);

      all[j]=new TF1(f_al,"pol4(0)+gaus(5)",1080,1150);
      all[j]->SetLineColor(kGreen);

      signal_cp[j]=new TF1(f_sc,"gaus(0)",1110,1120);
      signal_cp[j]->SetLineColor(kRed);

      bg_cp[j]=new TF1(f_bc,"pol4",1080,1180);
      bg_cp[j]->SetLineColor(kBlue);
      
      hists[j]->Fit(bg[j],"R");
      signal[j]->SetParameters(1500,1115,5,4000);
      hists[j]->Fit(signal[j],"R");
      
      all[j]->SetParameter(0,bg[j]->GetParameter(0));
      all[j]->SetParameter(1,bg[j]->GetParameter(1));
      all[j]->SetParameter(2,bg[j]->GetParameter(2));
      all[j]->SetParameter(3,bg[j]->GetParameter(3));
      all[j]->SetParameter(4,bg[j]->GetParameter(4));
      all[j]->SetParameter(5,signal[j]->GetParameter(0));
      all[j]->SetParameter(6,signal[j]->GetParameter(1));
      all[j]->SetParameter(7,signal[j]->GetParameter(2));

      hists[j]->Fit(all[j],"R");
      
      signal_cp[j]->SetParameter(0,all[j]->GetParameter(5));
      signal_cp[j]->SetParameter(1,all[j]->GetParameter(6));
      signal_cp[j]->SetParameter(2,all[j]->GetParameter(7));

      bg_cp[j]->SetParameter(0,all[j]->GetParameter(0));
      bg_cp[j]->SetParameter(1,all[j]->GetParameter(1));
      bg_cp[j]->SetParameter(2,all[j]->GetParameter(2));
      bg_cp[j]->SetParameter(3,all[j]->GetParameter(3));
      bg_cp[j]->SetParameter(4,all[j]->GetParameter(4));
      
      signal_cp[j]->Draw("same");
      //signal[j]->Draw("same");
      bg_cp[j]->Draw("same");

      d_signal[j]=signal_cp[j]->Integral(1110,1120);
      d_bcg[j]=bg_cp[j]->Integral(1110,1120);
      d_sig_to_bg[j]=d_signal[j]/d_bcg[j];
      d_signif[j]=d_signal[j]/TMath::Sqrt(d_signal[j]+d_bcg[j]);
    }

  
  TGraph *sig_to_bacg=new TGraph(25,d_cut,d_sig_to_bg);
  TGraph *signifi=new TGraph(25,d_cut,d_signif);
  c2->cd(1);
  sig_to_bacg->Draw("AC*");
  c2->cd(2);
  signifi->Draw("AC*");
  
  return 0;
}
