
#include "hcommondef.h"

using namespace CommonDefinitions;

//-----------------------------------------------------------------------------
EParticle CommonDefinitions::convertId(const char* name)
{
   using namespace CommonDefinitions;
   std::string tmp_name(name);
   if (tmp_name == "ep") return ePositron;
   else if (tmp_name == "em") return eElectron;
   else if (tmp_name == "pip") return ePiPlus;
   else if (tmp_name == "pim") return ePiMinus;
   else if (tmp_name == "p") return eProton;
   else if (tmp_name == "d") return eDeuteron;
   else if (tmp_name == "lpos") return eLeptonPos;
   else if (tmp_name == "lneg") return eLeptonNeg;
   else if (tmp_name == "hpos") return eHadronPos;
   else if (tmp_name == "hneg") return eHadronNeg;

return eUnknown;
}



//-----------------------------------------------------------------------------
EParticle CommonDefinitions::convertId(int n)
{
   using namespace CommonDefinitions;
   if (n == 2) return ePositron;
   else if (n == 3) return eElectron;
   else if (n == 8) return ePiPlus;
   else if (n == 9) return ePiMinus;
   else if (n == 14) return eProton;
   else if (n == 45) return eDeuteron;
   else if (n == 102) return eLeptonPos;
   else if (n == 103) return eLeptonNeg;
   else if (n == 104) return eHadronPos;
   else if (n == 105) return eHadronNeg;

return eUnknown;
}


//-----------------------------------------------------------------------------
std::string CommonDefinitions::convertId(CommonDefinitions::EParticle eid)
{
   if (eid == ePositron) return "ep";
   else if (eid == eElectron) return "em";
   else if (eid == ePiPlus) return "pip";
   else if (eid == ePiMinus) return "pim";
   else if (eid == eProton) return "p";
   else if (eid == eDeuteron) return "d";
   else if (eid == eLeptonPos) return "lpos";
   else if (eid == eLeptonNeg) return "lneg";
   else if (eid == eHadronPos) return "hpos";
   else if (eid == eHadronNeg) return "hneg";

return "none";
}


