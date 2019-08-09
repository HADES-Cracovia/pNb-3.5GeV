#include "PPimPipPim.h"
#include "PPimPipPim_buffer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "data.h"
#include <iostream>
#include <TLorentzVector.h>
#include <TVector3.h>
#include "hntuple.h"


using namespace std;
using namespace PATData;

void PPimPipPim::Loop()
{
  int licznik = 0;
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntries();

  double nbytes = 0, nb = 0;

  std::vector< PPimPipPim_ID_buffer >  buffer;
  std::vector<double> the_best;
  std::vector<int> isBest_vector;
 
  int event_number=-1;
  int event_mult=-1;

  int dif_events=1;
  int real_lambdas=0;
    
  for(Long64_t jentry=0; jentry<nentries;jentry++)
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0)
	{
	  cout<<"jentry out of range!!!"<<endl;
	  break;
	}
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      cout.precision(10);
      if(jentry%1000==0 && isBest!=-1)
	{
	  cout << "netry no. "<< jentry<<" from "<<nentries;
	  //cout<<" isBest: "<< isBest<<" event: "<<event;
	  cout<<endl;
	}

      if(isBest!=-1 /*&& trigdownscaleflag==1*/)
	{
	  //initialization for first event
	  if(event_number==-1)
	    { 
	      event_number=event;
	      event_mult=1;
	    }
	  
	  //reset event multiplisity in case of a new event
	  if(event!=event_number || jentry==(nentries-1)) //every new event or end of last event
	    {
	      dif_events++;
	      double min_value=10000000;
	      int best_hipo=-1;
	      int isBest_sum=0;
	      int lambda_in_event=0;
	      //find the best hypothesis
	      for(int j=0;j<the_best.size();j++)
		{
		  //cout<<the_best[j]<<" ";
		  isBest_sum=isBest_sum+isBest_vector[j];
		  if(the_best[j]<min_value)
		    {
		      min_value=the_best[j];
		      best_hipo=j;
		    }
		}
	      //cout<<endl;
	      /*if(isBest_sum<1)
		{
		cout<<"best hipo:"<<best_hipo;
		cout<<" isBest sum ="<<isBest_sum <<"for event "<<event_number;
		cout<<endl;
		}
	      */
	      for(int k=0;k<buffer.size();k++)
		{
		  //cout<<"writing event "<< endl <<"best hipo "<<best_hipo<<endl;
		  if(k==best_hipo)
		    filler(buffer[k],event_mult,1,1);
		  else
		    filler(buffer[k],event_mult,1,0);
		}
      
	      buffer.clear();
	      the_best.clear();
	      isBest_vector.clear();

	      event_number=event;
	      event_mult=1;

	      if(lambda_in_event>0)
		real_lambdas++;

	      //cout<<"no. of real lambdas in event "<<lambda_in_event<<endl;
	      if(jentry==(nentries-1))
		cout<<"no. of real labdas is all data "<<real_lambdas<<endl;
	    }
	  else
	    {
	      event_mult++;
	    }

	  double F = 1.006;
	  //double F=1;
	  TVector3 v1, v2, v3, v4, v5;
	  v2.SetXYZ(F*p_p*sin(D2R*p_theta)*cos(D2R*p_phi),F*p_p*sin(D2R*p_theta)*sin(D2R*p_phi),F*p_p*cos(D2R*p_theta));
	  v3.SetXYZ(F*pim1_p*sin(D2R*pim1_theta)*cos(D2R*pim1_phi),F*pim1_p*sin(D2R*pim1_theta)*sin(D2R*pim1_phi),F*pim1_p*cos(D2R*pim1_theta));
	  v4.SetXYZ(F*pip_p*sin(D2R*pip_theta)*cos(D2R*pip_phi),F*pip_p*sin(D2R*pip_theta)*sin(D2R*pip_phi),F*pip_p*cos(D2R*pip_theta));
	  v5.SetXYZ(F*pim2_p*sin(D2R*pim2_theta)*cos(D2R*pim2_phi),F*pim2_p*sin(D2R*pim2_theta)*sin(D2R*pim2_phi),F*pim2_p*cos(D2R*pim2_theta));

	  p->SetVectM( v2, 938.272013 );
	  pim1->SetVectM( v3, 139.57018 );
	  pip->SetVectM( v4, 139.57018 );
	  pim2->SetVectM( v5, 139.57018 );
	  /*
	    cout<<"first part"<<endl;
	    HParticleTool p_tool;  
	    cout<<"p_phi: "<<p_phi<<endl;
	    cout<<"p_phi by 3 vector: "<<v2.Phi()*R2D<<endl;
	    cout<<"p_phi by 4 vector: "<<p->Phi()*R2D<<endl;
	    cout<<"p_phi by getLabPhiDeg: "<<p_tool.getLabPhiDeg(*p)<<endl;
	    cout<<"p_phi by phiLabToPhiSecDeg: "<<p_tool.phiLabToPhiSecDeg(v2.Phi()*R2D)<<endl;
	    cout<<"p_phi by Atan(x/y): "<<TMath::ATan(v2.Y()/v2.X())*R2D<<endl;

	    cout<<"p_theta: "<<p_theta<<endl;
	    cout<<"p_theta by 3 vector: "<<v2.Theta()*R2D<<endl;
	    cout<<"p_theta by 4 vector: "<<p->Theta()*R2D<<endl;
	    //cout<<"p_theta by getLabThetaDeg: "<<p_tool.getLabThetaDeg(*p)<<endl;
	    //cout<<"p_theta by thetaLabToThetaSecDeg: "<<p_tool.thetaLabToThetaSecDeg(v2.Theta()*R2D)<<endl;
	    //cout<<"p_theta by Atan(x/y): "<<TMath::ATan(v2.Y()/v2.X())*R2D<<endl;
	    v2.Print();
	    cout<<endl;
	  */
	  *gammappip = *p + *pip;
	  *gammappim1 = *p + *pim1;
	  *gammappim2 = *p + *pim2;
	  *gammapim1pip= *pim1 + *pip;
	  *gammapim2pip= *pim2 + *pip;
	  *gammappim1pippim2=*pim1 +*pim2 + *pip + *p;
	  *miss=*beam-*gammappim1pippim2;

	  
	  Float_t m_inv_ppim1 = gammappim1->M();
	  Float_t m_inv_ppim2 = gammappim2->M();
	  Float_t m_inv_pippim1 = gammapim1pip->M();
	  Float_t m_inv_pippim2 = gammapim2pip->M();
	  Float_t m_inv_ppimpippim = gammappim1pippim2->M();
	  Float_t oa = R2D * openingangle(*p, *pim1);
	  //Float_t oa_rich = R2D * openingangle(r1, r2);

	  Float_t p_mass = p_p*p_p * (  1. / (p_beta*p_beta)  - 1. ) ;
	  Float_t pi_mass = pim1_p*pim1_p * (  1. / (pim1_beta*pim1_beta_new)  - 1. ) ;
	  Float_t pip_mass = pip_p*pip_p * (  1. / (pip_beta*pip_beta_new)  - 1. ) ;
	  Float_t pim1_mass = pim1_p*pim1_p * (  1. / (pim1_beta*pim1_beta_new)  - 1. ) ;
	  Float_t pim2_mass = pim2_p*pim2_p * (  1. / (pim2_beta*pim2_beta_new)  - 1. ) ;

	  TVector3 ver_p_pim1=vertex(p_r,p_z,*p,pim1_r,pim1_z,*pim1);
	  TVector3 ver_p_pim2=vertex(p_r,p_z,*p,pim2_r,pim2_z,*pim2);
	  TVector3 ver_pip_pim1=vertex(pip_r,pip_z,*pip,pim1_r,pim1_z,*pim1);
	  TVector3 ver_pip_pim2=vertex(pip_r,pip_z,*pip,pim2_r,pim2_z,*pim2);

	  TVector3 ver_to_ver_1=ver_p_pim1-ver_pip_pim2;
	  TVector3 ver_to_ver_2=ver_p_pim2-ver_pip_pim1;

	  Float_t oa_pim1_p=R2D*openingangle(pim1->Vect(),p->Vect());
	  Float_t oa_pim2_p=R2D*openingangle(pim2->Vect(),p->Vect());
	  Float_t oa_pip_p=R2D*openingangle(pip->Vect(),p->Vect());
	  Float_t oa_pim1_pim2=R2D*openingangle(pim1->Vect(),pim2->Vect());
	  Float_t oa_pim1_pip=R2D*openingangle(pim1->Vect(),pip->Vect());
	  Float_t oa_pim2_pip=R2D*openingangle(pim2->Vect(),pip->Vect());
                  
	  Float_t oa_lambda_1=R2D*openingangle(ver_to_ver_1,gammappim1->Vect());
	  Float_t oa_lambda_2=R2D*openingangle(ver_to_ver_2,gammappim2->Vect());
      
	  Float_t dist_p_pim1=trackDistance(p_r,p_z,*p,pim1_r,pim1_z,*pim1);
	  Float_t dist_p_pim2=trackDistance(p_r,p_z,*p,pim2_r,pim2_z,*pim2);
	  Float_t dist_pip_pim1=trackDistance(pip_r,pip_z,*pip,pim1_r,pim1_z,*pim1);
	  Float_t dist_pip_pim2=trackDistance(pip_r,pip_z,*pip,pim2_r,pim2_z,*pim2);
	  Float_t dist_lambda1_pip=trackDistance(pip_r,pip_z,*pip,ver_p_pim1.Z(),getR(ver_p_pim1),*gammappim1);
	  Float_t dist_lambda2_pip=trackDistance(pip_r,pip_z,*pip,ver_p_pim2.Z(),getR(ver_p_pim2),*gammappim2);
	  Float_t dist_lambda1_pim2=trackDistance(pim2_r,pim2_z,*pim2,ver_p_pim1.Z(),getR(ver_p_pim1),*gammappim1);
	  Float_t dist_lambda2_pim1=trackDistance(pim1_r,pim1_z,*pim1,ver_p_pim2.Z(),getR(ver_p_pim2),*gammappim2);
	  Float_t dist_ver_to_ver_1=ver_to_ver_1.Mag();
	  Float_t dist_ver_to_ver_2=ver_to_ver_2.Mag();
      
	  //Float_t quality=trackDistance(p_r,p_z,v2,pim1_r,pim1_z,v3);
	  //Float_t quality1=dist_p_pim1*dist_p_pim1+dist_pip_pim2*dist_pip_pim2;
	  //Float_t quality2=dist_p_pim2*dist_p_pim2+dist_pip_pim1*dist_pip_pim1;
	  Float_t quality1=TMath::Power(m_inv_ppim1-1116,2)
	    //+TMath::Power(dist_p_pim1/12,2)
	    //TMath::Power(dist_lambda1_pim2,2)+TMath::Power(dist_lambda1_pip,2)
	    ;
	  Float_t quality2=TMath::Power(m_inv_ppim2-1116,2)
	    //+TMath::Power(dist_p_pim2/12,2)
	    //TMath::Power(dist_lambda2_pim1,2)+TMath::Power(dist_lambda2_pip,2)
	    ;

	  Float_t quality=std::min(quality1,quality2);
	  
	  //add hypothesis to buffer and quality measure
	  buffer.push_back( PPimPipPim_ID_buffer( this ));
	  the_best.push_back(quality);
	  isBest_vector.push_back(isBest);

	  //cout<<"p pim1 dist from main part:"<<dist_p_pim1<<endl;
	}
	  
    }
  cout<<"all different values for \"event\" "<<dif_events<<endl;
  cout<<"events with real lambda "<<real_lambdas<<endl;
}


PPimPipPim::PPimPipPim(TTree *tree)
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  /*if (tree == 0) {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("be08280235056_dst_gen1_sep08_hadron_out.root");
    if (!f || !f->IsOpen()) {
    f = new TFile("be08280235056_dst_gen1_sep08_hadron_out.root");
    }
    f->GetObject("PPimPipPim",tree);
    }
    Init(tree);*/
  if (tree == 0)
    {
      TChain * chain = new TChain("PPimPipPim_ID","");
      
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron00.root/PPimPipPim_ID");

      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron01.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron02.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron03.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron04.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron05.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron06.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron07.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron08.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron09.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron10.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron11.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron12.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron13.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron14.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron15.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron16.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron17.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron18.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron19.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron20.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron21.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron22.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron23.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron24.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron25.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron26.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron27.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron28.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron29.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron30.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron31.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron32.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron33.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron34.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron35.root/PPimPipPim_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim_downscale_dedx/FILES/full_stat_3/hadron36.root/PPimPipPim_ID");
      tree = chain;
    }

  Init(tree);
}

PPimPipPim::~PPimPipPim()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

void PPimPipPim::filler( const PPimPipPim_ID_buffer& s,int event_mult, double WEIGHT,int isBest_new)
{
  double F = 1.006;
  //double F=1;
  TVector3 v1, v2, v3, v4, v5;
  v2.SetXYZ(F*s.p_p*sin(D2R*s.p_theta)*cos(D2R*s.p_phi),F*s.p_p*sin(D2R*s.p_theta)*sin(D2R*s.p_phi),F*s.p_p*cos(D2R*s.p_theta));
  v3.SetXYZ(F*s.pim1_p*sin(D2R*s.pim1_theta)*cos(D2R*s.pim1_phi),F*s.pim1_p*sin(D2R*s.pim1_theta)*sin(D2R*s.pim1_phi),F*s.pim1_p*cos(D2R*s.pim1_theta));
  v4.SetXYZ(F*s.pip_p*sin(D2R*s.pip_theta)*cos(D2R*s.pip_phi),F*s.pip_p*sin(D2R*s.pip_theta)*sin(D2R*s.pip_phi),F*s.pip_p*cos(D2R*s.pip_theta));
  v5.SetXYZ(F*s.pim2_p*sin(D2R*s.pim2_theta)*cos(D2R*s.pim2_phi),F*s.pim2_p*sin(D2R*s.pim2_theta)*sin(D2R*s.pim2_phi),F*s.pim2_p*cos(D2R*s.pim2_theta));
  /*
    TVector3 vtemp;
    vtemp.SetXYZ(F*s.p_p*sin(D2R*90)*cos(D2R*45),F*s.p_p*sin(D2R*90)*sin(D2R*45),F*s.p_p*cos(D2R*90));
    vtemp.Print();
  */  
  /*TVector3 r1, r2, r3,r4;
    r1.SetXYZ(sin(D2R*p_theta_rich)*cos(D2R*p_phi_rich),sin(D2R*p_theta_rich)*sin(D2R*p_phi_rich),cos(D2R*p_theta_rich));
    r2.SetXYZ(sin(D2R*pim1_theta_rich)*cos(D2R*pim1_phi_rich),sin(D2R*pim1_theta_rich)*sin(D2R*pim1_phi_rich),cos(D2R*pim1_theta_rich));
    r3.SetXYZ(sin(D2R*pip_theta_rich)*cos(D2R*pip_phi_rich),sin(D2R*pip_theta_rich)*sin(D2R*pip_phi_rich),cos(D2R*pip_theta_rich));
    r4.SetXYZ(sin(D2R*pim2_theta_rich)*cos(D2R*pim2_phi_rich),sin(D2R*pim2_theta_rich)*sin(D2R*pim2_phi_rich),cos(D2R*pim2_theta_rich));
  */      
  p->SetVectM( v2, 938.272013 );
  pim1->SetVectM( v3, 139.57018 );
  pip->SetVectM( v4, 139.57018 );
  pim2->SetVectM( v5, 139.57018 );
  /*
    cout<<"save part"<<endl;
    HParticleTool p_tool;  
    cout<<"p_phi: "<<s.p_phi<<endl;
    cout<<"p_phi by 3 vector: "<<v2.Phi()*R2D<<endl;
    cout<<"p_phi by 4 vector: "<<p->Phi()*R2D<<endl;
    cout<<"p_phi by getLabPhiDeg: "<<p_tool.getLabPhiDeg(*p)<<endl;
    cout<<"p_phi by phiLabToPhiSecDeg: "<<p_tool.phiLabToPhiSecDeg(v2.Phi()*R2D)<<endl;
    cout<<"p_phi by Atan(x/y): "<<TMath::ATan(v2.Y()/v2.X())*R2D<<endl;

    cout<<"p_theta: "<<s.p_theta<<endl;
    cout<<"p_theta by 3 vector: "<<v2.Theta()*R2D<<endl;
    cout<<"p_theta by 4 vector: "<<p->Theta()*R2D<<endl;
    //cout<<"p_theta by getLabThetaDeg: "<<p_tool.getLabThetaDeg(*p)<<endl;
    //cout<<"p_theta by thetaLabToThetaSecDeg: "<<p_tool.thetaLabToThetaSecDeg(v2.Theta()*R2D)<<endl;
    //cout<<"p_theta by Atan(x/y): "<<TMath::ATan(v2.Y()/v2.X())*R2D<<endl;
    v2.Print();
    cout<<endl;
  */
  *gammappip = *p + *pip;
  *gammappim1 = *p + *pim1;
  *gammappim2 = *p + *pim2;
  *gammapim1pip= *pim1 + *pip;
  *gammapim2pip= *pim2 + *pip;
  *gammappim1pippim2=*pim1 +*pim2 + *pip + *p;
  *miss=*beam-*gammappim1pippim2;
      
  //*ppim1 = *p + *pim1;
  //*p_delta = *p;
  //*pim1_delta = *pim1;
  //*ppim1_miss = *beam - *p - *pim1;
  Float_t m_inv_ppip = gammappip->M();
  Float_t m_inv_ppim1 = gammappim1->M();
  Float_t m_inv_ppim2 = gammappim2->M();
  Float_t m_inv_pippim1 = gammapim1pip->M();
  Float_t m_inv_pippim2 = gammapim2pip->M();
  Float_t m_inv_ppimpippim = gammappim1pippim2->M();
  Float_t oa = R2D * openingangle(*p, *pim1);
  //Float_t oa_rich = R2D * openingangle(r1, r2);

  Float_t p_mass = s.p_p*s.p_p * (  1. / (s.p_beta*s.p_beta)  - 1. ) ;
  //Float_t pi_mass = s.pim1_p*s.pim1_p * (  1. / (s.pim1_beta*s.pim1_beta_new)  - 1. ) ;
  Float_t pip_mass = s.pip_p*s.pip_p * (  1. / (s.pip_beta*s.pip_beta_new)  - 1. ) ;
  Float_t pim1_mass = s.pim1_p*s.pim1_p * (  1. / (s.pim1_beta*s.pim1_beta_new)  - 1. ) ;
  Float_t pim2_mass = s.pim2_p*s.pim2_p * (  1. / (s.pim2_beta*s.pim2_beta_new)  - 1. ) ;

  TVector3 eVert(s.eVert_x,s.eVert_y,s.eVert_z);
  TVector3 ver_p_pim1=vertex(s.p_r,s.p_z,*p,s.pim1_r,s.pim1_z,*pim1);
  TVector3 ver_p_pim2=vertex(s.p_r,s.p_z,*p,s.pim2_r,s.pim2_z,*pim2);
  TVector3 ver_pip_pim1=vertex(s.pip_r,s.pip_z,*pip,s.pim1_r,s.pim1_z,*pim1);
  TVector3 ver_pip_pim2=vertex(s.pip_r,s.pip_z,*pip,s.pim2_r,s.pim2_z,*pim2);
  
  
  TVector3 ver_to_ver_1=ver_p_pim1-eVert;//ver_pip_pim2;
  TVector3 ver_to_ver_2=ver_p_pim2-eVert;//ver_pip_pim1;

  Float_t oa_pim1_p=R2D*openingangle(pim1->Vect(),p->Vect());
  Float_t oa_pim2_p=R2D*openingangle(pim2->Vect(),p->Vect());
  Float_t oa_pip_p=R2D*openingangle(pip->Vect(),p->Vect());
  Float_t oa_pim1_pim2=R2D*openingangle(pim1->Vect(),pim2->Vect());
  Float_t oa_pim1_pip=R2D*openingangle(pim1->Vect(),pip->Vect());
  Float_t oa_pim2_pip=R2D*openingangle(pim2->Vect(),pip->Vect());
                  
  Float_t oa_lambda_1=R2D*openingangle(ver_to_ver_1,gammappim1->Vect());
  Float_t oa_lambda_2=R2D*openingangle(ver_to_ver_2,gammappim2->Vect());

  /*
    cout<<"vectors to calc"<<endl;
    cout<<"p_z: "<<p_z<<endl;
    cout<<"p_r: "<<p_r<<endl;
    cout<<"v2: "; v2.Print(); cout<<endl;
  */
  
  Float_t dist_p_pim1=trackDistance(s.p_r,s.p_z,*p,s.pim1_r,s.pim1_z,*pim1);
  Float_t dist_p_pim2=trackDistance(s.p_r,s.p_z,*p,s.pim2_r,s.pim2_z,*pim2);
  Float_t dist_pip_pim1=trackDistance(s.pip_r,s.pip_z,*pip,s.pim1_r,s.pim1_z,*pim1);
  Float_t dist_pip_pim2=trackDistance(s.pip_r,s.pip_z,*pip,s.pim2_r,s.pim2_z,*pim2);
  Float_t dist_lambda1_pip=trackDistance(s.pip_r,s.pip_z,*pip,ver_p_pim1.Z(),getR(ver_p_pim1),*gammappim1);
  Float_t dist_lambda2_pip=trackDistance(s.pip_r,s.pip_z,*pip,ver_p_pim2.Z(),getR(ver_p_pim2),*gammappim2);
  Float_t dist_lambda1_pim2=trackDistance(s.pim2_r,s.pim2_z,*pim2,ver_p_pim1.Z(),getR(ver_p_pim1),*gammappim1);
  Float_t dist_lambda2_pim1=trackDistance(s.pim1_r,s.pim1_z,*pim1,ver_p_pim2.Z(),getR(ver_p_pim2),*gammappim2);
  Float_t dist_ver_to_ver_1=ver_to_ver_1.Mag();
  Float_t dist_ver_to_ver_2=ver_to_ver_2.Mag();

  Float_t dist_lambda1_eVert=trackToPoint(ver_p_pim1,gammappim1->Vect(),eVert);
  Float_t dist_lambda2_eVert=trackToPoint(ver_p_pim2,gammappim2->Vect(),eVert);;
  Float_t dist_lambda1_ver_pip_pim=trackToPoint(ver_p_pim1,gammappim1->Vect(),ver_pip_pim2);;
  Float_t dist_lambda2_ver_pip_pim=trackToPoint(ver_p_pim2,gammappim2->Vect(),ver_pip_pim1);;

  Float_t dist_p1_eVert=trackToPoint(ver_p_pim1,p->Vect(),eVert);
  Float_t dist_p2_eVert=trackToPoint(ver_p_pim2,p->Vect(),eVert);
  Float_t dist_pim1_eVert=trackToPoint(ver_p_pim1,pim1->Vect(),eVert);
  Float_t dist_pim2_eVert=trackToPoint(ver_p_pim2,pim2->Vect(),eVert);
  
  //Float_t quality1=dist_p_pim1*dist_p_pim1+dist_pip_pim2*dist_pip_pim2;
  //Float_t quality2=dist_p_pim2*dist_p_pim2+dist_pip_pim1*dist_pip_pim1;
  Float_t quality1=TMath::Power(m_inv_ppim1-1116,2)
    //+TMath::Power(dist_p_pim1/12,2)
    //TMath::Power(dist_lambda1_pim2,2)+TMath::Power(dist_lambda1_pip,2)
    ;
  Float_t quality2=TMath::Power(m_inv_ppim2-1116,2)
    //+TMath::Power(dist_p_pim2/12,2)
    //TMath::Power(dist_lambda2_pim1,2)+TMath::Power(dist_lambda2_pip,2)
    ;
  Float_t quality=std::min(quality1,quality2);
  
  int pim_no, pim_sim_id, pim_sim_parentid;
  Float_t m_inv_ppim;
  Float_t m_inv_pippim;
  Float_t dist_p_pim;
  Float_t dist_pip_pim;
  Float_t oa_lambda;
  Float_t oa_p_pim;
  Float_t dist_ver_to_ver;
  TVector3 ver_p_pim;
  TVector3 ver_pip_pim;
  Float_t dist_lambda_eVert;
  Float_t dist_lambda_ver_pip_pim;
  Float_t dist_p_eVert;
  Float_t dist_pim_eVert;
  Float_t lambda_mom_z;
  TLorentzVector lorentz_lambda1115;
  TLorentzVector lorentz_k0;
  //cout<<"p pim1 dist from filler part:"<<dist_p_pim1<<endl;
  if(quality1<quality2)
    {
      pim_no=1;
      m_inv_ppim=m_inv_ppim1;
      m_inv_pippim=m_inv_pippim2;
      dist_p_pim=dist_p_pim1;
      dist_pip_pim=dist_pip_pim2;
      oa_lambda=oa_lambda_1;
      oa_p_pim=oa_pim1_p;
      dist_ver_to_ver=dist_ver_to_ver_1;
      ver_p_pim=ver_p_pim1;
      ver_pip_pim=ver_pip_pim2;
      //pim_sim_id=s.pim1_sim_id;
      //pim_sim_parentid=s.pim1_sim_parentid;
      dist_lambda_eVert=dist_lambda1_eVert;
      dist_lambda_ver_pip_pim=dist_lambda1_ver_pip_pim;
      dist_p_eVert=dist_p1_eVert;
      dist_pim_eVert=dist_pim1_eVert;
      lambda_mom_z=gammappim1->Z();
      lorentz_lambda1115=*gammappim1;
      lorentz_k0=*gammapim2pip;

      ver_pip_pim=vertex(ver_p_pim.Pt(),ver_p_pim.Z(),lorentz_lambda1115,ver_pip_pim.Pt(),ver_pip_pim.Z(),lorentz_k0);
      TVector3 ver_to_ver=ver_p_pim-ver_pip_pim;
      dist_ver_to_ver=ver_to_ver.Mag();
      oa_lambda=R2D*openingangle(ver_to_ver,lorentz_lambda1115.Vect());
    }
  else
    {
      pim_no=2;
      m_inv_ppim=m_inv_ppim2;
      m_inv_pippim=m_inv_pippim1;
      dist_p_pim=dist_p_pim2;
      dist_pip_pim=dist_pip_pim1;
      oa_lambda=oa_lambda_2;
      oa_p_pim=oa_pim2_p;
      dist_ver_to_ver=dist_ver_to_ver_2;
      ver_p_pim=ver_p_pim2;
      ver_pip_pim=ver_pip_pim1;
      //pim_sim_id=s.pim2_sim_id;
      //pim_sim_parentid=s.pim2_sim_parentid;
      dist_lambda_eVert=dist_lambda2_eVert;
      dist_lambda_ver_pip_pim=dist_lambda2_ver_pip_pim;
      dist_p_eVert=dist_p2_eVert;
      dist_pim_eVert=dist_pim2_eVert;
      lambda_mom_z=gammappim2->Z();
      lorentz_lambda1115=*gammappim2;
      lorentz_k0=*gammapim1pip;

      ver_pip_pim=vertex(ver_p_pim.Pt(),ver_p_pim.Z(),lorentz_lambda1115,ver_pip_pim.Pt(),ver_pip_pim.Z(),lorentz_k0);
      TVector3 ver_to_ver=ver_p_pim-ver_pip_pim;
      dist_ver_to_ver=ver_to_ver.Mag();
      oa_lambda=R2D*openingangle(ver_to_ver,lorentz_lambda1115.Vect());
    }

  bool simon_cut=(oa_p_pim > 15
		  && dist_p_pim < 10
		  && dist_lambda_eVert > 50
		  && dist_p_eVert > 5
		  && dist_pim_eVert > 15
		  );

  Float_t lambda_pt=lorentz_lambda1115.Pt();
  Float_t lambda_w=lorentz_lambda1115.Rapidity();
  Float_t k0_pt=lorentz_k0.Pt();
  Float_t k0_w=lorentz_k0.Rapidity();
  
  //save all important variables
  (*tlo)["isBest"]=s.isBest;
  (*tlo)["isBest_new"]=isBest_new;
  (*tlo)["event"]=s.event;
  (*tlo)["hneg_mult"]=s.hneg_mult;
  (*tlo)["hpos_mult"]=s.hpos_mult;
  (*tlo)["eVert_x"]=s.eVert_x;
  (*tlo)["eVert_y"]=s.eVert_y;
  (*tlo)["eVert_z"]=s.eVert_z;
  (*tlo)["totalmult"]=s.totalmult;
  (*tlo)["trigdownscaleflag"]=s.trigdownscaleflag;
  (*tlo)["trigdownscale"]=s.trigdownscale;
  (*tlo)["event_mult"]=event_mult;
  (*tlo)["hypothesis"]=pim_no;
  (*tlo)["hypothesis_quality"]=quality;
  
  (*tlo)["p_p"]=s.p_p;
  (*tlo)["p_theta"] = s.p_theta;
  (*tlo)["p_phi"] = s.p_phi;
  (*tlo)["p_beta"] = s.p_beta_new;
  (*tlo)["p_m"] = p_mass;
  (*tlo)["p_dedx"]=s.p_dedx_mdc;
  (*tlo)["p_q"]=s.p_q;
	  
  //(*tlo)["p_sim_p"]=s.p_sim_p;
  //(*tlo)["p_sim_id"]=s.p_sim_id;
  //(*tlo)["p_sim_parentid"]=s.p_sim_parentid;
  //(*tlo)["p_sim_vertex_x"]=s.p_sim_vertexx;
  //(*tlo)["p_sim_vertex_y"]=s.p_sim_vertexy;
  //(*tlo)["p_sim_vertex_z"]=s.p_sim_vertexz;
	  
  (*tlo)["pip_p"]=s.pip_p;
  (*tlo)["pip_theta"] = s.pip_theta;
  (*tlo)["pip_phi"] = s.pip_phi;
  (*tlo)["pip_beta"] = s.pip_beta_new;
  (*tlo)["pip_m"] = pip_mass;
  (*tlo)["pip_dedx"]=s.pip_dedx_mdc;
  (*tlo)["pip_q"]=s.pip_q;
	  
  //(*tlo)["pip_sim_p"]=s.pip_sim_p;
  //(*tlo)["pip_sim_id"]=s.pip_sim_id;
  //(*tlo)["pip_sim_parentid"]=s.pip_sim_parentid;
  //(*tlo)["pip_sim_vertex_x"]=s.pip_sim_vertexx;
  //(*tlo)["pip_sim_vertex_y"]=s.pip_sim_vertexy;
  //(*tlo)["pip_sim_vertex_z"]=s.pip_sim_vertexz;
	  
	  
  (*tlo)["pim1_p"]=s.pim1_p;
  (*tlo)["pim1_theta"] = s.pim1_theta;
  (*tlo)["pim1_phi"] = s.pim1_phi;
  (*tlo)["pim1_beta"] = s.pim1_beta_new;
  (*tlo)["pim1_m"] = pim1_mass;
  (*tlo)["pim1_dedx"]=s.pim1_dedx_mdc;
  (*tlo)["pim1_q"]=s.pim1_q;
	  
  //(*tlo)["pim1_sim_p"]=s.pim1_sim_p;
  //(*tlo)["pim1_sim_id"]=s.pim1_sim_id;
  //(*tlo)["pim1_sim_parentid"]=s.pim1_sim_parentid;
  //(*tlo)["pim1_sim_vertex_x"]=s.pim1_sim_vertexx;
  //(*tlo)["pim1_sim_vertex_y"]=s.pim1_sim_vertexy;
  //(*tlo)["pim1_sim_vertex_z"]=s.pim1_sim_vertexz;
	  
	  
  (*tlo)["pim2_p"]=s.pim2_p;
  (*tlo)["pim2_theta"] = s.pim2_theta;
  (*tlo)["pim2_phi"] = s.pim2_phi;
  (*tlo)["pim2_beta"] = s.pim2_beta_new;
  (*tlo)["pim2_m"] = pim2_mass;
  (*tlo)["pim2_dedx"]=s.pim2_dedx_mdc;
  (*tlo)["pim2_q"]=s.pim2_q;
	  
  //(*tlo)["pim2_sim_p"]=s.pim2_sim_p;
  //(*tlo)["pim2_sim_id"]=s.pim2_sim_id;
  //(*tlo)["pim2_sim_parentid"]=s.pim2_sim_parentid;
  //(*tlo)["pim2_sim_vertex_x"]=s.pim2_sim_vertexx;
  //(*tlo)["pim2_sim_vertex_y"]=s.pim2_sim_vertexy;
  //(*tlo)["pim2_sim_vertex_z"]=s.pim2_sim_vertexz;
	  	  
  //(*tlo)["pim_sim_id"]=pim_sim_id;
  //(*tlo)["pim_sim_parentid"]=pim_sim_parentid;

  (*tlo)["dist_pip_pim1"]=dist_pip_pim1;
  (*tlo)["dist_pip_pim2"] = dist_pip_pim2;
  (*tlo)["dist_pip_pim"] = dist_pip_pim;
  (*tlo)["dist_p_pim1"] = dist_p_pim1;
  (*tlo)["dist_p_pim2"] = dist_p_pim2;
  (*tlo)["dist_p_pim"] = dist_p_pim;
  (*tlo)["dist_lambda1_pim2"] = dist_lambda1_pim2;
  (*tlo)["dist_lambda1_pip"] = dist_lambda1_pip;
  (*tlo)["dist_lambda2_pim1"] = dist_lambda2_pim1;
  (*tlo)["dist_lambda2_pip"] = dist_lambda2_pip;
  (*tlo)["dist_ver_to_ver_1"]=dist_ver_to_ver_1;
  (*tlo)["dist_ver_to_ver_2"]=dist_ver_to_ver_2;
  (*tlo)["dist_ver_to_ver"]=dist_ver_to_ver;
  (*tlo)["dist_lambda1_eVert"]=dist_lambda1_eVert;
  (*tlo)["dist_lambda1_ver_pip_pim"]=dist_lambda1_ver_pip_pim;
  (*tlo)["dist_lambda2_eVert"]=dist_lambda2_eVert;
  (*tlo)["dist_lambda2_ver_pip_pim"]=dist_lambda2_ver_pip_pim;
  (*tlo)["dist_lambda_eVert"]=dist_lambda_eVert;
  (*tlo)["dist_lambda_ver_pip_pim"]=dist_lambda_ver_pip_pim;
  (*tlo)["dist_p1_eVert"]=dist_p1_eVert;
  (*tlo)["dist_pim1_eVert"]=dist_pim1_eVert;
  (*tlo)["dist_p2_eVert"]=dist_p2_eVert;
  (*tlo)["dist_pim2_eVert"]=dist_pim2_eVert;
  (*tlo)["dist_p_eVert"]=dist_p_eVert;
  (*tlo)["dist_pim_eVert"]=dist_pim_eVert;
  
	  
  (*tlo)["m_inv_p_pim1"] = m_inv_ppim1;
  (*tlo)["m_inv_p_pim2"] = m_inv_ppim2;
  (*tlo)["m_inv_p_pim"]=m_inv_ppim;

  (*tlo)["m_inv_pip_pim1"] = m_inv_pippim1;
  (*tlo)["m_inv_pip_pim2"] = m_inv_pippim2;
  (*tlo)["m_inv_pip_pim"] = m_inv_pippim;
  (*tlo)["m_inv_p_pim_pip_pim"] = m_inv_ppimpippim;
  (*tlo)["m_inv_p_pip"] = m_inv_ppip;
  
  (*tlo)["ver_p_pim1_x"]=ver_p_pim1.X();
  (*tlo)["ver_p_pim1_y"]=ver_p_pim1.Y();
  (*tlo)["ver_p_pim1_z"]=ver_p_pim1.Z();

  (*tlo)["ver_p_pim2_x"]=ver_p_pim2.X();
  (*tlo)["ver_p_pim2_y"]=ver_p_pim2.Y();
  (*tlo)["ver_p_pim2_z"]=ver_p_pim2.Z();

  (*tlo)["ver_p_pim_x"]=ver_p_pim.X();
  (*tlo)["ver_p_pim_y"]=ver_p_pim.Y();
  (*tlo)["ver_p_pim_z"]=ver_p_pim.Z();

  
  (*tlo)["ver_pip_pim1_x"]=ver_pip_pim1.X();
  (*tlo)["ver_pip_pim1_y"]=ver_pip_pim1.Y();
  (*tlo)["ver_pip_pim1_z"]=ver_pip_pim1.Z();

  (*tlo)["ver_pip_pim2_x"]=ver_pip_pim2.X();
  (*tlo)["ver_pip_pim2_y"]=ver_pip_pim2.Y();
  (*tlo)["ver_pip_pim2_z"]=ver_pip_pim2.Z();

  (*tlo)["ver_pip_pim_x"]=ver_pip_pim.X();
  (*tlo)["ver_pip_pim_y"]=ver_pip_pim.Y();
  (*tlo)["ver_pip_pim_z"]=ver_pip_pim.Z();

  (*tlo)["oa_lambda_1"]=oa_lambda_1;
  (*tlo)["oa_lambda_2"]=oa_lambda_2;
  (*tlo)["oa_lambda"]=oa_lambda;
  (*tlo)["oa_pim1_p"]=oa_pim1_p;
  (*tlo)["oa_pim2_p"]=oa_pim2_p;
  (*tlo)["oa_pim_p"]=oa_p_pim;
  (*tlo)["oa_pip_p"]=oa_pip_p;
  (*tlo)["oa_pim1_pim2"]=oa_pim1_pim2;
  (*tlo)["oa_pim1_pip"]=oa_pim1_pip;
  (*tlo)["oa_pim2_pip"]=oa_pim2_pip;
	 
  (*tlo)["miss_mass_kp"]=miss->M();
  (*tlo)["lambda_mom_z"]=lambda_mom_z;
  (*tlo)["simon_cuts"]=simon_cut;
	 
  (*tlo)["miss_mass_kp"]=miss->M();

  (*tlo)["lambda_pt"]=lambda_pt;
  (*tlo)["lambda_w"]=lambda_w;
  (*tlo)["lambda_p"]=lorentz_lambda1115.P();
  lorentz_lambda1115.Boost(-1*(beam->Vect()));
  (*tlo)["lambda_theta"]=lorentz_lambda1115.Theta();
  
  (*tlo)["k0_pt"]=k0_pt;
  (*tlo)["k0_w"]=k0_w;
  (*tlo)["k0_p"]=lorentz_k0.P();
  lorentz_k0.Boost(-1*(beam->Vect()));
  (*tlo)["k0_theta"]=lorentz_k0.Theta();
    
  tlo->fill();
}

Int_t PPimPipPim::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t PPimPipPim::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void PPimPipPim::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);
  
  fChain->SetBranchAddress("eVert_chi2", &eVert_chi2, &b_eVert_chi2);
  fChain->SetBranchAddress("eVert_x", &eVert_x, &b_eVert_x);
  fChain->SetBranchAddress("eVert_y", &eVert_y, &b_eVert_y);
  fChain->SetBranchAddress("eVert_z", &eVert_z, &b_eVert_z);
  fChain->SetBranchAddress("event", &event, &b_event);
  fChain->SetBranchAddress("hneg_mult", &hneg_mult, &b_hneg_mult);
  fChain->SetBranchAddress("hpos_mult", &hpos_mult, &b_hpos_mult);
  fChain->SetBranchAddress("isBest", &isBest, &b_isBest);
  fChain->SetBranchAddress("lneg_mult", &lneg_mult, &b_lneg_mult);
  fChain->SetBranchAddress("lpos_mult", &lpos_mult, &b_lpos_mult);
  fChain->SetBranchAddress("p_beta", &p_beta, &b_p_beta);
  fChain->SetBranchAddress("p_beta_new", &p_beta_new, &b_p_beta_new);
  fChain->SetBranchAddress("p_dedx_in", &p_dedx_in, &b_p_dedx_in);
  fChain->SetBranchAddress("p_dedx_in_sigma", &p_dedx_in_sigma, &b_p_dedx_in_sigma);
  fChain->SetBranchAddress("p_dedx_mdc", &p_dedx_mdc, &b_p_dedx_mdc);
  fChain->SetBranchAddress("p_dedx_mdc_sigma", &p_dedx_mdc_sigma, &b_p_dedx_mdc_sigma);
  fChain->SetBranchAddress("p_dedx_out", &p_dedx_out, &b_p_dedx_out);
  fChain->SetBranchAddress("p_dedx_out_sigma", &p_dedx_out_sigma, &b_p_dedx_out_sigma);
  fChain->SetBranchAddress("p_dedx_tof", &p_dedx_tof, &b_p_dedx_tof);
  fChain->SetBranchAddress("p_id", &p_id, &b_p_id);
  fChain->SetBranchAddress("p_isring", &p_isring, &b_p_isring);
  fChain->SetBranchAddress("p_kIsLepton", &p_kIsLepton, &b_p_kIsLepton);
  fChain->SetBranchAddress("p_kIsUsed", &p_kIsUsed, &b_p_kIsUsed);
  fChain->SetBranchAddress("p_mdcchi2", &p_mdcchi2, &b_p_mdcchi2);
  fChain->SetBranchAddress("p_oa_hadr", &p_oa_hadr, &b_p_oa_hadr);
  fChain->SetBranchAddress("p_oa_lept", &p_oa_lept, &b_p_oa_lept);
  fChain->SetBranchAddress("p_p", &p_p, &b_p_p);
  fChain->SetBranchAddress("p_phi", &p_phi, &b_p_phi);
  fChain->SetBranchAddress("p_q", &p_q, &b_p_q);
  fChain->SetBranchAddress("p_r", &p_r, &b_p_r);
  fChain->SetBranchAddress("p_resolution", &p_resolution, &b_p_resolution);
  fChain->SetBranchAddress("p_rkchi2", &p_rkchi2, &b_p_rkchi2);
  fChain->SetBranchAddress("p_sector", &p_sector, &b_p_sector);
  fChain->SetBranchAddress("p_shw_sum0", &p_shw_sum0, &b_p_shw_sum0);
  fChain->SetBranchAddress("p_shw_sum1", &p_shw_sum1, &b_p_shw_sum1);
  fChain->SetBranchAddress("p_shw_sum2", &p_shw_sum2, &b_p_shw_sum2);
  /*
    fChain->SetBranchAddress("p_sim_corrflag", &p_sim_corrflag, &b_p_sim_corrflag);
    fChain->SetBranchAddress("p_sim_geninfo", &p_sim_geninfo, &b_p_sim_geninfo);
    fChain->SetBranchAddress("p_sim_geninfo1", &p_sim_geninfo1, &b_p_sim_geninfo1);
    fChain->SetBranchAddress("p_sim_geninfo2", &p_sim_geninfo2, &b_p_sim_geninfo2);
    fChain->SetBranchAddress("p_sim_genweight", &p_sim_genweight, &b_p_sim_genweight);
    fChain->SetBranchAddress("p_sim_id", &p_sim_id, &b_p_sim_id);
    fChain->SetBranchAddress("p_sim_iscommon", &p_sim_iscommon, &b_p_sim_iscommon);
    fChain->SetBranchAddress("p_sim_mediumid", &p_sim_mediumid, &b_p_sim_mediumid);
    fChain->SetBranchAddress("p_sim_p", &p_sim_p, &b_p_sim_p);
    fChain->SetBranchAddress("p_sim_parentid", &p_sim_parentid, &b_p_sim_parentid);
    fChain->SetBranchAddress("p_sim_primaryflag", &p_sim_primaryflag, &b_p_sim_primaryflag);
    fChain->SetBranchAddress("p_sim_processid", &p_sim_processid, &b_p_sim_processid);
    fChain->SetBranchAddress("p_sim_px", &p_sim_px, &b_p_sim_px);
    fChain->SetBranchAddress("p_sim_py", &p_sim_py, &b_p_sim_py);
    fChain->SetBranchAddress("p_sim_pz", &p_sim_pz, &b_p_sim_pz);
    fChain->SetBranchAddress("p_sim_vertexx", &p_sim_vertexx, &b_p_sim_vertexx);
    fChain->SetBranchAddress("p_sim_vertexy", &p_sim_vertexy, &b_p_sim_vertexy);
    fChain->SetBranchAddress("p_sim_vertexz", &p_sim_vertexz, &b_p_sim_vertexz);
  */  
  fChain->SetBranchAddress("p_system", &p_system, &b_p_system);
  fChain->SetBranchAddress("p_theta", &p_theta, &b_p_theta);
  fChain->SetBranchAddress("p_tof_exp", &p_tof_exp, &b_p_tof_exp);
  fChain->SetBranchAddress("p_tof_mom", &p_tof_mom, &b_p_tof_mom);
  fChain->SetBranchAddress("p_tof_new", &p_tof_new, &b_p_tof_new);
  fChain->SetBranchAddress("p_tofino_mult", &p_tofino_mult, &b_p_tofino_mult);
  fChain->SetBranchAddress("p_track_length", &p_track_length, &b_p_track_length);
  fChain->SetBranchAddress("p_z", &p_z, &b_p_z);
  fChain->SetBranchAddress("pim1_beta", &pim1_beta, &b_pim1_beta);
  fChain->SetBranchAddress("pim1_beta_new", &pim1_beta_new, &b_pim1_beta_new);
  fChain->SetBranchAddress("pim1_dedx_in", &pim1_dedx_in, &b_pim1_dedx_in);
  fChain->SetBranchAddress("pim1_dedx_in_sigma", &pim1_dedx_in_sigma, &b_pim1_dedx_in_sigma);
  fChain->SetBranchAddress("pim1_dedx_mdc", &pim1_dedx_mdc, &b_pim1_dedx_mdc);
  fChain->SetBranchAddress("pim1_dedx_mdc_sigma", &pim1_dedx_mdc_sigma, &b_pim1_dedx_mdc_sigma);
  fChain->SetBranchAddress("pim1_dedx_out", &pim1_dedx_out, &b_pim1_dedx_out);
  fChain->SetBranchAddress("pim1_dedx_out_sigma", &pim1_dedx_out_sigma, &b_pim1_dedx_out_sigma);
  fChain->SetBranchAddress("pim1_dedx_tof", &pim1_dedx_tof, &b_pim1_dedx_tof);
  fChain->SetBranchAddress("pim1_id", &pim1_id, &b_pim1_id);
  fChain->SetBranchAddress("pim1_isring", &pim1_isring, &b_pim1_isring);
  fChain->SetBranchAddress("pim1_kIsLepton", &pim1_kIsLepton, &b_pim1_kIsLepton);
  fChain->SetBranchAddress("pim1_kIsUsed", &pim1_kIsUsed, &b_pim1_kIsUsed);
  fChain->SetBranchAddress("pim1_mdcchi2", &pim1_mdcchi2, &b_pim1_mdcchi2);
  fChain->SetBranchAddress("pim1_oa_hadr", &pim1_oa_hadr, &b_pim1_oa_hadr);
  fChain->SetBranchAddress("pim1_oa_lept", &pim1_oa_lept, &b_pim1_oa_lept);
  fChain->SetBranchAddress("pim1_p", &pim1_p, &b_pim1_p);
  fChain->SetBranchAddress("pim1_phi", &pim1_phi, &b_pim1_phi);
  fChain->SetBranchAddress("pim1_q", &pim1_q, &b_pim1_q);
  fChain->SetBranchAddress("pim1_r", &pim1_r, &b_pim1_r);
  fChain->SetBranchAddress("pim1_resolution", &pim1_resolution, &b_pim1_resolution);
  fChain->SetBranchAddress("pim1_rkchi2", &pim1_rkchi2, &b_pim1_rkchi2);
  fChain->SetBranchAddress("pim1_sector", &pim1_sector, &b_pim1_sector);
  fChain->SetBranchAddress("pim1_shw_sum0", &pim1_shw_sum0, &b_pim1_shw_sum0);
  fChain->SetBranchAddress("pim1_shw_sum1", &pim1_shw_sum1, &b_pim1_shw_sum1);
  fChain->SetBranchAddress("pim1_shw_sum2", &pim1_shw_sum2, &b_pim1_shw_sum2);
  /*
    fChain->SetBranchAddress("pim1_sim_corrflag", &pim1_sim_corrflag, &b_pim1_sim_corrflag);
    fChain->SetBranchAddress("pim1_sim_geninfo", &pim1_sim_geninfo, &b_pim1_sim_geninfo);
    fChain->SetBranchAddress("pim1_sim_geninfo1", &pim1_sim_geninfo1, &b_pim1_sim_geninfo1);
    fChain->SetBranchAddress("pim1_sim_geninfo2", &pim1_sim_geninfo2, &b_pim1_sim_geninfo2);
    fChain->SetBranchAddress("pim1_sim_genweight", &pim1_sim_genweight, &b_pim1_sim_genweight);
    fChain->SetBranchAddress("pim1_sim_id", &pim1_sim_id, &b_pim1_sim_id);
    fChain->SetBranchAddress("pim1_sim_iscommon", &pim1_sim_iscommon, &b_pim1_sim_iscommon);
    fChain->SetBranchAddress("pim1_sim_mediumid", &pim1_sim_mediumid, &b_pim1_sim_mediumid);
    fChain->SetBranchAddress("pim1_sim_p", &pim1_sim_p, &b_pim1_sim_p);
    fChain->SetBranchAddress("pim1_sim_parentid", &pim1_sim_parentid, &b_pim1_sim_parentid);
    fChain->SetBranchAddress("pim1_sim_primaryflag", &pim1_sim_primaryflag, &b_pim1_sim_primaryflag);
    fChain->SetBranchAddress("pim1_sim_processid", &pim1_sim_processid, &b_pim1_sim_processid);
    fChain->SetBranchAddress("pim1_sim_px", &pim1_sim_px, &b_pim1_sim_px);
    fChain->SetBranchAddress("pim1_sim_py", &pim1_sim_py, &b_pim1_sim_py);
    fChain->SetBranchAddress("pim1_sim_pz", &pim1_sim_pz, &b_pim1_sim_pz);
    fChain->SetBranchAddress("pim1_sim_vertexx", &pim1_sim_vertexx, &b_pim1_sim_vertexx);
    fChain->SetBranchAddress("pim1_sim_vertexy", &pim1_sim_vertexy, &b_pim1_sim_vertexy);
    fChain->SetBranchAddress("pim1_sim_vertexz", &pim1_sim_vertexz, &b_pim1_sim_vertexz);
  */  
  fChain->SetBranchAddress("pim1_system", &pim1_system, &b_pim1_system);
  fChain->SetBranchAddress("pim1_theta", &pim1_theta, &b_pim1_theta);
  fChain->SetBranchAddress("pim1_tof_exp", &pim1_tof_exp, &b_pim1_tof_exp);
  fChain->SetBranchAddress("pim1_tof_mom", &pim1_tof_mom, &b_pim1_tof_mom);
  fChain->SetBranchAddress("pim1_tof_new", &pim1_tof_new, &b_pim1_tof_new);
  fChain->SetBranchAddress("pim1_tofino_mult", &pim1_tofino_mult, &b_pim1_tofino_mult);
  fChain->SetBranchAddress("pim1_track_length", &pim1_track_length, &b_pim1_track_length);
  fChain->SetBranchAddress("pim1_z", &pim1_z, &b_pim1_z);
  fChain->SetBranchAddress("pim2_beta", &pim2_beta, &b_pim2_beta);
  fChain->SetBranchAddress("pim2_beta_new", &pim2_beta_new, &b_pim2_beta_new);
  fChain->SetBranchAddress("pim2_dedx_in", &pim2_dedx_in, &b_pim2_dedx_in);
  fChain->SetBranchAddress("pim2_dedx_in_sigma", &pim2_dedx_in_sigma, &b_pim2_dedx_in_sigma);
  fChain->SetBranchAddress("pim2_dedx_mdc", &pim2_dedx_mdc, &b_pim2_dedx_mdc);
  fChain->SetBranchAddress("pim2_dedx_mdc_sigma", &pim2_dedx_mdc_sigma, &b_pim2_dedx_mdc_sigma);
  fChain->SetBranchAddress("pim2_dedx_out", &pim2_dedx_out, &b_pim2_dedx_out);
  fChain->SetBranchAddress("pim2_dedx_out_sigma", &pim2_dedx_out_sigma, &b_pim2_dedx_out_sigma);
  fChain->SetBranchAddress("pim2_dedx_tof", &pim2_dedx_tof, &b_pim2_dedx_tof);
  fChain->SetBranchAddress("pim2_id", &pim2_id, &b_pim2_id);
  fChain->SetBranchAddress("pim2_isring", &pim2_isring, &b_pim2_isring);
  fChain->SetBranchAddress("pim2_kIsLepton", &pim2_kIsLepton, &b_pim2_kIsLepton);
  fChain->SetBranchAddress("pim2_kIsUsed", &pim2_kIsUsed, &b_pim2_kIsUsed);
  fChain->SetBranchAddress("pim2_mdcchi2", &pim2_mdcchi2, &b_pim2_mdcchi2);
  fChain->SetBranchAddress("pim2_oa_hadr", &pim2_oa_hadr, &b_pim2_oa_hadr);
  fChain->SetBranchAddress("pim2_oa_lept", &pim2_oa_lept, &b_pim2_oa_lept);
  fChain->SetBranchAddress("pim2_p", &pim2_p, &b_pim2_p);
  fChain->SetBranchAddress("pim2_phi", &pim2_phi, &b_pim2_phi);
  fChain->SetBranchAddress("pim2_q", &pim2_q, &b_pim2_q);
  fChain->SetBranchAddress("pim2_r", &pim2_r, &b_pim2_r);
  fChain->SetBranchAddress("pim2_resolution", &pim2_resolution, &b_pim2_resolution);
  fChain->SetBranchAddress("pim2_rkchi2", &pim2_rkchi2, &b_pim2_rkchi2);
  fChain->SetBranchAddress("pim2_sector", &pim2_sector, &b_pim2_sector);
  fChain->SetBranchAddress("pim2_shw_sum0", &pim2_shw_sum0, &b_pim2_shw_sum0);
  fChain->SetBranchAddress("pim2_shw_sum1", &pim2_shw_sum1, &b_pim2_shw_sum1);
  fChain->SetBranchAddress("pim2_shw_sum2", &pim2_shw_sum2, &b_pim2_shw_sum2);
  /*
    fChain->SetBranchAddress("pim2_sim_corrflag", &pim2_sim_corrflag, &b_pim2_sim_corrflag);
    fChain->SetBranchAddress("pim2_sim_geninfo", &pim2_sim_geninfo, &b_pim2_sim_geninfo);
    fChain->SetBranchAddress("pim2_sim_geninfo1", &pim2_sim_geninfo1, &b_pim2_sim_geninfo1);
    fChain->SetBranchAddress("pim2_sim_geninfo2", &pim2_sim_geninfo2, &b_pim2_sim_geninfo2);
    fChain->SetBranchAddress("pim2_sim_genweight", &pim2_sim_genweight, &b_pim2_sim_genweight);
    fChain->SetBranchAddress("pim2_sim_id", &pim2_sim_id, &b_pim2_sim_id);
    fChain->SetBranchAddress("pim2_sim_iscommon", &pim2_sim_iscommon, &b_pim2_sim_iscommon);
    fChain->SetBranchAddress("pim2_sim_mediumid", &pim2_sim_mediumid, &b_pim2_sim_mediumid);
    fChain->SetBranchAddress("pim2_sim_p", &pim2_sim_p, &b_pim2_sim_p);
    fChain->SetBranchAddress("pim2_sim_parentid", &pim2_sim_parentid, &b_pim2_sim_parentid);
    fChain->SetBranchAddress("pim2_sim_primaryflag", &pim2_sim_primaryflag, &b_pim2_sim_primaryflag);
    fChain->SetBranchAddress("pim2_sim_processid", &pim2_sim_processid, &b_pim2_sim_processid);
    fChain->SetBranchAddress("pim2_sim_px", &pim2_sim_px, &b_pim2_sim_px);
    fChain->SetBranchAddress("pim2_sim_py", &pim2_sim_py, &b_pim2_sim_py);
    fChain->SetBranchAddress("pim2_sim_pz", &pim2_sim_pz, &b_pim2_sim_pz);
    fChain->SetBranchAddress("pim2_sim_vertexx", &pim2_sim_vertexx, &b_pim2_sim_vertexx);
    fChain->SetBranchAddress("pim2_sim_vertexy", &pim2_sim_vertexy, &b_pim2_sim_vertexy);
    fChain->SetBranchAddress("pim2_sim_vertexz", &pim2_sim_vertexz, &b_pim2_sim_vertexz);
  */  
  fChain->SetBranchAddress("pim2_system", &pim2_system, &b_pim2_system);
  fChain->SetBranchAddress("pim2_theta", &pim2_theta, &b_pim2_theta);
  fChain->SetBranchAddress("pim2_tof_exp", &pim2_tof_exp, &b_pim2_tof_exp);
  fChain->SetBranchAddress("pim2_tof_mom", &pim2_tof_mom, &b_pim2_tof_mom);
  fChain->SetBranchAddress("pim2_tof_new", &pim2_tof_new, &b_pim2_tof_new);
  fChain->SetBranchAddress("pim2_tofino_mult", &pim2_tofino_mult, &b_pim2_tofino_mult);
  fChain->SetBranchAddress("pim2_track_length", &pim2_track_length, &b_pim2_track_length);
  fChain->SetBranchAddress("pim2_z", &pim2_z, &b_pim2_z);
  fChain->SetBranchAddress("pip_beta", &pip_beta, &b_pip_beta);
  fChain->SetBranchAddress("pip_beta_new", &pip_beta_new, &b_pip_beta_new);
  fChain->SetBranchAddress("pip_dedx_in", &pip_dedx_in, &b_pip_dedx_in);
  fChain->SetBranchAddress("pip_dedx_in_sigma", &pip_dedx_in_sigma, &b_pip_dedx_in_sigma);
  fChain->SetBranchAddress("pip_dedx_mdc", &pip_dedx_mdc, &b_pip_dedx_mdc);
  fChain->SetBranchAddress("pip_dedx_mdc_sigma", &pip_dedx_mdc_sigma, &b_pip_dedx_mdc_sigma);
  fChain->SetBranchAddress("pip_dedx_out", &pip_dedx_out, &b_pip_dedx_out);
  fChain->SetBranchAddress("pip_dedx_out_sigma", &pip_dedx_out_sigma, &b_pip_dedx_out_sigma);
  fChain->SetBranchAddress("pip_dedx_tof", &pip_dedx_tof, &b_pip_dedx_tof);
  fChain->SetBranchAddress("pip_id", &pip_id, &b_pip_id);
  fChain->SetBranchAddress("pip_isring", &pip_isring, &b_pip_isring);
  fChain->SetBranchAddress("pip_kIsLepton", &pip_kIsLepton, &b_pip_kIsLepton);
  fChain->SetBranchAddress("pip_kIsUsed", &pip_kIsUsed, &b_pip_kIsUsed);
  fChain->SetBranchAddress("pip_mdcchi2", &pip_mdcchi2, &b_pip_mdcchi2);
  fChain->SetBranchAddress("pip_oa_hadr", &pip_oa_hadr, &b_pip_oa_hadr);
  fChain->SetBranchAddress("pip_oa_lept", &pip_oa_lept, &b_pip_oa_lept);
  fChain->SetBranchAddress("pip_p", &pip_p, &b_pip_p);
  fChain->SetBranchAddress("pip_phi", &pip_phi, &b_pip_phi);
  fChain->SetBranchAddress("pip_q", &pip_q, &b_pip_q);
  fChain->SetBranchAddress("pip_r", &pip_r, &b_pip_r);
  fChain->SetBranchAddress("pip_resolution", &pip_resolution, &b_pip_resolution);
  fChain->SetBranchAddress("pip_rkchi2", &pip_rkchi2, &b_pip_rkchi2);
  fChain->SetBranchAddress("pip_sector", &pip_sector, &b_pip_sector);
  fChain->SetBranchAddress("pip_shw_sum0", &pip_shw_sum0, &b_pip_shw_sum0);
  fChain->SetBranchAddress("pip_shw_sum1", &pip_shw_sum1, &b_pip_shw_sum1);
  fChain->SetBranchAddress("pip_shw_sum2", &pip_shw_sum2, &b_pip_shw_sum2);
  /*
    fChain->SetBranchAddress("pip_sim_corrflag", &pip_sim_corrflag, &b_pip_sim_corrflag);
    fChain->SetBranchAddress("pip_sim_geninfo", &pip_sim_geninfo, &b_pip_sim_geninfo);
    fChain->SetBranchAddress("pip_sim_geninfo1", &pip_sim_geninfo1, &b_pip_sim_geninfo1);
    fChain->SetBranchAddress("pip_sim_geninfo2", &pip_sim_geninfo2, &b_pip_sim_geninfo2);
    fChain->SetBranchAddress("pip_sim_genweight", &pip_sim_genweight, &b_pip_sim_genweight);
    fChain->SetBranchAddress("pip_sim_id", &pip_sim_id, &b_pip_sim_id);
    fChain->SetBranchAddress("pip_sim_iscommon", &pip_sim_iscommon, &b_pip_sim_iscommon);
    fChain->SetBranchAddress("pip_sim_mediumid", &pip_sim_mediumid, &b_pip_sim_mediumid);
    fChain->SetBranchAddress("pip_sim_p", &pip_sim_p, &b_pip_sim_p);
    fChain->SetBranchAddress("pip_sim_parentid", &pip_sim_parentid, &b_pip_sim_parentid);
    fChain->SetBranchAddress("pip_sim_primaryflag", &pip_sim_primaryflag, &b_pip_sim_primaryflag);
    fChain->SetBranchAddress("pip_sim_processid", &pip_sim_processid, &b_pip_sim_processid);
    fChain->SetBranchAddress("pip_sim_px", &pip_sim_px, &b_pip_sim_px);
    fChain->SetBranchAddress("pip_sim_py", &pip_sim_py, &b_pip_sim_py);
    fChain->SetBranchAddress("pip_sim_pz", &pip_sim_pz, &b_pip_sim_pz);
    fChain->SetBranchAddress("pip_sim_vertexx", &pip_sim_vertexx, &b_pip_sim_vertexx);
    fChain->SetBranchAddress("pip_sim_vertexy", &pip_sim_vertexy, &b_pip_sim_vertexy);
    fChain->SetBranchAddress("pip_sim_vertexz", &pip_sim_vertexz, &b_pip_sim_vertexz);
  */  
  fChain->SetBranchAddress("pip_system", &pip_system, &b_pip_system);
  fChain->SetBranchAddress("pip_theta", &pip_theta, &b_pip_theta);
  fChain->SetBranchAddress("pip_tof_exp", &pip_tof_exp, &b_pip_tof_exp);
  fChain->SetBranchAddress("pip_tof_mom", &pip_tof_mom, &b_pip_tof_mom);
  fChain->SetBranchAddress("pip_tof_new", &pip_tof_new, &b_pip_tof_new);
  fChain->SetBranchAddress("pip_tofino_mult", &pip_tofino_mult, &b_pip_tofino_mult);
  fChain->SetBranchAddress("pip_track_length", &pip_track_length, &b_pip_track_length);
  fChain->SetBranchAddress("pip_z", &pip_z, &b_pip_z);
  fChain->SetBranchAddress("runnumber", &runnumber, &b_runnumber);
  fChain->SetBranchAddress("totalmult", &totalmult, &b_totalmult);
  fChain->SetBranchAddress("trigbit", &trigbit, &b_trigbit);
  fChain->SetBranchAddress("trigdec", &trigdec, &b_trigdec);
  fChain->SetBranchAddress("trigdownscale", &trigdownscale, &b_trigdownscale);
  fChain->SetBranchAddress("trigdownscaleflag", &trigdownscaleflag, &b_trigdownscaleflag);
  Notify();
}

Bool_t PPimPipPim::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void PPimPipPim::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t PPimPipPim::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
