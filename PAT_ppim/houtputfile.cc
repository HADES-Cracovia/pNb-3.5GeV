#include <iostream>
#include <string>
#include <TError.h>
#include "houtputfile.h"


// ****************************************************************************
ClassImp(HOutputFile)


//-----------------------------------------------------------------------------
HOutputFile::HOutputFile(const char* name, const char* opt) : HFile() 
{
   if (0 != name)
   {
      open(name, opt);
   }
}


//-----------------------------------------------------------------------------
HOutputFile::~HOutputFile()
{
}


//-----------------------------------------------------------------------------
Bool_t HOutputFile::open(const char* name, const char* opt)
{
   std::string tmp_name(name);
   if (tmp_name.find(".root") != std::string::npos)
    {
	add( name, opt );
	if ( kFALSE == isOutput() )
	{
	   std::cerr << "Output file name not opened in write mode." << std::endl;
	   return kFALSE;
	}
	std::cout << "Output root file opened: " << name << std::endl;
    }
    else 
    {
	std::cerr << "No valid output file name (no .root extension)." << std::endl;
        return kFALSE;
    }
return kTRUE;
}


//-----------------------------------------------------------------------------
Int_t HOutputFile::write()
{
   if ( isOutput() )
   {
      return fileArr.front()->Write();
   }

return 0;
}

//-----------------------------------------------------------------------------
Bool_t HOutputFile::close(const char*)
{
   if ( isOutput() )
   {
      fileArr.front()->Close();
      std::for_each( fileArr.begin(), fileArr.end(), DelFileObj() );
      fileArr.clear();
   }

return kTRUE;
}


//-----------------------------------------------------------------------------
Bool_t HOutputFile::isOutput() const
{
   if ( fileArr.size() > 0 && std::string( fileArr.front()->GetOption() ) == "CREATE" )
   {
      return kTRUE;
   }

return kFALSE;
}

//-----------------------------------------------------------------------------
TFile* HOutputFile::getOutput() const
{
   if ( isOutput() )
   {
      fileArr.front()->cd();
      return fileArr.front();
   }

return 0;
}


