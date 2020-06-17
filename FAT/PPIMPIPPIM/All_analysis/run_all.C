//#include "EventMixing.C"
#include "TMVAeval.C"
#include "createHistos.C"

#include "TFile.h"
#include "TTree.h"
#include <iostream>

using namespace std;

int run_all(void)
{
  bool experiment=1;//czy brac pod uwage pliki z eksperymentu
  bool b_TMVAeval=0;//czy uruchamiac przeliczenie sieci na nowo

  if(b_TMVAeval)
    {
      cout<<"Load all files"<<endl;
      TFile* fexperiment=new TFile("../pNb_dedex_buffer_in_FAT_new_vertex_Sigma.root","READ");
      TFile* fsim_SDppK0=new TFile("/lustre/nyx/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/../SDppK0_Rafal_part2.root","READ");
      TFile* fsim_S1385pK0=new TFile("/lustre/nyx/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/../S1385pK0_Rafal_part2.root","READ");
      TFile* fsim_LDppK0=new TFile("/lustre/nyx/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/../LDppK0_Rafal_part2.root","READ");
      TFile* fsim_L1520pippim=new TFile("/lustre/nyx/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/TMVAeval_DD/../pp_Lpippim_ver3_new_vertex.root","READ");
      TFile* fsim_LK0ppip=new TFile("/lustre/hades/user/knowakow/PP/FAT/PPIMPIPPIM_sim/pp_pK0Lpip_ver2.root","READ");
      cout<<"load trees"<<endl;
      TTree* texperiment;
      TTree* tsim_SDppK0;
      TTree* tsim_S1385pK0;
      TTree* tsim_LDppK0;
      TTree* tsim_L1520pippim;
      TTree* tsim_LK0ppip;

      fexperiment->GetObject("ppimpippim_results",texperiment);
      fexperiment->SetName("fexperiment");
      fsim_SDppK0->GetObject("ppimpippim",tsim_SDppK0);
      fsim_SDppK0->SetName("fsim_SDppK0");
      fsim_S1385pK0->GetObject("ppimpippim",tsim_S1385pK0);
      fsim_S1385pK0->SetName("fsim_S1385pK0");
      fsim_LDppK0->GetObject("ppimpippim",tsim_LDppK0);
      fsim_LDppK0->SetName("fsim_LDppK0");
      fsim_L1520pippim->GetObject("ppimpippim",tsim_L1520pippim);
      fsim_L1520pippim->SetName("fsim_L1520pippim");
      fsim_LK0ppip->GetObject("ppimpippim",tsim_LK0ppip);
      
      cout<<"Run TMVA processes"<<endl;
      //Run TMVAeval
      if(experiment)
	{
	  TMVAeval* TMexperiment=new TMVAeval(texperiment);
	  TMexperiment->Loop("TMVA_output_experiement.root");
	}
      TMVAeval* TM_sim_SDppK0=new TMVAeval(tsim_SDppK0);
      TM_sim_SDppK0->Loop("TMVA_output_sim_SDppK0.root");

      TMVAeval* TM_sim_S1385pK0=new TMVAeval(tsim_S1385pK0);
      TM_sim_S1385pK0->Loop("TMVA_output_sim_S1385pK0.root");

      TMVAeval* TM_sim_LDppK0=new TMVAeval(tsim_LDppK0);
      TM_sim_LDppK0->Loop("TMVA_output_sim_LDppK0.root");

      TMVAeval* TM_sim_L1520pippim=new TMVAeval(tsim_L1520pippim);
      TM_sim_L1520pippim->Loop("TMVA_output_sim_L1520pippim.root");

      TMVAeval* TM_sim_LK0ppim=new TMVAeval(tsim_LK0ppip);
      TM_sim_LK0ppim->Loop("TMVA_output_sim_LK0ppim.root");
      /*
      texperiment->delete();
      tsim_SDppK0->delete();
      tsim_S1385pK0->delete();
      tsim_LDppK0->delete();
      tsim_L1520pippim->delete();
      TM_sim_LK0ppim->delete();
      */
    }
  //Side-band part*************************
  
  cout<<"Load all files for s-b"<<endl;
  TFile* f_sb_experiment=new TFile("TMVA_output_experiement.root","READ");
  TFile* f_sb_sim_SDppK0=new TFile("TMVA_output_sim_SDppK0.root","READ");
  TFile* f_sb_sim_S1385pK0=new TFile("TMVA_output_sim_S1385pK0.root","READ");
  TFile* f_sb_sim_LDppK0=new TFile("TMVA_output_sim_LDppK0.root","READ");
  TFile* f_sb_sim_L1520pippim=new TFile("TMVA_output_sim_L1520pippim.root","READ");
  TFile* f_sb_sim_LK0ppip=new TFile("TMVA_output_sim_LK0ppim.root","READ");
  
  cout<<"load trees for s-b"<<endl;
  TTree* t_sb_experiment;
  TTree* t_sb_sim_SDppK0;
  TTree* t_sb_sim_S1385pK0;
  TTree* t_sb_sim_LDppK0;
  TTree* t_sb_sim_L1520pippim;
  TTree* t_sb_sim_LK0ppip;

  
  //Run createHistos
  if(experiment)
    {
      cout<<"Run making Side-Band for experiment"<<endl;
      f_sb_experiment->GetObject("TMVAeval",t_sb_experiment);
      f_sb_experiment->SetName("f_sb_experiment");
      createHistos* SB_experiment=new createHistos(t_sb_experiment);
      SB_experiment->Loop("SB_experiment.root");
      t_sb_experiment->Delete();
    }

 
  cout<<"Run making Side-Band for SDppK0"<<endl;
  f_sb_sim_SDppK0->GetObject("TMVAeval",t_sb_sim_SDppK0);
  f_sb_sim_SDppK0->SetName("f_sb_sim_SDppK0");
  createHistos* SB_sim_SDppK0=new createHistos(t_sb_sim_SDppK0);
  SB_sim_SDppK0->Loop("SB_sim_SDppK0.root");
  t_sb_sim_SDppK0->Delete();

  cout<<"Run making Side-Band for S1385"<<endl;
  f_sb_sim_S1385pK0->GetObject("TMVAeval",t_sb_sim_S1385pK0);
  f_sb_sim_S1385pK0->SetName("f_sb_sim_S1385pK0");
  createHistos* SB_sim_S1385pK0=new createHistos(t_sb_sim_S1385pK0);
  SB_sim_S1385pK0->Loop("SB_sim_S1385pK0.root");
  t_sb_sim_S1385pK0->Delete();

  cout<<"Run making Side-Band for LDppK0"<<endl;
  f_sb_sim_LDppK0->GetObject("TMVAeval",t_sb_sim_LDppK0);
  f_sb_sim_LDppK0->SetName("f_sb_sim_LDppK0");
  createHistos* SB_sim_LDppK0=new createHistos(t_sb_sim_LDppK0);
  SB_sim_LDppK0->Loop("SB_sim_LDppK0.root");
  t_sb_sim_LDppK0->Delete();

  cout<<"Run making Side-Band for L1520"<<endl;
  f_sb_sim_L1520pippim->GetObject("TMVAeval",t_sb_sim_L1520pippim);
  f_sb_sim_L1520pippim->SetName("f_sb_sim_L1520pippim");
  createHistos* SB_sim_L1520pippim=new createHistos(t_sb_sim_L1520pippim);
  SB_sim_L1520pippim->Loop("SB_sim_L1520pippim.root");
  t_sb_sim_L1520pippim->Delete();

  cout<<"Run making Side-Band for LK0ppip"<<endl;
  f_sb_sim_LK0ppip->GetObject("TMVAeval",t_sb_sim_LK0ppip);
  f_sb_sim_LK0ppip->SetName("f_sb_sim_LK0ppip");
  createHistos* SB_sim_LK0ppip=new createHistos(t_sb_sim_LK0ppip);
  SB_sim_LK0ppip->Loop("SB_sim_LK0ppip.root");
  t_sb_sim_LK0ppip->Delete();
   
   
  gROOT->ProcessLine(".x draw_norm.C");
}
