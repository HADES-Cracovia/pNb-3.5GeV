#include "hfile.h"
#include <cassert>
#include <TError.h>


// ****************************************************************************
ClassImp(HFile)


//-----------------------------------------------------------------------------
HFile::HFile()
{
}


//-----------------------------------------------------------------------------
HFile::~HFile()
{
   std::for_each( fileArr.begin(), fileArr.end(), DelFileObj() );
}


//-----------------------------------------------------------------------------
Bool_t HFile::add(const char* name, const char* opt)
{
   TFile *tmp = new TFile(name, opt);

   if (kFALSE == tmp->IsOpen())
   {
      Error("add", "File '%s' not opened.", name);
      return kFALSE;
   }
   fileArr.push_back( tmp );

return kTRUE;
}


//-----------------------------------------------------------------------------
Bool_t HFile::close(const char* name)
{
   if (0 == name) 
   {
      std::for_each( fileArr.begin(), fileArr.end(), DelFileObj() );
      fileArr.clear();
   }
   else
   {
      std::list<TFile*>::iterator iterFileArr = find_if( fileArr.begin(), fileArr.end(), std::bind2nd( IsFile(), name ) );
      (*iterFileArr)->Close();
      fileArr.erase( iterFileArr );
   }
return kTRUE;
}


//-----------------------------------------------------------------------------
const TObject* HFile::get(const char* name) const {
   std::list<TFile*>::const_iterator cIter = find_if( fileArr.begin(), fileArr.end(), std::bind2nd( IsName(), name ) );
   if (cIter == fileArr.end()) {
      return 0;
   }
 return ( dynamic_cast<const TObject*>((*cIter)->Get(name)) );
}


//-----------------------------------------------------------------------------
TTree* HFile::getTree(const char* name, int n) const
{
   assert( n > -1 && n < static_cast<int>(fileArr.size()) );
   std::list<TFile*>::const_iterator iter = fileArr.begin();
   while (n--) ++iter;
   return dynamic_cast<TTree*>( (*iter)->Get(name) );
}

//-----------------------------------------------------------------------------
long HFile::getEntries(const char* name, int n) const
{
   return getTree(name, n)->GetEntries();
}

//-----------------------------------------------------------------------------
int HFile::size() const
{
   return fileArr.size();
}


