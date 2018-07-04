#ifndef HTIMECUT_H
#define HTIMECUT_H

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
class HTimeCut : public HCut
{
public:

HTimeCut(const char* cutname, const char* filename=0, const char* opt="read") : HCut(cutname, filename, opt),  
                                            C(299792458), R2D(57.2957795130823229), D2R(1.74532925199432955e-02) {}
virtual ~HTimeCut() {}

Bool_t select(HReconstructor& rec);

private:

void calcTofMom(HHypCandidate *pHyp);
void calcTofMom (HParticle *pPart);
void calcTof(HHypCandidate *pHyp);

  const double C, R2D, D2R;
  double id, mom, theta, phi, tof, beta, q, track_length;
  TVector3 vect;
  TLorentzVector part;

  std::vector<double> delta_chi2;
  std::vector<double> sort_idx;
  std::vector< std::vector<double> > tof_new_arr;
  std::map< int, std::multimap<double, int> > best_cand;
  std::map< int, std::multimap<double, int> >::iterator best_cand_iter;
  std::multimap<double, int> cand;
  std::multimap<double, int>::iterator cand_iter;
  int size;
  int best_index, sort_index;
  double best_chi2;
  double delta_tof, tof_mean;
  HParticle *p1;
  HParticle *p2;

ClassDef(HTimeCut, 0)
};
// ****************************************************************************

#endif // HTIMECUT_H

