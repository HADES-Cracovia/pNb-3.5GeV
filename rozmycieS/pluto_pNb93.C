void pluto_pNb93(Int_t nEvt=1000) {  // p + C12 --> p + pi+ + X

  // Plot implemented C12 Fermi distribution with:
  //
  // root [0] makeDistributionManager()->Exec("nucleus_fermi:gamma");  // init plugin
  // root [1] makeDistributionManager()->LinkDB();
  // root [2] PChannelModel *fFermi = makeDynamicData()->GetParticleSecondaryModel("12C", "fermi");  // get Fermi dist
  // root [3] fFermi->Draw();  // plot it
  //

  //Add our quasi-free composite:
  makeStaticData()->AddParticle(14014, "p + p",0.938272+0.938272);
  //Creates just a symbolic link:
  makeStaticData()->AddAlias("p + p","p+p");

  //Executes the fermi plugin which adds also nuclei:
  makeDistributionManager()->Exec("nucleus_fermi");

  //Add a new composite particle (target_id*1000 * beam_id)
  makeStaticData()->AddParticle(754014,"p + 93Nb",86.54174+0.938272);
  //Creates again a symbolic link:
  makeStaticData()->AddAlias("p + 93Nb","p+93Nb");

  //adds a decay by using the "p + 12C" particle as created above:
  makeStaticData()->AddDecay(-1, "p + 12C -> (p + p) + 92Zr (quasi-free)","p + 92Zr","p + p,92Zr", 1.0 );

  //This is the fermi model (contributed by M. Dieterle and L. Witthauer, Basel):
  PFermiMomentumGA * pmodel = new PFermiMomentumGA("pp_in_93Nb@p + 93Nb_to_p + p_92Zr", "Quasi-free particle production <nucleus_fermi>",-1);
  
  pmodel->Add("q,parent");
  pmodel->Add("p,grandparent,beam");
  pmodel->Add("93Nb,grandparent,target");
  pmodel->Add("92Zr,daughter,spectator");
  pmodel->Add("q,daughter,composite");
  //    pmodel->Add("q1,daughter,composite");
  pmodel->Add("p,granddaughter,participant");
  pmodel->Add("p,granddaughter,p2");
  makeDistributionManager()->Add(pmodel);

  //  p beam momentum = 1.7 GeV/c
  //  PReaction *Reac = new PReaction ("_P1=1.7","p","12C","(p p) p pi+ n (11B)","pim_C12_2pion",0,0,0,0);  // phase space
  PReaction *Reac = new PReaction ("_P1=4.3","p","93Nb","(p p) K0S pi+ Lambda p (92Zr)","p_93Nb_LambdaK0",0,0,0,0); // via rho0

  TH1F * histo_Mmiss = new TH1F("Mmiss","missing mass",200,0.6,1.4);
  TH1F * histo_CMS = new TH1F("CMS","Centrum of Mass Energy",800,1.0,4.0);
  TH1F * histo_inv = new TH1F("inv","inv mass",120,0.0,.6);


  Reac->Do("p = P3E(0,0,.69,[p]->E());");  // set up p beam
  Reac->Do("q3= P3E([K0S]->Px()+[Lambda]->Px(),[K0S]->Py()+[Lambda]->Py(),[K0S]->Pz()+[Lambda]->Pz()-0.69,[K0S]->E()+[Lambda]->E()-0.7039-0.938);");
  Reac->Do("q1= P3E([K0S]->Px()+[Lambda]->Px(),[K0S]->Py()+[Lambda]->Py(),[K0S]->Pz()+[Lambda]->Pz(),[K0S]->E()+[Lambda]->E());");
  Reac->Do("q2= P3E([K0S]->Px()+[Lambda]->Px()+[p]->Px()+[pi+]->Px(),[K0S]->Py()+[Lambda]->Py()+[p]->Py()+[pi+]->Py(),[K0S]->Pz()+[Lambda]->Pz()+[p]->Pz()+[pi+]->Pz(),[K0S]->E()+[Lambda]->E()+[p]->E()+[pi+]->E());");
  
  Reac->Do(histo_CMS," _x = q2->M();");  // fill total CMS
  Reac->Do(histo_inv," _x = q1->M();");  // fill inv. mass


  Reac->Print();
  Reac->loop(nEvt);  // Number of events

  //   histo_Mmiss->Draw();
  histo_CMS->Draw();

  // save histogram
  TFile *out = new TFile("pim_C12_eta.root","update");
  histo_Mmiss->Write();
  histo_CMS->Write();
  histo_inv->Write();
  out->Close();

}
