#include "EpEp.h"
#include "data.h"
#include <iostream>
#include <TLorentzVector.h>
#include <TVector3.h>
#include "hntuple.h"

using namespace std;
using namespace PATData;


void EpEp::Loop()
{
   static long licznik = 0;

   if (fChain == 0) return;
/*
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
*/
        //tlo->fill();

   Long64_t nentries = fChain->GetEntries();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      ++licznik;
      if ((licznik % 100000)==0) cout << "EpEp Events: " << licznik << endl;


      double F = 1.006;
      TVector3 v1, v2, v3;
      v2.SetXYZ(F*ep1_p*sin(D2R*ep1_theta)*cos(D2R*ep1_phi),F*ep1_p*sin(D2R*ep1_theta)*sin(D2R*ep1_phi),F*ep1_p*cos(D2R*ep1_theta));
      v3.SetXYZ(F*ep2_p*sin(D2R*ep2_theta)*cos(D2R*ep2_phi),F*ep2_p*sin(D2R*ep2_theta)*sin(D2R*ep2_phi),F*ep2_p*cos(D2R*ep2_theta));

      TVector3 r1, r2;
      r1.SetXYZ(sin(D2R*ep1_theta_rich)*cos(D2R*ep1_phi_rich),sin(D2R*ep1_theta_rich)*sin(D2R*ep1_phi_rich),cos(D2R*ep1_theta_rich));
      r2.SetXYZ(sin(D2R*ep2_theta_rich)*cos(D2R*ep2_phi_rich),sin(D2R*ep2_theta_rich)*sin(D2R*ep2_phi_rich),cos(D2R*ep2_theta_rich));

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

      double e1_mass = ep1_p*ep1_p * (  1. / (ep1_beta*ep1_beta)  - 1. ) ;
      double e2_mass = ep2_p*ep2_p * (  1. / (ep2_beta*ep2_beta)  - 1. ) ;

      ACC = 1.;
      EFF = 1.;
      //float oa_corr_val;
#define SAMPLE 1
#if 0
      float new_mom, new_theta, new_phi, eff_sum, eff_sum_err;

      filter->GetAcc(  2, ep1_phi, ep1_theta, ep1_p, ep1_acc, ep1_acc_err );
      filter->GetAcc(  2, ep2_phi, ep2_theta, ep2_p, ep2_acc, ep2_acc_err );

      eff_sum = 0.;
      eff_sum_err = 0.;
      // 10 times sampling
      for (unsigned i=0; i<SAMPLE; ++i)
      {
         new_mom = filter->GetReSmearingMom(2,ep1_p/1000.);
         new_theta = filter->GetReSmearingTheta(2,ep1_p/1000.);
         new_phi = filter->GetReSmearingPhi(2,ep1_p/1000.);
         if((ep1_phi+new_phi)>360.) {
            new_phi-=360.;
         } else if (ep1_phi+new_phi<0.) {
            new_phi+=360.;
         }
         filter->GetEff(  2, ep1_phi+new_phi, ep1_theta+new_theta, ep1_p+new_mom, ep1_eff, ep1_eff_err );
         eff_sum += ep1_eff;
         eff_sum_err += ep1_eff_err;
      }
      ep1_eff = eff_sum / SAMPLE;
      ep1_eff_err = eff_sum_err / SAMPLE;

      eff_sum = 0.;
      eff_sum_err = 0.;
      // 10 times sampling
      for (unsigned i=0; i<SAMPLE; ++i)
      {
         new_mom = filter->GetReSmearingMom(3,ep2_p/1000.);
         new_theta = filter->GetReSmearingTheta(3,ep2_p/1000.);
         new_phi = filter->GetReSmearingPhi(3,ep2_p/1000.);
         if((ep2_phi+new_phi)>360.) {
            new_phi-=360.;
         } else if (ep2_phi+new_phi<0.) {
            new_phi+=360.;
         }
         filter->GetEff(  2, ep2_phi+new_phi, ep2_theta+new_theta, ep2_p+new_mom, ep2_eff, ep2_eff_err );
         eff_sum += ep2_eff;
         eff_sum_err += ep2_eff_err;
      }
      ep2_eff = eff_sum / SAMPLE;
      ep2_eff_err = eff_sum_err / SAMPLE;



    if ( ep1_eff<0.05 || ep1_eff_err>0.1 || ep1_acc_err>0.1 )
     {
        ep1_acc = 0.;
        ep1_eff = 0.;
     }
     if ( ep2_eff<0.05 || ep2_eff_err>0.1 || ep2_acc_err>0.1 )
     {
        ep2_acc = 0.;
        ep2_eff = 0.;
     }

     ACC = ep1_acc*ep2_acc > 0. ? 1./(ep1_acc*ep2_acc) : 0.;
     //EFF = ep1_eff*ep2_eff > 0. ? oa_corr_val/(ep1_eff*ep2_eff) : 0.;
#endif

     //EFF = 1.;



      gammae1e2->Boost(0., 0., -(beam->Beta()));
      e1_delta->Boost(0., 0., -(beam->Beta()));
      e2_delta->Boost(0., 0., -(beam->Beta()));

      e1_delta->Boost( -gammae1e2->Px()/gammae1e2->E(), -gammae1e2->Py()/gammae1e2->E(), -gammae1e2->Pz()/gammae1e2->E());
      e2_delta->Boost( -gammae1e2->Px()/gammae1e2->E(), -gammae1e2->Py()/gammae1e2->E(), -gammae1e2->Pz()/gammae1e2->E());

      //cout << "Poczatek obliczen..." << endl;

      double ang_cut =9.;
      //double ang_cut = 4.;
	  
      double close_cut =9.;
      double nonfit_close_cut =-4.;
      //double close_cut = 4.;

#ifdef FLANCH
      insideEp1S0 = (pEp1S0 == 0) ? 0 : pEp1S0->IsInside(ep1_z,ep1_theta);
      insideEp1S1 = (pEp1S1 == 0) ? 0 : pEp1S1->IsInside(ep1_z,ep1_theta);
      insideEp2S0 = (pEp2S0 == 0) ? 0 : pEp2S0->IsInside(ep2_z,ep2_theta);
      insideEp2S1 = (pEp2S1 == 0) ? 0 : pEp2S1->IsInside(ep2_z,ep2_theta);
      //insideEp1S0 = (pEp1S0 == 0) ? 0 : pEp1S0->IsInside(eVert_z,ep1_theta);
      //insideEp1S1 = (pEp1S1 == 0) ? 0 : pEp1S1->IsInside(eVert_z,ep1_theta);
      //insideEp2S0 = (pEp2S0 == 0) ? 0 : pEp2S0->IsInside(eVert_z,ep2_theta);
      //insideEp2S1 = (pEp2S1 == 0) ? 0 : pEp2S1->IsInside(eVert_z,ep2_theta);
#endif

#ifdef TARG
      insideTarget = ( pvertex_xy->IsInside(eVert_y, eVert_x) &&
                       pvertex_xz->IsInside(eVert_z, eVert_x) &&
                       pvertex_yz->IsInside(eVert_z, eVert_y) );
#else
      insideTarget = 1;
#endif

#ifdef RECTANG
      //insideEp1S0 = (ep1_theta > 50 && p_z < -50) ? 1 : 0;
      //insideEp1S1 = (ep1_theta > 50 && p_z < -50) ? 1 : 0;
      //insideEp2S0 = (ep2_theta > 50 && p_z < -50) ? 1 : 0;
      //insideEp2S1 = (ep2_theta > 50 && p_z < -50) ? 1 : 0;
      //insideEp1S0 = (ep1_theta > 50 && eVert_z < -50 /* && ep1_p<200.*/) ? 1 : 0;
      //insideEp1S1 = (ep1_theta > 50 && eVert_z < -50 /* && ep1_p<200.*/) ? 1 : 0;
      //insideEp2S0 = (ep2_theta > 50 && eVert_z < -50 /* && ep2_p<200.*/) ? 1 : 0;
      //insideEp2S1 = (ep2_theta > 50 && eVert_z < -50 /* && ep2_p<200.*/) ? 1 : 0;
      insideEp1S0 = (ep1_theta > 50 && ep1_z < -50 /* && ep1_p<200.*/) ? 1 : 0;
      insideEp1S1 = (ep1_theta > 50 && ep1_z < -50 /* && ep1_p<200.*/) ? 1 : 0;
      insideEp2S0 = (ep2_theta > 50 && ep2_z < -50 /* && ep2_p<200.*/) ? 1 : 0;
      insideEp2S1 = (ep2_theta > 50 && ep2_z < -50 /* && ep2_p<200.*/) ? 1 : 0;
#endif

//#ifdef NOCUT
      insideEp1S0 = 0;
      insideEp1S1 = 0;
      insideEp2S0 = 0;
      insideEp2S1 = 0;
//#endif


      NoLeptonE1 = !((ep1_oa_lept< close_cut&&ep1_oa_lept>0.0) &&ep1_oa_lept>nonfit_close_cut );
      NoHadronE1 = !(ep1_oa_hadr< close_cut &&ep1_oa_hadr>nonfit_close_cut );
      NoLeptonE2 = !((ep2_oa_lept< close_cut&&ep2_oa_lept>0.0) &&ep2_oa_lept>nonfit_close_cut );
      NoHadronE2 = !(ep2_oa_hadr< close_cut &&ep2_oa_hadr>nonfit_close_cut );
      NoHadronE1 = 1;
      NoHadronE2 = 1;


/*
      NoLeptonE1 = 1;
      NoHadronE1 = 1;
      NoLeptonE2 = 1;
      NoHadronE2 = 1;
*/

      Positron1 = (((ep1_system==0&&insideEp1S0==0)||(ep1_system==1&&insideEp1S1==0)));
      Positron2 = (((ep2_system==0&&insideEp2S0==0)||(ep2_system==1&&insideEp2S1==0)));

      PositronPositron = Positron1 && NoLeptonE1 && NoHadronE1  &&  Positron2 && NoLeptonE2 && NoHadronE2  && insideTarget &&
                         ( e1_mass < 5000. && e2_mass < 5000. );

      bool bt_ep1_condition=(ep1_isBT!=-1
			     //&& ep1_btMaxima>=2
			     && ep1_btPadsRing>=2
			    );
      bool bt_ep2_condition=(ep2_isBT!=-1
			     //&& ep2_btMaxima>=2
			     && ep2_btPadsRing>=2
			    );
      bool bt_condition=(bt_ep1_condition && bt_ep2_condition);
      bool pre_shower= (ep1_system==0?(ep1_shw_sum1+ep1_shw_sum2-ep1_shw_sum0) > (parametrization(ep1_p)):true)
	             &&(ep2_system==0?(ep2_shw_sum1+ep2_shw_sum2-ep2_shw_sum0) > (parametrization(ep2_p)):true);
      
      bool mass_condition=(ep1_p>100 && ep2_p>100 && ep1_p <2000. && ep2_p < 2000.
			   //&& ep1_p>200 && ep2_p>200
			   //&&(ep1_system==0?ep1_beta>0.95:ep1_beta>0.92)&&(ep2_system==0?ep2_beta>0.95:ep2_beta>0.92)
			   && ep1_beta<1.1 && ep2_beta<1.1
			   && ep1_beta>0.9 && ep2_beta>0.9
			   && pre_shower
			   );
      int i_array;


      if (PositronPositron && /*(((int)trigbit)&16) &&*/ isBest>=0 && oa > ang_cut)
	{
	  if( mass_condition )
	  {
	    i_array=0;
	    if(ep1_isring && !bt_ep1_condition && !ep2_isring && bt_ep2_condition)
	      i_array=1;
	    if(ep1_isring && !bt_ep1_condition && ep2_isring && bt_ep2_condition)
	      i_array=2;
	    if(ep1_isring && !bt_ep1_condition && ep2_isring && !bt_ep2_condition)
	      i_array=3;
	    if(ep1_isring && bt_ep1_condition && !ep2_isring && bt_ep2_condition)
	      i_array=4;
	    if(ep1_isring && bt_ep1_condition && ep2_isring && bt_ep2_condition)
	      i_array=5;
	    if(ep1_isring && bt_ep1_condition && ep2_isring && !bt_ep2_condition)
	      i_array=6;
	    if(!ep1_isring && bt_ep1_condition && !ep2_isring && bt_ep2_condition)
	      i_array=7;
	    if(!ep1_isring && bt_ep1_condition && ep2_isring && bt_ep2_condition)
	      i_array=8;
	    if(!ep1_isring && bt_ep1_condition && ep2_isring && !bt_ep2_condition)
	      i_array=9;

	    if(i_array!=0)
	      bt_rf_stat_back1->Fill(i_array);
	    if(m_inv_e1e2>140 && i_array!=0)
	      bt_rf_stat_pi_back1->Fill(i_array);
	      
	    if(bt_condition)
	      bt_rf_stat_back1->Fill(10);
	    if(ep1_isring && ep2_isring)
	      bt_rf_stat_back1->Fill(11);
	    if(bt_condition && ep1_isring && ep2_isring)
	      bt_rf_stat_back1->Fill(12);
	    if((bt_ep1_condition ||ep1_isring)&&(bt_ep2_condition||ep2_isring) && !(ep2_isring && ep1_isring))
	      bt_rf_stat_back1->Fill(13);
	    
	    if(m_inv_e1e2>140 && m_inv_e1e2<700)
	      {
		if(bt_condition)
		  bt_rf_stat_pi_back1->Fill(10);
		if(ep1_isring && ep2_isring)
		  bt_rf_stat_pi_back1->Fill(11);
		if(bt_condition && ep1_isring && ep2_isring)
		  bt_rf_stat_pi_back1->Fill(12);
		if((bt_ep1_condition ||ep1_isring)&&(bt_ep2_condition||ep2_isring) && !(ep2_isring && ep1_isring))
		  bt_rf_stat_pi_back1->Fill(13);
	      }
	    
	    if(m_inv_e1e2<140)
	      {
		if(bt_condition )
		  bt_rf_stat_back1->Fill(14);
		if(ep1_isring && ep2_isring )
		  bt_rf_stat_back1->Fill(15);
		if((bt_ep1_condition ||ep1_isring)&&(bt_ep2_condition||ep2_isring) && !(ep2_isring && ep1_isring))
		  bt_rf_stat_back1->Fill(16);
	      }
	    if(m_inv_e1e2>700)
	      {
		if(bt_condition )
		  bt_rf_stat_back1->Fill(17);
		if(ep1_isring && ep2_isring)
		  bt_rf_stat_back1->Fill(18);
		if((bt_ep1_condition ||ep1_isring)&&(bt_ep2_condition||ep2_isring) && !(ep2_isring && ep1_isring))
		  bt_rf_stat_back1->Fill(19);
	      }
	    if(m_inv_e1e2>140 && m_inv_e1e2<700)
	      {
		if(bt_condition )
		  bt_rf_stat_back1->Fill(20);
		if(ep1_isring && ep2_isring)
		  bt_rf_stat_back1->Fill(21);
		if((bt_ep1_condition ||ep1_isring)&&(bt_ep2_condition||ep2_isring) && !(ep2_isring && ep1_isring))
		  bt_rf_stat_back1->Fill(22);
	      }
	  }

	  if(ep1_isring>0 && ep2_isring>0 && mass_condition)
	    if(bt_condition)
	      {
		sig_rf_and_bt_back1->Fill(m_inv_e1e2/1000., EFF );
	      }
	  
	  if(ep1_isring>0 && ep2_isring>0 && mass_condition)
	    { // [1]
	    sig_all_back1->Fill(m_inv_e1e2/1000., EFF );
            sig_all_var_back1->Fill(m_inv_e1e2/1000., EFF );
	    //ep2_mom->Fill(ep2_p);
	    //ep1_mom->Fill(ep1_p);
            //ep1_beta_mom->Fill( ep1_beta_new, ep1_p, EFF );
            //ep2_beta_mom->Fill( ep2_beta_new, ep2_p, EFF );
	    }
	  if(mass_condition && (bt_ep1_condition ||ep1_isring)&&(bt_ep2_condition||ep2_isring) && !(ep2_isring && ep1_isring))//pure backtracking signal
	    {
	      pureBT_signal_back1->Fill(m_inv_e1e2/1000., EFF );
	      pureBT_signal_back1_var->Fill(m_inv_e1e2/1000., EFF );
	      if(ep1_isBT!=-1)
		{
		  //pureBT_beta_mom_back1->Fill( ep1_beta_new, ep1_p, EFF );
		  //pureBT_beta_mom->Fill( ep1_beta_new, ep1_p, EFF );
		}
	      if(ep2_isBT!=-1)
		{
		  // pureBT_beta_mom_back1->Fill( ep2_beta_new, ep1_p, EFF );
		//pureBT_beta_mom->Fill( ep2_beta_new, ep2_p, EFF );
		}
	    }
	  if ( mass_condition )  
	    if (  bt_condition )
	      { // [2]
	      //if ( (ep1_isBT != -1 && ep2_isBT != -1) ) { // [3]
	      //if ( (ep1_isBT != -1 || ep2_isBT != -1) && !(ep1_isring>0 && ep2_isring>0) ) { // [4]
	      //if ( (ep1_isBT != -1 || ep1_isring>0) && (ep2_isBT != -1 || ep2_isring>0) ) { // [5]
	      //if ( (ep1_isBT != -1 && ep2_isBT != -1) && !(ep1_isring>0 && ep2_isring>0) ) { // [6]

	      //if ( (ep1_isBT != -1 || ep2_isBT != -1) ) { // [2]
	      //iF ( (ep1_isBT != -1 && ep2_isBT != -1) ) { // [3]
	      //if ( (ep1_isBT != -1 || ep2_isBT != -1) && !(ep1_isring>0 && ep2_isring>0) ) { // [4]
	      //if ( (ep1_isBT != -1 || ep1_isring>0) && (ep2_isBT != -1 || ep2_isring>0) ) { // [5]
	      //if ( (ep1_isBT != -1 && ep2_isBT != -1) && !(ep1_isring>0 && ep2_isring>0) ) { // [6]
	      //if ( (ep1_isBT != -1 && ep2_isBT != -1) && (ep1_isring>0 && ep2_isring>0) ) { // [7]
	      //if ( !(ep1_isBT != -1 && ep2_isBT != -1) && (ep1_isring>0 && ep2_isring>0) ) { // [8]
	      sig_all_bt_back1->Fill(m_inv_e1e2/1000., EFF );
	      sig_all_var_bt_back1->Fill(m_inv_e1e2/1000., EFF );
	      //ep1_beta_mom_bt->Fill( ep1_beta_new, ep1_p, EFF );
	      //ep2_beta_mom_bt->Fill( ep2_beta_new, ep2_p, EFF );
	      //ep2_mom_bt->Fill(ep2_p);
	      //ep1_mom_bt->Fill(ep1_p);
	      }
	  /*
	    (*tlo)["ep_OAmom"] = ep1_p;
	    (*tlo)["ep_theta"] = ep1_theta;
	    (*tlo)["ep_theta_rich"] = ep1_theta_rich;
	    (*tlo)["ep_phi"] = ep1_phi;
	    (*tlo)["ep_phi_rich"] = ep1_phi_rich;
	    (*tlo)["ep_beta"] = ep1_beta_new;
	    (*tlo)["ep2_mom"] = ep2_p;
	    (*tlo)["ep2_theta"] = ep2_theta;
	    (*tlo)["ep2_theta_rich"] = ep2_theta_rich;
	    (*tlo)["ep2_phi"] = ep2_phi;
	    (*tlo)["ep2_phi_rich"] = ep2_phi_rich;
	    (*tlo)["ep2_beta"] = ep2_beta_new;
	    (*tlo)["oa"] = oa;
	    (*tlo)["oa_rich"] = oa_rich;
	    (*tlo)["sig"] = -1;
	    (*tlo)["ep_m"] = e1_mass;
	    (*tlo)["ep2_m"] = e2_mass;
	    (*tlo)["epep2_inv_mass"] = m_inv_e1e2 / 1000.;
	    (*tlo)["epep2_inv_mass2"] = m2_inv_e1e2 / 1000000.;
	    (*tlo)["epep2_miss_mass"] = e1e2_miss->M() / 1000.;
	    (*tlo)["epep2_miss_mass2"] = e1e2_miss->M2() / 1000000.;
	    (*tlo)["epep2_y"] = e1e2->Rapidity();
	    (*tlo)["epep2_pt"] = e1e2->Pt() / 1000.;

	    (*tlo)["ep_rich_amp"] = ep1_rich_amp;
	    (*tlo)["ep_rich_centr"] = ep1_rich_centr;
	    (*tlo)["ep_rich_padnum"] = ep1_rich_padnum;
	    (*tlo)["ep_rich_patmat"] = ep1_rich_patmat;
	    (*tlo)["ep_rich_houtra"] = ep1_rich_houtra;
	    (*tlo)["ep2_rich_amp"] = ep2_rich_amp;
	    (*tlo)["ep2_rich_centr"] = ep2_rich_centr;
	    (*tlo)["ep2_rich_padnum"] = ep2_rich_padnum;
	    (*tlo)["ep2_rich_patmat"] = ep2_rich_patmat;
	    (*tlo)["ep2_rich_houtra"] = ep2_rich_houtra;

	    (*tlo)["eVert_x"] = eVert_x;
	    (*tlo)["eVert_y"] = eVert_y;
	    (*tlo)["eVert_z"] = eVert_z;

	    (*tlo)["eVertReco_z"] = eVertReco_z;
	    (*tlo)["eVertReco_x"] = eVertReco_x;
	    (*tlo)["eVertReco_y"] = eVertReco_y;
	    (*tlo)["evtPileupMeta"] = evtPileupMeta;
	    (*tlo)["evtPileupStart"] = evtPileupStart;
	    (*tlo)["ep_isOffVertexClust"] = ep1_isOffVertexClust;
	    (*tlo)["ep_p_corr_ep"] = ep1_p_corr_ep;
	    (*tlo)["ep2_isOffVertexClust"] = ep2_isOffVertexClust;
	    (*tlo)["ep2_p_corr_ep2"] = ep2_p_corr_ep;
	  */


	  //tlo->fill();
	}


   }
}



// --------------------------------------------------------------------------------------------
EpEp::EpEp(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.

   ep1_acc = ep1_acc_err = ep2_acc = ep2_acc_err = 0.;
   ep1_eff = ep1_eff_err = ep2_eff = ep2_eff_err = 0.;


   if (tree == 0) {

      TChain * chain = new TChain("EpEp_ID","");
      //chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT/FILES/288/day288.root/EpEp_ID");
      //chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT/FILES/288_new/lepton288new.root/EpEp_ID");
      //chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT/FILES/288_new_pcut/lepton288new_p.root/EpEp_ID");
      //chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT/FILES/288_new_std/dilepton_sep08_KN.root/EpEp_ID");
      //chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT/FILES/sep08_all/sep08_lepton_all.root/EpEm_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_epem/FILES/sep08_all/list5/sum5.root/EpEp_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_epem/FILES/sep08_all/list4/sum4.root/Ep_Ep_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_epem/FILES/sep08_all/list3/sum3.root/Ep_Ep_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_epem/FILES/sep08_all/list2/sum2.root/Ep_Ep_ID");
      chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_epem/FILES/sep08_all/list1/sum1.root/Ep_Ep_ID");

      //chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/lepton656.root/EpEp_ID");
      //chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/lepton690.root/EpEp_ID");
      //chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/lepton748.root/EpEp_ID");
      //chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/lepton800.root/EpEp_ID");


      // -- PE 690 ----------------------------------------
      /*      
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/196/lepton196.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/197/lepton197.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/198/lepton198.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/232/lepton232.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/233/lepton233.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/234/lepton234.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/235/lepton235.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/236/lepton236.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/237/lepton237.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/238/lepton238.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/239/lepton239.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/240/lepton240.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/241/lepton241.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/242/lepton242.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/243/lepton243.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/244/lepton244.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/245/lepton245.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/246/lepton246.root/EpEp_ID");
      */ 
/*
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/196/lepton196.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/197/lepton197.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/198/lepton198.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/232/lepton232.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/233/lepton233.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/234/lepton234.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/235/lepton235.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/236/lepton236.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/237/lepton237.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/238/lepton238.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/239/lepton239.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/240/lepton240.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/241/lepton241.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/242/lepton242.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/243/lepton243.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/244/lepton244.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/245/lepton245.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/246/lepton246.root/EpEp_ID");
*/
      // -- PE 656 ----------------------------------------
      /*
       chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/247/656/lepton247_656.root/EpEp_ID");
       chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/248/656/lepton248_656.root/EpEp_ID");
       chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/249/656/lepton249_656.root/EpEp_ID");
      */
/*
       chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/247/656/lepton247_656.root/EpEp_ID");
       chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/248/656/lepton248_656.root/EpEp_ID");
       chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/249/656/lepton249_656.root/EpEp_ID");
*/
      // -- PE 748 ----------------------------------------
      /*
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/246/748/lepton246_748.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/247/748/lepton247_748.root/EpEp_ID");
      */
/*
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/246/748/lepton246_748.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/247/748/lepton247_748.root/EpEp_ID");
*/
      // -- PE 800 ----------------------------------------
      /*
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/249/800/lepton249_800.root/EpEp_ID");
      */
/*
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/249/800/lepton249_800.root/EpEp_ID");
*/
      // --  C 656 ----------------------------------------
      /*
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/252/656/lepton252_656.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/253/656/lepton253_656.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/254/656/lepton254_656.root/EpEp_ID");
      */
/*
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/252/656/lepton252_656.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/253/656/lepton253_656.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/254/656/lepton254_656.root/EpEp_ID");
*/
      // --  C 690 ----------------------------------------
      /*
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/195/lepton195.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/250/lepton250.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/251/lepton251.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/254/lepton254.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/255/lepton255.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/256/lepton256.root/EpEp_ID");
      */

      //chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/195/lepton195.root/EpEp_ID");
      //chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/250/lepton250.root/EpEp_ID");
      //chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/251/lepton251.root/EpEp_ID");
      //chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/254/lepton254.root/EpEp_ID");
      //chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/255/lepton255.root/EpEp_ID");
      //chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/256/lepton256.root/EpEp_ID");

      // --  C 748 ----------------------------------------
      /*
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/252/748/lepton252_748.root/EpEp_ID");
      */
/*
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/252/748/lepton252_748.root/EpEp_ID");
*/
      // --  C 800 ----------------------------------------
      
      //chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/251/800/lepton251_800.root/EpEp_ID");
      //chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/LEPTONS/252/800/lepton252_800.root/EpEp_ID");
      
      /*
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/251/800/lepton251_800.root/EpEp_ID");
      chain->Add("/hera/hades/user/przygoda/PAT2/out/exp/gen1/252/800/lepton252_800.root/EpEp_ID");
      */

     
      tree = chain;

   }
   Init(tree);
}

// --------------------------------------------------------------------------------------------
EpEp::~EpEp()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

// --------------------------------------------------------------------------------------------
Int_t EpEp::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

// --------------------------------------------------------------------------------------------
Long64_t EpEp::LoadTree(Long64_t entry)
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

// --------------------------------------------------------------------------------------------
void EpEp::Init(TTree *tree)
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
   fChain->SetBranchAddress("ep1_beta", &ep1_beta, &b_ep1_beta);
   fChain->SetBranchAddress("ep1_beta_new", &ep1_beta_new, &b_ep1_beta_new);
   fChain->SetBranchAddress("ep1_btChargeRing", &ep1_btChargeRing, &b_ep1_btChargeRing);
   fChain->SetBranchAddress("ep1_btChargeSum", &ep1_btChargeSum, &b_ep1_btChargeSum);
   fChain->SetBranchAddress("ep1_btChi2", &ep1_btChi2, &b_ep1_btChi2);
   fChain->SetBranchAddress("ep1_btClusters", &ep1_btClusters, &b_ep1_btClusters);
   fChain->SetBranchAddress("ep1_btMaxima", &ep1_btMaxima, &b_ep1_btMaxima);
   fChain->SetBranchAddress("ep1_btMaximaCharge", &ep1_btMaximaCharge, &b_ep1_btMaximaCharge);
   fChain->SetBranchAddress("ep1_btMaximaChargeShared", &ep1_btMaximaChargeShared, &b_ep1_btMaximaChargeShared);
   fChain->SetBranchAddress("ep1_btMaximaChargeSharedFragment", &ep1_btMaximaChargeSharedFragment, &b_ep1_btMaximaChargeSharedFragment);
   fChain->SetBranchAddress("ep1_btMaximaShared", &ep1_btMaximaShared, &b_ep1_btMaximaShared);
   fChain->SetBranchAddress("ep1_btMaximaSharedFragment", &ep1_btMaximaSharedFragment, &b_ep1_btMaximaSharedFragment);
   fChain->SetBranchAddress("ep1_btMeanDist", &ep1_btMeanDist, &b_ep1_btMeanDist);
   fChain->SetBranchAddress("ep1_btNearbyMaxima", &ep1_btNearbyMaxima, &b_ep1_btNearbyMaxima);
   fChain->SetBranchAddress("ep1_btNearbyMaximaShared", &ep1_btNearbyMaximaShared, &b_ep1_btNearbyMaximaShared);
   fChain->SetBranchAddress("ep1_btPadsClus", &ep1_btPadsClus, &b_ep1_btPadsClus);
   fChain->SetBranchAddress("ep1_btPadsRing", &ep1_btPadsRing, &b_ep1_btPadsRing);
   fChain->SetBranchAddress("ep1_btRingMatrix", &ep1_btRingMatrix, &b_ep1_btRingMatrix);
   fChain->SetBranchAddress("ep1_dedx_mdc", &ep1_dedx_mdc, &b_ep1_dedx_mdc);
   fChain->SetBranchAddress("ep1_dedx_tof", &ep1_dedx_tof, &b_ep1_dedx_tof);
   fChain->SetBranchAddress("ep1_id", &ep1_id, &b_ep1_id);
   fChain->SetBranchAddress("ep1_isBT", &ep1_isBT, &b_ep1_isBT);
   fChain->SetBranchAddress("ep1_isOffVertexClust", &ep1_isOffVertexClust, &b_ep1_isOffVertexClust);
   fChain->SetBranchAddress("ep1_isPrimaryVertex", &ep1_isPrimaryVertex, &b_ep1_isPrimaryVertex);
   fChain->SetBranchAddress("ep1_isUsedVertex", &ep1_isUsedVertex, &b_ep1_isUsedVertex);
   fChain->SetBranchAddress("ep1_isring", &ep1_isring, &b_ep1_isring);
   fChain->SetBranchAddress("ep1_isringmdc", &ep1_isringmdc, &b_ep1_isringmdc);
   fChain->SetBranchAddress("ep1_isringnomatch", &ep1_isringnomatch, &b_ep1_isringnomatch);
   fChain->SetBranchAddress("ep1_isringtrack", &ep1_isringtrack, &b_ep1_isringtrack);
   fChain->SetBranchAddress("ep1_kIsLepton", &ep1_kIsLepton, &b_ep1_kIsLepton);
   fChain->SetBranchAddress("ep1_kIsUsed", &ep1_kIsUsed, &b_ep1_kIsUsed);
   fChain->SetBranchAddress("ep1_mdcinnerchi2", &ep1_mdcinnerchi2, &b_ep1_mdcinnerchi2);
   fChain->SetBranchAddress("ep1_mdcouterchi2", &ep1_mdcouterchi2, &b_ep1_mdcouterchi2);
   fChain->SetBranchAddress("ep1_oa_hadr", &ep1_oa_hadr, &b_ep1_oa_hadr);
   fChain->SetBranchAddress("ep1_oa_lept", &ep1_oa_lept, &b_ep1_oa_lept);
   fChain->SetBranchAddress("ep1_p", &ep1_p, &b_ep1_p);
   fChain->SetBranchAddress("ep1_p_corr_em", &ep1_p_corr_em, &b_ep1_p_corr_em);
   fChain->SetBranchAddress("ep1_p_corr_ep", &ep1_p_corr_ep, &b_ep1_p_corr_ep);
   fChain->SetBranchAddress("ep1_p_corr_p", &ep1_p_corr_p, &b_ep1_p_corr_p);
   fChain->SetBranchAddress("ep1_p_corr_pim", &ep1_p_corr_pim, &b_ep1_p_corr_pim);
   fChain->SetBranchAddress("ep1_p_corr_pip", &ep1_p_corr_pip, &b_ep1_p_corr_pip);
   fChain->SetBranchAddress("ep1_phi", &ep1_phi, &b_ep1_phi);
   fChain->SetBranchAddress("ep1_phi_rich", &ep1_phi_rich, &b_ep1_phi_rich);
   fChain->SetBranchAddress("ep1_pid", &ep1_pid, &b_ep1_pid);
   fChain->SetBranchAddress("ep1_q", &ep1_q, &b_ep1_q);
   fChain->SetBranchAddress("ep1_r", &ep1_r, &b_ep1_r);
   fChain->SetBranchAddress("ep1_resolution", &ep1_resolution, &b_ep1_resolution);
   fChain->SetBranchAddress("ep1_resoultion", &ep1_resoultion, &b_ep1_resoultion);
   fChain->SetBranchAddress("ep1_rich_amp", &ep1_rich_amp, &b_ep1_rich_amp);
   fChain->SetBranchAddress("ep1_rich_centr", &ep1_rich_centr, &b_ep1_rich_centr);
   fChain->SetBranchAddress("ep1_rich_houtra", &ep1_rich_houtra, &b_ep1_rich_houtra);
   fChain->SetBranchAddress("ep1_rich_padnum", &ep1_rich_padnum, &b_ep1_rich_padnum);
   fChain->SetBranchAddress("ep1_rich_patmat", &ep1_rich_patmat, &b_ep1_rich_patmat);
   fChain->SetBranchAddress("ep1_rkchi2", &ep1_rkchi2, &b_ep1_rkchi2);
   fChain->SetBranchAddress("ep1_sector", &ep1_sector, &b_ep1_sector);
   fChain->SetBranchAddress("ep1_shw_sum0", &ep1_shw_sum0, &b_ep1_shw_sum0);
   fChain->SetBranchAddress("ep1_shw_sum1", &ep1_shw_sum1, &b_ep1_shw_sum1);
   fChain->SetBranchAddress("ep1_shw_sum2", &ep1_shw_sum2, &b_ep1_shw_sum2);
   fChain->SetBranchAddress("ep1_system", &ep1_system, &b_ep1_system);
   fChain->SetBranchAddress("ep1_theta", &ep1_theta, &b_ep1_theta);
   fChain->SetBranchAddress("ep1_theta_rich", &ep1_theta_rich, &b_ep1_theta_rich);
   fChain->SetBranchAddress("ep1_tof_mom", &ep1_tof_mom, &b_ep1_tof_mom);
   fChain->SetBranchAddress("ep1_tof_new", &ep1_tof_new, &b_ep1_tof_new);
   fChain->SetBranchAddress("ep1_tof_rec", &ep1_tof_rec, &b_ep1_tof_rec);
   fChain->SetBranchAddress("ep1_track_length", &ep1_track_length, &b_ep1_track_length);
   fChain->SetBranchAddress("ep1_tracklength", &ep1_tracklength, &b_ep1_tracklength);
   fChain->SetBranchAddress("ep1_z", &ep1_z, &b_ep1_z);
   fChain->SetBranchAddress("ep2_beta", &ep2_beta, &b_ep2_beta);
   fChain->SetBranchAddress("ep2_beta_new", &ep2_beta_new, &b_ep2_beta_new);
   fChain->SetBranchAddress("ep2_btChargeRing", &ep2_btChargeRing, &b_ep2_btChargeRing);
   fChain->SetBranchAddress("ep2_btChargeSum", &ep2_btChargeSum, &b_ep2_btChargeSum);
   fChain->SetBranchAddress("ep2_btChi2", &ep2_btChi2, &b_ep2_btChi2);
   fChain->SetBranchAddress("ep2_btClusters", &ep2_btClusters, &b_ep2_btClusters);
   fChain->SetBranchAddress("ep2_btMaxima", &ep2_btMaxima, &b_ep2_btMaxima);
   fChain->SetBranchAddress("ep2_btMaximaCharge", &ep2_btMaximaCharge, &b_ep2_btMaximaCharge);
   fChain->SetBranchAddress("ep2_btMaximaChargeShared", &ep2_btMaximaChargeShared, &b_ep2_btMaximaChargeShared);
   fChain->SetBranchAddress("ep2_btMaximaChargeSharedFragment", &ep2_btMaximaChargeSharedFragment, &b_ep2_btMaximaChargeSharedFragment);
   fChain->SetBranchAddress("ep2_btMaximaShared", &ep2_btMaximaShared, &b_ep2_btMaximaShared);
   fChain->SetBranchAddress("ep2_btMaximaSharedFragment", &ep2_btMaximaSharedFragment, &b_ep2_btMaximaSharedFragment);
   fChain->SetBranchAddress("ep2_btMeanDist", &ep2_btMeanDist, &b_ep2_btMeanDist);
   fChain->SetBranchAddress("ep2_btNearbyMaxima", &ep2_btNearbyMaxima, &b_ep2_btNearbyMaxima);
   fChain->SetBranchAddress("ep2_btNearbyMaximaShared", &ep2_btNearbyMaximaShared, &b_ep2_btNearbyMaximaShared);
   fChain->SetBranchAddress("ep2_btPadsClus", &ep2_btPadsClus, &b_ep2_btPadsClus);
   fChain->SetBranchAddress("ep2_btPadsRing", &ep2_btPadsRing, &b_ep2_btPadsRing);
   fChain->SetBranchAddress("ep2_btRingMatrix", &ep2_btRingMatrix, &b_ep2_btRingMatrix);
   fChain->SetBranchAddress("ep2_dedx_mdc", &ep2_dedx_mdc, &b_ep2_dedx_mdc);
   fChain->SetBranchAddress("ep2_dedx_tof", &ep2_dedx_tof, &b_ep2_dedx_tof);
   fChain->SetBranchAddress("ep2_isBT", &ep2_isBT, &b_ep2_isBT);
   fChain->SetBranchAddress("ep2_id", &ep2_id, &b_ep2_id);
   fChain->SetBranchAddress("ep2_isOffVertexClust", &ep2_isOffVertexClust, &b_ep2_isOffVertexClust);
   fChain->SetBranchAddress("ep2_isPrimaryVertex", &ep2_isPrimaryVertex, &b_ep2_isPrimaryVertex);
   fChain->SetBranchAddress("ep2_isUsedVertex", &ep2_isUsedVertex, &b_ep2_isUsedVertex);
   fChain->SetBranchAddress("ep2_isring", &ep2_isring, &b_ep2_isring);
   fChain->SetBranchAddress("ep2_isringmdc", &ep2_isringmdc, &b_ep2_isringmdc);
   fChain->SetBranchAddress("ep2_isringnomatch", &ep2_isringnomatch, &b_ep2_isringnomatch);
   fChain->SetBranchAddress("ep2_isringtrack", &ep2_isringtrack, &b_ep2_isringtrack);
   fChain->SetBranchAddress("ep2_kIsLepton", &ep2_kIsLepton, &b_ep2_kIsLepton);
   fChain->SetBranchAddress("ep2_kIsUsed", &ep2_kIsUsed, &b_ep2_kIsUsed);
   fChain->SetBranchAddress("ep2_mdcinnerchi2", &ep2_mdcinnerchi2, &b_ep2_mdcinnerchi2);
   fChain->SetBranchAddress("ep2_mdcouterchi2", &ep2_mdcouterchi2, &b_ep2_mdcouterchi2);
   fChain->SetBranchAddress("ep2_oa_hadr", &ep2_oa_hadr, &b_ep2_oa_hadr);
   fChain->SetBranchAddress("ep2_oa_lept", &ep2_oa_lept, &b_ep2_oa_lept);
   fChain->SetBranchAddress("ep2_p", &ep2_p, &b_ep2_p);
   fChain->SetBranchAddress("ep2_p_corr_em", &ep2_p_corr_em, &b_ep2_p_corr_em);
   fChain->SetBranchAddress("ep2_p_corr_ep", &ep2_p_corr_ep, &b_ep2_p_corr_ep);
   fChain->SetBranchAddress("ep2_p_corr_p", &ep2_p_corr_p, &b_ep2_p_corr_p);
   fChain->SetBranchAddress("ep2_p_corr_pim", &ep2_p_corr_pim, &b_ep2_p_corr_pim);
   fChain->SetBranchAddress("ep2_p_corr_pip", &ep2_p_corr_pip, &b_ep2_p_corr_pip);
   fChain->SetBranchAddress("ep2_phi", &ep2_phi, &b_ep2_phi);
   fChain->SetBranchAddress("ep2_phi_rich", &ep2_phi_rich, &b_ep2_phi_rich);
   fChain->SetBranchAddress("ep2_pid", &ep2_pid, &b_ep2_pid);
   fChain->SetBranchAddress("ep2_q", &ep2_q, &b_ep2_q);
   fChain->SetBranchAddress("ep2_r", &ep2_r, &b_ep2_r);
   fChain->SetBranchAddress("ep2_resolution", &ep2_resolution, &b_ep2_resolution);
   fChain->SetBranchAddress("ep2_resoultion", &ep2_resoultion, &b_ep2_resoultion);
   fChain->SetBranchAddress("ep2_rich_amp", &ep2_rich_amp, &b_ep2_rich_amp);
   fChain->SetBranchAddress("ep2_rich_centr", &ep2_rich_centr, &b_ep2_rich_centr);
   fChain->SetBranchAddress("ep2_rich_houtra", &ep2_rich_houtra, &b_ep2_rich_houtra);
   fChain->SetBranchAddress("ep2_rich_padnum", &ep2_rich_padnum, &b_ep2_rich_padnum);
   fChain->SetBranchAddress("ep2_rich_patmat", &ep2_rich_patmat, &b_ep2_rich_patmat);
   fChain->SetBranchAddress("ep2_rkchi2", &ep2_rkchi2, &b_ep2_rkchi2);
   fChain->SetBranchAddress("ep2_sector", &ep2_sector, &b_ep2_sector);
   fChain->SetBranchAddress("ep2_shw_sum0", &ep2_shw_sum0, &b_ep2_shw_sum0);
   fChain->SetBranchAddress("ep2_shw_sum1", &ep2_shw_sum1, &b_ep2_shw_sum1);
   fChain->SetBranchAddress("ep2_shw_sum2", &ep2_shw_sum2, &b_ep2_shw_sum2);
   fChain->SetBranchAddress("ep2_system", &ep2_system, &b_ep2_system);
   fChain->SetBranchAddress("ep2_theta", &ep2_theta, &b_ep2_theta);
   fChain->SetBranchAddress("ep2_theta_rich", &ep2_theta_rich, &b_ep2_theta_rich);
   fChain->SetBranchAddress("ep2_tof_mom", &ep2_tof_mom, &b_ep2_tof_mom);
   fChain->SetBranchAddress("ep2_tof_new", &ep2_tof_new, &b_ep2_tof_new);
   fChain->SetBranchAddress("ep2_tof_rec", &ep2_tof_rec, &b_ep2_tof_rec);
   fChain->SetBranchAddress("ep2_track_length", &ep2_track_length, &b_ep2_track_length);
   fChain->SetBranchAddress("ep2_tracklength", &ep2_tracklength, &b_ep2_tracklength);
   fChain->SetBranchAddress("ep2_z", &ep2_z, &b_ep2_z);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("evtFlashMDC", &evtFlashMDC, &b_evtFlashMDC);
   fChain->SetBranchAddress("evtGood", &evtGood, &b_evtGood);
   fChain->SetBranchAddress("evtGoodTrig", &evtGoodTrig, &b_evtGoodTrig);
   fChain->SetBranchAddress("evtLepMult", &evtLepMult, &b_evtLepMult);
   fChain->SetBranchAddress("evtMDCMult", &evtMDCMult, &b_evtMDCMult);
   fChain->SetBranchAddress("evtPileupMDC", &evtPileupMDC, &b_evtPileupMDC);
   fChain->SetBranchAddress("evtPileupMeta", &evtPileupMeta, &b_evtPileupMeta);
   fChain->SetBranchAddress("evtPileupStart", &evtPileupStart, &b_evtPileupStart);
   fChain->SetBranchAddress("evtStart", &evtStart, &b_evtStart);
   fChain->SetBranchAddress("evtVertCand", &evtVertCand, &b_evtVertCand);
   fChain->SetBranchAddress("evtVertClust", &evtVertClust, &b_evtVertClust);
   fChain->SetBranchAddress("fw_beta_1", &fw_beta_1, &b_fw_beta_1);
   fChain->SetBranchAddress("fw_beta_2", &fw_beta_2, &b_fw_beta_2);
   fChain->SetBranchAddress("fw_beta_3", &fw_beta_3, &b_fw_beta_3);
   fChain->SetBranchAddress("fw_charge_1", &fw_charge_1, &b_fw_charge_1);
   fChain->SetBranchAddress("fw_charge_2", &fw_charge_2, &b_fw_charge_2);
   fChain->SetBranchAddress("fw_charge_3", &fw_charge_3, &b_fw_charge_3);
   fChain->SetBranchAddress("fw_cluster_mult", &fw_cluster_mult, &b_fw_cluster_mult);
   fChain->SetBranchAddress("fw_distance_1", &fw_distance_1, &b_fw_distance_1);
   fChain->SetBranchAddress("fw_distance_2", &fw_distance_2, &b_fw_distance_2);
   fChain->SetBranchAddress("fw_distance_3", &fw_distance_3, &b_fw_distance_3);
   fChain->SetBranchAddress("fw_mult", &fw_mult, &b_fw_mult);
   fChain->SetBranchAddress("fw_p_1", &fw_p_1, &b_fw_p_1);
   fChain->SetBranchAddress("fw_p_2", &fw_p_2, &b_fw_p_2);
   fChain->SetBranchAddress("fw_p_3", &fw_p_3, &b_fw_p_3);
   fChain->SetBranchAddress("fw_phi_1", &fw_phi_1, &b_fw_phi_1);
   fChain->SetBranchAddress("fw_phi_2", &fw_phi_2, &b_fw_phi_2);
   fChain->SetBranchAddress("fw_phi_3", &fw_phi_3, &b_fw_phi_3);
   fChain->SetBranchAddress("fw_size_1", &fw_size_1, &b_fw_size_1);
   fChain->SetBranchAddress("fw_size_2", &fw_size_2, &b_fw_size_2);
   fChain->SetBranchAddress("fw_size_3", &fw_size_3, &b_fw_size_3);
   fChain->SetBranchAddress("fw_spectator_1", &fw_spectator_1, &b_fw_spectator_1);
   fChain->SetBranchAddress("fw_spectator_2", &fw_spectator_2, &b_fw_spectator_2);
   fChain->SetBranchAddress("fw_spectator_3", &fw_spectator_3, &b_fw_spectator_3);
   fChain->SetBranchAddress("fw_theta_1", &fw_theta_1, &b_fw_theta_1);
   fChain->SetBranchAddress("fw_theta_2", &fw_theta_2, &b_fw_theta_2);
   fChain->SetBranchAddress("fw_theta_3", &fw_theta_3, &b_fw_theta_3);
   fChain->SetBranchAddress("fw_time_1", &fw_time_1, &b_fw_time_1);
   fChain->SetBranchAddress("fw_time_2", &fw_time_2, &b_fw_time_2);
   fChain->SetBranchAddress("fw_time_3", &fw_time_3, &b_fw_time_3);
   fChain->SetBranchAddress("fw_time_min_1", &fw_time_min_1, &b_fw_time_min_1);
   fChain->SetBranchAddress("fw_time_min_2", &fw_time_min_2, &b_fw_time_min_2);
   fChain->SetBranchAddress("fw_time_min_3", &fw_time_min_3, &b_fw_time_min_3);
   fChain->SetBranchAddress("fw_x_lab_1", &fw_x_lab_1, &b_fw_x_lab_1);
   fChain->SetBranchAddress("fw_x_lab_2", &fw_x_lab_2, &b_fw_x_lab_2);
   fChain->SetBranchAddress("fw_x_lab_3", &fw_x_lab_3, &b_fw_x_lab_3);
   fChain->SetBranchAddress("fw_y_lab_1", &fw_y_lab_1, &b_fw_y_lab_1);
   fChain->SetBranchAddress("fw_y_lab_2", &fw_y_lab_2, &b_fw_y_lab_2);
   fChain->SetBranchAddress("fw_y_lab_3", &fw_y_lab_3, &b_fw_y_lab_3);
   fChain->SetBranchAddress("fw_z_lab_1", &fw_z_lab_1, &b_fw_z_lab_1);
   fChain->SetBranchAddress("fw_z_lab_2", &fw_z_lab_2, &b_fw_z_lab_2);
   fChain->SetBranchAddress("fw_z_lab_3", &fw_z_lab_3, &b_fw_z_lab_3);
   fChain->SetBranchAddress("hneg_mult", &hneg_mult, &b_hneg_mult);
   fChain->SetBranchAddress("hpos_mult", &hpos_mult, &b_hpos_mult);
   fChain->SetBranchAddress("isBest", &isBest, &b_isBest);
   fChain->SetBranchAddress("lneg_mult", &lneg_mult, &b_lneg_mult);
   fChain->SetBranchAddress("lpos_mult", &lpos_mult, &b_lpos_mult);
   fChain->SetBranchAddress("pt_costh_1", &pt_costh_1, &b_pt_costh_1);
   fChain->SetBranchAddress("pt_costh_2", &pt_costh_2, &b_pt_costh_2);
   fChain->SetBranchAddress("pt_costh_3", &pt_costh_3, &b_pt_costh_3);
   fChain->SetBranchAddress("pt_costh_4", &pt_costh_4, &b_pt_costh_4);
   fChain->SetBranchAddress("pt_counter", &pt_counter, &b_pt_counter);
   fChain->SetBranchAddress("pt_match_1", &pt_match_1, &b_pt_match_1);
   fChain->SetBranchAddress("pt_match_2", &pt_match_2, &b_pt_match_2);
   fChain->SetBranchAddress("pt_match_3", &pt_match_3, &b_pt_match_3);
   fChain->SetBranchAddress("pt_match_4", &pt_match_4, &b_pt_match_4);
   fChain->SetBranchAddress("pt_mult", &pt_mult, &b_pt_mult);
   fChain->SetBranchAddress("pt_p_1", &pt_p_1, &b_pt_p_1);
   fChain->SetBranchAddress("pt_p_2", &pt_p_2, &b_pt_p_2);
   fChain->SetBranchAddress("pt_p_3", &pt_p_3, &b_pt_p_3);
   fChain->SetBranchAddress("pt_p_4", &pt_p_4, &b_pt_p_4);
   fChain->SetBranchAddress("pt_phi0_1", &pt_phi0_1, &b_pt_phi0_1);
   fChain->SetBranchAddress("pt_phi0_2", &pt_phi0_2, &b_pt_phi0_2);
   fChain->SetBranchAddress("pt_phi0_3", &pt_phi0_3, &b_pt_phi0_3);
   fChain->SetBranchAddress("pt_phi0_4", &pt_phi0_4, &b_pt_phi0_4);
   fChain->SetBranchAddress("pt_phi_1", &pt_phi_1, &b_pt_phi_1);
   fChain->SetBranchAddress("pt_phi_2", &pt_phi_2, &b_pt_phi_2);
   fChain->SetBranchAddress("pt_phi_3", &pt_phi_3, &b_pt_phi_3);
   fChain->SetBranchAddress("pt_phi_4", &pt_phi_4, &b_pt_phi_4);
   fChain->SetBranchAddress("pt_px_1", &pt_px_1, &b_pt_px_1);
   fChain->SetBranchAddress("pt_px_2", &pt_px_2, &b_pt_px_2);
   fChain->SetBranchAddress("pt_px_3", &pt_px_3, &b_pt_px_3);
   fChain->SetBranchAddress("pt_px_4", &pt_px_4, &b_pt_px_4);
   fChain->SetBranchAddress("pt_py_1", &pt_py_1, &b_pt_py_1);
   fChain->SetBranchAddress("pt_py_2", &pt_py_2, &b_pt_py_2);
   fChain->SetBranchAddress("pt_py_3", &pt_py_3, &b_pt_py_3);
   fChain->SetBranchAddress("pt_py_4", &pt_py_4, &b_pt_py_4);
   fChain->SetBranchAddress("pt_pz_1", &pt_pz_1, &b_pt_pz_1);
   fChain->SetBranchAddress("pt_pz_2", &pt_pz_2, &b_pt_pz_2);
   fChain->SetBranchAddress("pt_pz_3", &pt_pz_3, &b_pt_pz_3);
   fChain->SetBranchAddress("pt_pz_4", &pt_pz_4, &b_pt_pz_4);
   fChain->SetBranchAddress("pt_theta0_1", &pt_theta0_1, &b_pt_theta0_1);
   fChain->SetBranchAddress("pt_theta0_2", &pt_theta0_2, &b_pt_theta0_2);
   fChain->SetBranchAddress("pt_theta0_3", &pt_theta0_3, &b_pt_theta0_3);
   fChain->SetBranchAddress("pt_theta0_4", &pt_theta0_4, &b_pt_theta0_4);
   fChain->SetBranchAddress("pt_theta_1", &pt_theta_1, &b_pt_theta_1);
   fChain->SetBranchAddress("pt_theta_2", &pt_theta_2, &b_pt_theta_2);
   fChain->SetBranchAddress("pt_theta_3", &pt_theta_3, &b_pt_theta_3);
   fChain->SetBranchAddress("pt_theta_4", &pt_theta_4, &b_pt_theta_4);
   fChain->SetBranchAddress("pt_x1_1", &pt_x1_1, &b_pt_x1_1);
   fChain->SetBranchAddress("pt_x1_2", &pt_x1_2, &b_pt_x1_2);
   fChain->SetBranchAddress("pt_x1_3", &pt_x1_3, &b_pt_x1_3);
   fChain->SetBranchAddress("pt_x1_4", &pt_x1_4, &b_pt_x1_4);
   fChain->SetBranchAddress("pt_x2_1", &pt_x2_1, &b_pt_x2_1);
   fChain->SetBranchAddress("pt_x2_2", &pt_x2_2, &b_pt_x2_2);
   fChain->SetBranchAddress("pt_x2_3", &pt_x2_3, &b_pt_x2_3);
   fChain->SetBranchAddress("pt_x2_4", &pt_x2_4, &b_pt_x2_4);
   fChain->SetBranchAddress("pt_xtarg_1", &pt_xtarg_1, &b_pt_xtarg_1);
   fChain->SetBranchAddress("pt_xtarg_2", &pt_xtarg_2, &b_pt_xtarg_2);
   fChain->SetBranchAddress("pt_xtarg_3", &pt_xtarg_3, &b_pt_xtarg_3);
   fChain->SetBranchAddress("pt_xtarg_4", &pt_xtarg_4, &b_pt_xtarg_4);
   fChain->SetBranchAddress("pt_y1_1", &pt_y1_1, &b_pt_y1_1);
   fChain->SetBranchAddress("pt_y1_2", &pt_y1_2, &b_pt_y1_2);
   fChain->SetBranchAddress("pt_y1_3", &pt_y1_3, &b_pt_y1_3);
   fChain->SetBranchAddress("pt_y1_4", &pt_y1_4, &b_pt_y1_4);
   fChain->SetBranchAddress("pt_y2_1", &pt_y2_1, &b_pt_y2_1);
   fChain->SetBranchAddress("pt_y2_2", &pt_y2_2, &b_pt_y2_2);
   fChain->SetBranchAddress("pt_y2_3", &pt_y2_3, &b_pt_y2_3);
   fChain->SetBranchAddress("pt_y2_4", &pt_y2_4, &b_pt_y2_4);
   fChain->SetBranchAddress("pt_ytarg_1", &pt_ytarg_1, &b_pt_ytarg_1);
   fChain->SetBranchAddress("pt_ytarg_2", &pt_ytarg_2, &b_pt_ytarg_2);
   fChain->SetBranchAddress("pt_ytarg_3", &pt_ytarg_3, &b_pt_ytarg_3);
   fChain->SetBranchAddress("pt_ytarg_4", &pt_ytarg_4, &b_pt_ytarg_4);
   fChain->SetBranchAddress("runnumber", &runnumber, &b_runnumber);
   fChain->SetBranchAddress("start_cluster_size_1st", &start_cluster_size_1st, &b_start_cluster_size_1st);
   fChain->SetBranchAddress("start_cluster_size_2nd", &start_cluster_size_2nd, &b_start_cluster_size_2nd);
   fChain->SetBranchAddress("start_cluster_size_max", &start_cluster_size_max, &b_start_cluster_size_max);
   fChain->SetBranchAddress("start_corrflag", &start_corrflag, &b_start_corrflag);
   fChain->SetBranchAddress("start_counter", &start_counter, &b_start_counter);
   fChain->SetBranchAddress("start_flag", &start_flag, &b_start_flag);
   fChain->SetBranchAddress("start_module", &start_module, &b_start_module);
   fChain->SetBranchAddress("start_mult", &start_mult, &b_start_mult);
   fChain->SetBranchAddress("start_multipliticy", &start_multipliticy, &b_start_multipliticy);
   fChain->SetBranchAddress("start_resolution", &start_resolution, &b_start_resolution);
   fChain->SetBranchAddress("start_strip", &start_strip, &b_start_strip);
   fChain->SetBranchAddress("start_time", &start_time, &b_start_time);
   fChain->SetBranchAddress("start_time_2nd", &start_time_2nd, &b_start_time_2nd);
   fChain->SetBranchAddress("start_track", &start_track, &b_start_track);
   fChain->SetBranchAddress("start_width", &start_width, &b_start_width);
   fChain->SetBranchAddress("totalmult", &totalmult, &b_totalmult);
   fChain->SetBranchAddress("trigbit", &trigbit, &b_trigbit);
   fChain->SetBranchAddress("trigdec", &trigdec, &b_trigdec);
   fChain->SetBranchAddress("trigdownscale", &trigdownscale, &b_trigdownscale);
   fChain->SetBranchAddress("trigdownscaleflag", &trigdownscaleflag, &b_trigdownscaleflag);
   Notify();
}

// --------------------------------------------------------------------------------------------
Bool_t EpEp::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

// --------------------------------------------------------------------------------------------
void EpEp::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

// --------------------------------------------------------------------------------------------
Int_t EpEp::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

