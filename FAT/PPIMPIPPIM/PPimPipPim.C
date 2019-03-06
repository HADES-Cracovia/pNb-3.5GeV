#include "PPimPipPim.h"
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

  int nentries = fChain->GetEntriesFast();

  double nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      ++licznik;
      if ((licznik % 100000)==0) cout << "Events: " << licznik << " "<<(1.0*licznik)/(1.0*nentries)*100<<" %"<< endl;


      double F = 1.006;
      TVector3 v1, v2, v3, v4, v5;
      v2.SetXYZ(F*p_p*sin(D2R*p_theta)*cos(D2R*p_phi),F*p_p*sin(D2R*p_theta)*sin(D2R*p_phi),F*p_p*cos(D2R*p_theta));
      v3.SetXYZ(F*pim1_p*sin(D2R*pim1_theta)*cos(D2R*pim1_phi),F*pim1_p*sin(D2R*pim1_theta)*sin(D2R*pim1_phi),F*pim1_p*cos(D2R*pim1_theta));
      v4.SetXYZ(F*pip_p*sin(D2R*pip_theta)*cos(D2R*pip_phi),F*pip_p*sin(D2R*pip_theta)*sin(D2R*pip_phi),F*pip_p*cos(D2R*pip_theta));
      v5.SetXYZ(F*pim2_p*sin(D2R*pim2_theta)*cos(D2R*pim2_phi),F*pim2_p*sin(D2R*pim2_theta)*sin(D2R*pim2_phi),F*pim2_p*cos(D2R*pim2_theta));

      TVector3 r1, r2, r3,r4;
      r1.SetXYZ(sin(D2R*p_theta_rich)*cos(D2R*p_phi_rich),sin(D2R*p_theta_rich)*sin(D2R*p_phi_rich),cos(D2R*p_theta_rich));
      r2.SetXYZ(sin(D2R*pim1_theta_rich)*cos(D2R*pim1_phi_rich),sin(D2R*pim1_theta_rich)*sin(D2R*pim1_phi_rich),cos(D2R*pim1_theta_rich));
      r3.SetXYZ(sin(D2R*pip_theta_rich)*cos(D2R*pip_phi_rich),sin(D2R*pip_theta_rich)*sin(D2R*pip_phi_rich),cos(D2R*pip_theta_rich));
      r4.SetXYZ(sin(D2R*pim2_theta_rich)*cos(D2R*pim2_phi_rich),sin(D2R*pim2_theta_rich)*sin(D2R*pim2_phi_rich),cos(D2R*pim2_theta_rich));
      p->SetVectM( v2, 938.272013 );
      pim1->SetVectM( v3, 139.57018 );
      pip->SetVectM( v4, 139.57018 );
      pim2->SetVectM( v5, 139.57018 );

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

      double m_inv_ppim1 = gammappim1->M();
      double m_inv_ppim2 = gammappim2->M();
      double m_inv_pippim1 = gammapim1pip->M();
      double m_inv_pippim2 = gammapim2pip->M();
      double m_inv_ppimpippim = gammappim1pippim2->M();
      double oa = R2D * openingangle(*p, *pim1);
      double oa_rich = R2D * openingangle(r1, r2);

      double p_mass = p_p*p_p * (  1. / (p_beta*p_beta)  - 1. ) ;
      double pi_mass = pim1_p*pim1_p * (  1. / (pim1_beta*pim1_beta_new)  - 1. ) ;
      double pip_mass = pim1_p*pim1_p * (  1. / (pim1_beta*pim1_beta_new)  - 1. ) ;
      double pim1_mass = pim1_p*pim1_p * (  1. / (pim1_beta*pim1_beta_new)  - 1. ) ;
      double pim2_mass = pim2_p*pim2_p * (  1. / (pim2_beta*pim2_beta_new)  - 1. ) ;

      TVector3 ver_p_pim1=vertex(p_r,p_z,v2,pim1_r,pim1_z,v3);
      TVector3 ver_p_pim2=vertex(p_r,p_z,v2,pim2_r,pim2_z,v5);
      TVector3 ver_pip_pim1=vertex(pip_r,pip_z,v4,pim1_r,pim1_z,v3);
      TVector3 ver_pip_pim2=vertex(pip_r,pip_z,v4,pim2_r,pim2_z,v5);

      TVector3 ver_to_ver_1=ver_p_pim1-ver_pip_pim2;
      TVector3 ver_to_ver_2=ver_p_pim2-ver_pip_pim1;

      double oa_pim1_p=R2D*openingangle(pim1->Vect(),p->Vect());
      double oa_pim2_p=R2D*openingangle(pim2->Vect(),p->Vect());
      double oa_pip_p=R2D*openingangle(pip->Vect(),p->Vect());
      double oa_pim1_pim2=R2D*openingangle(pim1->Vect(),pim2->Vect());
      double oa_pim1_pip=R2D*openingangle(pim1->Vect(),pip->Vect());
      double oa_pim2_pip=R2D*openingangle(pim2->Vect(),pip->Vect());
                  
      double oa_lambda_1=R2D*openingangle(ver_to_ver_1,gammappim1->Vect());
      double oa_lambda_2=R2D*openingangle(ver_to_ver_2,gammappim2->Vect());
      
      double dist_p_pim1=trackDistance(p_r,p_z,v2,pim1_r,pim1_z,v3);
      double dist_p_pim2=trackDistance(p_r,p_z,v2,pim2_r,pim2_z,v5);
      double dist_pip_pim1=trackDistance(pip_r,pip_z,v4,pim1_r,pim1_z,v3);
      double dist_pip_pim2=trackDistance(pip_r,pip_z,v4,pim2_r,pim2_z,v5);
      double dist_lambda1_pip=trackDistance(pip_r,pip_z,v4,ver_pip_pim1.Z(),getR(ver_pip_pim1),gammappim1->Vect());
      double dist_lambda2_pip=trackDistance(pip_r,pip_z,v4,ver_pip_pim2.Z(),getR(ver_pip_pim2),gammappim2->Vect());
      double dist_lambda1_pim2=trackDistance(pim2_r,pim2_z,v5,ver_pip_pim1.Z(),getR(ver_pip_pim1),gammappim1->Vect());
      double dist_lambda2_pim1=trackDistance(pim1_r,pim1_z,v3,ver_pip_pim2.Z(),getR(ver_pip_pim2),gammappim2->Vect());
      double dist_ver_to_ver_1=ver_to_ver_1.Mag();
      double dist_ver_to_ver_2=ver_to_ver_2.Mag();
      

      //  cout << "opening angle = " << oa << endl;

      ACC = 1.;
      EFF = 1.;

      /*
	gammappi->Boost(0., 0., -(beam->Beta()));
	p_delta->Boost(0., 0., -(beam->Beta()));
	pi_delta->Boost(0., 0., -(beam->Beta()));
	p_delta->Boost( -gammappi->Px()/gammappi->E(), -gammappi->Py()/gammappi->E(), -gammappi->Pz()/gammappi->E());
	pi_delta->Boost( -gammappi->Px()/gammappi->E(), -gammappi->Py()/gammappi->E(), -gammappi->Pz()/gammappi->E());
      */
      //cout << "Poczatek obliczen..." << endl;

      //double ang_cut = 0.;
      //double ang_cut = 9.;

      //double close_cut = 9.;
      //double nonfit_close_cut = -4.;
      //double close_cut = 0.;
      //double nonfit_close_cut = 0.;
      //double close_cut = 4.;


#ifdef FLANCH
      //insidePim1S0 = (pPim1S0 == 0) ? 0 : pPim1S0->IsInside(pim1_z,pim1_theta);
      //insidePim1S1 = (pPim1S1 == 0) ? 0 : pPim1S1->IsInside(pim1_z,pim1_theta);
      //insideEpS0 = (pPS0 == 0) ? 0 : pPS0->IsInside(p_z,p_theta);
      //insidePS1 = (pPS1 == 0) ? 0 : pPS1->IsInside(p_z,p_theta);
      //insidePim1S0 = (pPim1S0 == 0) ? 0 : pPim1S0->IsInside(eVert_z,pim1_theta);
      //insidePim1S1 = (pPim1S1 == 0) ? 0 : pPim1S1->IsInside(eVert_z,pim1_theta);
      //insidePS0 = (pPS0 == 0) ? 0 : pPS0->IsInside(eVert_z,p_theta);
      //insideEpS1 = (pPS1 == 0) ? 0 : pPS1->IsInside(eVert_z,p_theta);
#endif

      insideTarget = 1;

#ifdef RECTANG
      //insidePim1S0 = (pim1_theta > 50 && pim1_z < -50 /* && pim1_p<200.*/) ? 1 : 0;
      //insidePim1S1 = (pim1_theta > 50 && pim1_z < -50 /* && pim1_p<200.*/) ? 1 : 0;
      //insidePS0 = (p_theta > 50 && p_z < -50 /* && p_p<200.*/) ? 1 : 0;
      //insidePS1 = (p_theta > 50 && p_z < -50 /* && p_p<200.*/) ? 1 : 0;
#endif

      //#ifdef NOCUT
      //insidePim1S0 = 0;
      //insidePim1S1 = 0;
      //insidePS0 = 0;
      //insidePS1 = 0;
      //#endif


      //NoLeptonP = !((p_oa_lept< close_cut&&p_oa_lept>0.0) &&p_oa_lept>nonfit_close_cut );
      //NoHadronP = !(p_oa_hadr< close_cut &&p_oa_hadr>nonfit_close_cut );
      //NoLeptonPI = !((pim1_oa_lept< close_cut&&pim1_oa_lept>0.0) &&pim1_oa_lept>nonfit_close_cut );
      //NoHadronPI = !(pim1_oa_hadr< close_cut &&pim1_oa_hadr>nonfit_close_cut );
      //NoHadronP = 1;
      //NoHadronPI = 1;

      /*
	NoLeptonP = 1;
	NoHadronP = 1;
	NoLeptonPI = 1;
	NoHadronPI = 1;
      */
      double chi_max=180;
      double sum1=dist_p_pim1*dist_p_pim1+dist_pip_pim2*dist_pip_pim2+dist_lambda1_pip*dist_lambda1_pip+dist_lambda1_pim2*dist_lambda1_pim2;
      double sum2=dist_p_pim2*dist_p_pim2+dist_pip_pim1*dist_pip_pim1+dist_lambda2_pip*dist_lambda2_pip+dist_lambda2_pim1*dist_lambda2_pim1;

      double sum1_1=dist_p_pim1+dist_pip_pim2+dist_lambda1_pip+dist_lambda1_pim2;
      double sum2_1=dist_p_pim2+dist_pip_pim1+dist_lambda2_pip+dist_lambda2_pim1;


      if(isBest>=0 && trigdownscaleflag==1)
	{
	  (*tlo)["isBest"]=isBest;
	  (*tlo)["event"]=event;
	  (*tlo)["hneg_mult"]=hneg_mult;
	  (*tlo)["hpos_mult"]=hpos_mult;
	  (*tlo)["eVert_x"]=eVert_x;
	  (*tlo)["eVert_y"]=eVert_y;
	  (*tlo)["eVert_z"]=eVert_z;
	  (*tlo)["totalmult"]=totalmult;
	  (*tlo)["trigdownscaleflag"]=trigdownscaleflag;
	  (*tlo)["trigdownscale"]=trigdownscale;
	  
	  (*tlo)["p_p"]=p_p;
	  (*tlo)["p_theta"] = p_theta;
	  (*tlo)["p_theta_rich"] = p_theta_rich;
	  (*tlo)["p_phi"] = p_phi;
	  (*tlo)["p_phi_rich"] = p_phi_rich;
	  (*tlo)["p_beta"] = p_beta_new;
	  (*tlo)["p_m"] = p_mass;
	  (*tlo)["p_dedx"]=p_dedx_mdc;
	  
	  (*tlo)["pip_p"]=pip_p;
	  (*tlo)["pip_theta"] = pip_theta;
	  (*tlo)["pip_theta_rich"] = pip_theta_rich;
	  (*tlo)["pip_phi"] = pip_phi;
	  (*tlo)["pip_phi_rich"] = pip_phi_rich;
	  (*tlo)["pip_beta"] = pip_beta_new;
	  (*tlo)["pip_m"] = pip_mass;
	  (*tlo)["pip_dedx"]=pip_dedx_mdc;

	  (*tlo)["pim1_p"]=pim1_p;
	  (*tlo)["pim1_theta"] = pim1_theta;
	  (*tlo)["pim1_theta_rich"] = pim1_theta_rich;
	  (*tlo)["pim1_phi"] = pim1_phi;
	  (*tlo)["pim1_phi_rich"] = pim1_phi_rich;
	  (*tlo)["pim1_beta"] = pim1_beta_new;
	  (*tlo)["pim1_m"] = pim1_mass;
	  (*tlo)["pim1_dedx"]=pim1_dedx_mdc;
	  
	  (*tlo)["pim2_p"]=pim2_p;
	  (*tlo)["pim2_theta"] = pim2_theta;
	  (*tlo)["pim2_theta_rich"] = pim2_theta_rich;
	  (*tlo)["pim2_phi"] = pim2_phi;
	  (*tlo)["pim2_phi_rich"] = pim2_phi_rich;
	  (*tlo)["pim2_beta"] = pim2_beta_new;
	  (*tlo)["pim2_m"] = pim2_mass;
	  (*tlo)["pim2_dedx"]=pim2_dedx_mdc;
	  
	  (*tlo)["dist_pip_pim1"]=dist_pip_pim1;
	  (*tlo)["dist_pip_pim2"] = dist_pip_pim2;
	  (*tlo)["dist_p_pim1"] = dist_p_pim1;
	  (*tlo)["dist_p_pim2"] = dist_p_pim2;
	  (*tlo)["dist_lambda1_pim2"] = dist_lambda1_pim2;
	  (*tlo)["dist_lambda1_pip"] = dist_lambda1_pip;
	  (*tlo)["dist_lambda2_pim1"] = dist_lambda2_pim1;
	  (*tlo)["dist_lambda2_pip"] = dist_lambda2_pip;
	  (*tlo)["dist_ver_to_ver_1"]=dist_ver_to_ver_1;
	  (*tlo)["dist_ver_to_ver_2"]=dist_ver_to_ver_2;
	  
	  (*tlo)["m_inv_p_pim1"] = m_inv_ppim1;
	  (*tlo)["m_inv_p_pim2"] = m_inv_ppim2;
	  (*tlo)["m_inv_pip_pim1"] = m_inv_pippim1;
	  (*tlo)["m_inv_pip_pim2"] = m_inv_pippim2;
	  (*tlo)["m_inv_p_pim_pip_pim"] = m_inv_ppimpippim;

	  (*tlo)["ver_p_pim1_x"]=ver_p_pim1.X();
	  (*tlo)["ver_p_pim1_y"]=ver_p_pim1.Y();
	  (*tlo)["ver_p_pim1_z"]=ver_p_pim1.Z();

	  (*tlo)["ver_p_pim2_x"]=ver_p_pim2.X();
	  (*tlo)["ver_p_pim2_y"]=ver_p_pim2.Y();
	  (*tlo)["ver_p_pim2_z"]=ver_p_pim2.Z();

	  (*tlo)["ver_pip_pim1_x"]=ver_pip_pim1.X();
	  (*tlo)["ver_pip_pim1_y"]=ver_pip_pim1.Y();
	  (*tlo)["ver_pip_pim1_z"]=ver_pip_pim1.Z();

	  (*tlo)["ver_pip_pim2_x"]=ver_pip_pim2.X();
	  (*tlo)["ver_pip_pim2_y"]=ver_pip_pim2.Y();
	  (*tlo)["ver_pip_pim2_z"]=ver_pip_pim2.Z();

	  (*tlo)["sum_dist_1"]=sum1_1;
	  (*tlo)["sum_dist_2"]=sum2_1;
	  
	  (*tlo)["sum_dist2_1"]=sum1;
	  (*tlo)["sum_dist2_2"]=sum2;

	  (*tlo)["oa_lambda_1"]=oa_lambda_1;
	  (*tlo)["oa_lambda_2"]=oa_lambda_2;
	  (*tlo)["oa_pim1_p"]=oa_pim1_p;
	  (*tlo)["oa_pim2_p"]=oa_pim2_p;
	  (*tlo)["oa_pip_p"]=oa_pip_p;
	  (*tlo)["oa_pim1_pim2"]=oa_pim1_pim2;
	  (*tlo)["oa_pim1_pip"]=oa_pim1_pip;
	  (*tlo)["oa_pim2_pip"]=oa_pim2_pip;
	 
	  (*tlo)["miss_mass_kp"]=miss->M();
	  	  
	  tlo->fill();
	  /*	  
	  p_p_beta->Fill(p_p,p_beta_new);
	  pim_p_beta->Fill(pim1_p,pim1_beta_new);
	  pim_p_beta->Fill(pim1_p,pim1_beta_new);
	  pip_p_beta->Fill(pip_p,pip_beta_new);

	  p_pim_mass->Fill(m_inv_ppim1);
	  p_pim_mass->Fill(m_inv_ppim2);
	  p_pim1_mass->Fill(m_inv_ppim1);
	  p_pim2_mass->Fill(m_inv_ppim2);

	  pim_pip_mass->Fill(m_inv_pippim2);
	  pim_pip_mass->Fill(m_inv_pippim1);
	  pim2_pip_mass->Fill(m_inv_pippim2);
	  pim1_pip_mass->Fill(m_inv_pippim1);

	  p_pim_pip_pim_mass->Fill(m_inv_ppimpippim);

	  dist_p_pim_pim_pip->Fill(dist_p_pim1,dist_pip_pim1);
	  dist_p_pim_pim_pip->Fill(dist_p_pim2,dist_pip_pim2);
	  dist_p_pim->Fill(dist_p_pim2);
	  dist_p_pim->Fill(dist_p_pim1);
	  dist_pim_pip->Fill(dist_pip_pim2);
	  dist_pim_pip->Fill(dist_pip_pim1);
	  */

	  /*
	  double sum1=dist_p_pim1*dist_p_pim1+dist_pip_pim2*dist_pip_pim2+dist_lambda1_pip*dist_lambda1_pip+dist_lambda1_pim2*dist_lambda1_pim2;
	  double sum2=dist_p_pim2*dist_p_pim2+dist_pip_pim1*dist_pip_pim1+dist_lambda2_pip*dist_lambda2_pip+dist_lambda2_pim1*dist_lambda2_pim1;

	  sum_dist_1->Fill(sum1);
	  sum_dist_2->Fill(sum2);
	  if(sum1<chi_max || sum2<chi_max)
	    sum_dist_diff->Fill(TMath::Abs(sum1-sum2));

	  if(chi_max>sum1)
	    {
	      chi_p_pim_mass->Fill(m_inv_ppim1);
	      chi_pip_pim_mass->Fill(m_inv_pippim2);
	      chi_lambda_vertex->Fill(ver_p_pim1.Z(),getR(ver_p_pim1));
	      chi_final_mass->Fill(m_inv_ppimpippim);

	      if(m_inv_ppim1<1120 && m_inv_ppim1>1110 && m_inv_pippim2<460)
		{
		  LM_chi_p_pim_mass->Fill(m_inv_ppim1);
		  LM_chi_pip_pim_mass->Fill(m_inv_pippim2);
		  LM_chi_lambda_vertex->Fill(ver_p_pim1.Z(),getR(ver_p_pim1));
		  LM_chi_final_mass->Fill(m_inv_ppimpippim);
		}
	    }

	  if(sum2<chi_max)
	    {
	      chi_p_pim_mass->Fill(m_inv_ppim2);
	      chi_pip_pim_mass->Fill(m_inv_pippim1);
	      chi_lambda_vertex->Fill(ver_p_pim2.Z(),getR(ver_p_pim2));
	      chi_final_mass->Fill(m_inv_ppimpippim);

	      if(m_inv_ppim2<1120 && m_inv_ppim2>1110 && m_inv_pippim1<460)
		{
		  LM_chi_p_pim_mass->Fill(m_inv_ppim2);
		  LM_chi_pip_pim_mass->Fill(m_inv_pippim1);
		  LM_chi_lambda_vertex->Fill(ver_p_pim2.Z(),getR(ver_p_pim2));
		  LM_chi_final_mass->Fill(m_inv_ppimpippim);
		}
	    }
	  //optimalization part
	  double dist1=(ver_p_pim1-ver_pip_pim2).Mag();
	  double dist2=(ver_p_pim2-ver_pip_pim1).Mag();

	  for(int i=0;i<10;i++)
	    for(int j=0;j<10;j++)
	      {
		if(sum1<250+50*i && dist1>j*2)
		  if(m_inv_ppim1<1120 && m_inv_ppim1>1110)
		    signal_fit[i][j]->Fill(m_inv_ppimpippim);

		if(sum2<250+50*i  && dist2>j*2)
		  if(m_inv_ppim2<1120 && m_inv_ppim2>1110)
		    signal_fit[i][j]->Fill(m_inv_ppimpippim);
	      }
	  //end of opt part
	  */	
	}
	  
    }
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
  if (tree == 0) {

    TChain * chain = new TChain("PPimPipPim_ID","");
    //chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/day280/hadron.root/PPimPipPim_ID");
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
  

  fChain->SetBranchAddress("isBest", &isBest, &b_isBest);
  fChain->SetBranchAddress("eVertClust_chi2", &eVertClust_chi2, &b_eVertClust_chi2);
  fChain->SetBranchAddress("eVertClust_x", &eVertClust_x, &b_eVertClust_x);
  fChain->SetBranchAddress("eVertClust_y", &eVertClust_y, &b_eVertClust_y);
  fChain->SetBranchAddress("eVertClust_z", &eVertClust_z, &b_eVertClust_z);
  fChain->SetBranchAddress("eVertReco_chi2", &eVertReco_chi2, &b_eVertReco_chi2);
  fChain->SetBranchAddress("eVertReco_x", &eVertReco_x, &b_eVertReco_x);
  fChain->SetBranchAddress("eVertReco_y", &eVertReco_y, &b_eVertReco_y);
  fChain->SetBranchAddress("eVertReco_z", &eVertReco_z, &b_eVertReco_z);
  fChain->SetBranchAddress("eVert_chi2", &eVert_chi2, &b_eVert_chi2);
  fChain->SetBranchAddress("eVert_x", &eVert_x, &b_eVert_x);
  fChain->SetBranchAddress("eVert_y", &eVert_y, &b_eVert_y);
  fChain->SetBranchAddress("eVert_z", &eVert_z, &b_eVert_z);
  fChain->SetBranchAddress("event", &event, &b_event);
  fChain->SetBranchAddress("hneg_mult", &hneg_mult, &b_hneg_mult);
  fChain->SetBranchAddress("hpos_mult", &hpos_mult, &b_hpos_mult);
  fChain->SetBranchAddress("p_beta", &p_beta, &b_p_beta);
  fChain->SetBranchAddress("p_beta_new", &p_beta_new, &b_p_beta_new);
  fChain->SetBranchAddress("p_btChargeRing", &p_btChargeRing, &b_p_btChargeRing);
  fChain->SetBranchAddress("p_btChargeSum", &p_btChargeSum, &b_p_btChargeSum);
  fChain->SetBranchAddress("p_btChi2", &p_btChi2, &b_p_btChi2);
  fChain->SetBranchAddress("p_btClusters", &p_btClusters, &b_p_btClusters);
  fChain->SetBranchAddress("p_btMaxima", &p_btMaxima, &b_p_btMaxima);
  fChain->SetBranchAddress("p_btMaximaCharge", &p_btMaximaCharge, &b_p_btMaximaCharge);
  fChain->SetBranchAddress("p_btMaximaChargeShared", &p_btMaximaChargeShared, &b_p_btMaximaChargeShared);
  fChain->SetBranchAddress("p_btMaximaChargeSharedFragment", &p_btMaximaChargeSharedFragment, &b_p_btMaximaChargeSharedFragment);
  fChain->SetBranchAddress("p_btMaximaShared", &p_btMaximaShared, &b_p_btMaximaShared);
  fChain->SetBranchAddress("p_btMaximaSharedFragment", &p_btMaximaSharedFragment, &b_p_btMaximaSharedFragment);
  fChain->SetBranchAddress("p_btMeanDist", &p_btMeanDist, &b_p_btMeanDist);
  fChain->SetBranchAddress("p_btNearbyMaxima", &p_btNearbyMaxima, &b_p_btNearbyMaxima);
  fChain->SetBranchAddress("p_btNearbyMaximaShared", &p_btNearbyMaximaShared, &b_p_btNearbyMaximaShared);
  fChain->SetBranchAddress("p_btPadsClus", &p_btPadsClus, &b_p_btPadsClus);
  fChain->SetBranchAddress("p_btPadsRing", &p_btPadsRing, &b_p_btPadsRing);
  fChain->SetBranchAddress("p_btRingMatrix", &p_btRingMatrix, &b_p_btRingMatrix);
  fChain->SetBranchAddress("p_dedx_mdc", &p_dedx_mdc, &b_p_dedx_mdc);
  fChain->SetBranchAddress("p_dedx_tof", &p_dedx_tof, &b_p_dedx_tof);
  fChain->SetBranchAddress("p_id", &p_id, &b_p_id);
  fChain->SetBranchAddress("p_isBT", &p_isBT, &b_p_isBT);
  fChain->SetBranchAddress("p_isOffVertexClust", &p_isOffVertexClust, &b_p_isOffVertexClust);
  fChain->SetBranchAddress("p_isPrimaryVertex", &p_isPrimaryVertex, &b_p_isPrimaryVertex);
  fChain->SetBranchAddress("p_isUsedVertex", &p_isUsedVertex, &b_p_isUsedVertex);
  fChain->SetBranchAddress("p_isring", &p_isring, &b_p_isring);
  fChain->SetBranchAddress("p_isringmdc", &p_isringmdc, &b_p_isringmdc);
  fChain->SetBranchAddress("p_isringnomatch", &p_isringnomatch, &b_p_isringnomatch);
  fChain->SetBranchAddress("p_isringtrack", &p_isringtrack, &b_p_isringtrack);
  fChain->SetBranchAddress("p_kIsLepton", &p_kIsLepton, &b_p_kIsLepton);
  fChain->SetBranchAddress("p_kIsUsed", &p_kIsUsed, &b_p_kIsUsed);
  fChain->SetBranchAddress("p_mdcinnerchi2", &p_mdcinnerchi2, &b_p_mdcinnerchi2);
  fChain->SetBranchAddress("p_mdcouterchi2", &p_mdcouterchi2, &b_p_mdcouterchi2);
  fChain->SetBranchAddress("p_oa_hadr", &p_oa_hadr, &b_p_oa_hadr);
  fChain->SetBranchAddress("p_oa_lept", &p_oa_lept, &b_p_oa_lept);
  fChain->SetBranchAddress("p_p", &p_p, &b_p_p);
  fChain->SetBranchAddress("p_p_corr_em", &p_p_corr_em, &b_p_p_corr_em);
  fChain->SetBranchAddress("p_p_corr_ep", &p_p_corr_ep, &b_p_p_corr_ep);
  fChain->SetBranchAddress("p_p_corr_p", &p_p_corr_p, &b_p_p_corr_p);
  fChain->SetBranchAddress("p_p_corr_pim", &p_p_corr_pim, &b_p_p_corr_pim);
  fChain->SetBranchAddress("p_p_corr_pip", &p_p_corr_pip, &b_p_p_corr_pip);
  fChain->SetBranchAddress("p_phi", &p_phi, &b_p_phi);
  fChain->SetBranchAddress("p_phi_rich", &p_phi_rich, &b_p_phi_rich);
  fChain->SetBranchAddress("p_pid", &p_pid, &b_p_pid);
  fChain->SetBranchAddress("p_q", &p_q, &b_p_q);
  fChain->SetBranchAddress("p_r", &p_r, &b_p_r);
  fChain->SetBranchAddress("p_resolution", &p_resolution, &b_p_resolution);
  fChain->SetBranchAddress("p_resoultion", &p_resoultion, &b_p_resoultion);
  fChain->SetBranchAddress("p_rich_amp", &p_rich_amp, &b_p_rich_amp);
  fChain->SetBranchAddress("p_rich_centr", &p_rich_centr, &b_p_rich_centr);
  fChain->SetBranchAddress("p_rich_houtra", &p_rich_houtra, &b_p_rich_houtra);
  fChain->SetBranchAddress("p_rich_padnum", &p_rich_padnum, &b_p_rich_padnum);
  fChain->SetBranchAddress("p_rich_patmat", &p_rich_patmat, &b_p_rich_patmat);
  fChain->SetBranchAddress("p_rkchi2", &p_rkchi2, &b_p_rkchi2);
  fChain->SetBranchAddress("p_sector", &p_sector, &b_p_sector);
  fChain->SetBranchAddress("p_shw_sum0", &p_shw_sum0, &b_p_shw_sum0);
  fChain->SetBranchAddress("p_shw_sum1", &p_shw_sum1, &b_p_shw_sum1);
  fChain->SetBranchAddress("p_shw_sum2", &p_shw_sum2, &b_p_shw_sum2);
  fChain->SetBranchAddress("p_system", &p_system, &b_p_system);
  fChain->SetBranchAddress("p_theta", &p_theta, &b_p_theta);
  fChain->SetBranchAddress("p_theta_rich", &p_theta_rich, &b_p_theta_rich);
  fChain->SetBranchAddress("p_tof_mom", &p_tof_mom, &b_p_tof_mom);
  fChain->SetBranchAddress("p_tof_new", &p_tof_new, &b_p_tof_new);
  fChain->SetBranchAddress("p_tof_rec", &p_tof_rec, &b_p_tof_rec);
  fChain->SetBranchAddress("p_track_length", &p_track_length, &b_p_track_length);
  fChain->SetBranchAddress("p_tracklength", &p_tracklength, &b_p_tracklength);
  fChain->SetBranchAddress("p_z", &p_z, &b_p_z);
  fChain->SetBranchAddress("pim1_beta", &pim1_beta, &b_pim1_beta);
  fChain->SetBranchAddress("pim1_beta_new", &pim1_beta_new, &b_pim1_beta_new);
  fChain->SetBranchAddress("pim1_btChargeRing", &pim1_btChargeRing, &b_pim1_btChargeRing);
  fChain->SetBranchAddress("pim1_btChargeSum", &pim1_btChargeSum, &b_pim1_btChargeSum);
  fChain->SetBranchAddress("pim1_btChi2", &pim1_btChi2, &b_pim1_btChi2);
  fChain->SetBranchAddress("pim1_btClusters", &pim1_btClusters, &b_pim1_btClusters);
  fChain->SetBranchAddress("pim1_btMaxima", &pim1_btMaxima, &b_pim1_btMaxima);
  fChain->SetBranchAddress("pim1_btMaximaCharge", &pim1_btMaximaCharge, &b_pim1_btMaximaCharge);
  fChain->SetBranchAddress("pim1_btMaximaChargeShared", &pim1_btMaximaChargeShared, &b_pim1_btMaximaChargeShared);
  fChain->SetBranchAddress("pim1_btMaximaChargeSharedFragment", &pim1_btMaximaChargeSharedFragment, &b_pim1_btMaximaChargeSharedFragment);
  fChain->SetBranchAddress("pim1_btMaximaShared", &pim1_btMaximaShared, &b_pim1_btMaximaShared);
  fChain->SetBranchAddress("pim1_btMaximaSharedFragment", &pim1_btMaximaSharedFragment, &b_pim1_btMaximaSharedFragment);
  fChain->SetBranchAddress("pim1_btMeanDist", &pim1_btMeanDist, &b_pim1_btMeanDist);
  fChain->SetBranchAddress("pim1_btNearbyMaxima", &pim1_btNearbyMaxima, &b_pim1_btNearbyMaxima);
  fChain->SetBranchAddress("pim1_btNearbyMaximaShared", &pim1_btNearbyMaximaShared, &b_pim1_btNearbyMaximaShared);
  fChain->SetBranchAddress("pim1_btPadsClus", &pim1_btPadsClus, &b_pim1_btPadsClus);
  fChain->SetBranchAddress("pim1_btPadsRing", &pim1_btPadsRing, &b_pim1_btPadsRing);
  fChain->SetBranchAddress("pim1_btRingMatrix", &pim1_btRingMatrix, &b_pim1_btRingMatrix);
  fChain->SetBranchAddress("pim1_dedx_mdc", &pim1_dedx_mdc, &b_pim1_dedx_mdc);
  fChain->SetBranchAddress("pim1_dedx_tof", &pim1_dedx_tof, &b_pim1_dedx_tof);
  fChain->SetBranchAddress("pim1_id", &pim1_id, &b_pim1_id);
  fChain->SetBranchAddress("pim1_isBT", &pim1_isBT, &b_pim1_isBT);
  fChain->SetBranchAddress("pim1_isOffVertexClust", &pim1_isOffVertexClust, &b_pim1_isOffVertexClust);
  fChain->SetBranchAddress("pim1_isPrimaryVertex", &pim1_isPrimaryVertex, &b_pim1_isPrimaryVertex);
  fChain->SetBranchAddress("pim1_isUsedVertex", &pim1_isUsedVertex, &b_pim1_isUsedVertex);
  fChain->SetBranchAddress("pim1_isring", &pim1_isring, &b_pim1_isring);
  fChain->SetBranchAddress("pim1_isringmdc", &pim1_isringmdc, &b_pim1_isringmdc);
  fChain->SetBranchAddress("pim1_isringnomatch", &pim1_isringnomatch, &b_pim1_isringnomatch);
  fChain->SetBranchAddress("pim1_isringtrack", &pim1_isringtrack, &b_pim1_isringtrack);
  fChain->SetBranchAddress("pim1_kIsLepton", &pim1_kIsLepton, &b_pim1_kIsLepton);
  fChain->SetBranchAddress("pim1_kIsUsed", &pim1_kIsUsed, &b_pim1_kIsUsed);
  fChain->SetBranchAddress("pim1_mdcinnerchi2", &pim1_mdcinnerchi2, &b_pim1_mdcinnerchi2);
  fChain->SetBranchAddress("pim1_mdcouterchi2", &pim1_mdcouterchi2, &b_pim1_mdcouterchi2);
  fChain->SetBranchAddress("pim1_oa_hadr", &pim1_oa_hadr, &b_pim1_oa_hadr);
  fChain->SetBranchAddress("pim1_oa_lept", &pim1_oa_lept, &b_pim1_oa_lept);
  fChain->SetBranchAddress("pim1_p", &pim1_p, &b_pim1_p);
  fChain->SetBranchAddress("pim1_p_corr_em", &pim1_p_corr_em, &b_pim1_p_corr_em);
  fChain->SetBranchAddress("pim1_p_corr_ep", &pim1_p_corr_ep, &b_pim1_p_corr_ep);
  fChain->SetBranchAddress("pim1_p_corr_p", &pim1_p_corr_p, &b_pim1_p_corr_p);
  fChain->SetBranchAddress("pim1_p_corr_pim", &pim1_p_corr_pim, &b_pim1_p_corr_pim);
  fChain->SetBranchAddress("pim1_p_corr_pip", &pim1_p_corr_pip, &b_pim1_p_corr_pip);
  fChain->SetBranchAddress("pim1_phi", &pim1_phi, &b_pim1_phi);
  fChain->SetBranchAddress("pim1_phi_rich", &pim1_phi_rich, &b_pim1_phi_rich);
  fChain->SetBranchAddress("pim1_pid", &pim1_pid, &b_pim1_pid);
  fChain->SetBranchAddress("pim1_q", &pim1_q, &b_pim1_q);
  fChain->SetBranchAddress("pim1_r", &pim1_r, &b_pim1_r);
  fChain->SetBranchAddress("pim1_resolution", &pim1_resolution, &b_pim1_resolution);
  fChain->SetBranchAddress("pim1_resoultion", &pim1_resoultion, &b_pim1_resoultion);
  fChain->SetBranchAddress("pim1_rich_amp", &pim1_rich_amp, &b_pim1_rich_amp);
  fChain->SetBranchAddress("pim1_rich_centr", &pim1_rich_centr, &b_pim1_rich_centr);
  fChain->SetBranchAddress("pim1_rich_houtra", &pim1_rich_houtra, &b_pim1_rich_houtra);
  fChain->SetBranchAddress("pim1_rich_padnum", &pim1_rich_padnum, &b_pim1_rich_padnum);
  fChain->SetBranchAddress("pim1_rich_patmat", &pim1_rich_patmat, &b_pim1_rich_patmat);
  fChain->SetBranchAddress("pim1_rkchi2", &pim1_rkchi2, &b_pim1_rkchi2);
  fChain->SetBranchAddress("pim1_sector", &pim1_sector, &b_pim1_sector);
  fChain->SetBranchAddress("pim1_shw_sum0", &pim1_shw_sum0, &b_pim1_shw_sum0);
  fChain->SetBranchAddress("pim1_shw_sum1", &pim1_shw_sum1, &b_pim1_shw_sum1);
  fChain->SetBranchAddress("pim1_shw_sum2", &pim1_shw_sum2, &b_pim1_shw_sum2);
  fChain->SetBranchAddress("pim1_system", &pim1_system, &b_pim1_system);
  fChain->SetBranchAddress("pim1_theta", &pim1_theta, &b_pim1_theta);
  fChain->SetBranchAddress("pim1_theta_rich", &pim1_theta_rich, &b_pim1_theta_rich);
  fChain->SetBranchAddress("pim1_tof_mom", &pim1_tof_mom, &b_pim1_tof_mom);
  fChain->SetBranchAddress("pim1_tof_new", &pim1_tof_new, &b_pim1_tof_new);
  fChain->SetBranchAddress("pim1_tof_rec", &pim1_tof_rec, &b_pim1_tof_rec);
  fChain->SetBranchAddress("pim1_track_length", &pim1_track_length, &b_pim1_track_length);
  fChain->SetBranchAddress("pim1_tracklength", &pim1_tracklength, &b_pim1_tracklength);
  fChain->SetBranchAddress("pim1_z", &pim1_z, &b_pim1_z);
  fChain->SetBranchAddress("pim2_beta", &pim2_beta, &b_pim2_beta);
  fChain->SetBranchAddress("pim2_beta_new", &pim2_beta_new, &b_pim2_beta_new);
  fChain->SetBranchAddress("pim2_btChargeRing", &pim2_btChargeRing, &b_pim2_btChargeRing);
  fChain->SetBranchAddress("pim2_btChargeSum", &pim2_btChargeSum, &b_pim2_btChargeSum);
  fChain->SetBranchAddress("pim2_btChi2", &pim2_btChi2, &b_pim2_btChi2);
  fChain->SetBranchAddress("pim2_btClusters", &pim2_btClusters, &b_pim2_btClusters);
  fChain->SetBranchAddress("pim2_btMaxima", &pim2_btMaxima, &b_pim2_btMaxima);
  fChain->SetBranchAddress("pim2_btMaximaCharge", &pim2_btMaximaCharge, &b_pim2_btMaximaCharge);
  fChain->SetBranchAddress("pim2_btMaximaChargeShared", &pim2_btMaximaChargeShared, &b_pim2_btMaximaChargeShared);
  fChain->SetBranchAddress("pim2_btMaximaChargeSharedFragment", &pim2_btMaximaChargeSharedFragment, &b_pim2_btMaximaChargeSharedFragment);
  fChain->SetBranchAddress("pim2_btMaximaShared", &pim2_btMaximaShared, &b_pim2_btMaximaShared);
  fChain->SetBranchAddress("pim2_btMaximaSharedFragment", &pim2_btMaximaSharedFragment, &b_pim2_btMaximaSharedFragment);
  fChain->SetBranchAddress("pim2_btMeanDist", &pim2_btMeanDist, &b_pim2_btMeanDist);
  fChain->SetBranchAddress("pim2_btNearbyMaxima", &pim2_btNearbyMaxima, &b_pim2_btNearbyMaxima);
  fChain->SetBranchAddress("pim2_btNearbyMaximaShared", &pim2_btNearbyMaximaShared, &b_pim2_btNearbyMaximaShared);
  fChain->SetBranchAddress("pim2_btPadsClus", &pim2_btPadsClus, &b_pim2_btPadsClus);
  fChain->SetBranchAddress("pim2_btPadsRing", &pim2_btPadsRing, &b_pim2_btPadsRing);
  fChain->SetBranchAddress("pim2_btRingMatrix", &pim2_btRingMatrix, &b_pim2_btRingMatrix);
  fChain->SetBranchAddress("pim2_dedx_mdc", &pim2_dedx_mdc, &b_pim2_dedx_mdc);
  fChain->SetBranchAddress("pim2_dedx_tof", &pim2_dedx_tof, &b_pim2_dedx_tof);
  fChain->SetBranchAddress("pim2_id", &pim2_id, &b_pim2_id);
  fChain->SetBranchAddress("pim2_isBT", &pim2_isBT, &b_pim2_isBT);
  fChain->SetBranchAddress("pim2_isOffVertexClust", &pim2_isOffVertexClust, &b_pim2_isOffVertexClust);
  fChain->SetBranchAddress("pim2_isPrimaryVertex", &pim2_isPrimaryVertex, &b_pim2_isPrimaryVertex);
  fChain->SetBranchAddress("pim2_isUsedVertex", &pim2_isUsedVertex, &b_pim2_isUsedVertex);
  fChain->SetBranchAddress("pim2_isring", &pim2_isring, &b_pim2_isring);
  fChain->SetBranchAddress("pim2_isringmdc", &pim2_isringmdc, &b_pim2_isringmdc);
  fChain->SetBranchAddress("pim2_isringnomatch", &pim2_isringnomatch, &b_pim2_isringnomatch);
  fChain->SetBranchAddress("pim2_isringtrack", &pim2_isringtrack, &b_pim2_isringtrack);
  fChain->SetBranchAddress("pim2_kIsLepton", &pim2_kIsLepton, &b_pim2_kIsLepton);
  fChain->SetBranchAddress("pim2_kIsUsed", &pim2_kIsUsed, &b_pim2_kIsUsed);
  fChain->SetBranchAddress("pim2_mdcinnerchi2", &pim2_mdcinnerchi2, &b_pim2_mdcinnerchi2);
  fChain->SetBranchAddress("pim2_mdcouterchi2", &pim2_mdcouterchi2, &b_pim2_mdcouterchi2);
  fChain->SetBranchAddress("pim2_oa_hadr", &pim2_oa_hadr, &b_pim2_oa_hadr);
  fChain->SetBranchAddress("pim2_oa_lept", &pim2_oa_lept, &b_pim2_oa_lept);
  fChain->SetBranchAddress("pim2_p", &pim2_p, &b_pim2_p);
  fChain->SetBranchAddress("pim2_p_corr_em", &pim2_p_corr_em, &b_pim2_p_corr_em);
  fChain->SetBranchAddress("pim2_p_corr_ep", &pim2_p_corr_ep, &b_pim2_p_corr_ep);
  fChain->SetBranchAddress("pim2_p_corr_p", &pim2_p_corr_p, &b_pim2_p_corr_p);
  fChain->SetBranchAddress("pim2_p_corr_pim", &pim2_p_corr_pim, &b_pim2_p_corr_pim);
  fChain->SetBranchAddress("pim2_p_corr_pip", &pim2_p_corr_pip, &b_pim2_p_corr_pip);
  fChain->SetBranchAddress("pim2_phi", &pim2_phi, &b_pim2_phi);
  fChain->SetBranchAddress("pim2_phi_rich", &pim2_phi_rich, &b_pim2_phi_rich);
  fChain->SetBranchAddress("pim2_pid", &pim2_pid, &b_pim2_pid);
  fChain->SetBranchAddress("pim2_q", &pim2_q, &b_pim2_q);
  fChain->SetBranchAddress("pim2_r", &pim2_r, &b_pim2_r);
  fChain->SetBranchAddress("pim2_resolution", &pim2_resolution, &b_pim2_resolution);
  fChain->SetBranchAddress("pim2_resoultion", &pim2_resoultion, &b_pim2_resoultion);
  fChain->SetBranchAddress("pim2_rich_amp", &pim2_rich_amp, &b_pim2_rich_amp);
  fChain->SetBranchAddress("pim2_rich_centr", &pim2_rich_centr, &b_pim2_rich_centr);
  fChain->SetBranchAddress("pim2_rich_houtra", &pim2_rich_houtra, &b_pim2_rich_houtra);
  fChain->SetBranchAddress("pim2_rich_padnum", &pim2_rich_padnum, &b_pim2_rich_padnum);
  fChain->SetBranchAddress("pim2_rich_patmat", &pim2_rich_patmat, &b_pim2_rich_patmat);
  fChain->SetBranchAddress("pim2_rkchi2", &pim2_rkchi2, &b_pim2_rkchi2);
  fChain->SetBranchAddress("pim2_sector", &pim2_sector, &b_pim2_sector);
  fChain->SetBranchAddress("pim2_shw_sum0", &pim2_shw_sum0, &b_pim2_shw_sum0);
  fChain->SetBranchAddress("pim2_shw_sum1", &pim2_shw_sum1, &b_pim2_shw_sum1);
  fChain->SetBranchAddress("pim2_shw_sum2", &pim2_shw_sum2, &b_pim2_shw_sum2);
  fChain->SetBranchAddress("pim2_system", &pim2_system, &b_pim2_system);
  fChain->SetBranchAddress("pim2_theta", &pim2_theta, &b_pim2_theta);
  fChain->SetBranchAddress("pim2_theta_rich", &pim2_theta_rich, &b_pim2_theta_rich);
  fChain->SetBranchAddress("pim2_tof_mom", &pim2_tof_mom, &b_pim2_tof_mom);
  fChain->SetBranchAddress("pim2_tof_new", &pim2_tof_new, &b_pim2_tof_new);
  fChain->SetBranchAddress("pim2_tof_rec", &pim2_tof_rec, &b_pim2_tof_rec);
  fChain->SetBranchAddress("pim2_track_length", &pim2_track_length, &b_pim2_track_length);
  fChain->SetBranchAddress("pim2_tracklength", &pim2_tracklength, &b_pim2_tracklength);
  fChain->SetBranchAddress("pim2_z", &pim2_z, &b_pim2_z);
  fChain->SetBranchAddress("pip_beta", &pip_beta, &b_pip_beta);
  fChain->SetBranchAddress("pip_beta_new", &pip_beta_new, &b_pip_beta_new);
  fChain->SetBranchAddress("pip_btChargeRing", &pip_btChargeRing, &b_pip_btChargeRing);
  fChain->SetBranchAddress("pip_btChargeSum", &pip_btChargeSum, &b_pip_btChargeSum);
  fChain->SetBranchAddress("pip_btChi2", &pip_btChi2, &b_pip_btChi2);
  fChain->SetBranchAddress("pip_btClusters", &pip_btClusters, &b_pip_btClusters);
  fChain->SetBranchAddress("pip_btMaxima", &pip_btMaxima, &b_pip_btMaxima);
  fChain->SetBranchAddress("pip_btMaximaCharge", &pip_btMaximaCharge, &b_pip_btMaximaCharge);
  fChain->SetBranchAddress("pip_btMaximaChargeShared", &pip_btMaximaChargeShared, &b_pip_btMaximaChargeShared);
  fChain->SetBranchAddress("pip_btMaximaChargeSharedFragment", &pip_btMaximaChargeSharedFragment, &b_pip_btMaximaChargeSharedFragment);
  fChain->SetBranchAddress("pip_btMaximaShared", &pip_btMaximaShared, &b_pip_btMaximaShared);
  fChain->SetBranchAddress("pip_btMaximaSharedFragment", &pip_btMaximaSharedFragment, &b_pip_btMaximaSharedFragment);
  fChain->SetBranchAddress("pip_btMeanDist", &pip_btMeanDist, &b_pip_btMeanDist);
  fChain->SetBranchAddress("pip_btNearbyMaxima", &pip_btNearbyMaxima, &b_pip_btNearbyMaxima);
  fChain->SetBranchAddress("pip_btNearbyMaximaShared", &pip_btNearbyMaximaShared, &b_pip_btNearbyMaximaShared);
  fChain->SetBranchAddress("pip_btPadsClus", &pip_btPadsClus, &b_pip_btPadsClus);
  fChain->SetBranchAddress("pip_btPadsRing", &pip_btPadsRing, &b_pip_btPadsRing);
  fChain->SetBranchAddress("pip_btRingMatrix", &pip_btRingMatrix, &b_pip_btRingMatrix);
  fChain->SetBranchAddress("pip_dedx_mdc", &pip_dedx_mdc, &b_pip_dedx_mdc);
  fChain->SetBranchAddress("pip_dedx_tof", &pip_dedx_tof, &b_pip_dedx_tof);
  fChain->SetBranchAddress("pip_id", &pip_id, &b_pip_id);
  fChain->SetBranchAddress("pip_isBT", &pip_isBT, &b_pip_isBT);
  fChain->SetBranchAddress("pip_isOffVertexClust", &pip_isOffVertexClust, &b_pip_isOffVertexClust);
  fChain->SetBranchAddress("pip_isPrimaryVertex", &pip_isPrimaryVertex, &b_pip_isPrimaryVertex);
  fChain->SetBranchAddress("pip_isUsedVertex", &pip_isUsedVertex, &b_pip_isUsedVertex);
  fChain->SetBranchAddress("pip_isring", &pip_isring, &b_pip_isring);
  fChain->SetBranchAddress("pip_isringmdc", &pip_isringmdc, &b_pip_isringmdc);
  fChain->SetBranchAddress("pip_isringnomatch", &pip_isringnomatch, &b_pip_isringnomatch);
  fChain->SetBranchAddress("pip_isringtrack", &pip_isringtrack, &b_pip_isringtrack);
  fChain->SetBranchAddress("pip_kIsLepton", &pip_kIsLepton, &b_pip_kIsLepton);
  fChain->SetBranchAddress("pip_kIsUsed", &pip_kIsUsed, &b_pip_kIsUsed);
  fChain->SetBranchAddress("pip_mdcinnerchi2", &pip_mdcinnerchi2, &b_pip_mdcinnerchi2);
  fChain->SetBranchAddress("pip_mdcouterchi2", &pip_mdcouterchi2, &b_pip_mdcouterchi2);
  fChain->SetBranchAddress("pip_oa_hadr", &pip_oa_hadr, &b_pip_oa_hadr);
  fChain->SetBranchAddress("pip_oa_lept", &pip_oa_lept, &b_pip_oa_lept);
  fChain->SetBranchAddress("pip_p", &pip_p, &b_pip_p);
  fChain->SetBranchAddress("pip_p_corr_em", &pip_p_corr_em, &b_pip_p_corr_em);
  fChain->SetBranchAddress("pip_p_corr_ep", &pip_p_corr_ep, &b_pip_p_corr_ep);
  fChain->SetBranchAddress("pip_p_corr_p", &pip_p_corr_p, &b_pip_p_corr_p);
  fChain->SetBranchAddress("pip_p_corr_pim", &pip_p_corr_pim, &b_pip_p_corr_pim);
  fChain->SetBranchAddress("pip_p_corr_pip", &pip_p_corr_pip, &b_pip_p_corr_pip);
  fChain->SetBranchAddress("pip_phi", &pip_phi, &b_pip_phi);
  fChain->SetBranchAddress("pip_phi_rich", &pip_phi_rich, &b_pip_phi_rich);
  fChain->SetBranchAddress("pip_pid", &pip_pid, &b_pip_pid);
  fChain->SetBranchAddress("pip_q", &pip_q, &b_pip_q);
  fChain->SetBranchAddress("pip_r", &pip_r, &b_pip_r);
  fChain->SetBranchAddress("pip_resolution", &pip_resolution, &b_pip_resolution);
  fChain->SetBranchAddress("pip_resoultion", &pip_resoultion, &b_pip_resoultion);
  fChain->SetBranchAddress("pip_rich_amp", &pip_rich_amp, &b_pip_rich_amp);
  fChain->SetBranchAddress("pip_rich_centr", &pip_rich_centr, &b_pip_rich_centr);
  fChain->SetBranchAddress("pip_rich_houtra", &pip_rich_houtra, &b_pip_rich_houtra);
  fChain->SetBranchAddress("pip_rich_padnum", &pip_rich_padnum, &b_pip_rich_padnum);
  fChain->SetBranchAddress("pip_rich_patmat", &pip_rich_patmat, &b_pip_rich_patmat);
  fChain->SetBranchAddress("pip_rkchi2", &pip_rkchi2, &b_pip_rkchi2);
  fChain->SetBranchAddress("pip_sector", &pip_sector, &b_pip_sector);
  fChain->SetBranchAddress("pip_shw_sum0", &pip_shw_sum0, &b_pip_shw_sum0);
  fChain->SetBranchAddress("pip_shw_sum1", &pip_shw_sum1, &b_pip_shw_sum1);
  fChain->SetBranchAddress("pip_shw_sum2", &pip_shw_sum2, &b_pip_shw_sum2);
  fChain->SetBranchAddress("pip_system", &pip_system, &b_pip_system);
  fChain->SetBranchAddress("pip_theta", &pip_theta, &b_pip_theta);
  fChain->SetBranchAddress("pip_theta_rich", &pip_theta_rich, &b_pip_theta_rich);
  fChain->SetBranchAddress("pip_tof_mom", &pip_tof_mom, &b_pip_tof_mom);
  fChain->SetBranchAddress("pip_tof_new", &pip_tof_new, &b_pip_tof_new);
  fChain->SetBranchAddress("pip_tof_rec", &pip_tof_rec, &b_pip_tof_rec);
  fChain->SetBranchAddress("pip_track_length", &pip_track_length, &b_pip_track_length);
  fChain->SetBranchAddress("pip_tracklength", &pip_tracklength, &b_pip_tracklength);
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
