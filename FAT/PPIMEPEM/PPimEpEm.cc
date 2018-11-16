
#include "PPimEpEm.h"
#include "data.h"
#include <iostream>
#include <TLorentzVector.h>
#include <TVector3.h>
#include "hntuple.h"


using namespace std;
using namespace PATData;

void PPimEpEm::Loop()
{
  static long licznik = 0;

  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntries();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      ++licznik;
      if ((licznik % 100000)==0) cout << "Events: " << licznik << endl;


      double F = 1.006;
      TVector3 v1, v2, v3;
      v2.SetXYZ(F*ep_p*sin(D2R*ep_theta)*cos(D2R*ep_phi),F*ep_p*sin(D2R*ep_theta)*sin(D2R*ep_phi),F*ep_p*cos(D2R*ep_theta));
      v3.SetXYZ(F*em_p*sin(D2R*em_theta)*cos(D2R*em_phi),F*em_p*sin(D2R*em_theta)*sin(D2R*em_phi),F*em_p*cos(D2R*em_theta));

      TVector3 r1, r2;
      r1.SetXYZ(sin(D2R*ep_theta_rich)*cos(D2R*ep_phi_rich),sin(D2R*ep_theta_rich)*sin(D2R*ep_phi_rich),cos(D2R*ep_theta_rich));
      r2.SetXYZ(sin(D2R*em_theta_rich)*cos(D2R*em_phi_rich),sin(D2R*em_theta_rich)*sin(D2R*em_phi_rich),cos(D2R*em_theta_rich));

      e1->SetVectM( v2, 0.51099906 );
      e2->SetVectM( v3, 0.51099906 );

      *gammae1e2 = *e1 + *e2;
      *e1e2 = *e1 + *e2;
      *e1_delta = *e1;
      *e2_delta = *e2;
      *e1e2_miss = *beam - *e1 - *e2;

      double m2_inv_e1e2 = gammae1e2->M2();
      double m_inv_e1e2 = gammae1e2->M();
      double oa = R2D * openingangle(*e1, *e2);
      double oa_rich = R2D * openingangle(r1, r2);

      double e1_mass = ep_p*ep_p * (  1. / (ep_beta*ep_beta)  - 1. ) ;
      double e2_mass = em_p*em_p * (  1. / (em_beta*em_beta)  - 1. ) ;

      //	  cout << "opening angle = " << oa << endl;

      ACC = 1.;
      EFF = 1.;


      gammae1e2->Boost(0., 0., -(beam->Beta()));
      e1_delta->Boost(0., 0., -(beam->Beta()));
      e2_delta->Boost(0., 0., -(beam->Beta()));

      e1_delta->Boost( -gammae1e2->Px()/gammae1e2->E(), -gammae1e2->Py()/gammae1e2->E(), -gammae1e2->Pz()/gammae1e2->E());
      e2_delta->Boost( -gammae1e2->Px()/gammae1e2->E(), -gammae1e2->Py()/gammae1e2->E(), -gammae1e2->Pz()/gammae1e2->E());

      //cout << "Poczatek obliczen..." << endl;

      //double ang_cut = 0.;
      double ang_cut = 4.;

      double close_cut = 4.;
      double nonfit_close_cut = -4.;
    
#ifdef FLANCH
      insideEmS0 = (pEmS0 == 0) ? 0 : pEmS0->IsInside(em_z,em_theta);
      insideEmS1 = (pEmS1 == 0) ? 0 : pEmS1->IsInside(em_z,em_theta);
      insideEpS0 = (pEpS0 == 0) ? 0 : pEpS0->IsInside(ep_z,ep_theta);
      insideEpS1 = (pEpS1 == 0) ? 0 : pEpS1->IsInside(ep_z,ep_theta);
      //insideEmS0 = (pEmS0 == 0) ? 0 : pEmS0->IsInside(eVert_z,em_theta);
      //insideEmS1 = (pEmS1 == 0) ? 0 : pEmS1->IsInside(eVert_z,em_theta);
      //insideEpS0 = (pEpS0 == 0) ? 0 : pEpS0->IsInside(eVert_z,ep_theta);
      //insideEpS1 = (pEpS1 == 0) ? 0 : pEpS1->IsInside(eVert_z,ep_theta);
#endif

      insideTarget = 1;

#ifdef RECTANG
      insideEmS0 = (em_theta > 50 && em_z < -50 /* && em_p<200.*/) ? 1 : 0;
      insideEmS1 = (em_theta > 50 && em_z < -50 /* && em_p<200.*/) ? 1 : 0;
      insideEpS0 = (ep_theta > 50 && ep_z < -50 /* && ep_p<200.*/) ? 1 : 0;
      insideEpS1 = (ep_theta > 50 && ep_z < -50 /* && ep_p<200.*/) ? 1 : 0;
#endif

      //#ifdef NOCUT
      insideEmS0 = 0;
      insideEmS1 = 0;
      insideEpS0 = 0;
      insideEpS1 = 0;
      //#endif


      NoLeptonE1 = !((ep_oa_lept< close_cut&&ep_oa_lept>0.0) &&ep_oa_lept>nonfit_close_cut );
      NoHadronE1 = !(ep_oa_hadr< close_cut &&ep_oa_hadr>nonfit_close_cut );
      NoLeptonE2 = !((em_oa_lept< close_cut&&em_oa_lept>0.0) &&em_oa_lept>nonfit_close_cut );
      NoHadronE2 = !(em_oa_hadr< close_cut &&em_oa_hadr>nonfit_close_cut );
      NoHadronE1 = 1;
      NoHadronE2 = 1;

      /*
	NoLeptonE1 = 1;
	NoHadronE1 = 1;
	NoLeptonE2 = 1;
	NoHadronE2 = 1;
      */

      //Hadronic part
      bool is_lambda=0;
      double min_distance=20;
      double min_z=0;

      TVector3 v_pion, v_prot;
      v_pion.SetXYZ(F*pim_p*sin(D2R*pim_theta)*cos(D2R*pim_phi),F*pim_p*sin(D2R*pim_theta)*sin(D2R*pim_phi),F*pim_p*cos(D2R*pim_theta));
      v_prot.SetXYZ(F*p_p*sin(D2R*p_theta)*cos(D2R*p_phi),F*p_p*sin(D2R*p_theta)*sin(D2R*p_phi),F*p_p*cos(D2R*p_theta));

      TVector3 r_pion,r_prot;
      r_pion.SetXYZ(sin(D2R*pim_theta)*cos(D2R*pim_phi),sin(D2R*pim_theta)*sin(D2R*pim_phi),cos(D2R*pim_theta));
      r_prot.SetXYZ(sin(D2R*p_theta)*cos(D2R*p_phi),sin(D2R*p_theta)*sin(D2R*p_phi),cos(D2R*p_theta));

 
      l_pion->SetVectM( v_pion, 139.57018 );
      l_proton->SetVectM( v_prot, 938.272029 );
      *gamma_protonpion = *l_pion + *l_proton;

      double lambda1520_mass=(*gamma_protonpion+*gammae1e2).M();
      double lambda_m=gamma_protonpion->M();
      double lambda_d=trackDistance(p_r,p_z,v_prot,pim_r,pim_z,v_pion);
      TVector3 lambda_ver=vertex(p_r,p_z,v2,pim_r,pim_z,v3);

      if(isBest!=-1)
	{
	  dist_pim_p->Fill(lambda_d);
	  m_pim_p->Fill(lambda_m);
	  lambda_vertex->Fill(lambda_ver.Z(),TMath::Sqrt(lambda_ver.X()*lambda_ver.X()+lambda_ver.Y()*lambda_ver.Y()));

	  if(  lambda_d<min_distance
	       && lambda_ver.Z()>min_z)
	    m_pim_p_ZD->Fill(lambda_m);
     
	  if(  lambda_d<min_distance
	       && lambda_m<1120
	       && lambda_m>1110
	       && lambda_ver.Z()>min_z)
	    {
	      is_lambda=true;
	      //m_pim_p_ZD->Fill(lambda_m);
	    }
	  p_beta_mom->Fill(p_beta_new,p_p);
	  pim_beta_mom->Fill(pim_beta_new,pim_p);
	}
      //End of hadronic part



    
      Positron = (((ep_system==0&&insideEpS0==0)||(ep_system==1&&insideEpS1==0)));
      Electron = (((em_system==0&&insideEmS0==0)||(em_system==1&&insideEmS1==0)));

      ElectronPositron = Positron && NoLeptonE1 && NoHadronE1  &&  Electron && NoLeptonE2 && NoHadronE2  &&  insideTarget;


      bool bt_em_condition=(em_isBT!=-1
			    //&& em_btMaxima>=2
			    && em_btPadsRing>=2
			    );
      bool bt_ep_condition=(ep_isBT!=-1
			    //&& ep_btMaxima>=2
			    && ep_btPadsRing>=2
			    );
      bool bt_condition=(bt_em_condition && bt_ep_condition);
      bool pre_shower= (ep_system==0?(ep_shw_sum1+ep_shw_sum2-ep_shw_sum0) > (parametrization(ep_p)):true)
	&&(em_system==0?(em_shw_sum1+em_shw_sum2-em_shw_sum0) > (parametrization(em_p)):true);								   
      bool mass_condition=(ep_p>100 && em_p>100 && ep_p<2000. && em_p<2000.
			   //&& ep_p>200 && em_p>200
			   //&&(ep_system==0?ep_beta>0.95:ep_beta>0.92)&&(em_system==0?em_beta>0.95:em_beta>0.92)
			   && em_beta<1.1 && ep_beta<1.1
			   && em_beta>0.9 && ep_beta>0.9
			   && pre_shower
			   && is_lambda
			   );
      int i_array=0;

      if (ElectronPositron && /*(((int)trigbit)&16) && trigdec>0 &&*/  isBest>=0 && oa > ang_cut /*&& eVertReco_z>-500 */) 
	{
	  ep_beta_mom->Fill( ep_beta_new, ep_p, EFF );
	  em_beta_mom->Fill( em_beta_new, em_p, EFF );
	  m_pim_p_ep_em->Fill(lambda1520_mass);

	  if(is_lambda)
	    m_pim_p_ep_em_ZD->Fill(lambda1520_mass);
	  
	
	  if(bt_ep_condition && ep_system==0)
	    q_vs_p_leptons_BT->Fill(ep_p,ep_shw_sum1+ep_shw_sum2-ep_shw_sum0);
	  if(bt_em_condition && em_system==0)
	    q_vs_p_leptons_BT->Fill(em_p,ep_shw_sum1+em_shw_sum2-em_shw_sum0);
	  if(ep_isring && ep_system==0)
	    q_vs_p_leptons_RF->Fill(ep_p,ep_shw_sum1+ep_shw_sum2-ep_shw_sum0);
	  if(em_isring && em_system==0)
	    q_vs_p_leptons_RF->Fill(em_p,em_shw_sum1+em_shw_sum2-em_shw_sum0);
	   
	  if( mass_condition )
	    {
	      if(ep_isring && !bt_ep_condition && !em_isring && bt_em_condition)
		i_array=1;
	      if(ep_isring && !bt_ep_condition && em_isring && bt_em_condition)
		i_array=2;
	      if(ep_isring && !bt_ep_condition && em_isring && !bt_em_condition)
		i_array=3;
	      if(ep_isring && bt_ep_condition && !em_isring && bt_em_condition)
		i_array=4;
	      if(ep_isring && bt_ep_condition && em_isring && bt_em_condition)
		i_array=5;
	      if(ep_isring && bt_ep_condition && em_isring && !bt_em_condition)
		i_array=6;
	      if(!ep_isring && bt_ep_condition && !em_isring && bt_em_condition)
		i_array=7;
	      if(!ep_isring && bt_ep_condition && em_isring && bt_em_condition)
		i_array=8;
	      if(!ep_isring && bt_ep_condition && em_isring && !bt_em_condition)
		i_array=9;

	      if(i_array!=0)
		bt_rf_stat->Fill(i_array);
	      if(m_inv_e1e2>140 && i_array!=0)
		bt_rf_stat_pi->Fill(i_array);
	      
	      if(bt_condition)
		bt_rf_stat->Fill(10);
	      if(ep_isring && em_isring)
		bt_rf_stat->Fill(11);
	      if(bt_condition && ep_isring && em_isring)
		bt_rf_stat->Fill(12);
	      if((bt_ep_condition ||ep_isring)&&(bt_em_condition||em_isring) && !(em_isring && ep_isring))
		bt_rf_stat->Fill(13);
	    
	      if(m_inv_e1e2>140 && m_inv_e1e2<700)
		{
		  if(bt_condition )
		    bt_rf_stat_pi->Fill(10);
		  if(ep_isring && em_isring )
		    bt_rf_stat_pi->Fill(11);
		  if(bt_condition && ep_isring && em_isring )
		    bt_rf_stat_pi->Fill(12);
		  if((bt_ep_condition ||ep_isring)&&(bt_em_condition||em_isring) && !(em_isring && ep_isring))
		    bt_rf_stat_pi->Fill(13);
		}
	      if(m_inv_e1e2<140)
		{
		  if(bt_condition )
		    bt_rf_stat->Fill(14);
		  if(ep_isring && em_isring )
		    bt_rf_stat->Fill(15);
		  if((bt_ep_condition ||ep_isring)&&(bt_em_condition||em_isring) && !(em_isring && ep_isring))
		    bt_rf_stat->Fill(16);
		}
	      if(m_inv_e1e2>700)
		{
		  if(bt_condition )
		    bt_rf_stat->Fill(17);
		  if(ep_isring && em_isring)
		    bt_rf_stat->Fill(18);
		  if((bt_ep_condition ||ep_isring)&&(bt_em_condition||em_isring) && !(em_isring && ep_isring))
		    bt_rf_stat->Fill(19);
		}
	      if(m_inv_e1e2>140 && m_inv_e1e2<700)
		{
		  if(bt_condition )
		    bt_rf_stat->Fill(20);
		  if(ep_isring && em_isring)
		    bt_rf_stat->Fill(21);
		  if((bt_ep_condition ||ep_isring)&&(bt_em_condition||em_isring) && !(em_isring && ep_isring))
		    bt_rf_stat->Fill(22);
		}
	    }

	  if(ep_isring>0 && em_isring>0 && mass_condition)
	    if(bt_condition)
	      {
		sig_rf_and_bt->Fill(m_inv_e1e2/1000., EFF );
	      }
	  
	  if(ep_isring>0 && em_isring>0 && mass_condition)  //RF signal
	    {
	      if(is_lambda)
		m_pim_p_ep_em_ZD_RF->Fill(lambda1520_mass);
	      sig_all->Fill(m_inv_e1e2/1000., EFF );
	      sig_all_var->Fill(m_inv_e1e2/1000., EFF );
	      em_mom->Fill(em_p);
	      ep_mom->Fill(ep_p);
	      
	      rf_freedom->Fill((em_theta-em_theta_rich),(em_phi-em_phi_rich)*TMath::Sin(em_theta*TMath::DegToRad()),em_p);
	      rf_freedom->Fill((ep_theta-ep_theta_rich),(ep_phi-ep_phi_rich)*TMath::Sin(ep_theta*TMath::DegToRad()),ep_p);
	      rf_f_dtheta->Fill((em_theta-em_theta_rich),em_p);
	      rf_f_dphi->Fill((em_phi-em_phi_rich)*TMath::Sin(em_theta*TMath::DegToRad()),em_p);
	      rf_f_dtheta->Fill((ep_theta-ep_theta_rich),ep_p);
	      rf_f_dphi->Fill((ep_phi-ep_phi_rich)*TMath::Sin(ep_theta*TMath::DegToRad()),ep_p);
	      momentum_spectrum->Fill(em_p*(-1));
	      momentum_spectrum->Fill(ep_p);
	      double p_max=1000.;
	      for(int h=0;h<9;h++)
		{
		  if(ep_p>h/9.*p_max && ep_p<(h+1)/9.*p_max)
		    phi_theta_rich[h]->Fill((ep_theta-ep_theta_rich),(ep_phi-ep_phi_rich)*TMath::Sin(ep_theta*TMath::DegToRad()));
		  if(em_p>h/9.*p_max && em_p<(h+1)/9.*p_max)
		    phi_theta_rich[h]->Fill((em_theta-em_theta_rich),(em_phi-em_phi_rich)*TMath::Sin(em_theta*TMath::DegToRad()));
		}
	    }
	  if(mass_condition && (bt_ep_condition||ep_isring) && (bt_em_condition||em_isring) && !(em_isring && ep_isring))//pure backtracking signal
	    {
	      pureBT_signal->Fill(m_inv_e1e2/1000., EFF );
	      pureBT_signal_var->Fill(m_inv_e1e2/1000., EFF );
	      if(ep_isBT!=-1)
		{
		  pureBT_beta_mom->Fill( ep_beta_new, ep_p, EFF );
		  momentum_spectrum_pureBT->Fill(ep_p);
		  //pureBT_beta_mom_var->Fill( ep_beta_new, ep_p, EFF );
		}
	      if(em_isBT!=-1)
		{
		  pureBT_beta_mom->Fill( em_beta_new, em_p, EFF );
		  momentum_spectrum_pureBT->Fill(em_p*(-1));
		  //pureBT_beta_mom_var->Fill( em_beta_new, em_p, EFF );
		}
	    }
	  if (mass_condition)  
	    if (bt_condition)//bt signal
	      {
		if(is_lambda)
		  m_pim_p_ep_em_ZD_BT->Fill(lambda1520_mass);
		sig_all_bt->Fill(m_inv_e1e2/1000., EFF );
		sig_all_var_bt->Fill(m_inv_e1e2/1000., EFF );
		ep_beta_mom_bt->Fill( ep_beta_new, ep_p, EFF );
		em_beta_mom_bt->Fill( em_beta_new, em_p, EFF );
		em_mom_bt->Fill(em_p);
		ep_mom_bt->Fill(ep_p);
		momentum_spectrum_bt->Fill(em_p*(-1));
		momentum_spectrum_bt->Fill(ep_p);

	      }

	  if(m_inv_e1e2>140.)  miss_all->Fill(e1e2_miss->M()/1000., EFF );

	  sig_all_var2->Fill(m_inv_e1e2/1000., EFF );
	  rapidity_all->Fill( e1e2->Rapidity(), EFF  );
	  pt_all->Fill( e1e2->Pt() / 1000. , EFF );
	  if (m_inv_e1e2 > 140. && e1e2_miss->M()>860.&& e1e2_miss->M()<1020.)
	    {
	      cos_ep->Fill( cos( openingangle( *e1_delta, *gammae1e2 ) ) );
	      cos_em->Fill( cos( openingangle( *e2_delta, *gammae1e2 ) ) );
	      cos_sum->Fill( cos( openingangle( *e1_delta, *gammae1e2 ) ), 0.5 );
	      cos_sum->Fill( cos( openingangle( *e2_delta, *gammae1e2 ) ), 0.5 );
	      cos_ep_cm->Fill( cos(gammae1e2->Theta() ));
	      rapidity_140_all->Fill( e1e2->Rapidity(), EFF  );
	      pt_140_all->Fill( e1e2->Pt() / 1000., EFF  );
	    }
	}

      //tlo->fill();

      // if (Cut(ientry) < 0) continue;
    } // end of main loop
} // eof Loop 



// -------------------------------------------------------------------------------------------------
PPimEpEm::PPimEpEm(TTree *tree) 
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.

  em_acc = em_acc_err = ep_acc = ep_acc_err = 0.;
  em_eff = em_eff_err = ep_eff = ep_eff_err = 0.;

  if (tree == 0) {
	  
    TChain * chain = new TChain("EpEm_ID","");

    // -- NOWA EPOKA ANALIZY ----------------------------------------
    //chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT/FILES/288/day288.root/EpEm_ID");
    //chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT/FILES/288_new/lepton288new.root/EpEm_ID");
    //chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT/FILES/288_new_pcut/lepton288new_p.root/EpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton00.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton01.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton02.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton03.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton04.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton05.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton06.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton07.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton08.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton09.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton10.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton11.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton12.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton13.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton14.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton15.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton16.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton17.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton18.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton19.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton20.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton21.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton22.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton23.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton24.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton25.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton26.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton27.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton28.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton29.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton30.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton31.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton32.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton33.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton34.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton35.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton36.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton37.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton38.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton39.root/PPimEpEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton40.root/PPimEpEm_ID");
      
    tree = chain; 
  }

  Init(tree);
}


// -------------------------------------------------------------------------------------------------
PPimEpEm::~PPimEpEm()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

// -------------------------------------------------------------------------------------------------
Int_t PPimEpEm::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

// -------------------------------------------------------------------------------------------------
Long64_t PPimEpEm::LoadTree(Long64_t entry)
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

// -------------------------------------------------------------------------------------------------
void PPimEpEm::Init(TTree *tree)
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
  fChain->SetBranchAddress("em_beta", &em_beta, &b_em_beta);
  fChain->SetBranchAddress("em_beta_new", &em_beta_new, &b_em_beta_new);
  fChain->SetBranchAddress("em_btChargeRing", &em_btChargeRing, &b_em_btChargeRing);
  fChain->SetBranchAddress("em_btChargeSum", &em_btChargeSum, &b_em_btChargeSum);
  fChain->SetBranchAddress("em_btChi2", &em_btChi2, &b_em_btChi2);
  fChain->SetBranchAddress("em_btClusters", &em_btClusters, &b_em_btClusters);
  fChain->SetBranchAddress("em_btMaxima", &em_btMaxima, &b_em_btMaxima);
  fChain->SetBranchAddress("em_btMaximaCharge", &em_btMaximaCharge, &b_em_btMaximaCharge);
  fChain->SetBranchAddress("em_btMaximaChargeShared", &em_btMaximaChargeShared, &b_em_btMaximaChargeShared);
  fChain->SetBranchAddress("em_btMaximaChargeSharedFragment", &em_btMaximaChargeSharedFragment, &b_em_btMaximaChargeSharedFragment);
  fChain->SetBranchAddress("em_btMaximaShared", &em_btMaximaShared, &b_em_btMaximaShared);
  fChain->SetBranchAddress("em_btMaximaSharedFragment", &em_btMaximaSharedFragment, &b_em_btMaximaSharedFragment);
  fChain->SetBranchAddress("em_btMeanDist", &em_btMeanDist, &b_em_btMeanDist);
  fChain->SetBranchAddress("em_btNearbyMaxima", &em_btNearbyMaxima, &b_em_btNearbyMaxima);
  fChain->SetBranchAddress("em_btNearbyMaximaShared", &em_btNearbyMaximaShared, &b_em_btNearbyMaximaShared);
  fChain->SetBranchAddress("em_btPadsClus", &em_btPadsClus, &b_em_btPadsClus);
  fChain->SetBranchAddress("em_btPadsRing", &em_btPadsRing, &b_em_btPadsRing);
  fChain->SetBranchAddress("em_btRingMatrix", &em_btRingMatrix, &b_em_btRingMatrix);
  fChain->SetBranchAddress("em_dedx_mdc", &em_dedx_mdc, &b_em_dedx_mdc);
  fChain->SetBranchAddress("em_dedx_tof", &em_dedx_tof, &b_em_dedx_tof);
  fChain->SetBranchAddress("em_id", &em_id, &b_em_id);
  fChain->SetBranchAddress("em_isBT", &em_isBT, &b_em_isBT);
  fChain->SetBranchAddress("em_isOffVertexClust", &em_isOffVertexClust, &b_em_isOffVertexClust);
  fChain->SetBranchAddress("em_isPrimaryVertex", &em_isPrimaryVertex, &b_em_isPrimaryVertex);
  fChain->SetBranchAddress("em_isUsedVertex", &em_isUsedVertex, &b_em_isUsedVertex);
  fChain->SetBranchAddress("em_isring", &em_isring, &b_em_isring);
  fChain->SetBranchAddress("em_isringmdc", &em_isringmdc, &b_em_isringmdc);
  fChain->SetBranchAddress("em_isringnomatch", &em_isringnomatch, &b_em_isringnomatch);
  fChain->SetBranchAddress("em_isringtrack", &em_isringtrack, &b_em_isringtrack);
  fChain->SetBranchAddress("em_kIsLepton", &em_kIsLepton, &b_em_kIsLepton);
  fChain->SetBranchAddress("em_kIsUsed", &em_kIsUsed, &b_em_kIsUsed);
  fChain->SetBranchAddress("em_mdcinnerchi2", &em_mdcinnerchi2, &b_em_mdcinnerchi2);
  fChain->SetBranchAddress("em_mdcouterchi2", &em_mdcouterchi2, &b_em_mdcouterchi2);
  fChain->SetBranchAddress("em_oa_hadr", &em_oa_hadr, &b_em_oa_hadr);
  fChain->SetBranchAddress("em_oa_lept", &em_oa_lept, &b_em_oa_lept);
  fChain->SetBranchAddress("em_p", &em_p, &b_em_p);
  fChain->SetBranchAddress("em_p_corr_em", &em_p_corr_em, &b_em_p_corr_em);
  fChain->SetBranchAddress("em_p_corr_ep", &em_p_corr_ep, &b_em_p_corr_ep);
  fChain->SetBranchAddress("em_p_corr_p", &em_p_corr_p, &b_em_p_corr_p);
  fChain->SetBranchAddress("em_p_corr_pim", &em_p_corr_pim, &b_em_p_corr_pim);
  fChain->SetBranchAddress("em_p_corr_pip", &em_p_corr_pip, &b_em_p_corr_pip);
  fChain->SetBranchAddress("em_phi", &em_phi, &b_em_phi);
  fChain->SetBranchAddress("em_phi_rich", &em_phi_rich, &b_em_phi_rich);
  fChain->SetBranchAddress("em_pid", &em_pid, &b_em_pid);
  fChain->SetBranchAddress("em_q", &em_q, &b_em_q);
  fChain->SetBranchAddress("em_r", &em_r, &b_em_r);
  fChain->SetBranchAddress("em_resolution", &em_resolution, &b_em_resolution);
  fChain->SetBranchAddress("em_resoultion", &em_resoultion, &b_em_resoultion);
  fChain->SetBranchAddress("em_rich_amp", &em_rich_amp, &b_em_rich_amp);
  fChain->SetBranchAddress("em_rich_centr", &em_rich_centr, &b_em_rich_centr);
  fChain->SetBranchAddress("em_rich_houtra", &em_rich_houtra, &b_em_rich_houtra);
  fChain->SetBranchAddress("em_rich_padnum", &em_rich_padnum, &b_em_rich_padnum);
  fChain->SetBranchAddress("em_rich_patmat", &em_rich_patmat, &b_em_rich_patmat);
  fChain->SetBranchAddress("em_rkchi2", &em_rkchi2, &b_em_rkchi2);
  fChain->SetBranchAddress("em_sector", &em_sector, &b_em_sector);
  fChain->SetBranchAddress("em_shw_sum0", &em_shw_sum0, &b_em_shw_sum0);
  fChain->SetBranchAddress("em_shw_sum1", &em_shw_sum1, &b_em_shw_sum1);
  fChain->SetBranchAddress("em_shw_sum2", &em_shw_sum2, &b_em_shw_sum2);
  fChain->SetBranchAddress("em_system", &em_system, &b_em_system);
  fChain->SetBranchAddress("em_theta", &em_theta, &b_em_theta);
  fChain->SetBranchAddress("em_theta_rich", &em_theta_rich, &b_em_theta_rich);
  fChain->SetBranchAddress("em_tof_mom", &em_tof_mom, &b_em_tof_mom);
  fChain->SetBranchAddress("em_tof_new", &em_tof_new, &b_em_tof_new);
  fChain->SetBranchAddress("em_tof_rec", &em_tof_rec, &b_em_tof_rec);
  fChain->SetBranchAddress("em_track_length", &em_track_length, &b_em_track_length);
  fChain->SetBranchAddress("em_tracklength", &em_tracklength, &b_em_tracklength);
  fChain->SetBranchAddress("em_z", &em_z, &b_em_z);
  fChain->SetBranchAddress("ep_beta", &ep_beta, &b_ep_beta);
  fChain->SetBranchAddress("ep_beta_new", &ep_beta_new, &b_ep_beta_new);
  fChain->SetBranchAddress("ep_btChargeRing", &ep_btChargeRing, &b_ep_btChargeRing);
  fChain->SetBranchAddress("ep_btChargeSum", &ep_btChargeSum, &b_ep_btChargeSum);
  fChain->SetBranchAddress("ep_btChi2", &ep_btChi2, &b_ep_btChi2);
  fChain->SetBranchAddress("ep_btClusters", &ep_btClusters, &b_ep_btClusters);
  fChain->SetBranchAddress("ep_btMaxima", &ep_btMaxima, &b_ep_btMaxima);
  fChain->SetBranchAddress("ep_btMaximaCharge", &ep_btMaximaCharge, &b_ep_btMaximaCharge);
  fChain->SetBranchAddress("ep_btMaximaChargeShared", &ep_btMaximaChargeShared, &b_ep_btMaximaChargeShared);
  fChain->SetBranchAddress("ep_btMaximaChargeSharedFragment", &ep_btMaximaChargeSharedFragment, &b_ep_btMaximaChargeSharedFragment);
  fChain->SetBranchAddress("ep_btMaximaShared", &ep_btMaximaShared, &b_ep_btMaximaShared);
  fChain->SetBranchAddress("ep_btMaximaSharedFragment", &ep_btMaximaSharedFragment, &b_ep_btMaximaSharedFragment);
  fChain->SetBranchAddress("ep_btMeanDist", &ep_btMeanDist, &b_ep_btMeanDist);
  fChain->SetBranchAddress("ep_btNearbyMaxima", &ep_btNearbyMaxima, &b_ep_btNearbyMaxima);
  fChain->SetBranchAddress("ep_btNearbyMaximaShared", &ep_btNearbyMaximaShared, &b_ep_btNearbyMaximaShared);
  fChain->SetBranchAddress("ep_btPadsClus", &ep_btPadsClus, &b_ep_btPadsClus);
  fChain->SetBranchAddress("ep_btPadsRing", &ep_btPadsRing, &b_ep_btPadsRing);
  fChain->SetBranchAddress("ep_btRingMatrix", &ep_btRingMatrix, &b_ep_btRingMatrix);
  fChain->SetBranchAddress("ep_dedx_mdc", &ep_dedx_mdc, &b_ep_dedx_mdc);
  fChain->SetBranchAddress("ep_dedx_tof", &ep_dedx_tof, &b_ep_dedx_tof);
  fChain->SetBranchAddress("ep_id", &ep_id, &b_ep_id);
  fChain->SetBranchAddress("ep_isBT", &ep_isBT, &b_ep_isBT);
  fChain->SetBranchAddress("ep_isOffVertexClust", &ep_isOffVertexClust, &b_ep_isOffVertexClust);
  fChain->SetBranchAddress("ep_isPrimaryVertex", &ep_isPrimaryVertex, &b_ep_isPrimaryVertex);
  fChain->SetBranchAddress("ep_isUsedVertex", &ep_isUsedVertex, &b_ep_isUsedVertex);
  fChain->SetBranchAddress("ep_isring", &ep_isring, &b_ep_isring);
  fChain->SetBranchAddress("ep_isringmdc", &ep_isringmdc, &b_ep_isringmdc);
  fChain->SetBranchAddress("ep_isringnomatch", &ep_isringnomatch, &b_ep_isringnomatch);
  fChain->SetBranchAddress("ep_isringtrack", &ep_isringtrack, &b_ep_isringtrack);
  fChain->SetBranchAddress("ep_kIsLepton", &ep_kIsLepton, &b_ep_kIsLepton);
  fChain->SetBranchAddress("ep_kIsUsed", &ep_kIsUsed, &b_ep_kIsUsed);
  fChain->SetBranchAddress("ep_mdcinnerchi2", &ep_mdcinnerchi2, &b_ep_mdcinnerchi2);
  fChain->SetBranchAddress("ep_mdcouterchi2", &ep_mdcouterchi2, &b_ep_mdcouterchi2);
  fChain->SetBranchAddress("ep_oa_hadr", &ep_oa_hadr, &b_ep_oa_hadr);
  fChain->SetBranchAddress("ep_oa_lept", &ep_oa_lept, &b_ep_oa_lept);
  fChain->SetBranchAddress("ep_p", &ep_p, &b_ep_p);
  fChain->SetBranchAddress("ep_p_corr_em", &ep_p_corr_em, &b_ep_p_corr_em);
  fChain->SetBranchAddress("ep_p_corr_ep", &ep_p_corr_ep, &b_ep_p_corr_ep);
  fChain->SetBranchAddress("ep_p_corr_p", &ep_p_corr_p, &b_ep_p_corr_p);
  fChain->SetBranchAddress("ep_p_corr_pim", &ep_p_corr_pim, &b_ep_p_corr_pim);
  fChain->SetBranchAddress("ep_p_corr_pip", &ep_p_corr_pip, &b_ep_p_corr_pip);
  fChain->SetBranchAddress("ep_phi", &ep_phi, &b_ep_phi);
  fChain->SetBranchAddress("ep_phi_rich", &ep_phi_rich, &b_ep_phi_rich);
  fChain->SetBranchAddress("ep_pid", &ep_pid, &b_ep_pid);
  fChain->SetBranchAddress("ep_q", &ep_q, &b_ep_q);
  fChain->SetBranchAddress("ep_r", &ep_r, &b_ep_r);
  fChain->SetBranchAddress("ep_resolution", &ep_resolution, &b_ep_resolution);
  fChain->SetBranchAddress("ep_resoultion", &ep_resoultion, &b_ep_resoultion);
  fChain->SetBranchAddress("ep_rich_amp", &ep_rich_amp, &b_ep_rich_amp);
  fChain->SetBranchAddress("ep_rich_centr", &ep_rich_centr, &b_ep_rich_centr);
  fChain->SetBranchAddress("ep_rich_houtra", &ep_rich_houtra, &b_ep_rich_houtra);
  fChain->SetBranchAddress("ep_rich_padnum", &ep_rich_padnum, &b_ep_rich_padnum);
  fChain->SetBranchAddress("ep_rich_patmat", &ep_rich_patmat, &b_ep_rich_patmat);
  fChain->SetBranchAddress("ep_rkchi2", &ep_rkchi2, &b_ep_rkchi2);
  fChain->SetBranchAddress("ep_sector", &ep_sector, &b_ep_sector);
  fChain->SetBranchAddress("ep_shw_sum0", &ep_shw_sum0, &b_ep_shw_sum0);
  fChain->SetBranchAddress("ep_shw_sum1", &ep_shw_sum1, &b_ep_shw_sum1);
  fChain->SetBranchAddress("ep_shw_sum2", &ep_shw_sum2, &b_ep_shw_sum2);
  fChain->SetBranchAddress("ep_system", &ep_system, &b_ep_system);
  fChain->SetBranchAddress("ep_theta", &ep_theta, &b_ep_theta);
  fChain->SetBranchAddress("ep_theta_rich", &ep_theta_rich, &b_ep_theta_rich);
  fChain->SetBranchAddress("ep_tof_mom", &ep_tof_mom, &b_ep_tof_mom);
  fChain->SetBranchAddress("ep_tof_new", &ep_tof_new, &b_ep_tof_new);
  fChain->SetBranchAddress("ep_tof_rec", &ep_tof_rec, &b_ep_tof_rec);
  fChain->SetBranchAddress("ep_track_length", &ep_track_length, &b_ep_track_length);
  fChain->SetBranchAddress("ep_tracklength", &ep_tracklength, &b_ep_tracklength);
  fChain->SetBranchAddress("ep_z", &ep_z, &b_ep_z);
  fChain->SetBranchAddress("event", &event, &b_event);
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
  fChain->SetBranchAddress("pim_beta", &pim_beta, &b_pim_beta);
  fChain->SetBranchAddress("pim_beta_new", &pim_beta_new, &b_pim_beta_new);
  fChain->SetBranchAddress("pim_btChargeRing", &pim_btChargeRing, &b_pim_btChargeRing);
  fChain->SetBranchAddress("pim_btChargeSum", &pim_btChargeSum, &b_pim_btChargeSum);
  fChain->SetBranchAddress("pim_btChi2", &pim_btChi2, &b_pim_btChi2);
  fChain->SetBranchAddress("pim_btClusters", &pim_btClusters, &b_pim_btClusters);
  fChain->SetBranchAddress("pim_btMaxima", &pim_btMaxima, &b_pim_btMaxima);
  fChain->SetBranchAddress("pim_btMaximaCharge", &pim_btMaximaCharge, &b_pim_btMaximaCharge);
  fChain->SetBranchAddress("pim_btMaximaChargeShared", &pim_btMaximaChargeShared, &b_pim_btMaximaChargeShared);
  fChain->SetBranchAddress("pim_btMaximaChargeSharedFragment", &pim_btMaximaChargeSharedFragment, &b_pim_btMaximaChargeSharedFragment);
  fChain->SetBranchAddress("pim_btMaximaShared", &pim_btMaximaShared, &b_pim_btMaximaShared);
  fChain->SetBranchAddress("pim_btMaximaSharedFragment", &pim_btMaximaSharedFragment, &b_pim_btMaximaSharedFragment);
  fChain->SetBranchAddress("pim_btMeanDist", &pim_btMeanDist, &b_pim_btMeanDist);
  fChain->SetBranchAddress("pim_btNearbyMaxima", &pim_btNearbyMaxima, &b_pim_btNearbyMaxima);
  fChain->SetBranchAddress("pim_btNearbyMaximaShared", &pim_btNearbyMaximaShared, &b_pim_btNearbyMaximaShared);
  fChain->SetBranchAddress("pim_btPadsClus", &pim_btPadsClus, &b_pim_btPadsClus);
  fChain->SetBranchAddress("pim_btPadsRing", &pim_btPadsRing, &b_pim_btPadsRing);
  fChain->SetBranchAddress("pim_btRingMatrix", &pim_btRingMatrix, &b_pim_btRingMatrix);
  fChain->SetBranchAddress("pim_dedx_mdc", &pim_dedx_mdc, &b_pim_dedx_mdc);
  fChain->SetBranchAddress("pim_dedx_tof", &pim_dedx_tof, &b_pim_dedx_tof);
  fChain->SetBranchAddress("pim_id", &pim_id, &b_pim_id);
  fChain->SetBranchAddress("pim_isBT", &pim_isBT, &b_pim_isBT);
  fChain->SetBranchAddress("pim_isOffVertexClust", &pim_isOffVertexClust, &b_pim_isOffVertexClust);
  fChain->SetBranchAddress("pim_isPrimaryVertex", &pim_isPrimaryVertex, &b_pim_isPrimaryVertex);
  fChain->SetBranchAddress("pim_isUsedVertex", &pim_isUsedVertex, &b_pim_isUsedVertex);
  fChain->SetBranchAddress("pim_isring", &pim_isring, &b_pim_isring);
  fChain->SetBranchAddress("pim_isringmdc", &pim_isringmdc, &b_pim_isringmdc);
  fChain->SetBranchAddress("pim_isringnomatch", &pim_isringnomatch, &b_pim_isringnomatch);
  fChain->SetBranchAddress("pim_isringtrack", &pim_isringtrack, &b_pim_isringtrack);
  fChain->SetBranchAddress("pim_kIsLepton", &pim_kIsLepton, &b_pim_kIsLepton);
  fChain->SetBranchAddress("pim_kIsUsed", &pim_kIsUsed, &b_pim_kIsUsed);
  fChain->SetBranchAddress("pim_mdcinnerchi2", &pim_mdcinnerchi2, &b_pim_mdcinnerchi2);
  fChain->SetBranchAddress("pim_mdcouterchi2", &pim_mdcouterchi2, &b_pim_mdcouterchi2);
  fChain->SetBranchAddress("pim_oa_hadr", &pim_oa_hadr, &b_pim_oa_hadr);
  fChain->SetBranchAddress("pim_oa_lept", &pim_oa_lept, &b_pim_oa_lept);
  fChain->SetBranchAddress("pim_p", &pim_p, &b_pim_p);
  fChain->SetBranchAddress("pim_p_corr_em", &pim_p_corr_em, &b_pim_p_corr_em);
  fChain->SetBranchAddress("pim_p_corr_ep", &pim_p_corr_ep, &b_pim_p_corr_ep);
  fChain->SetBranchAddress("pim_p_corr_p", &pim_p_corr_p, &b_pim_p_corr_p);
  fChain->SetBranchAddress("pim_p_corr_pim", &pim_p_corr_pim, &b_pim_p_corr_pim);
  fChain->SetBranchAddress("pim_p_corr_pip", &pim_p_corr_pip, &b_pim_p_corr_pip);
  fChain->SetBranchAddress("pim_phi", &pim_phi, &b_pim_phi);
  fChain->SetBranchAddress("pim_phi_rich", &pim_phi_rich, &b_pim_phi_rich);
  fChain->SetBranchAddress("pim_pid", &pim_pid, &b_pim_pid);
  fChain->SetBranchAddress("pim_q", &pim_q, &b_pim_q);
  fChain->SetBranchAddress("pim_r", &pim_r, &b_pim_r);
  fChain->SetBranchAddress("pim_resolution", &pim_resolution, &b_pim_resolution);
  fChain->SetBranchAddress("pim_resoultion", &pim_resoultion, &b_pim_resoultion);
  fChain->SetBranchAddress("pim_rich_amp", &pim_rich_amp, &b_pim_rich_amp);
  fChain->SetBranchAddress("pim_rich_centr", &pim_rich_centr, &b_pim_rich_centr);
  fChain->SetBranchAddress("pim_rich_houtra", &pim_rich_houtra, &b_pim_rich_houtra);
  fChain->SetBranchAddress("pim_rich_padnum", &pim_rich_padnum, &b_pim_rich_padnum);
  fChain->SetBranchAddress("pim_rich_patmat", &pim_rich_patmat, &b_pim_rich_patmat);
  fChain->SetBranchAddress("pim_rkchi2", &pim_rkchi2, &b_pim_rkchi2);
  fChain->SetBranchAddress("pim_sector", &pim_sector, &b_pim_sector);
  fChain->SetBranchAddress("pim_shw_sum0", &pim_shw_sum0, &b_pim_shw_sum0);
  fChain->SetBranchAddress("pim_shw_sum1", &pim_shw_sum1, &b_pim_shw_sum1);
  fChain->SetBranchAddress("pim_shw_sum2", &pim_shw_sum2, &b_pim_shw_sum2);
  fChain->SetBranchAddress("pim_system", &pim_system, &b_pim_system);
  fChain->SetBranchAddress("pim_theta", &pim_theta, &b_pim_theta);
  fChain->SetBranchAddress("pim_theta_rich", &pim_theta_rich, &b_pim_theta_rich);
  fChain->SetBranchAddress("pim_tof_mom", &pim_tof_mom, &b_pim_tof_mom);
  fChain->SetBranchAddress("pim_tof_new", &pim_tof_new, &b_pim_tof_new);
  fChain->SetBranchAddress("pim_tof_rec", &pim_tof_rec, &b_pim_tof_rec);
  fChain->SetBranchAddress("pim_track_length", &pim_track_length, &b_pim_track_length);
  fChain->SetBranchAddress("pim_tracklength", &pim_tracklength, &b_pim_tracklength);
  fChain->SetBranchAddress("pim_z", &pim_z, &b_pim_z);
  fChain->SetBranchAddress("hneg_mult", &hneg_mult, &b_hneg_mult);
  fChain->SetBranchAddress("hpos_mult", &hpos_mult, &b_hpos_mult);
  fChain->SetBranchAddress("isBest", &isBest, &b_isBest);
  fChain->SetBranchAddress("lneg_mult", &lneg_mult, &b_lneg_mult);
  fChain->SetBranchAddress("lpos_mult", &lpos_mult, &b_lpos_mult);
  fChain->SetBranchAddress("runnumber", &runnumber, &b_runnumber);
  fChain->SetBranchAddress("totalmult", &totalmult, &b_totalmult);
  fChain->SetBranchAddress("trigbit", &trigbit, &b_trigbit);
  fChain->SetBranchAddress("trigdec", &trigdec, &b_trigdec);
  fChain->SetBranchAddress("trigdownscale", &trigdownscale, &b_trigdownscale);
  fChain->SetBranchAddress("trigdownscaleflag", &trigdownscaleflag, &b_trigdownscaleflag);
  Notify();
}

// -------------------------------------------------------------------------------------------------
Bool_t PPimEpEm::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

// -------------------------------------------------------------------------------------------------
void PPimEpEm::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}

// -------------------------------------------------------------------------------------------------
Int_t PPimEpEm::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
