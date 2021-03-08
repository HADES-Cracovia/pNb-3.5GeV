void set_sum_style(TH1F* hist)
{
  hist->SetLineColor(kGreen);
  hist->SetLineWidth(3);
}
void set_fill_style(TH1F* hist)
{
  hist->SetFillStyle(3325);
  hist->SetFillColor(hist->GetLineColor());
}
int EM_L1116_check(void)
{
  
  TFile* data=new TFile("./final_output.root","read");
  TFile* simul_L1520pippim=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/kombinatoryka_L1520_w_pippim.root","read");
  TFile* simul_L1520thermal=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/kombinatoryka_L1520_thermal.root","read");
  TFile* simul_LDppK0=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/kombinatoryka_LDppK0.root","read");
  TFile* simul_S1385pK0=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/kombinatoryka_S1385pK0.root","read");
  TFile* simul_SDppK0=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/kombinatoryka_SDppK0.root","read");
  
  
  TFile* output=new TFile("EM_check_output.root","recreate");
  TH1F* hL1116_original_spectrum=(TH1F*)data->Get("orginal_spectrum");
  TH1F* hL1116_EM=(TH1F*)data->Get("h_EM_for_L1116");

  //pp->L(1520) p K+
  TH1F* hL1520pippim_unfitted;
  hL1520pippim_unfitted=(TH1F*)((TCanvas*)simul_L1520pippim->Get("c1"))->GetPrimitive("");
  hL1520pippim_unfitted->SetName("hL1520pippim_unfitted");
  TH1F* hL1520pippim_sum=hL1520pippim_unfitted->Clone("hL1520pippim_sum");
  hL1520pippim_sum->Add(hL1116_EM,1);

  TCanvas* cL1520_pip_pim=new TCanvas("cL1520_pip_pim");
  hL1116_original_spectrum->Draw();
  hL1116_EM->Draw("same");
  hL1520pippim_unfitted->Draw("same");
  hL1520pippim_sum->Draw("same");
  set_sum_style(hL1520pippim_sum);
  set_fill_style(hL1520pippim_unfitted);
  //Thermal source
  TH1F* hL1520thermal_unfitted;
  hL1520thermal_unfitted=(TH1F*)((TCanvas*)simul_L1520thermal->Get("c1"))->GetPrimitive("");
  hL1520thermal_unfitted->SetName("hL1520thermal_unfitted");
  hL1520thermal_unfitted->Scale(24);
  TH1F* hL1520thermal_sum=hL1520thermal_unfitted->Clone("hL1520thermal_sum");
  hL1520thermal_sum->Add(hL1116_EM,1);

  TCanvas* cL1520_thermal=new TCanvas("cL1520_thermal");
  hL1116_original_spectrum->Draw();
  hL1116_EM->Draw("same");
  hL1520thermal_unfitted->Draw("same");
  hL1520thermal_sum->Draw("same");
  set_sum_style(hL1520thermal_sum);
  set_fill_style(hL1520thermal_unfitted);
 
  //LDppK0
  TH1F* hLDppK0_unfitted;
  hLDppK0_unfitted=(TH1F*)((TCanvas*)simul_LDppK0->Get("c1"))->GetPrimitive("");
  hLDppK0_unfitted->SetName("hLDppK0_unfitted");
  hLDppK0_unfitted->Scale(8);
  TH1F* hLDppK0_sum=hLDppK0_unfitted->Clone("hLDppK0_sum");
  hLDppK0_sum->Add(hL1116_EM,0.5);

  TCanvas* cLDppK0=new TCanvas("cLDppK0");
  hL1116_original_spectrum->Draw();
  hL1116_EM->Draw("same");
  hLDppK0_unfitted->Draw("same");
  hLDppK0_sum->Draw("same");
  set_sum_style(hLDppK0_sum);
  set_fill_style(hLDppK0_unfitted);
 
  //S1385pK0
  TH1F* hS1385pK0_unfitted;
  hS1385pK0_unfitted=(TH1F*)((TCanvas*)simul_S1385pK0->Get("c1"))->GetPrimitive("");
  hS1385pK0_unfitted->SetName("hS1385pK0_unfitted");
  hS1385pK0_unfitted->Scale(10);
  TH1F* hS1385pK0_sum=hS1385pK0_unfitted->Clone("hS1385pK0_sum");
  hS1385pK0_sum->Add(hL1116_EM,0.5);
  
  TCanvas* cS1385pK0=new TCanvas("cS1385pK0");
  hL1116_original_spectrum->Draw();
  hL1116_EM->Draw("same");
  hS1385pK0_unfitted->Draw("same");
  hS1385pK0_sum->Draw("same");
  set_sum_style(hS1385pK0_sum);
  set_fill_style(hS1385pK0_unfitted);
 
  //SDppK0
  TH1F* hSDppK0_unfitted;
  hSDppK0_unfitted=(TH1F*)((TCanvas*)simul_SDppK0->Get("c1"))->GetPrimitive("");
  hSDppK0_unfitted->SetName("hSDppK0_unfitted");
  hSDppK0_unfitted->Scale(10);
  TH1F* hSDppK0_sum=hSDppK0_unfitted->Clone("hSDppK0_sum");
  hSDppK0_sum->Add(hL1116_EM,0.5);

  TCanvas* cSDppK0=new TCanvas("cSDppK0");
  hL1116_original_spectrum->Draw();
  hL1116_EM->Draw("same");
  hSDppK0_unfitted->Draw("same");
  hSDppK0_sum->Draw("same");
  set_sum_style(hSDppK0_sum);
  set_fill_style(hSDppK0_unfitted);
 
  
  //save histograms
  hSDppK0_sum->Write();
  hSDppK0_unfitted->Write();
  hS1385pK0_sum->Write();
  hS1385pK0_unfitted->Write();
  hLDppK0_sum->Write();
  hLDppK0_unfitted->Write();
  hL1520thermal_sum->Write();
  hL1520thermal_unfitted->Write();
  hL1520pippim_sum->Write();
  hL1520pippim_unfitted->Write();
  hL1116_EM->Write();
  hL1116_original_spectrum->Write();
  //save canvases
  cL1520_pip_pim->Write();
  cL1520_thermal->Write();
  cLDppK0->Write();
  cS1385pK0->Write();
  cSDppK0->Write();
  //output->Write();
  return 0;
}
