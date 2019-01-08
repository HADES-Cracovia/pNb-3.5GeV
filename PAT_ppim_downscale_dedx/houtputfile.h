#ifndef HOUTPUTFILE_H
#define HOUTPUTFILE_H

#include <TFile.h>
#include "hfile.h"


// ****************************************************************************
class HOutputFile : public HFile
{
 public:

   HOutputFile(const char* name = 0, const char* opt = 0);
   ~HOutputFile();

   Bool_t open(const char* name, const char* opt);
   Int_t write();
   Bool_t close(const char*);

   Bool_t isOutput() const;
   TFile* getOutput() const;


ClassDef(HOutputFile, 0)
};
// ****************************************************************************

#endif // HOUTPUTFILE_H


