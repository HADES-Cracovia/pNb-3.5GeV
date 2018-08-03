#include "EpEm.h"
#include "data.h"
#include <iostream>
#include <TLorentzVector.h>
#include <TVector3.h>
#include "hntuple.h"


using namespace std;
using namespace PATData;

void EpEm::Loop()
{
    static long licznik = 0;

   if (fChain == 0) return;
/*
        (*tlo)["em_btChargeRing"] = 0;
        (*tlo)["em_btChargeSum"] = 0;
        (*tlo)["em_btChi2"] = 0;
        (*tlo)["em_btClusters"] = 0;
        (*tlo)["em_btMaxima"] = 0;
        (*tlo)["em_btMaximaCharge"] = 0;
        (*tlo)["em_btMaximaChargeShared"] = 0;
        (*tlo)["em_btMaximaChargeSharedFragment"] = 0;
        (*tlo)["em_btMaximaShared"] = 0;
        (*tlo)["em_btMaximaSharedFragment"] = 0;
        (*tlo)["em_btMeanDist"] = 0;
        (*tlo)["em_btNearbyMaxima"] = 0;
        (*tlo)["em_btNearbyMaximaShared"] = 0;
        (*tlo)["em_btPadsClus"] = 0;
        (*tlo)["em_btPadsRing"] = 0;
        (*tlo)["em_btRingMatrix"] = 0;
        (*tlo)["ep_btChargeRing"] = 0;
        (*tlo)["ep_btChargeSum"] = 0;
        (*tlo)["ep_btChi2"] = 0;
        (*tlo)["ep_btClusters"] = 0;
        (*tlo)["ep_btMaxima"] = 0;
        (*tlo)["ep_btMaximaCharge"] = 0;
        (*tlo)["ep_btMaximaChargeShared"] = 0;
        (*tlo)["ep_btMaximaChargeSharedFragment"] = 0;
        (*tlo)["ep_btMaximaShared"] = 0;
        (*tlo)["ep_btMaximaSharedFragment"] = 0;
        (*tlo)["ep_btMeanDist"] = 0;
        (*tlo)["ep_btNearbyMaxima"] = 0;
        (*tlo)["ep_btNearbyMaximaShared"] = 0;
        (*tlo)["ep_btPadsClus"] = 0;
        (*tlo)["ep_btPadsRing"] = 0;
        (*tlo)["ep_btRingMatrix"] = 0;


        (*tlo)["ep_mom"] = 0;
        (*tlo)["ep_theta"] = 0;
        (*tlo)["ep_theta_rich"] = 0;
        (*tlo)["ep_phi"] = 0;
        (*tlo)["ep_phi_rich"] = 0;
        (*tlo)["ep_beta"] = 0;
        (*tlo)["em_mom"] = 0;
        (*tlo)["em_theta"] = 0;
        (*tlo)["em_theta_rich"] = 0;
        (*tlo)["em_phi"] = 0;
        (*tlo)["em_phi_rich"] = 0;
        (*tlo)["em_beta"] = 0;
        (*tlo)["oa"] = 0;
        (*tlo)["oa_rich"] = 0;
        (*tlo)["sig"] = 0;
        (*tlo)["ep_m"] = 0;
        (*tlo)["em_m"] = 0;
        (*tlo)["epem_inv_mass"] = 0;
        (*tlo)["epem_inv_mass2"] = 0;
        (*tlo)["epem_miss_mass"] = 0;
        (*tlo)["epem_miss_mass2"] = 0;
        (*tlo)["epem_y"] = 0;
        (*tlo)["epem_pt"] = 0;
        (*tlo)["ep_rich_amp"] = 0;
        (*tlo)["ep_rich_centr"] = 0;
        (*tlo)["ep_rich_padnum"] = 0;
        (*tlo)["ep_rich_patmat"] = 0;
        (*tlo)["ep_rich_houtra"] = 0;
        (*tlo)["em_rich_amp"] = 0;
        (*tlo)["em_rich_centr"] = 0;
        (*tlo)["em_rich_padnum"] = 0;
        (*tlo)["em_rich_patmat"] = 0;
        (*tlo)["em_rich_houtra"] = 0;

	    (*tlo)["eVert_x"] = 0;
	    (*tlo)["eVert_y"] = 0;
	    (*tlo)["eVert_z"] = 0;

        (*tlo)["eVertReco_z"] = -1000.;
        (*tlo)["eVertReco_x"] = -1000.;
        (*tlo)["eVertReco_y"] = -1000.;
        (*tlo)["evtPileupMeta"] = 0.;
        (*tlo)["evtPileupStart"] = 0.;
        (*tlo)["ep_isOffVertexClust"] = 0.;
        (*tlo)["ep_p_corr_ep"] = 0.;
        (*tlo)["em_isOffVertexClust"] = 0.;
        (*tlo)["em_p_corr_em"] = 0.;

        tlo->fill();
*/

   Long64_t nentries = fChain->GetEntries();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
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
      double ang_cut = 9.;

      double close_cut = 9.;
      double nonfit_close_cut = -4.;
      //double close_cut = 0.;
      //double nonfit_close_cut = 0.;
      //double close_cut = 4.;


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

      Positron = (((ep_system==0&&insideEpS0==0)||(ep_system==1&&insideEpS1==0)));
      Electron = (((em_system==0&&insideEmS0==0)||(em_system==1&&insideEmS1==0)));

      ElectronPositron = Positron && NoLeptonE1 && NoHadronE1  &&  Electron && NoLeptonE2 && NoHadronE2  &&  insideTarget;


      if (ElectronPositron && /*(((int)trigbit)&16) &&*/ isBest==1 && oa > ang_cut ) 
      {
/*        (*tlo)["ep_mom"] = ep_p;
        (*tlo)["ep_theta"] = ep_theta;
        (*tlo)["ep_theta_rich"] = ep_theta_rich;
        (*tlo)["ep_phi"] = ep_phi;
        (*tlo)["ep_phi_rich"] = ep_phi_rich;
        (*tlo)["ep_beta"] = ep_beta_new;
        (*tlo)["em_mom"] = em_p;
        (*tlo)["em_theta"] = em_theta;
        (*tlo)["em_theta_rich"] = em_theta_rich;
        (*tlo)["em_phi"] = em_phi;
        (*tlo)["em_phi_rich"] = em_phi_rich;
        (*tlo)["em_beta"] = em_beta_new;
        (*tlo)["oa"] = oa;
        (*tlo)["oa_rich"] = oa_rich;
        (*tlo)["sig"] = 1;
        (*tlo)["ep_m"] = e1_mass;
        (*tlo)["em_m"] = e2_mass;
        (*tlo)["epem_inv_mass"] = m_inv_e1e2 / 1000.;
        (*tlo)["epem_inv_mass2"] = m2_inv_e1e2 / 1000000.;
        (*tlo)["epem_miss_mass"] = e1e2_miss->M() / 1000.;
        (*tlo)["epem_miss_mass2"] = e1e2_miss->M2() / 1000000.;
        (*tlo)["epem_y"] = e1e2->Rapidity();
        (*tlo)["epem_pt"] = e1e2->Pt() / 1000.;

        (*tlo)["ep_rich_amp"] = ep_rich_amp;
        (*tlo)["ep_rich_centr"] = ep_rich_centr;
        (*tlo)["ep_rich_padnum"] = ep_rich_padnum;
        (*tlo)["ep_rich_patmat"] = ep_rich_patmat;
        (*tlo)["ep_rich_houtra"] = ep_rich_houtra;
        (*tlo)["em_rich_amp"] = em_rich_amp;
        (*tlo)["em_rich_centr"] = em_rich_centr;
        (*tlo)["em_rich_padnum"] = em_rich_padnum;
        (*tlo)["em_rich_patmat"] = em_rich_patmat;
        (*tlo)["em_rich_houtra"] = em_rich_houtra;

   	    (*tlo)["eVert_x"] = eVert_x;
	    (*tlo)["eVert_y"] = eVert_y;
	    (*tlo)["eVert_z"] = eVert_z;

        (*tlo)["eVertReco_z"] = eVertReco_z;
        (*tlo)["eVertReco_x"] = eVertReco_x;
        (*tlo)["eVertReco_y"] = eVertReco_y;


        tlo->fill();
*/
      }
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
			   );
      int i_array=0;

      if (ElectronPositron && /*(((int)trigbit)&16) && trigdec>0 &&*/  isBest>=0 && oa > ang_cut /*&& eVertReco_z>-500 */) 
      {
	
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
	  
	if(ep_isring>0 && em_isring>0 && mass_condition) { //RF signal
	    sig_all->Fill(m_inv_e1e2/1000., EFF );
            sig_all_var->Fill(m_inv_e1e2/1000., EFF );
	    em_mom->Fill(em_p);
	    ep_mom->Fill(ep_p);
            ep_beta_mom->Fill( ep_beta_new, ep_p, EFF );
            em_beta_mom->Fill( em_beta_new, em_p, EFF );
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
	      sig_all_bt->Fill(m_inv_e1e2/1000., EFF );
	      sig_all_var_bt->Fill(m_inv_e1e2/1000., EFF );
	      ep_beta_mom_bt->Fill( ep_beta_new, ep_p, EFF );
	      em_beta_mom_bt->Fill( em_beta_new, em_p, EFF );
	      em_mom_bt->Fill(em_p);
	      ep_mom_bt->Fill(ep_p);
	      momentum_spectrum_bt->Fill(em_p*(-1));
	      momentum_spectrum_bt->Fill(ep_p);


	      (*tlo)["em_btChargeRing"] = em_btChargeRing;
	      (*tlo)["em_btChargeSum"] = em_btChargeSum;
	      (*tlo)["em_btChi2"] = em_btChi2;
	      (*tlo)["em_btClusters"] = em_btClusters;
	      (*tlo)["em_btMaxima"] = em_btMaxima;
	      (*tlo)["em_btMaximaCharge"] = em_btMaximaCharge;
	      (*tlo)["em_btMaximaChargeShared"] = em_btMaximaChargeShared;
	      (*tlo)["em_btMaximaChargeSharedFragment"] = em_btMaximaChargeSharedFragment;
	      (*tlo)["em_btMaximaShared"] = em_btMaximaShared;
	      (*tlo)["em_btMaximaSharedFragment"] = em_btMaximaSharedFragment;
	      (*tlo)["em_btMeanDist"] = em_btMeanDist;
	      (*tlo)["em_btNearbyMaxima"] = em_btNearbyMaxima;
	      (*tlo)["em_btNearbyMaximaShared"] = em_btNearbyMaximaShared;
	      (*tlo)["em_btPadsClus"] = em_btPadsClus;
	      (*tlo)["em_btPadsRing"] = em_btPadsRing;
	      (*tlo)["em_btRingMatrix"] = em_btRingMatrix;
	      (*tlo)["ep_btChargeRing"] = ep_btChargeRing;
	      (*tlo)["ep_btChargeSum"] = ep_btChargeSum;
	      (*tlo)["ep_btChi2"] = ep_btChi2;
	      (*tlo)["ep_btClusters"] = ep_btClusters;
	      (*tlo)["ep_btMaxima"] = ep_btMaxima;
	      (*tlo)["ep_btMaximaCharge"] = ep_btMaximaCharge;
	      (*tlo)["ep_btMaximaChargeShared"] = ep_btMaximaChargeShared;
	      (*tlo)["ep_btMaximaChargeSharedFragment"] = ep_btMaximaChargeSharedFragment;
	      (*tlo)["ep_btMaximaShared"] = ep_btMaximaShared;
	      (*tlo)["ep_btMaximaSharedFragment"] = ep_btMaximaSharedFragment;
	      (*tlo)["ep_btMeanDist"] = ep_btMeanDist;
	      (*tlo)["ep_btNearbyMaxima"] = ep_btNearbyMaxima;
	      (*tlo)["ep_btNearbyMaximaShared"] = ep_btNearbyMaximaShared;
	      (*tlo)["ep_btPadsClus"] = ep_btPadsClus;
	      (*tlo)["ep_btPadsRing"] = ep_btPadsRing;
	      (*tlo)["ep_btRingMatrix"] = ep_btRingMatrix;
	      (*tlo)["ep_mom"] = ep_p;
	      (*tlo)["ep_theta"] = ep_theta;
	      (*tlo)["ep_theta_rich"] = ep_theta_rich;
	      (*tlo)["ep_phi"] = ep_phi;
	      (*tlo)["ep_phi_rich"] = ep_phi_rich;
	      (*tlo)["ep_beta"] = ep_beta_new;
	      (*tlo)["em_mom"] = em_p;
	      (*tlo)["em_theta"] = em_theta;
	      (*tlo)["em_theta_rich"] = em_theta_rich;
	      (*tlo)["em_phi"] = em_phi;
	      (*tlo)["em_phi_rich"] = em_phi_rich;
	      (*tlo)["em_beta"] = em_beta_new;
	      (*tlo)["oa"] = oa;
	      (*tlo)["oa_rich"] = oa_rich;
	      (*tlo)["sig"] = 1;
	      (*tlo)["ep_m"] = e1_mass;
	      (*tlo)["em_m"] = e2_mass;
	      (*tlo)["epem_inv_mass"] = m_inv_e1e2 / 1000.;
	      (*tlo)["epem_inv_mass2"] = m2_inv_e1e2 / 1000000.;
	      (*tlo)["epem_miss_mass"] = e1e2_miss->M() / 1000.;
	      (*tlo)["epem_miss_mass2"] = e1e2_miss->M2() / 1000000.;
	      (*tlo)["epem_y"] = e1e2->Rapidity();
	      (*tlo)["epem_pt"] = e1e2->Pt() / 1000.;

	      (*tlo)["ep_rich_amp"] = ep_rich_amp;
	      (*tlo)["ep_rich_centr"] = ep_rich_centr;
	      (*tlo)["ep_rich_padnum"] = ep_rich_padnum;
	      (*tlo)["ep_rich_patmat"] = ep_rich_patmat;
	      (*tlo)["ep_rich_houtra"] = ep_rich_houtra;
	      (*tlo)["em_rich_amp"] = em_rich_amp;
	      (*tlo)["em_rich_centr"] = em_rich_centr;
	      (*tlo)["em_rich_padnum"] = em_rich_padnum;
	      (*tlo)["em_rich_patmat"] = em_rich_patmat;
	      (*tlo)["em_rich_houtra"] = em_rich_houtra;

	      (*tlo)["eVert_x"] = eVert_x;
	      (*tlo)["eVert_y"] = eVert_y;
	      (*tlo)["eVert_z"] = eVert_z;

	      (*tlo)["eVertReco_z"] = eVertReco_z;
	      (*tlo)["eVertReco_x"] = eVertReco_x;
	      (*tlo)["eVertReco_y"] = eVertReco_y;

	      tlo->fill();
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
EpEm::EpEm(TTree *tree) 
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
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_epem/FILES/sep08_all/list5/sum5.root/EpEm_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_epem/FILES/sep08_all/list4/sum4.root/EpEm_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_epem/FILES/sep08_all/list3/sum3.root/EpEm_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_epem/FILES/sep08_all/list2/sum2.root/EpEm_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_epem/FILES/sep08_all/list1/sum1.root/EpEm_ID");

      // -- PE 690 ----------------------------------------
      /*       
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/196/lepton196.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/197/lepton197.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/198/lepton198.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/232/lepton232.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/233/lepton233.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/234/lepton234.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/235/lepton235.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/236/lepton236.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/237/lepton237.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/238/lepton238.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/239/lepton239.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/240/lepton240.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/241/lepton241.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/242/lepton242.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/243/lepton243.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/244/lepton244.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/245/lepton245.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/246/lepton246.root/EpEm_ID");
      */ 
/*
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/196/lepton196.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/197/lepton197.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/198/lepton198.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/232/lepton232.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/233/lepton233.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/234/lepton234.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/235/lepton235.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/236/lepton236.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/237/lepton237.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/238/lepton238.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/239/lepton239.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/240/lepton240.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/241/lepton241.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/242/lepton242.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/243/lepton243.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/244/lepton244.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/245/lepton245.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/246/lepton246.root/EpEm_ID");
*/
      // -- PE 656 ----------------------------------------
      /*
       chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/247/656/lepton247_656.root/EpEm_ID");
       chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/248/656/lepton248_656.root/EpEm_ID");
       chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/249/656/lepton249_656.root/EpEm_ID");
      */
/*
       chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/247/656/lepton247_656.root/EpEm_ID");
       chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/248/656/lepton248_656.root/EpEm_ID");
       chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/249/656/lepton249_656.root/EpEm_ID");
*/
      // -- PE 748 ----------------------------------------
      /*
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/246/748/lepton246_748.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/247/748/lepton247_748.root/EpEm_ID");
      */
/*
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/246/748/lepton246_748.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/247/748/lepton247_748.root/EpEm_ID");
*/
      // -- PE 800 ----------------------------------------
      /*
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/249/800/lepton249_800.root/EpEm_ID");
      */
/*
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/249/800/lepton249_800.root/EpEm_ID");
*/
      // --  C 656 ----------------------------------------
      /*
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/252/656/lepton252_656.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/253/656/lepton253_656.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/254/656/lepton254_656.root/EpEm_ID");
      */
/*
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/252/656/lepton252_656.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/253/656/lepton253_656.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/254/656/lepton254_656.root/EpEm_ID");
*/
      // --  C 690 ----------------------------------------
      /* 
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/195/lepton195.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/250/lepton250.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/251/lepton251.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/254/lepton254.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/255/lepton255.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/256/lepton256.root/EpEm_ID");
      */ 
/*
      //chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/195/lepton195.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/250/lepton250.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/251/lepton251.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/254/lepton254.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/255/lepton255.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/256/lepton256.root/EpEm_ID");
*/
      // --  C 748 ----------------------------------------
      /*
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/252/748/lepton252_748.root/EpEm_ID");
      */
/*
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/252/748/lepton252_748.root/EpEm_ID");
*/
      // --  C 800 ----------------------------------------
      
      //chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/251/800/lepton251_800.root/EpEm_ID");
      //chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/252/800/lepton252_800.root/EpEm_ID");
      

      /*
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/251/800/lepton251_800.root/EpEm_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/252/800/lepton252_800.root/EpEm_ID");
      */


      
	  tree = chain; 
   }

   Init(tree);
}


// -------------------------------------------------------------------------------------------------
EpEm::~EpEm()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

// -------------------------------------------------------------------------------------------------
Int_t EpEm::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

// -------------------------------------------------------------------------------------------------
Long64_t EpEm::LoadTree(Long64_t entry)
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
void EpEm::Init(TTree *tree)
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
Bool_t EpEm::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

// -------------------------------------------------------------------------------------------------
void EpEm::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

// -------------------------------------------------------------------------------------------------
Int_t EpEm::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
