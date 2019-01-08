#ifndef HFILE_H
#define HFILE_H

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <list>
#include <functional>
#include <algorithm>


// ****************************************************************************
class HFile
{
 protected:

    struct IsName : std::binary_function<TFile*, const char*, bool> {
       bool operator()(TFile* ptrF, const char* name) const {
          return ( 0 != ptrF->Get(name) );
       }
    };

    struct IsFile : std::binary_function<const TFile*, const char*, bool> {
       bool operator()(const TFile* ptrF, const char* name) const {
          return ( TString(name) == ptrF->GetName() );
       }
    };

    struct DelFileObj {
       void operator()(TFile* ptr) {
          ptr->Close();
          delete ptr;
       }
    };


   Bool_t add(const char* name, const char* opt);
   std::list<TFile*> fileArr;
	
 public:

   HFile();
   virtual ~HFile();

   virtual Bool_t open(const char* name, const char* opt = "read") = 0;
   virtual Int_t write() = 0;
   virtual Bool_t close(const char* name = 0);

   virtual Bool_t isOutput() const = 0;
   virtual TFile* getOutput() const = 0;

   TTree* getTree(const char* name, int n = 0) const;
   long getEntries(const char* name, int n = 0) const;
   int size() const;

   virtual const TObject* get(const char* name) const;


ClassDef(HFile, 0)
};
// ****************************************************************************

#endif // HFILE_H


