void pluto_macro(Int_t nEvt=1000) {  // pi- + C12 --> pi- + pi+ + X

  // Plot implemented C12 Fermi distribution with:
  //
  // root [0] makeDistributionManager()->Exec("nucleus_fermi:gamma");  // init plugin
  // root [1] makeDistributionManager()->LinkDB();
  // root [2] PChannelModel *fFermi = makeDynamicData()->GetParticleSecondaryModel("93Nb", "fermi");  // get Fermi dist
  // root [3] fFermi->Draw();  // plot it
  //

  //Add our quasi-free composite:
  makeStaticData()->AddParticle(14009, "pi- + p",0.938272+0.13957);
  //Creates just a symbolic link:
  makeStaticData()->AddAlias("pi- + p","pi-+p");

  //Executes the fermi plugin which adds also nuclei:
  makeDistributionManager()->Exec("nucleus_fermi");

  //Add a new composite particle (target_id*1000 * beam_id)
  makeStaticData()->AddParticle(754009,"pi- + 93Nb",86.54174+0.139570);
  //Creates again a symbolic link:
  makeStaticData()->AddAlias("pi- + 93Nb","pi-+93Nb");

  //adds a decay by using the "pi- + 93Nb" particle as created above:
  makeStaticData()->AddDecay(-1, "pi- + 93Nb -> (pi- + p) + 92Zr (quasi-free)","pi- + 93Nb","pi- + p,92Zr", 1.0 );

  //This is the fermi model (contributed by M. Dieterle and L. Witthauer, Basel):
  PFermiMomentumGA * pmodel = new PFermiMomentumGA("pi-p_in_93Nb@pi- + 93Nb_to_pi- + p_92Zr", "Quasi-free particle production <nucleus_fermi>",-1);
  pmodel->Add("q,parent");
  pmodel->Add("pi-,grandparent,beam");
  pmodel->Add("93Nb,grandparent,target");
  pmodel->Add("92Zr,daughter,spectator");
  pmodel->Add("q,daughter,composite");
  //    pmodel->Add("q1,daughter,composite");
  pmodel->Add("p,granddaughter,participant");
  pmodel->Add("pi-,granddaughter,p2");
  makeDistributionManager()->Add(pmodel);

  //  pi- beam momentum = 1.7 GeV/c
  //  PReaction *Reac = new PReaction ("_P1=1.7","pi-","93Nb","(pi- p) pi- pi+ n (92Zr)","pim_C12_2pion",0,0,0,0);  // phase space
  PReaction *Reac = new PReaction ("_P1=.69","pi-","93Nb","(pi- p) eta [dilepton [e+ e-] g] n (92Zr)","pim_Nb93_2ele",0,0,0,0); // via rho0

  TH1F * histo_Mmiss = new TH1F("Mmiss","missing mass",200,0.6,1.4);
  TH1F * histo_CMS = new TH1F("CMS","Centrum of Mass Energy",200,1.0,2.0);
  TH1F * histo_inv = new TH1F("inv","inv mass",120,0.0,.6);


  Reac->Do("pim = P3E(0,0,.69,[pi-]->E());");  // set up pi- beam
  Reac->Do("q3= P3E([e-]->Px()+[e+]->Px(),[e-]->Py()+[e+]->Py(),[e-]->Pz()+[e+]->Pz()-0.69,[e-]->E()+[e+]->E()-0.7039-0.938);");
  Reac->Do("q1= P3E([e-]->Px()+[e+]->Px(),[e-]->Py()+[e+]->Py(),[e-]->Pz()+[e+]->Pz(),[e-]->E()+[e+]->E());");
  Reac->Do("q2= P3E([e-]->Px()+[e+]->Px()+[g]->Px()+[n]->Px(),[e-]->Py()+[e+]->Py()+[g]->Py()+[n]->Py(),[e-]->Pz()+[e+]->Pz()+[g]->Pz()+[n]->Pz(),[e-]->E()+[e+]->E()+[g]->E()+[n]->E());");
  Reac->Do("pipindet = 0; if [e-]->Theta()*57.296>15 && [e-]->Theta()*57.296<85 && [e-]->P()>0.10; pipindet = 1;"); // e- acc
  Reac->Do("pimindet = 0; if [e+]->Theta()*57.296>15 && [e+]->Theta()*57.296<85 && [e+]->P()>0.10; pimindet = 1;"); // e+ acc
  Reac->Do("accepted = pipindet*pimindet;");

  Reac->Do(histo_Mmiss,"if accepted && q1->M()>0.12; _x = q3->M()");  // fill missing mass histogram
  Reac->Do(histo_CMS," _x = q2->M();");  // fill total CMS
  Reac->Do(histo_inv," _x = q1->M();");  // fill inv. mass


  Reac->Print();
  Reac->loop(nEvt);  // Number of events

  //   histo_Mmiss->Draw();
  histo_CMS->Draw();

  // save histogram
  TFile *out = new TFile("pim_Nb93_eta.root","update");
  histo_Mmiss->Write();
  histo_CMS->Write();
  histo_inv->Write();
  out->Close();

}
