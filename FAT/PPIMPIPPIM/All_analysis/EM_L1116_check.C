int EM_L1116_check(void)
{
  
  TFile* data=new TFile("./final_output.root","read");
  TFile* simul_L1520pippim=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/kombinatoryka_L1520_w_pippim.root","read");
  TFile* simul_L1520thermal=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/pp_after_TMVA_DD_6_n+4_pNb_newVertex_L1520_thermal.root","read");
  
  
  TFile* output=new TFile("EM_check_output.root","recreate");
  TH1F* hL1520pippim_unfitted;
  //load_histogram(simul_L1520pippim,hL1520pippim_unfitted,"hL1520pippim_unfitted");
  hL1520pippim_unfitted=(TH1F*)((TCanvas*)simul_L1520pippim->Get("c1"))->GetPrimitive("");
  hL1520pippim_unfitted->SetName("hL1520pippim_unfitted");
  
  hL1520pippim_unfitted->Print();
  hL1520pippim_unfitted->Draw();
  hL1520pippim_unfitted->Write();
  //loadhistograms from file

  //output->Write();
  return 0;
}
