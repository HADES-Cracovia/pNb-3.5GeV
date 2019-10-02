//#include <TROOT.h>
//#include "createHistos.h"
//#include "TLimit_test.C"

int run_scripts()
{
  gROOT->ProcessLine(".L createHistos.C++");
  createHistos l;
  l.Loop();
  gROOT->ProcessLine(".x TLimit_test.C");
  return 0;
}
