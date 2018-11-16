#include "PPimEmEm.h"
#include "data.h"
#include <iostream>
#include <TLorentzVector.h>
#include <TVector3.h>
#include "hntuple.h"

using namespace std;
using namespace PATData;


void PPimEmEm::Loop()
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
    if ((licznik % 100000)==0) cout << "PPimEmEm Events: " << licznik << endl;

  
    double F = 1.006;
    TVector3 v1, v2, v3;
    v2.SetXYZ(F*em1_p*sin(D2R*em1_theta)*cos(D2R*em1_phi),F*em1_p*sin(D2R*em1_theta)*sin(D2R*em1_phi),F*em1_p*cos(D2R*em1_theta));
    v3.SetXYZ(F*em2_p*sin(D2R*em2_theta)*cos(D2R*em2_phi),F*em2_p*sin(D2R*em2_theta)*sin(D2R*em2_phi),F*em2_p*cos(D2R*em2_theta));

    TVector3 r1, r2;
    r1.SetXYZ(sin(D2R*em1_theta_rich)*cos(D2R*em1_phi_rich),sin(D2R*em1_theta_rich)*sin(D2R*em1_phi_rich),cos(D2R*em1_theta_rich));
    r2.SetXYZ(sin(D2R*em2_theta_rich)*cos(D2R*em2_phi_rich),sin(D2R*em2_theta_rich)*sin(D2R*em2_phi_rich),cos(D2R*em2_theta_rich));

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

    double e1_mass = em1_p*em1_p * (  1. / (em1_beta*em1_beta)  - 1. ) ;
    double e2_mass = em2_p*em2_p * (  1. / (em2_beta*em2_beta)  - 1. ) ;

    ACC = 1.;
    EFF = 1.;


    gammae1e2->Boost(0., 0., -(beam->Beta()));
    e1_delta->Boost(0., 0., -(beam->Beta()));
    e2_delta->Boost(0., 0., -(beam->Beta()));

    e1_delta->Boost( -gammae1e2->Px()/gammae1e2->E(), -gammae1e2->Py()/gammae1e2->E(), -gammae1e2->Pz()/gammae1e2->E());
    e2_delta->Boost( -gammae1e2->Px()/gammae1e2->E(), -gammae1e2->Py()/gammae1e2->E(), -gammae1e2->Pz()/gammae1e2->E());

    //cout << "Poczatek obliczen..." << endl;

    double ang_cut = 4.;
    //double ang_cut = 4.;

    double close_cut = 4.;
    double nonfit_close_cut = -4.;
    //double close_cut = 4.;


#ifdef FLANCH
    insideEm1S0 = (pEm1S0 == 0) ? 0 : pEm1S0->IsInside(em1_z,em1_theta);
    insideEm1S1 = (pEm1S1 == 0) ? 0 : pEm1S1->IsInside(em1_z,em1_theta);
    insideEm2S0 = (pEm2S0 == 0) ? 0 : pEm2S0->IsInside(em2_z,em2_theta);
    insideEm2S1 = (pEm2S1 == 0) ? 0 : pEm2S1->IsInside(em2_z,em2_theta);
    //insideEm1S0 = (pEm1S0 == 0) ? 0 : pEm1S0->IsInside(eVert_z,em1_theta);
    //insideEm1S1 = (pEm1S1 == 0) ? 0 : pEm1S1->IsInside(eVert_z,em1_theta);
    //insideEm2S0 = (pEm2S0 == 0) ? 0 : pEm2S0->IsInside(eVert_z,em2_theta);
    //insideEm2S1 = (pEm2S1 == 0) ? 0 : pEm2S1->IsInside(eVert_z,em2_theta);
#endif

#ifdef TARG
    insideTarget = ( pvertex_xy->IsInside(eVert_y, eVert_x) &&
		     pvertex_xz->IsInside(eVert_z, eVert_x) &&
		     pvertex_yz->IsInside(eVert_z, eVert_y) );
#else
    insideTarget = 1;
#endif

#ifdef RECTANG
    //insideEm1S0 = (em1_theta > 50 && p_z < -50) ? 1 : 0;
    //insideEm1S1 = (em1_theta > 50 && p_z < -50) ? 1 : 0;
    //insideEm2S0 = (em2_theta > 50 && p_z < -50) ? 1 : 0;
    //insideEm2S1 = (em2_theta > 50 && p_z < -50) ? 1 : 0;
    //insideEm1S0 = (em1_theta > 50 && eVert_z < -50 /* && em1_p<200.*/) ? 1 : 0;
    //insideEm1S1 = (em1_theta > 50 && eVert_z < -50 /* && em1_p<200.*/) ? 1 : 0;
    //insideEm2S0 = (em2_theta > 50 && eVert_z < -50 /* && em2_p<200.*/) ? 1 : 0;
    //insideEm2S1 = (em2_theta > 50 && eVert_z < -50 /* && em2_p<200.*/) ? 1 : 0;
    insideEm1S0 = (em1_theta > 50 && em1_z < -50 /* && em1_p<200.*/) ? 1 : 0;
    insideEm1S1 = (em1_theta > 50 && em1_z < -50 /* && em1_p<200.*/) ? 1 : 0;
    insideEm2S0 = (em2_theta > 50 && em2_z < -50 /* && em2_p<200.*/) ? 1 : 0;
    insideEm2S1 = (em2_theta > 50 && em2_z < -50 /* && em2_p<200.*/) ? 1 : 0;
#endif

    //#ifdef NOCUT
    insideEm1S0 = 0;
    insideEm1S1 = 0;
    insideEm2S0 = 0;
    insideEm2S1 = 0;
    //#endif


    NoLeptonE1 = !((em1_oa_lept< close_cut&&em1_oa_lept>0.0) &&em1_oa_lept>nonfit_close_cut );
    NoHadronE1 = !(em1_oa_hadr< close_cut &&em1_oa_hadr>nonfit_close_cut );
    NoLeptonE2 = !((em2_oa_lept< close_cut&&em2_oa_lept>0.0) &&em2_oa_lept>nonfit_close_cut );
    NoHadronE2 = !(em2_oa_hadr< close_cut &&em2_oa_hadr>nonfit_close_cut );
    NoHadronE1 = 1;
    NoHadronE2 = 1;

    /*
      NoLeptonE1 = 1;
      NoHadronE1 = 1;
      NoLeptonE2 = 1;
      NoHadronE2 = 1;
    */

    Electron1 = (((em1_system==0&&insideEm1S0==0)||(em1_system==1&&insideEm1S1==0)));
    Electron2 = (((em2_system==0&&insideEm2S0==0)||(em2_system==1&&insideEm2S1==0)));

    ElectronElectron = Electron1 && NoLeptonE1 && NoHadronE1  &&  Electron2 && NoLeptonE2 && NoHadronE2 && insideTarget &&
      ( e1_mass < 5000. && e2_mass < 5000. );

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

    double lambda_m=gamma_protonpion->M();
    double lambda_d=trackDistance(p_r,p_z,v_prot,pim_r,pim_z,v_pion);
    TVector3 lambda_ver=vertex(p_r,p_z,v2,pim_r,pim_z,v3);
    
    if(  lambda_d<min_distance
	 && lambda_m<1120
	 && lambda_m>1110
	 && lambda_ver.Z()>min_z)
      {
	is_lambda=true;
      }
    //End of hadronic part

    bool bt_em1_condition=(em1_isBT!=-1
			   //&& em1_btMaxima>=2
			   && em1_btPadsRing>=2
			   );
    bool bt_em2_condition=(em2_isBT!=-1
			   //&& em2_btMaxima>=2
			   && em2_btPadsRing>=2
			   );
    bool pre_shower= (em1_system==0?(em1_shw_sum1+em1_shw_sum2-em1_shw_sum0) > (parametrization(em1_p)):true)
      &&(em2_system==0?(em2_shw_sum1+em2_shw_sum2-em2_shw_sum0) > (parametrization(em2_p)):true);
    bool bt_condition=(bt_em1_condition && bt_em2_condition);
    bool mass_condition=(em1_p>100 && em2_p>100 && em1_p <2000. && em2_p <2000.
			 //&& em_p>200 && em_p>200
			 //&&(em_system==0?em_beta>0.95:em_beta>0.92)&&(em_system==0?em_beta>0.95:em_beta>0.92)
			 && em1_beta<1.1 && em2_beta<1.1
			 && em1_beta>0.9 && em2_beta>0.9
			 && pre_shower
			 && is_lambda
			 );
    int i_array;

      
    if (ElectronElectron && /*(((int)trigbit)&16) && trigdec>0 */ isBest>=0 && oa > ang_cut /*&& eVertReco_z>-500*/)
      {
	//           (*tlo)["mm"] = -1;
	if( mass_condition )
	  {
	    i_array=0;
	    if(em1_isring && !bt_em1_condition && !em2_isring && bt_em2_condition)
	      i_array=1;
	    if(em1_isring && !bt_em1_condition && em2_isring && bt_em2_condition)
	      i_array=2;
	    if(em1_isring && !bt_em1_condition && em2_isring && !bt_em2_condition)
	      i_array=3;
	    if(em1_isring && bt_em1_condition && !em2_isring && bt_em2_condition)
	      i_array=4;
	    if(em1_isring && bt_em1_condition && em2_isring && bt_em2_condition)
	      i_array=5;
	    if(em1_isring && bt_em1_condition && em2_isring && !bt_em2_condition)
	      i_array=6;
	    if(!em1_isring && bt_em1_condition && !em2_isring && bt_em2_condition)
	      i_array=7;
	    if(!em1_isring && bt_em1_condition && em2_isring && bt_em2_condition)
	      i_array=8;
	    if(!em1_isring && bt_em1_condition && em2_isring && !bt_em2_condition)
	      i_array=9;

	    if(i_array!=0)
	      bt_rf_stat_back2->Fill(i_array);
	    if(m_inv_e1e2>140 && i_array!=0)
	      bt_rf_stat_pi_back2->Fill(i_array);
	      
	    if(bt_condition)
	      bt_rf_stat_back2->Fill(10);
	    if(em1_isring && em2_isring)
	      bt_rf_stat_back2->Fill(11);
	    if(bt_condition && em1_isring && em2_isring)
	      bt_rf_stat_back2->Fill(12);
	    if((bt_em1_condition ||em1_isring)&&(bt_em2_condition||em2_isring) && !(em2_isring && em1_isring))
	      bt_rf_stat_back2->Fill(13);

	    if( m_inv_e1e2>140 && m_inv_e1e2<700)
	      {
		if(bt_condition)
		  bt_rf_stat_pi_back2->Fill(10);
		if(em1_isring && em2_isring)
		  bt_rf_stat_pi_back2->Fill(11);
		if(bt_condition && em1_isring && em2_isring)
		  bt_rf_stat_pi_back2->Fill(12);
		if((bt_em1_condition ||em1_isring)&&(bt_em2_condition||em2_isring) && !(em2_isring && em1_isring))
		  bt_rf_stat_pi_back2->Fill(13);
	      }
	    if(m_inv_e1e2<140)
	      {
		if(bt_condition )
		  bt_rf_stat_back2->Fill(14);
		if(em1_isring && em2_isring )
		  bt_rf_stat_back2->Fill(15);
		if((bt_em1_condition ||em1_isring)&&(bt_em2_condition||em2_isring) && !(em2_isring && em1_isring))
		  bt_rf_stat_back2->Fill(16);
	      }
	    if(m_inv_e1e2>700)
	      {
		if(bt_condition )
		  bt_rf_stat_back2->Fill(17);
		if(em1_isring && em2_isring)
		  bt_rf_stat_back2->Fill(18);
		if((bt_em1_condition ||em1_isring)&&(bt_em2_condition||em2_isring) && !(em2_isring && em1_isring))
		  bt_rf_stat_back2->Fill(19);
	      }
	    if(m_inv_e1e2>140 && m_inv_e1e2<700)
	      {
		if(bt_condition )
		  bt_rf_stat_back2->Fill(20);
		if(em1_isring && em2_isring)
		  bt_rf_stat_back2->Fill(21);
		if((bt_em1_condition ||em1_isring)&&(bt_em2_condition||em2_isring) && !(em2_isring && em1_isring))
		  bt_rf_stat_back2->Fill(22);
	      }
	  }
	  
	if(em1_isring>0 && em2_isring>0 && mass_condition)
	  if(bt_condition)
	    {
	      sig_rf_and_bt_back2->Fill(m_inv_e1e2/1000., EFF );
	    }
	  
	if(em1_isring>0 && em2_isring>0 && mass_condition)
	  { // [1]
	    sig_all_back2->Fill(m_inv_e1e2/1000., EFF );
	    sig_all_var_back2->Fill(m_inv_e1e2/1000., EFF );
	    //em2_mom->Fill(em2_p);
	    //em1_mom->Fill(em1_p);
	    //em1_beta_mom->Fill( em1_beta_new, em1_p, EFF );
	    //em2_beta_mom->Fill( em2_beta_new, em2_p, EFF );
	  }
	if(mass_condition && (bt_em1_condition||em1_isring) && (bt_em2_condition||em2_isring) && !(em2_isring && em1_isring))//pure backtracking signal
	  {
	    pureBT_signal_back2->Fill(m_inv_e1e2/1000., EFF );
	    pureBT_signal_back2_var->Fill(m_inv_e1e2/1000., EFF);
	    if(em1_isBT!=-1)
	      {
		//pureBT_beta_mom->Fill( em1_beta_new, em1_p, EFF );
	      }
	    if(em2_isBT!=-1)
	      {
		//pureBT_beta_mom->Fill( em2_beta_new, em2_p, EFF );
	      }
	  }
	if ( mass_condition )  
	  if (  bt_condition )
	    { // [2]
	      //if ( (em1_isBT != -1 && em2_isBT != -1) ) { // [3]
	      //if ( (em1_isBT != -1 || em2_isBT != -1) && !(em1_isring>0 && em2_isring>0) ) { // [4]
	      //if ( (em1_isBT != -1 || em1_isring>0) && (em2_isBT != -1 || em2_isring>0) ) { // [5]
	      //if ( (em1_isBT != -1 && em2_isBT != -1) && !(em1_isring>0 && em2_isring>0) ) { // [6]

	      //if ( (em1_isBT != -1 || em2_isBT != -1) ) { // [2]
	      //iF ( (em1_isBT != -1 && em2_isBT != -1) ) { // [3]
	      //if ( (em1_isBT != -1 || em2_isBT != -1) && !(em1_isring>0 && em2_isring>0) ) { // [4]
	      //if ( (em1_isBT != -1 || em1_isring>0) && (em2_isBT != -1 || em2_isring>0) ) { // [5]
	      //if ( (em1_isBT != -1 && em2_isBT != -1) && !(em1_isring>0 && em2_isring>0) ) { // [6]
	      //if ( (em1_isBT != -1 && em2_isBT != -1) && (em1_isring>0 && em2_isring>0) ) { // [7]
	      //if ( !(em1_isBT != -1 && em2_isBT != -1) && (em1_isring>0 && em2_isring>0) ) { // [8]
	      sig_all_bt_back2->Fill(m_inv_e1e2/1000., EFF );
	      sig_all_var_bt_back2->Fill(m_inv_e1e2/1000., EFF );
	      //em1_beta_mom_bt->Fill( em1_beta_new, em1_p, EFF );
	      //em2_beta_mom_bt->Fill( em2_beta_new, em2_p, EFF );
	      //em2_mom_bt->Fill(em2_p);
	      //em1_mom_bt->Fill(em1_p);
	    }

	if(m_inv_e1e2>140) miss_all_back2->Fill(e1e2_miss->M()/1000., EFF );

         
	rapidity_back1->Fill( e1e2->Rapidity() , EFF  );
	pt_back1->Fill( e1e2->Pt() / 1000. , EFF  );
	if (m_inv_e1e2 > 140. && e1e2_miss->M()>860.&& e1e2_miss->M()<1020)
	  {
	    cos_ep_back1->Fill( cos( openingangle( *e1_delta, *gammae1e2 ) ) );
	    cos_em_back1->Fill( cos( openingangle( *e2_delta, *gammae1e2 ) ) );
	    cos_sum_back1->Fill( cos( openingangle( *e1_delta, *gammae1e2 ) ), 0.5 );
	    cos_sum_back1->Fill( cos( openingangle( *e2_delta, *gammae1e2 ) ), 0.5 );
	    rapidity_140_back1->Fill( e1e2->Rapidity() , EFF  );
	    pt_140_back1->Fill( e1e2->Pt() / 1000. , EFF  );
	  }
      }


    //tlo->fill();

    // if (Cut(ientry) < 0) continue;
  }
}




PPimEmEm::PPimEmEm(TTree *tree)
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.

  em1_acc = em1_acc_err = em2_acc = em2_acc_err = 0.;
  em1_eff = em1_eff_err = em2_eff = em2_eff_err = 0.;

  if (tree == 0) {

    TChain * chain = new TChain("PPimEmEm_ID","");
    //chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT/FILES/288/day288.root/EmEm_ID");
    //chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT/FILES/288_new/lepton288new.root/EmEm_ID");
    //chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT/FILES/288_new_pcut/lepton288new_p.root/EmEm_ID");
    //chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT/FILES/288_new_std/dilepton_sep08_KN.root/EmEm_ID");
    //chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT/FILES/sep08_all/sep08_lepton_all.root/EpEm_ID");
    //chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_epem/FILES/sep08_all/list5/sum5.root/EmEm_ID");
    //chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_epem/FILES/sep08_all/list4/sum4.root/EmEm_ID");
    //chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_epem/FILES/sep08_all/list3/sum3.root/EmEm_ID");
    //chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_epem/FILES/sep08_all/list2/sum2.root/EmEm_ID");
    //chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_epem/FILES/sep08_all/list1/sum1.root/EmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton00.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton01.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton02.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton03.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton04.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton05.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton06.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton07.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton08.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton09.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton10.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton11.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton12.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton13.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton14.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton15.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton16.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton17.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton18.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton19.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton20.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton21.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton22.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton23.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton24.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton25.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton26.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton27.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton28.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton29.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton30.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton31.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton32.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton33.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton34.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton35.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton36.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton37.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton38.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton39.root/PPimEmEm_ID");
    chain->Add("/lustre/nyx/hades/user/knowakow/PNB/PAT_ppim/FILES/full_stat_2/lepton40.root/PPimEmEm_ID");
      
    tree = chain;

  }
  Init(tree);
}


// --------------------------------------------------------------------------------------------
PPimEmEm::~PPimEmEm()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

// --------------------------------------------------------------------------------------------
Int_t PPimEmEm::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

// --------------------------------------------------------------------------------------------
Long64_t PPimEmEm::LoadTree(Long64_t entry)
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
void PPimEmEm::Init(TTree *tree)
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
  fChain->SetBranchAddress("em1_beta", &em1_beta, &b_em1_beta);
  fChain->SetBranchAddress("em1_beta_new", &em1_beta_new, &b_em1_beta_new);
  fChain->SetBranchAddress("em1_btChargeRing", &em1_btChargeRing, &b_em1_btChargeRing);
  fChain->SetBranchAddress("em1_btChargeSum", &em1_btChargeSum, &b_em1_btChargeSum);
  fChain->SetBranchAddress("em1_btChi2", &em1_btChi2, &b_em1_btChi2);
  fChain->SetBranchAddress("em1_btClusters", &em1_btClusters, &b_em1_btClusters);
  fChain->SetBranchAddress("em1_btMaxima", &em1_btMaxima, &b_em1_btMaxima);
  fChain->SetBranchAddress("em1_btMaximaCharge", &em1_btMaximaCharge, &b_em1_btMaximaCharge);
  fChain->SetBranchAddress("em1_btMaximaChargeShared", &em1_btMaximaChargeShared, &b_em1_btMaximaChargeShared);
  fChain->SetBranchAddress("em1_btMaximaChargeSharedFragment", &em1_btMaximaChargeSharedFragment, &b_em1_btMaximaChargeSharedFragment);
  fChain->SetBranchAddress("em1_btMaximaShared", &em1_btMaximaShared, &b_em1_btMaximaShared);
  fChain->SetBranchAddress("em1_btMaximaSharedFragment", &em1_btMaximaSharedFragment, &b_em1_btMaximaSharedFragment);
  fChain->SetBranchAddress("em1_btMeanDist", &em1_btMeanDist, &b_em1_btMeanDist);
  fChain->SetBranchAddress("em1_btNearbyMaxima", &em1_btNearbyMaxima, &b_em1_btNearbyMaxima);
  fChain->SetBranchAddress("em1_btNearbyMaximaShared", &em1_btNearbyMaximaShared, &b_em1_btNearbyMaximaShared);
  fChain->SetBranchAddress("em1_btPadsClus", &em1_btPadsClus, &b_em1_btPadsClus);
  fChain->SetBranchAddress("em1_btPadsRing", &em1_btPadsRing, &b_em1_btPadsRing);
  fChain->SetBranchAddress("em1_btRingMatrix", &em1_btRingMatrix, &b_em1_btRingMatrix);
  fChain->SetBranchAddress("em1_dedx_mdc", &em1_dedx_mdc, &b_em1_dedx_mdc);
  fChain->SetBranchAddress("em1_dedx_tof", &em1_dedx_tof, &b_em1_dedx_tof);
  fChain->SetBranchAddress("em1_id", &em1_id, &b_em1_id);
  fChain->SetBranchAddress("em1_isBT", &em1_isBT, &b_em1_isBT);
  fChain->SetBranchAddress("em1_isOffVertexClust", &em1_isOffVertexClust, &b_em1_isOffVertexClust);
  fChain->SetBranchAddress("em1_isPrimaryVertex", &em1_isPrimaryVertex, &b_em1_isPrimaryVertex);
  fChain->SetBranchAddress("em1_isUsedVertex", &em1_isUsedVertex, &b_em1_isUsedVertex);
  fChain->SetBranchAddress("em1_isring", &em1_isring, &b_em1_isring);
  fChain->SetBranchAddress("em1_isringmdc", &em1_isringmdc, &b_em1_isringmdc);
  fChain->SetBranchAddress("em1_isringnomatch", &em1_isringnomatch, &b_em1_isringnomatch);
  fChain->SetBranchAddress("em1_isringtrack", &em1_isringtrack, &b_em1_isringtrack);
  fChain->SetBranchAddress("em1_kIsLepton", &em1_kIsLepton, &b_em1_kIsLepton);
  fChain->SetBranchAddress("em1_kIsUsed", &em1_kIsUsed, &b_em1_kIsUsed);
  fChain->SetBranchAddress("em1_mdcinnerchi2", &em1_mdcinnerchi2, &b_em1_mdcinnerchi2);
  fChain->SetBranchAddress("em1_mdcouterchi2", &em1_mdcouterchi2, &b_em1_mdcouterchi2);
  fChain->SetBranchAddress("em1_oa_hadr", &em1_oa_hadr, &b_em1_oa_hadr);
  fChain->SetBranchAddress("em1_oa_lept", &em1_oa_lept, &b_em1_oa_lept);
  fChain->SetBranchAddress("em1_p", &em1_p, &b_em1_p);
  fChain->SetBranchAddress("em1_p_corr_em", &em1_p_corr_em, &b_em1_p_corr_em);
  fChain->SetBranchAddress("em1_p_corr_ep", &em1_p_corr_ep, &b_em1_p_corr_ep);
  fChain->SetBranchAddress("em1_p_corr_p", &em1_p_corr_p, &b_em1_p_corr_p);
  fChain->SetBranchAddress("em1_p_corr_pim", &em1_p_corr_pim, &b_em1_p_corr_pim);
  fChain->SetBranchAddress("em1_p_corr_pip", &em1_p_corr_pip, &b_em1_p_corr_pip);
  fChain->SetBranchAddress("em1_phi", &em1_phi, &b_em1_phi);
  fChain->SetBranchAddress("em1_phi_rich", &em1_phi_rich, &b_em1_phi_rich);
  fChain->SetBranchAddress("em1_pid", &em1_pid, &b_em1_pid);
  fChain->SetBranchAddress("em1_q", &em1_q, &b_em1_q);
  fChain->SetBranchAddress("em1_r", &em1_r, &b_em1_r);
  fChain->SetBranchAddress("em1_resolution", &em1_resolution, &b_em1_resolution);
  fChain->SetBranchAddress("em1_resoultion", &em1_resoultion, &b_em1_resoultion);
  fChain->SetBranchAddress("em1_rich_amp", &em1_rich_amp, &b_em1_rich_amp);
  fChain->SetBranchAddress("em1_rich_centr", &em1_rich_centr, &b_em1_rich_centr);
  fChain->SetBranchAddress("em1_rich_houtra", &em1_rich_houtra, &b_em1_rich_houtra);
  fChain->SetBranchAddress("em1_rich_padnum", &em1_rich_padnum, &b_em1_rich_padnum);
  fChain->SetBranchAddress("em1_rich_patmat", &em1_rich_patmat, &b_em1_rich_patmat);
  fChain->SetBranchAddress("em1_rkchi2", &em1_rkchi2, &b_em1_rkchi2);
  fChain->SetBranchAddress("em1_sector", &em1_sector, &b_em1_sector);
  fChain->SetBranchAddress("em1_shw_sum0", &em1_shw_sum0, &b_em1_shw_sum0);
  fChain->SetBranchAddress("em1_shw_sum1", &em1_shw_sum1, &b_em1_shw_sum1);
  fChain->SetBranchAddress("em1_shw_sum2", &em1_shw_sum2, &b_em1_shw_sum2);
  fChain->SetBranchAddress("em1_system", &em1_system, &b_em1_system);
  fChain->SetBranchAddress("em1_theta", &em1_theta, &b_em1_theta);
  fChain->SetBranchAddress("em1_theta_rich", &em1_theta_rich, &b_em1_theta_rich);
  fChain->SetBranchAddress("em1_tof_mom", &em1_tof_mom, &b_em1_tof_mom);
  fChain->SetBranchAddress("em1_tof_new", &em1_tof_new, &b_em1_tof_new);
  fChain->SetBranchAddress("em1_tof_rec", &em1_tof_rec, &b_em1_tof_rec);
  fChain->SetBranchAddress("em1_track_length", &em1_track_length, &b_em1_track_length);
  fChain->SetBranchAddress("em1_tracklength", &em1_tracklength, &b_em1_tracklength);
  fChain->SetBranchAddress("em1_z", &em1_z, &b_em1_z);
  fChain->SetBranchAddress("em2_beta", &em2_beta, &b_em2_beta);
  fChain->SetBranchAddress("em2_beta_new", &em2_beta_new, &b_em2_beta_new);
  fChain->SetBranchAddress("em2_btChargeRing", &em2_btChargeRing, &b_em2_btChargeRing);
  fChain->SetBranchAddress("em2_btChargeSum", &em2_btChargeSum, &b_em2_btChargeSum);
  fChain->SetBranchAddress("em2_btChi2", &em2_btChi2, &b_em2_btChi2);
  fChain->SetBranchAddress("em2_btClusters", &em2_btClusters, &b_em2_btClusters);
  fChain->SetBranchAddress("em2_btMaxima", &em2_btMaxima, &b_em2_btMaxima);
  fChain->SetBranchAddress("em2_btMaximaCharge", &em2_btMaximaCharge, &b_em2_btMaximaCharge);
  fChain->SetBranchAddress("em2_btMaximaChargeShared", &em2_btMaximaChargeShared, &b_em2_btMaximaChargeShared);
  fChain->SetBranchAddress("em2_btMaximaChargeSharedFragment", &em2_btMaximaChargeSharedFragment, &b_em2_btMaximaChargeSharedFragment);
  fChain->SetBranchAddress("em2_btMaximaShared", &em2_btMaximaShared, &b_em2_btMaximaShared);
  fChain->SetBranchAddress("em2_btMaximaSharedFragment", &em2_btMaximaSharedFragment, &b_em2_btMaximaSharedFragment);
  fChain->SetBranchAddress("em2_btMeanDist", &em2_btMeanDist, &b_em2_btMeanDist);
  fChain->SetBranchAddress("em2_btNearbyMaxima", &em2_btNearbyMaxima, &b_em2_btNearbyMaxima);
  fChain->SetBranchAddress("em2_btNearbyMaximaShared", &em2_btNearbyMaximaShared, &b_em2_btNearbyMaximaShared);
  fChain->SetBranchAddress("em2_btPadsClus", &em2_btPadsClus, &b_em2_btPadsClus);
  fChain->SetBranchAddress("em2_btPadsRing", &em2_btPadsRing, &b_em2_btPadsRing);
  fChain->SetBranchAddress("em2_btRingMatrix", &em2_btRingMatrix, &b_em2_btRingMatrix);
  fChain->SetBranchAddress("em2_dedx_mdc", &em2_dedx_mdc, &b_em2_dedx_mdc);
  fChain->SetBranchAddress("em2_dedx_tof", &em2_dedx_tof, &b_em2_dedx_tof);
  fChain->SetBranchAddress("em2_isBT", &em2_isBT, &b_em2_isBT);
  fChain->SetBranchAddress("em2_id", &em2_id, &b_em2_id);
  fChain->SetBranchAddress("em2_isOffVertexClust", &em2_isOffVertexClust, &b_em2_isOffVertexClust);
  fChain->SetBranchAddress("em2_isPrimaryVertex", &em2_isPrimaryVertex, &b_em2_isPrimaryVertex);
  fChain->SetBranchAddress("em2_isUsedVertex", &em2_isUsedVertex, &b_em2_isUsedVertex);
  fChain->SetBranchAddress("em2_isring", &em2_isring, &b_em2_isring);
  fChain->SetBranchAddress("em2_isringmdc", &em2_isringmdc, &b_em2_isringmdc);
  fChain->SetBranchAddress("em2_isringnomatch", &em2_isringnomatch, &b_em2_isringnomatch);
  fChain->SetBranchAddress("em2_isringtrack", &em2_isringtrack, &b_em2_isringtrack);
  fChain->SetBranchAddress("em2_kIsLepton", &em2_kIsLepton, &b_em2_kIsLepton);
  fChain->SetBranchAddress("em2_kIsUsed", &em2_kIsUsed, &b_em2_kIsUsed);
  fChain->SetBranchAddress("em2_mdcinnerchi2", &em2_mdcinnerchi2, &b_em2_mdcinnerchi2);
  fChain->SetBranchAddress("em2_mdcouterchi2", &em2_mdcouterchi2, &b_em2_mdcouterchi2);
  fChain->SetBranchAddress("em2_oa_hadr", &em2_oa_hadr, &b_em2_oa_hadr);
  fChain->SetBranchAddress("em2_oa_lept", &em2_oa_lept, &b_em2_oa_lept);
  fChain->SetBranchAddress("em2_p", &em2_p, &b_em2_p);
  fChain->SetBranchAddress("em2_p_corr_em", &em2_p_corr_em, &b_em2_p_corr_em);
  fChain->SetBranchAddress("em2_p_corr_ep", &em2_p_corr_ep, &b_em2_p_corr_ep);
  fChain->SetBranchAddress("em2_p_corr_p", &em2_p_corr_p, &b_em2_p_corr_p);
  fChain->SetBranchAddress("em2_p_corr_pim", &em2_p_corr_pim, &b_em2_p_corr_pim);
  fChain->SetBranchAddress("em2_p_corr_pip", &em2_p_corr_pip, &b_em2_p_corr_pip);
  fChain->SetBranchAddress("em2_phi", &em2_phi, &b_em2_phi);
  fChain->SetBranchAddress("em2_phi_rich", &em2_phi_rich, &b_em2_phi_rich);
  fChain->SetBranchAddress("em2_pid", &em2_pid, &b_em2_pid);
  fChain->SetBranchAddress("em2_q", &em2_q, &b_em2_q);
  fChain->SetBranchAddress("em2_r", &em2_r, &b_em2_r);
  fChain->SetBranchAddress("em2_resolution", &em2_resolution, &b_em2_resolution);
  fChain->SetBranchAddress("em2_resoultion", &em2_resoultion, &b_em2_resoultion);
  fChain->SetBranchAddress("em2_rich_amp", &em2_rich_amp, &b_em2_rich_amp);
  fChain->SetBranchAddress("em2_rich_centr", &em2_rich_centr, &b_em2_rich_centr);
  fChain->SetBranchAddress("em2_rich_houtra", &em2_rich_houtra, &b_em2_rich_houtra);
  fChain->SetBranchAddress("em2_rich_padnum", &em2_rich_padnum, &b_em2_rich_padnum);
  fChain->SetBranchAddress("em2_rich_patmat", &em2_rich_patmat, &b_em2_rich_patmat);
  fChain->SetBranchAddress("em2_rkchi2", &em2_rkchi2, &b_em2_rkchi2);
  fChain->SetBranchAddress("em2_sector", &em2_sector, &b_em2_sector);
  fChain->SetBranchAddress("em2_shw_sum0", &em2_shw_sum0, &b_em2_shw_sum0);
  fChain->SetBranchAddress("em2_shw_sum1", &em2_shw_sum1, &b_em2_shw_sum1);
  fChain->SetBranchAddress("em2_shw_sum2", &em2_shw_sum2, &b_em2_shw_sum2);
  fChain->SetBranchAddress("em2_system", &em2_system, &b_em2_system);
  fChain->SetBranchAddress("em2_theta", &em2_theta, &b_em2_theta);
  fChain->SetBranchAddress("em2_theta_rich", &em2_theta_rich, &b_em2_theta_rich);
  fChain->SetBranchAddress("em2_tof_mom", &em2_tof_mom, &b_em2_tof_mom);
  fChain->SetBranchAddress("em2_tof_new", &em2_tof_new, &b_em2_tof_new);
  fChain->SetBranchAddress("em2_tof_rec", &em2_tof_rec, &b_em2_tof_rec);
  fChain->SetBranchAddress("em2_track_length", &em2_track_length, &b_em2_track_length);
  fChain->SetBranchAddress("em2_tracklength", &em2_tracklength, &b_em2_tracklength);
  fChain->SetBranchAddress("em2_z", &em2_z, &b_em2_z);
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
Bool_t PPimEmEm::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

// --------------------------------------------------------------------------------------------
void PPimEmEm::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}

// --------------------------------------------------------------------------------------------
Int_t PPimEmEm::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}


