#include "houtput.h"

ClassImp(HOutput)


HOutput::HOutput(HOutputFile *ptrF) : ptrFile(ptrF), prefix(), suffix(), isFixed(false)
{
}


HOutput::~HOutput()
{
   write();
}


void HOutput::write()
{
   if (ptrFile && isFixed==true)
   {
      ptrFile->getOutput()->cd();
      ptrNtuple->Write();
   }
}


void HOutput::book(const char* name, const char* title, const char* var)
{
    ptrNtuple = new HNtuple(name, title, var);
    ptrNtuple->setFile(ptrFile->getOutput());
    isFixed = true;
}


void HOutput::book(const char* name, const char* title)
{
    ptrNtuple = new HNtuple(name, title);
    ptrNtuple->setFile(ptrFile->getOutput());
}


void HOutput::book(std::string name, std::string title, std::string var)
{
    ptrNtuple = new HNtuple(name.c_str(), title.c_str(), var.c_str());
    ptrNtuple->setFile(ptrFile->getOutput());
    isFixed = true;
}


void HOutput::book(std::string name, std::string title)
{
    ptrNtuple = new HNtuple(name.c_str(), title.c_str());
    ptrNtuple->setFile(ptrFile->getOutput());
}


void HOutput::fill()
{
   ptrNtuple->fill();
   isFixed = true;
}



