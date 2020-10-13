int draw()
{
  TFile *INCL_inside=new TFile("Lambda1520_in_out_and_allhist.root","OPEN");
  TFile *INCL_outside=new TFile("Lambda1520_after_cascade_insidedecay.root","OPEN");
  TFile *data=new TFile("../final_output.root","OPEN");

  //L(1520) inv mass
  TH1D* hL1520data=(TH1D*)data->Get("h1520_exp_EM");
  TH1D* hL1520INCLin=(TH1D*)INCL_inside->Get("HpzpizLambda1520_decay_inside_before_cascade");
  TH1D* hL1520INCLout=(TH1D*)INCL_outside->Get("HpizeroLambda1520");

  //set the same binning as in data file
  /*hL1520INCLout->Rebin(hL1520data->GetBinWidth(1));
  hL1520INCLin->Rebin(hL1520data->GetBinWidth(1));
  */
  //add both INCL predictions
  //TH1D* hL1520INCLsum=(TH1D*)hL1520INCLin->Clone("hL1520INCLsum");
  //hL1520INCLsum->Add(hL1520INCLout,1);
  
  TCanvas *cL1520=new TCanvas("cL1520");
  //hL1520INCLsum->Draw();
  hL1520INCLout->Draw("same");
  hL1520INCLin->Draw("same");
  
}
