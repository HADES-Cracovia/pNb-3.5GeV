#ifndef HOUTPUT
#define HOUTPUT

#include <string>
#include <vector>
#include "hcommondef.h"
#include "houtputfile.h"
#include "hntuple.h"

using namespace CommonDefinitions;

struct IsName : std::binary_function<HNtuple*, const char*, bool> {
   bool operator()(HNtuple* ptrE, const char* name) const {
      return ( std::string(name) == ptrE->getName() );
   }
};


class HOutput
{
  public:
     HOutput(HOutputFile *ptrF);
     virtual ~HOutput();

     void book(const char* name, const char* title, const char* var);
     void book(const char* name, const char* title);
     void book(std::string name, std::string title, std::string var);
     void book(std::string name, std::string title);

     void setSuffix(const char* suf = 0) { suffix = (suf != 0) ? suf : ""; }
     void setPrefix(const char* pre = 0) { prefix = (pre != 0) ? pre : ""; }
     void setSuffix(std::string suf) { suffix = suf; }
     void setPrefix(std::string pre) { prefix = pre; }

     bool fixed() { return isFixed; }

     void set(std::string name, float val) { keyword = prefix + name + suffix; (*ptrNtuple)[keyword.c_str()] = val; }
     void fill();

  private:

     void write(); // called in destructor
     
     HOutputFile *ptrFile;
     HNtuple* ptrNtuple;

     std::string prefix;
     std::string suffix;
     std::string keyword;

     bool isFixed;

ClassDef(HOutput, 0)  //
};



#endif // HOUTPUT
