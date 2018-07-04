#ifndef HCUT_H
#define HCUT_H

#include <TROOT.h>
#include <TFile.h>
#include <TH1.h>
#include <TCutG.h>
#include <list>
#include <string>
#include <functional>
#include <algorithm>


class HReconstructor;


// ****************************************************************************
class HCut
{
    struct IsOpenCut : std::binary_function<const TFile*, const char*, bool> {
       bool operator()(const TFile* ptrF, const char* opt) const {
          TString tmp(opt);
          tmp.ToUpper();
          return ( tmp == ptrF->GetOption() );
       }
    };

    struct IsNameCut : std::binary_function<TFile*, const char*, bool> {
       bool operator()(TFile* ptrF, const char* name) const {
          return ( 0 != ptrF->Get(name) );
       }
    };

    struct IsFileCut : std::binary_function<const TFile*, const char*, bool> {
       bool operator()(const TFile* ptrF, const char* name) const {
          return ( TString(name) == ptrF->GetName() );
       }
    };

    struct DelFileObjCut {
       void operator()(TFile* ptr) {
          if (TString("READ") != ptr->GetOption()) ptr->Write();
          ptr->Close();
          delete ptr;
       }
    };



public:

HCut(const char* cutname, const char* filename=0, const char* opt="read");
virtual ~HCut();


Bool_t open(const char* filename, const char* opt="read");
Bool_t close(const char* filename = 0);

const char* getName() { return name.c_str(); }

virtual Bool_t select(HReconstructor& rec) = 0;

Bool_t isOpen(const char* opt) const;
const TH1* getHist(const char* name) const;
TCutG* getCut(const char* name);

private:

   std::list<TFile*> fileArr;
   std::list<TFile*>::iterator iterFileArr;

   std::string name;

ClassDef(HCut, 0)
};
// ****************************************************************************

#endif // HCUT_H

