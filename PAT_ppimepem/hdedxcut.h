#ifndef HDEDXCUT_H
#define HDEDXCUT_H

#include <TROOT.h>
#include <TFile.h>
#include <TH1.h>
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
class HDedxCut : public HCut
{
public:

HDedxCut(const char* cutname, const char* filename=0, const char* opt="read") : HCut(cutname, filename, opt),
          p_dedx_cut(0), ep_dedx_cut(0), em_dedx_cut(0), pip_dedx_cut(0), pim_dedx_cut(0) 
		 {
		    p_dedx_cut = getCut("p_dedx_cut");
		    ep_dedx_cut = getCut("ep_dedx_cut");
		    em_dedx_cut = getCut("em_dedx_cut");
		    pip_dedx_cut = getCut("pip_dedx_cut");
		    pim_dedx_cut = getCut("pim_dedx_cut");
		 }
virtual ~HDedxCut() {}

Bool_t select(HReconstructor& rec);

private:

void graphCut(HHypCandidate *pHyp);
bool graphCut(HParticle *pPart);

  int id;
  double dedx_in, dedx_out, beta;
  TCutG *p_dedx_cut;
  TCutG *ep_dedx_cut;
  TCutG *em_dedx_cut;
  TCutG *pip_dedx_cut;
  TCutG *pim_dedx_cut;


ClassDef(HDedxCut, 0)
};
// ****************************************************************************

#endif // HDEDXCUT_H

