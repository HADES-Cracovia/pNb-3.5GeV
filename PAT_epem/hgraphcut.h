#ifndef HGRAPHCUT_H
#define HGRAPHCUT_H

#include <TROOT.h>
#include <TFile.h>
#include <TH1.h>
#include <TF1.h>
#include <iostream>
#include <list>
#include <functional>
#include <algorithm>
#include <map>
#include <vector>
#include <TVector3.h>
#include <TLorentzVector.h>
#include "hhypcandidate.h"
#include "hcut.h"


// ****************************************************************************
class HGraphCut : public HCut
{
public:

HGraphCut(const char* cutname, const char* filename=0, const char* opt="read") : HCut(cutname, filename, opt),
          p_cut(0), d_cut(0), ep_cut(0), em_cut(0), pip_cut(0), pim_cut(0) 
		 {
		    p_cut = getCut("p_cut");
            if (p_cut) std::cout << "p_cut has been read" << std::endl;
		    d_cut = getCut("d_cut");
            if (d_cut) std::cout << "d_cut has been read" << std::endl;
		    ep_cut = getCut("ep_cut");
            if (ep_cut) std::cout << "ep_cut has been read" << std::endl;
		    em_cut = getCut("em_cut");
            if (em_cut) std::cout << "em_cut has been read" << std::endl;
		    pip_cut = getCut("pip_cut");
            // **************** TEMPORARY 
            //pip_cut = getCut("p_cut"); // reverse cut
            // ****************************
            if (pip_cut) std::cout << "pip_cut has been read" << std::endl;
		    pim_cut = getCut("pim_cut");
            if (pim_cut) std::cout << "pim_cut has been read" << std::endl;

            showerF = new TF1("showerF","-19.551 + 0.0882075*x -2.00111e-5*x*x + 5.39299e-9*x*x*x",0,3000);
		 }
virtual ~HGraphCut() {
   delete showerF;
}

Bool_t select(HReconstructor& rec);

private:

void graphCut(HHypCandidate *pHyp);
bool graphCut(HParticle *pPart);

  int id;
  double mom, beta;
  TCutG *p_cut;
  TCutG *d_cut;
  TCutG *ep_cut;
  TCutG *em_cut;
  TCutG *pip_cut;
  TCutG *pim_cut;

  TF1* showerF;
  Bool_t isGoodShower(TF1* shwF, size_t system, double mom, double sum0, double sum1, double sum2);

  TCutG *cutRICH;


ClassDef(HGraphCut, 0)
};
// ****************************************************************************

#endif // HGRAPHCUT_H

