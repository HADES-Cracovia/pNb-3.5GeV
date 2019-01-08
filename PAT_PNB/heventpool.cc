#include "heventpool.h"
#include <iostream>
using namespace std;


//-----------------------------------------------------------------------------
void HEventPool::update() 
{
   reset();
   if (pEvent)
   {
      dataIter = pEvent->begin();
	  while ( dataIter != pEvent->end() )
	  {
	     set( dataIter->first, dataIter->second );
		 ++dataIter;
	  }
   }
}


//-----------------------------------------------------------------------------
void HEventPool::reset() 
{
   dataIter = begin();
   while ( dataIter != end() )
   {
       set( dataIter->first, 0. );
	   ++dataIter;
   }
}
