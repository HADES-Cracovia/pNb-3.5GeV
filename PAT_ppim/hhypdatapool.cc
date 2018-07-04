#include "hades.h"
#include "hevent.h"
#include "heventheader.h"
#include "hhypdatapool.h"
#include <algorithm>
#include <iostream>


// ****************************************************************************
ClassImp(HHypDataPool)

//-----------------------------------------------------------------------------
HHypDataPool::HHypDataPool() 
{
}

//-----------------------------------------------------------------------------
HHypDataPool::~HHypDataPool() 
{ 
}



//-----------------------------------------------------------------------------
void HHypDataPool::addHypCand(std::string name, HHypCandidate* ptrC)
{
   hypCand.insert( pair<std::string, HHypCandidate*>( name, ptrC ) );
   ++hypNum[name];
}
   

//-----------------------------------------------------------------------------
std::string HHypDataPool::getName(int n)
{
   int count = n;
   HypNumIter it = hypNum.begin();
   while(count > 0)
   {
      ++it;
      --count;
      if (it == hypNum.end()) return "";
   }

return it->first;
}


//-----------------------------------------------------------------------------
MultiHypIterPair HHypDataPool::equal_range( std::string name )
{  
   return hypCand.equal_range( name );
}

//-----------------------------------------------------------------------------
MultiHypIter HHypDataPool::lower_bound( std::string name )
{
   return hypCand.lower_bound( name );
}  

//-----------------------------------------------------------------------------
MultiHypIter HHypDataPool::upper_bound( std::string name )
{
   return hypCand.upper_bound( name );
}



//-----------------------------------------------------------------------------
HHypCandidate* HHypDataPool::getHyp(std::string name, int n)
{
   if ( getNum(name) == 0 || getNum(name) < n ) return 0;
   MultiHypIter iter = lower_bound( name );
   int count = -1;
   while (++count < n) ++iter;
   return iter->second;
}

//-----------------------------------------------------------------------------
HHypCandidate* HHypDataPool::getHyp(unsigned int n)
{
   if ( hypCand.size() == 0 || hypCand.size() < n+1 ) return 0;
   MultiHypIter iter = hypCand.begin();
   unsigned int count = 0;
   while (count++ < n) ++iter;
   return iter->second;
}


//-----------------------------------------------------------------------------
void HHypDataPool::dump() {
   std::cout << "[DEBUG] HHypPool size: " << hypCand.size() << std::endl;
   std::cout << "[DEBUG] ";
   for (HypNum::iterator i=hypNum.begin(); i!=hypNum.end(); ++i) { std::cout << i->first << "(" << i->second << ")  "; }
   std::cout<<std::endl;
}


