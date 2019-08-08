void pluto_np_ppPim_pNb93(Int_t nEvt=10000) {  // p + Nb93 --> p + K0S + Lambda + pi+ + X

  // Plot implemented C12 Fermi distribution with:
  //
  // root [0] makeDistributionManager()->Exec("nucleus_fermi:gamma");  // init plugin
  // root [1] makeDistributionManager()->LinkDB();
  // root [2] PChannelModel *fFermi = makeDynamicData()->GetParticleSecondaryModel("12C", "fermi");  // get Fermi dist
  // root [3] fFermi->Draw();  // plot it
  //

  //Add our quasi-free composite:
  makeStaticData()->AddParticle(13014, "p + n",0.938272+0.939565);
  //Creates just a symbolic link:
  makeStaticData()->AddAlias("p + n","p+n");

  //Executes the fermi plugin which adds also nuclei:
  makeDistributionManager()->Exec("nucleus_fermi");

  //Add a new composite particle (target_id*1000 * beam_id)
  makeStaticData()->AddParticle(754014,"p + 93Nb",86.54174+0.938272);
  //Creates again a symbolic link:
  makeStaticData()->AddAlias("p + 93Nb","p+93Nb");

  //adds a decay by using the "p + 12C" particle as created above:
  makeStaticData()->AddDecay(-1, "p + 93Nb -> (p + n) + 92Nb (quasi-free)","p + 93Nb","p + n,92Nb", 1.0 );

  //This is the fermi model (contributed by M. Dieterle and L. Witthauer, Basel):
  PFermiMomentumGA * pmodel = new PFermiMomentumGA("pn_in_93Nb@p + 93Nb_to_p + n_92Nb", "Quasi-free particle production <nucleus_fermi>",-1);
  
  pmodel->Add("q,parent");
  pmodel->Add("p,grandparent,beam");
  pmodel->Add("93Nb,grandparent,target");
  pmodel->Add("92Nb,daughter,spectator");
  pmodel->Add("q,daughter,composite");
  //    pmodel->Add("q1,daughter,composite");
  pmodel->Add("p,granddaughter,participant");
  pmodel->Add("p,granddaughter,p2");
  makeDistributionManager()->Add(pmodel);

  //  p beam momentum = 1.7 GeV/c
  //  PReaction *Reac = new PReaction ("_P1=1.7","p","12C","(p p) p pi+ n (11B)","pim_C12_2pion",0,0,0,0);  // phase space
  PReaction *Reac = new PReaction ("_P1=4.338","p","93Nb","(p n) p p pi- (92Nb)","p_93Nb_PPPim",0,0,0,0); // via rho0

  //TH1F * histo_Mmiss = new TH1F("Mmiss","missing mass",500,0,2);
  //TH1F * histo_CMS = new TH1F("CMS","Centrum of Mass Energy",750,1.0,4.0);
  //TH1F * histo_Pim_E=new TH1F("Pim_E","#pi^{-} total E",500,0,1.5);
  //TH1F * histo_inv = new TH1F("inv","inv mass",250,1,2);
  //TH1F * histo_beam_Ek = new TH1F("histo_beam_Ek","Beam kinetic energy",200,0,4);

  //Reac->Do("p1 = P3E(0,0,4.338,[p]->E());");  // set up p beam
  //ac->Do("q3= P3E([K0S]->Px()+[Lambda]->Px(),[K0S]->Py()+[Lambda]->Py(),[K0S]->Pz()+[Lambda]->Pz()-0.69,[K0S]->E()+[Lambda]->E()-0.7039-0.938);");
  //Reac->Do("q1= P3E([K0S]->Px()+[Lambda]->Px(),[K0S]->Py()+[Lambda]->Py(),[K0S]->Pz()+[Lambda]->Pz(),[K0S]->E()+[Lambda]->E());");//inv mas of registered particles
  //Reac->Do("q2= P3E([p]->Px()+[pi-]->Px()+[p]->Px(),[p]->Py()+[pi-]->Py()+[p]->Py(),[p]->Pz()+[pi-]->Pz()+[p]->Pz(),[p]->E()+[pim-]->E()+[p]->E());");
  //Reac->Do("q3= P3E([pi-]->Px(),[pi-]->Py(),[pi-]->Pz(),[pi-]->E());");//pion 4-vector
  
  //Reac->Do(histo_CMS," _x = q2->M();");  // fill total CMS
  //Reac->Do(histo_Pim_E,"_x=q3->E();");
  //Reac->Do(histo_inv," _x = q1->M();");  // fill inv. mass
  //Reac->Do(histo_Mmiss,"_x = q3->M();"); //fill missing mass
  //Reac->Do(histo_beam_Ek,"_x = p1->E();");// fill kinetic energy of beam

  Reac->Print();
  Reac->loop(nEvt);  // Number of events

  //   histo_Mmiss->Draw();
  //histo_CMS->Draw();
  //histo_Pim_E->Draw();

  // save histogram
  TFile *out = new TFile("p_93Nb_PPPim_pictres.root","update");
  //histo_Mmiss->Write();
  //histo_CMS->Write();
  //histo_inv->Write();
  //histo_beam_Ek->Write();
  //histo_Pim_E->Write();
  out->Close();

}
