#include "hcut.h"
#include "heditor.h"
#include <TError.h>


// ****************************************************************************
ClassImp(HCut)


//-----------------------------------------------------------------------------
HCut::HCut(const char* cutname, const char* filename, const char* opt) : name(cutname)  
{
   if (0 != filename) {
      open(filename, opt);
   }
}


//-----------------------------------------------------------------------------
HCut::~HCut()
{
   std::for_each( fileArr.begin(), fileArr.end(), DelFileObjCut() );
}


//-----------------------------------------------------------------------------
Bool_t HCut::open(const char* filename, const char* opt)
{
   TFile *tmp = new TFile(filename, opt);

   if (kFALSE == tmp->IsOpen())
   {
      ErrorMsg(WARNING, "HCut::open", 3, "File '", filename, "' not found.");
      return kFALSE;
   }
   fileArr.push_back( tmp );

return kTRUE;
}


//-----------------------------------------------------------------------------
Bool_t HCut::close(const char* filename)
{
   if (0 == filename)
   {
      std::for_each( fileArr.begin(), fileArr.end(), DelFileObjCut() );
   }
   else
   {
      iterFileArr = find_if( fileArr.begin(), fileArr.end(), std::bind2nd( IsFileCut(), filename ) );
      (*iterFileArr)->Close();
      fileArr.erase( iterFileArr );
   }
 return kTRUE;
}


//-----------------------------------------------------------------------------
Bool_t HCut::isOpen(const char* opt) const
{
   return static_cast<Bool_t>( std::count_if( fileArr.begin(), fileArr.end(), std::bind2nd( IsOpenCut(), opt ) ) );
}

//-----------------------------------------------------------------------------
const TH1* HCut::getHist(const char* name) const {
   std::list<TFile*>::const_iterator cIter = find_if( fileArr.begin(), fileArr.end(), std::bind2nd( IsNameCut(), name ) );
   if (cIter == fileArr.end()) {
      return 0;
   }
 return ( dynamic_cast<const TH1*>((*cIter)->Get(name)) );
}


//-----------------------------------------------------------------------------
TCutG* HCut::getCut(const char* name) {
   std::list<TFile*>::iterator cIter = find_if( fileArr.begin(), fileArr.end(), std::bind2nd( IsNameCut(), name ) );
   if (cIter == fileArr.end()) {
      return 0;
   }
 return ( dynamic_cast<TCutG*>((*cIter)->Get(name)) );
}


