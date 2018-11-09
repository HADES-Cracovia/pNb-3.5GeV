#ifndef HTRACKCUT_H
#define HTRACKCUT_H

#include <TROOT.h>
#include <TFile.h>
#include <TH1.h>
#include <list>
#include <functional>
#include <algorithm>
#include "hcut.h"
#include "hparticlecand.h"


// ****************************************************************************
class HTrackCut : public HCut
{
public:

HTrackCut(const char* cutname, const char* filename=0, const char* opt="read") : HCut(cutname, filename, opt) {}
virtual ~HTrackCut() {}

Bool_t select(HReconstructor& rec);

private:

Double_t getValue(double p1, double p2, double p3, double p4, double p5, double x);
Double_t getXtheta(Short_t pid, Short_t system, Short_t sector, Float_t mom);
Double_t getYphi(Short_t pid, Short_t system, Short_t sector, Float_t mom);
Bool_t isInside(Double_t x1, Double_t y1, Short_t pid, Short_t system, Short_t sector, Float_t mom);

ClassDef(HTrackCut, 0)
};
// ****************************************************************************

#endif // HTRACKCUT_H

